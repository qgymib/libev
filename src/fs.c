#include "ev.h"
#include "loop.h"
#include "fs.h"
#include "threadpool.h"
#include "allocator.h"
#include "handle.h"
#include "misc.h"
#include <sys/stat.h>
#include <assert.h>

#if !defined(S_ISDIR) && defined(S_IFMT) && defined(S_IFDIR)
#   define S_ISDIR(m) (((m) & S_IFMT) == S_IFDIR)
#endif

typedef struct ev_dirent_record_s
{
    ev_list_node_t      node;   /**< List node */
    ev_dirent_t         data;   /**< Dirent info */
} ev_dirent_record_t;

typedef struct fs_readdir_helper
{
    ev_fs_req_t*        req;    /**< File system request */
    ssize_t             cnt;    /**< Dirent counter */
} fs_readdir_helper_t;

typedef struct fs_remove_helper
{
	const char*         parent_path;
	int                 ret;
} fs_remove_helper_t;

static void _ev_fs_erase_req(ev_file_t* file, ev_fs_req_t* req)
{
    ev_list_erase(&file->work_queue, &req->node);
}

static void _ev_fs_cleanup_req_as_open(ev_fs_req_t* token)
{
    if (token->req.as_open.path != NULL)
    {
        ev__free(token->req.as_open.path);
        token->req.as_open.path = NULL;
    }
}

static void _ev_fs_cleanup_req_as_seek(ev_fs_req_t* req)
{
	(void)req;
}

static void _ev_fs_cleanup_req_as_read(ev_fs_req_t* req)
{
    ev__read_exit(&req->req.as_read.read_req);
}

static void _ev_fs_cleanup_req_as_write(ev_fs_req_t* req)
{
    ev__write_exit(&req->req.as_write.write_req);
}

static void _ev_fs_cleanup_req_as_fstat(ev_fs_req_t* req)
{
    (void)req;
}

static void _ev_fs_cleanup_req_as_readdir(ev_fs_req_t* req)
{
    ev_list_node_t* it;
    while ((it = ev_list_pop_front(&req->rsp.dirents)) != NULL)
    {
        ev_dirent_record_t* rec = EV_CONTAINER_OF(it, ev_dirent_record_t, node);
        ev__free((char*)rec->data.name);
        ev__free(rec);
    }

    if (req->req.as_readdir.path != NULL)
    {
        ev__free(req->req.as_readdir.path);
        req->req.as_readdir.path = NULL;
    }
}

static void _ev_fs_cleanup_req_as_readfile(ev_fs_req_t* req)
{
    if (req->req.as_readfile.path != NULL)
    {
        ev__free(req->req.as_readfile.path);
        req->req.as_readfile.path = NULL;
    }

    if (req->rsp.filecontent.data != NULL)
    {
        ev__free(req->rsp.filecontent.data);
        req->rsp.filecontent.data = NULL;
    }
    req->rsp.filecontent.size = 0;
}

static void _ev_fs_cleanup_req_as_mkdir(ev_fs_req_t* req)
{
    if (req->req.as_mkdir.path != NULL)
    {
        ev__free(req->req.as_mkdir.path);
        req->req.as_mkdir.path = NULL;
    }
}

static void _ev_fs_cleanup_req_as_remove(ev_fs_req_t* req)
{
    if (req->req.as_remove.path != NULL)
    {
        ev__free(req->req.as_remove.path);
        req->req.as_remove.path = NULL;
    }
}

static void _ev_fs_init_req(ev_fs_req_t* req, ev_file_t* file, ev_file_cb cb, ev_fs_req_type_t type)
{
    req->req_type = type;
    req->cb = cb;
    req->file = file;
    req->result = EV_EINPROGRESS;

    if (file != NULL)
    {
        ev_list_push_back(&file->work_queue, &req->node);
    }
}

static int _ev_fs_init_req_as_open(ev_fs_req_t* token, ev_file_t* file,
    const char* path, int flags, int mode, ev_file_cb cb)
{
    _ev_fs_init_req(token, file, cb, EV_FS_REQ_OPEN);

    if ((token->req.as_open.path = ev__strdup(path)) == NULL)
    {
        return EV_ENOMEM;
    }

    token->req.as_open.flags = flags;
    token->req.as_open.mode = mode;

    return EV_SUCCESS;
}

static int _ev_fs_init_req_as_seek(ev_fs_req_t* token, ev_file_t* file,
    int whence, ssize_t offset, ev_file_cb cb)
{
    _ev_fs_init_req(token, file, cb, EV_FS_REQ_SEEK);

    token->req.as_seek.whence = whence;
    token->req.as_seek.offset = offset;

    return EV_SUCCESS;
}

static int _ev_fs_init_req_as_read(ev_fs_req_t* req, ev_file_t* file,
    ev_buf_t bufs[], size_t nbuf, ssize_t offset, ev_file_cb cb)
{
    _ev_fs_init_req(req, file, cb, EV_FS_REQ_READ);

    int ret = ev__read_init(&req->req.as_read.read_req, bufs, nbuf);
    if (ret != EV_SUCCESS)
    {
        return ret;
    }
    req->req.as_read.offset = offset;

    return EV_SUCCESS;
}

static int _ev_fs_init_req_as_write(ev_fs_req_t* token, ev_file_t* file,
    ev_buf_t bufs[], size_t nbuf, ssize_t offset, ev_file_cb cb)
{
    _ev_fs_init_req(token, file, cb, EV_FS_REQ_WRITE);

    int ret = ev__write_init(&token->req.as_write.write_req, bufs, nbuf);
    if (ret != EV_SUCCESS)
    {
        return ret;
    }
    token->req.as_write.offset = offset;

    return EV_SUCCESS;
}

static void _ev_fs_init_req_as_fstat(ev_fs_req_t* req, ev_file_t* file, ev_file_cb cb)
{
    _ev_fs_init_req(req, file, cb, EV_FS_REQ_FSTAT);
}

static int _ev_fs_init_req_as_readdir(ev_fs_req_t* req, const char* path, ev_file_cb cb)
{
    _ev_fs_init_req(req, NULL, cb, EV_FS_REQ_READDIR);
    req->req.as_readdir.path = ev__strdup(path);
    if (req->req.as_readdir.path == NULL)
    {
        return EV_ENOMEM;
    }

    ev_list_init(&req->rsp.dirents);

    return EV_SUCCESS;
}

static int _ev_fs_init_req_as_readfile(ev_fs_req_t* req, const char* path,
    ev_file_cb cb)
{
    _ev_fs_init_req(req, NULL, cb, EV_FS_REQ_READFILE);

    req->req.as_readfile.path = ev__strdup(path);
    if (req->req.as_readfile.path == NULL)
    {
        return EV_ENOMEM;
    }

    req->rsp.filecontent = ev_buf_make(NULL, 0);

    return EV_SUCCESS;
}

static int _ev_fs_init_req_as_mkdir(ev_fs_req_t* req, const char* path, int mode,
    ev_file_cb cb)
{
    _ev_fs_init_req(req, NULL, cb, EV_FS_REQ_MKDIR);

    req->req.as_mkdir.path = ev__strdup(path);
    if (req->req.as_mkdir.path == NULL)
    {
        return EV_ENOMEM;
    }
    req->req.as_mkdir.mode = mode;

    return EV_SUCCESS;
}

static int _ev_fs_init_req_as_remove(ev_fs_req_t* req, const char* path, int recursion, ev_file_cb cb)
{
    _ev_fs_init_req(req, NULL, cb, EV_FS_REQ_REMOVE);

    req->req.as_remove.path = ev__strdup(path);
    if (req->req.as_remove.path == NULL)
    {
        return EV_ENOMEM;
    }
    req->req.as_remove.recursion = recursion;

    return EV_SUCCESS;
}

/**
 * @brief Check if \p file have pending task.
 * @return  bool
 */
static int _ev_file_have_pending(ev_file_t* file)
{
    return ev_list_size(&file->work_queue) != 0;
}

static void _ev_file_do_close_callback(ev_file_t* file)
{
    if (file->close_cb != NULL)
    {
        file->close_cb(file);
    }
}

static void _ev_file_do_close_callback_if_necessary(ev_file_t* file)
{
    if (file == NULL)
    {
        return;
    }
    if (file->close_cb != NULL && !_ev_file_have_pending(file))
    {
        _ev_file_do_close_callback(file);
    }
}

static void _ev_file_on_close(ev_handle_t* handle)
{
    ev_file_t* file = EV_CONTAINER_OF(handle, ev_file_t, base);
    _ev_file_do_close_callback(file);
}

static void _ev_file_cancel_all_pending_task(ev_file_t* file, size_t* failure_count)
{
    *failure_count = 0;

    ev_list_node_t* it = ev_list_begin(&file->work_queue);
    for (; it != NULL; it = ev_list_next(it))
    {
        ev_fs_req_t* req = EV_CONTAINER_OF(it, ev_fs_req_t, node);
        if (ev_loop_cancel(&req->work_token) != EV_SUCCESS)
        {
            *failure_count += 1;
        }
    }
}

static int _ev_fs_on_readdir_entry(ev_dirent_t* info, void* arg)
{
    fs_readdir_helper_t* helper = arg;

    ev_dirent_record_t* rec = ev__malloc(sizeof(ev_dirent_record_t));
    if (rec == NULL)
    {
        goto err_nomem;
    }

    rec->data.type = info->type;
    rec->data.name = ev__strdup(info->name);
    if (rec->data.name == NULL)
    {
        goto err_nomem;
    }

    ev_list_push_back(&helper->req->rsp.dirents, &rec->node);
    helper->cnt++;

    return 0;

err_nomem:
    if (rec != NULL)
    {
        ev__free(rec);
    }
    helper->req->result = EV_ENOMEM;
    return -1;
}

static void _ev_fs_on_done(ev_work_t* work, int status)
{
    ev_fs_req_t* req = EV_CONTAINER_OF(work, ev_fs_req_t, work_token);
    ev_file_t* file = req->file;

    if (status == EV_ECANCELED)
    {
        assert(req->result == EV_SUCCESS);
        req->result = EV_ECANCELED;
    }

    if (file != NULL)
    {
        ev__handle_event_dec(&file->base);
        _ev_fs_erase_req(file, req);
    }
    req->cb(req);

    /**
     * As describe in #ev_file_exit(), we have to check close status.
     */
    _ev_file_do_close_callback_if_necessary(file);
}

static void _ev_file_on_open(ev_work_t* work)
{
    ev_fs_req_t* req = EV_CONTAINER_OF(work, ev_fs_req_t, work_token);
    ev_file_t* file = req->file;

    req->result = ev_file_open_sync(file, req->req.as_open.path,
        req->req.as_open.flags, req->req.as_open.mode);
}

static void _ev_file_on_read(ev_work_t* work)
{
	ev_fs_req_t* req = EV_CONTAINER_OF(work, ev_fs_req_t, work_token);
	ev_file_t* file = req->file;
	ev_read_t* read_req = &req->req.as_read.read_req;

    req->result = ev_file_read_sync(file, read_req->data.bufs,
        read_req->data.nbuf);
}

static void _ev_file_on_pread(ev_work_t* work)
{
    ev_fs_req_t* req = EV_CONTAINER_OF(work, ev_fs_req_t, work_token);
    ev_file_t* file = req->file;
    ev_read_t* read_req = &req->req.as_read.read_req;

    req->result = ev_file_pread_sync(file, read_req->data.bufs,
        read_req->data.nbuf, req->req.as_read.offset);
}

static void _ev_file_on_write(ev_work_t* work)
{
	ev_fs_req_t* req = EV_CONTAINER_OF(work, ev_fs_req_t, work_token);
	ev_file_t* file = req->file;
	ev_write_t* write_req = &req->req.as_write.write_req;

	req->result = ev_file_write_sync(file, write_req->bufs,
		write_req->nbuf);
}

static void _ev_file_on_pwrite(ev_work_t* work)
{
    ev_fs_req_t* req = EV_CONTAINER_OF(work, ev_fs_req_t, work_token);
    ev_file_t* file = req->file;
    ev_write_t* write_req = &req->req.as_write.write_req;

    req->result = ev_file_pwrite_sync(file, write_req->bufs,
        write_req->nbuf, req->req.as_write.offset);
}

static void _ev_file_on_fstat(ev_work_t* work)
{
    ev_fs_req_t* req = EV_CONTAINER_OF(work, ev_fs_req_t, work_token);
    ev_file_t* file = req->file;

    req->result = ev_file_stat_sync(file, &req->rsp.fileinfo);
}

static void _ev_fs_on_readdir(ev_work_t* work)
{
    ev_fs_req_t* req = EV_CONTAINER_OF(work, ev_fs_req_t, work_token);

    fs_readdir_helper_t helper = { req, 0 };
    req->result = ev__fs_readdir(req->req.as_readdir.path,
        _ev_fs_on_readdir_entry, &helper);

    /* If operation success, replace result with dirent counter */
    if (req->result == EV_SUCCESS)
    {
        req->result = helper.cnt;
    }
}

static void _ev_fs_on_readfile(ev_work_t* work)
{
    ev_fs_req_t* req = EV_CONTAINER_OF(work, ev_fs_req_t, work_token);
    const char* path = req->req.as_readfile.path;

    ev_os_file_t file = EV_OS_FILE_INVALID;
    req->result = ev__fs_open(&file, path, EV_FS_O_RDONLY, 0);
    if (req->result != EV_SUCCESS)
    {
        return;
    }

    ev_fs_stat_t statbuf = EV_FS_STAT_INVALID;
    req->result = ev__fs_fstat(file, &statbuf);
    if (req->result != EV_SUCCESS)
    {
        goto close_file;
    }

    void* data = ev__malloc(statbuf.st_size);
    req->rsp.filecontent = ev_buf_make(data, statbuf.st_size);

    if (req->rsp.filecontent.data == NULL)
    {
        req->result = EV_ENOMEM;
        goto close_file;
    }

    req->result = ev__fs_preadv(file, &req->rsp.filecontent, 1, 0);

close_file:
    ev__fs_close(file);
}

static void _ev_fs_on_mkdir(ev_work_t* work)
{
    ev_fs_req_t* req = EV_CONTAINER_OF(work, ev_fs_req_t, work_token);
    const char* path = req->req.as_mkdir.path;
    int mode = req->req.as_mkdir.mode;

    req->result = ev_fs_mkdir_sync(path, mode);
}

static void _ev_fs_on_remove(ev_work_t* work)
{
    ev_fs_req_t* req = EV_CONTAINER_OF(work, ev_fs_req_t, work_token);
    const char* path = req->req.as_remove.path;

    req->result = ev_fs_remove_sync(path, req->req.as_remove.recursion);
}

static int _ev_file_read_template(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
	size_t nbuf, ssize_t offset, ev_file_cb cb, ev_work_cb work_cb)
{
	ev_loop_t* loop = file->base.loop;

	int ret = _ev_fs_init_req_as_read(req, file, bufs, nbuf, offset, cb);
	if (ret != EV_SUCCESS)
	{
		return ret;
	}

	ev__handle_event_add(&file->base);

	ret = ev__loop_submit_threadpool(loop, &req->work_token,
		EV_THREADPOOL_WORK_IO_FAST, work_cb, _ev_fs_on_done);
	if (ret != EV_SUCCESS)
	{
		_ev_fs_cleanup_req_as_read(req);
		ev__handle_event_dec(&file->base);
		return ret;
	}

	return EV_SUCCESS;
}

static int _ev_file_pwrite_template(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
	size_t nbuf, ssize_t offset, ev_file_cb cb, ev_work_cb work_cb)
{
	int ret;
	ev_loop_t* loop = file->base.loop;

	ret = _ev_fs_init_req_as_write(req, file, bufs, nbuf, offset, cb);
	if (ret != EV_SUCCESS)
	{
		return ret;
	}

	ev__handle_event_add(&file->base);

	ret = ev__loop_submit_threadpool(loop, &req->work_token,
		EV_THREADPOOL_WORK_IO_FAST, work_cb, _ev_fs_on_done);
	if (ret != EV_SUCCESS)
	{
		_ev_fs_cleanup_req_as_write(req);
		ev__handle_event_dec(&file->base);
		return ret;
	}

	return EV_SUCCESS;
}

static void _ev_fs_on_seek(ev_work_t* work)
{
	ev_fs_req_t* req = EV_CONTAINER_OF(work, ev_fs_req_t, work_token);
	ev_file_t* file = req->file;

	req->result = ev__fs_seek(file->file, req->req.as_seek.whence, req->req.as_seek.offset);
}

static int _ev_fs_remove(const char* path)
{
	int errcode;
	if (remove(path) != 0)
	{
		errcode = errno;
		return ev__translate_sys_error(errcode);
	}
	return 0;
}

static  int _ev_fs_remove_helper(ev_dirent_t* info, void* arg)
{
	fs_remove_helper_t* helper = arg;
	const char* parent_path = helper->parent_path;
	size_t parent_path_sz = strlen(parent_path);
	size_t name_sz = strlen(info->name);
	size_t full_path_sz = parent_path_sz + 1 + name_sz;

	char* full_path = ev__malloc(full_path_sz + 1);
	snprintf(full_path, full_path_sz + 1, "%s/%s", parent_path, info->name);

	helper->ret = ev__fs_remove(full_path, 1);
	ev__free(full_path);

	return helper->ret;
}

int ev_file_init(ev_loop_t* loop, ev_file_t* file)
{
    if (loop->threadpool.pool == NULL)
    {
        return EV_ENOTHREADPOOL;
    }

    file->file = EV_OS_FILE_INVALID;
    file->close_cb = NULL;
    ev__handle_init(loop, &file->base, EV_ROLE_EV_FILE);
    ev_list_init(&file->work_queue);

    return EV_SUCCESS;
}

void ev_file_exit(ev_file_t* file, ev_file_close_cb cb)
{
    size_t failure_count;

    /**
     * Cancel all pending task. Do note that some tasks might be cancel failed
     * as they are currently executing.
     */
    _ev_file_cancel_all_pending_task(file, &failure_count);

    /**
     * It should be safe to close handle, event there are some works in
     * progress.
     */
    if (file->file != EV_OS_FILE_INVALID)
    {
        ev__fs_close(file->file);
        file->file = EV_OS_FILE_INVALID;
    }

    file->close_cb = cb;

    /**
     * If all pending task was cancel, it is safe to close handle, because they
     * are in the backlog queue.
     */
    if (failure_count == 0)
    {
        ev__handle_exit(&file->base, _ev_file_on_close);
        return;
    }

    /**
     * Now we have some problem, because some task is executing.
     *
     * We cannot close handle directly as these tasks will surely callback after
     * this handle closed.
     *
     * So we have to check close status in file operations callback. Once no
     * pending tasks, we can close this handle.
     */
}

int ev_file_open(ev_file_t* file, ev_fs_req_t* token, const char* path,
    int flags, int mode, ev_file_cb cb)
{
    ev_loop_t* loop = file->base.loop;

    int ret = _ev_fs_init_req_as_open(token, file, path, flags, mode, cb);
    if (ret != EV_SUCCESS)
    {
        return ret;
    }

    ev__handle_event_add(&file->base);

    ret = ev__loop_submit_threadpool(loop, &token->work_token,
        EV_THREADPOOL_WORK_IO_FAST, _ev_file_on_open, _ev_fs_on_done);
    if (ret != EV_SUCCESS)
    {
        _ev_fs_cleanup_req_as_open(token);
        ev__handle_event_dec(&file->base);
        return ret;
    }

    return EV_SUCCESS;
}

int ev_file_open_sync(ev_file_t* file, const char* path, int flags, int mode)
{
    return ev__fs_open(&file->file, path, flags, mode);
}

int ev_file_seek(ev_file_t* file, ev_fs_req_t* req, int whence, ssize_t offset, ev_file_cb cb)
{
    int ret;
	ev_loop_t* loop = file->base.loop;
    _ev_fs_init_req_as_seek(req, file, whence, offset, cb);

    ev__handle_event_add(&file->base);

    ret = ev__loop_submit_threadpool(loop, &req->work_token,
        EV_THREADPOOL_WORK_IO_FAST, _ev_fs_on_seek, _ev_fs_on_done);
	if (ret != EV_SUCCESS)
	{
		ev__handle_event_dec(&file->base);
		return ret;
	}

    return EV_SUCCESS;
}

int ev_file_read(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
    size_t nbuf, ev_file_cb cb)
{
    return _ev_file_read_template(file, req, bufs, nbuf, 0, cb, _ev_file_on_read);
}

ssize_t ev_file_read_sync(ev_file_t* file, ev_buf_t bufs[], size_t nbuf)
{
    return ev__fs_readv(file->file, bufs, nbuf);
}

int ev_file_pread(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
    size_t nbuf, ssize_t offset, ev_file_cb cb)
{
    return _ev_file_read_template(file, req, bufs, nbuf, offset, cb, _ev_file_on_pread);
}

ssize_t ev_file_pread_sync(ev_file_t* file, ev_buf_t bufs[], size_t nbuf,
    ssize_t offset)
{
    return ev__fs_preadv(file->file, bufs, nbuf, offset);
}

int ev_file_write(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
	size_t nbuf, ev_file_cb cb)
{
	return _ev_file_pwrite_template(file, req, bufs, nbuf, 0, cb, _ev_file_on_write);
}

ssize_t ev_file_write_sync(ev_file_t* file, ev_buf_t bufs[], size_t nbuf)
{
    return ev__fs_writev(file->file, bufs, nbuf);
}

int ev_file_pwrite(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
    size_t nbuf, ssize_t offset, ev_file_cb cb)
{
    return _ev_file_pwrite_template(file, req, bufs, nbuf, offset, cb, _ev_file_on_pwrite);
}

ssize_t ev_file_pwrite_sync(ev_file_t* file, ev_buf_t bufs[], size_t nbuf,
    ssize_t offset)
{
    return ev__fs_pwritev(file->file, bufs, nbuf, offset);
}

int ev_file_stat(ev_file_t* file, ev_fs_req_t* req, ev_file_cb cb)
{
    int ret;
    ev_loop_t* loop = file->base.loop;

    _ev_fs_init_req_as_fstat(req, file, cb);
    ev__handle_event_add(&file->base);

    ret = ev__loop_submit_threadpool(loop, &req->work_token, EV_THREADPOOL_WORK_IO_FAST,
        _ev_file_on_fstat, _ev_fs_on_done);
    if (ret != EV_SUCCESS)
    {
        _ev_fs_cleanup_req_as_fstat(req);
        ev__handle_event_dec(&file->base);
        return ret;
    }

    return EV_SUCCESS;
}

int ev_file_stat_sync(ev_file_t* file, ev_fs_stat_t* stat)
{
    return ev__fs_fstat(file->file, stat);
}

int ev_fs_readdir(ev_loop_t* loop, ev_fs_req_t* req, const char* path,
    ev_file_cb callback)
{
    int ret;

    ret = _ev_fs_init_req_as_readdir(req, path, callback);
    if (ret != EV_SUCCESS)
    {
        return ret;
    }

    ret = ev__loop_submit_threadpool(loop, &req->work_token, EV_THREADPOOL_WORK_IO_FAST,
        _ev_fs_on_readdir, _ev_fs_on_done);
    if (ret != EV_SUCCESS)
    {
        _ev_fs_cleanup_req_as_readdir(req);
        return ret;
    }

    return EV_SUCCESS;
}

int ev_fs_readfile(ev_loop_t* loop, ev_fs_req_t* req, const char* path,
    ev_file_cb cb)
{
    int ret;

    ret = _ev_fs_init_req_as_readfile(req, path, cb);
    if (ret != EV_SUCCESS)
    {
        return ret;
    }

    ret = ev__loop_submit_threadpool(loop, &req->work_token, EV_THREADPOOL_WORK_IO_FAST,
        _ev_fs_on_readfile, _ev_fs_on_done);
    if (ret != EV_SUCCESS)
    {
        _ev_fs_cleanup_req_as_readfile(req);
        return ret;
    }

    return EV_SUCCESS;
}

int ev_fs_mkdir(ev_loop_t* loop, ev_fs_req_t* req, const char* path, int mode,
    ev_file_cb cb)
{
    int ret;

    ret = _ev_fs_init_req_as_mkdir(req, path, mode, cb);
    if (ret != EV_SUCCESS)
    {
        return ret;
    }

    ret = ev__loop_submit_threadpool(loop, &req->work_token, EV_THREADPOOL_WORK_IO_FAST,
        _ev_fs_on_mkdir, _ev_fs_on_done);
    if (ret != EV_SUCCESS)
    {
        _ev_fs_cleanup_req_as_mkdir(req);
        return ret;
    }

    return EV_SUCCESS;
}

int ev_fs_mkdir_sync(const char* path, int mode)
{
    return ev__fs_mkdir(path, mode);
}

int ev_fs_remove(ev_loop_t* loop, ev_fs_req_t* req, const char* path, int recursion, ev_file_cb cb)
{
    int ret;

    ret = _ev_fs_init_req_as_remove(req, path, recursion, cb);
    if (ret != EV_SUCCESS)
    {
        return ret;
    }

    ret = ev__loop_submit_threadpool(loop, &req->work_token, EV_THREADPOOL_WORK_IO_FAST,
        _ev_fs_on_remove, _ev_fs_on_done);
    if (ret != EV_SUCCESS)
    {
        _ev_fs_cleanup_req_as_remove(req);
        return ret;
    }

    return EV_SUCCESS;
}

int ev_fs_remove_sync(const char* path, int recursion)
{
    return ev__fs_remove(path, recursion);
}

ev_fs_stat_t* ev_fs_get_statbuf(ev_fs_req_t* req)
{
    return &req->rsp.fileinfo;
}

void ev_fs_req_cleanup(ev_fs_req_t* req)
{
    switch (req->req_type)
    {
    case EV_FS_REQ_OPEN:
        _ev_fs_cleanup_req_as_open(req);
        break;

    case EV_FS_REQ_SEEK:
        _ev_fs_cleanup_req_as_seek(req);
        break;

    case EV_FS_REQ_READ:
        _ev_fs_cleanup_req_as_read(req);
        break;

    case EV_FS_REQ_WRITE:
        _ev_fs_cleanup_req_as_write(req);
        break;

    case EV_FS_REQ_FSTAT:
        _ev_fs_cleanup_req_as_fstat(req);
        break;

    case EV_FS_REQ_READDIR:
        _ev_fs_cleanup_req_as_readdir(req);
        break;

    case EV_FS_REQ_READFILE:
        _ev_fs_cleanup_req_as_readfile(req);
        break;

    case EV_FS_REQ_MKDIR:
        _ev_fs_cleanup_req_as_mkdir(req);
        break;

    default:
        EV_ABORT("req:%d", req->req_type);
    }
}

ev_file_t* ev_fs_get_file(ev_fs_req_t* req)
{
    return req->file;
}

ev_dirent_t* ev_fs_get_first_dirent(ev_fs_req_t* req)
{
    ev_list_node_t* it = ev_list_begin(&req->rsp.dirents);
    if (it == NULL)
    {
        return NULL;
    }

    ev_dirent_record_t* rec = EV_CONTAINER_OF(it, ev_dirent_record_t, node);
    return &rec->data;
}

ev_dirent_t* ev_fs_get_next_dirent(ev_dirent_t* curr)
{
    if (curr == NULL)
    {
        return NULL;
    }

    ev_dirent_record_t* rec = EV_CONTAINER_OF(curr, ev_dirent_record_t, data);

    ev_list_node_t* next_node = ev_list_next(&rec->node);
    if (next_node == NULL)
    {
        return NULL;
    }

    ev_dirent_record_t* next_rec = EV_CONTAINER_OF(next_node, ev_dirent_record_t, node);
    return &next_rec->data;
}

ev_buf_t* ev_fs_get_filecontent(ev_fs_req_t* req)
{
    return &req->rsp.filecontent;
}

API_LOCAL int ev__fs_remove(const char* path, int recursive)
{
    int ret;

    struct stat buf;
    if (stat(path, &buf) != 0)
    {
        ret = errno;
        return ev__translate_sys_error(ret);
    }

    if (!S_ISDIR(buf.st_mode) || !recursive)
    {
        goto finish;
    }

    fs_remove_helper_t helper;
    helper.parent_path = path;
    helper.ret = 0;

    if ((ret = ev__fs_readdir(path, _ev_fs_remove_helper, &helper)) != 0)
    {
        return helper.ret;
	}

finish:
    return _ev_fs_remove(path);
}
