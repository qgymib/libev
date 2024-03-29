#ifndef __EV_FILE_SYSTEM_H__
#define __EV_FILE_SYSTEM_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_FILESYSTEM File System
 * @{
 */

/**
 * @brief Directory type.
 */
typedef enum ev_dirent_type_e
{
    EV_DIRENT_UNKNOWN,
    EV_DIRENT_FILE,
    EV_DIRENT_DIR,
    EV_DIRENT_LINK,
    EV_DIRENT_FIFO,
    EV_DIRENT_SOCKET,
    EV_DIRENT_CHR,
    EV_DIRENT_BLOCK
} ev_dirent_type_t;

/**
 * @brief File system request type.
 */
enum ev_fs_req_type_e
{
    EV_FS_REQ_UNKNOWN,
    EV_FS_REQ_OPEN,
    EV_FS_REQ_SEEK,
    EV_FS_REQ_READ,
    EV_FS_REQ_WRITE,
    EV_FS_REQ_FSTAT,
    EV_FS_REQ_READDIR,
    EV_FS_REQ_READFILE,
    EV_FS_REQ_MKDIR,
    EV_FS_REQ_REMOVE,
};

/**
 * @brief Typedef of #ev_fs_req_type_e.
 */
typedef enum ev_fs_req_type_e ev_fs_req_type_t;

struct ev_file_s;

/**
 * @brief Typedef of #ev_file_s.
 */
typedef struct ev_file_s ev_file_t;

struct ev_fs_req_s;

/**
 * @brief Typedef of #ev_fs_req_s.
 */
typedef struct ev_fs_req_s ev_fs_req_t;

struct ev_fs_stat_s;

/**
 * @brief Typedef of #ev_fs_stat_s.
 */
typedef struct ev_fs_stat_s ev_fs_stat_t;

struct ev_dirent_s;

/**
 * @brief Typedef of #ev_dirent_s.
 */
typedef struct ev_dirent_s ev_dirent_t;

/**
 * @brief File close callback
 * @param[in] file      File handle
 */
typedef void (*ev_file_close_cb)(ev_file_t* file);

/**
 * @brief File operation callback
 * @note Always call #ev_fs_req_cleanup() to free resource in \p req.
 * @warning Missing call to #ev_fs_req_cleanup() will cause resource leak.
 * @param[in] req       Request token
 */
typedef void (*ev_file_cb)(ev_fs_req_t* req);

/**
 * @brief File type.
 */
struct ev_file_s
{
    ev_handle_t                 base;           /**< Base object */
    ev_os_file_t                file;           /**< File handle */
    ev_file_close_cb            close_cb;       /**< Close callback */
    ev_list_t                   work_queue;     /**< Work queue */
};

/**
 * @brief File status information.
 */
struct ev_fs_stat_s
{
    uint64_t                    st_dev;         /**< ID of device containing file */
    uint64_t                    st_ino;         /**< Inode number */
    uint64_t                    st_mode;        /**< File type and mode */
    uint64_t                    st_nlink;       /**< Number of hard links */
    uint64_t                    st_uid;         /**< User ID of owner */
    uint64_t                    st_gid;         /**< Group ID of owner */
    uint64_t                    st_rdev;        /**< Device ID (if special file) */

    uint64_t                    st_size;        /**< Total size, in bytes */
    uint64_t                    st_blksize;     /**< Block size for filesystem I/O */
    uint64_t                    st_blocks;      /**< Number of 512B blocks allocated */
    uint64_t                    st_flags;       /**< File flags */
    uint64_t                    st_gen;         /**< Generation number of this i-node. */

    ev_timespec_t               st_atim;        /**< Time of last access */
    ev_timespec_t               st_mtim;        /**< Time of last modification */
    ev_timespec_t               st_ctim;        /**< Time of last status change */
    ev_timespec_t               st_birthtim;    /**< Time of file creation */
};
#define EV_FS_STAT_INVALID  \
    {\
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
        EV_TIMESPEC_INVALID,\
        EV_TIMESPEC_INVALID,\
        EV_TIMESPEC_INVALID,\
        EV_TIMESPEC_INVALID,\
    }

/**
 * @brief Directory entry.
 */
struct ev_dirent_s
{
    char*                       name;           /**< Entry name */
    ev_dirent_type_t            type;           /**< Entry type */
};

/**
 * @brief File system request token.
 */
struct ev_fs_req_s
{
    ev_fs_req_type_t            req_type;       /**< Request type */
    ev_list_node_t              node;           /**< Queue node */
    ev_work_t                   work_token;     /**< Thread pool token */
    ev_file_t*                  file;           /**< File handle */
    ev_file_cb                  cb;             /**< File operation callback */
    ssize_t                     result;         /**< Result */

    union
    {
        struct
        {
            char*               path;           /**< File path */
            int                 flags;          /**< File flags */
            int                 mode;           /**< File mode */
        }as_open;

        struct
        {
            int                 whence;         /**< Directive */
            ssize_t             offset;         /**< Offset */
        } as_seek;

        struct
        {
            ssize_t             offset;         /**< File offset */
            ev_read_t           read_req;       /**< Read token */
        }as_read;

        struct
        {
            ssize_t             offset;         /**< File offset */
            ev_write_t          write_req;      /**< Write token */
        }as_write;

        struct
        {
            char*               path;           /**< Directory path */
        }as_readdir;

        struct
        {
            char*               path;           /**< File path */
        }as_readfile;

        struct
        {
            char*               path;           /**< Directory path */
            int                 mode;           /**< The mode for the new directory */
        }as_mkdir;

        struct
        {
            char*               path;           /**< Path */
            int                 recursion;      /**< Recursion delete */
        } as_remove;
    }req;

    union
    {
        ev_fs_stat_t            fileinfo;       /**< File information */
        ev_list_t               dirents;        /**< Dirent list */
        ev_buf_t                filecontent;    /**< File content */
    }rsp;
};

#define EV_FS_REQ_INVALID \
    {\
        EV_FS_REQ_UNKNOWN,\
        EV_LIST_NODE_INIT,\
        EV_WORK_INVALID,\
        NULL,\
        NULL,\
        EV_EINPROGRESS,\
        { { NULL, 0, 0 } },\
        { EV_FS_STAT_INVALID },\
    }

/**
 * @brief Initialize a file handle
 * @param[in] loop      Event loop
 * @param[out] file     File handle
 * @return              #ev_errno_t
 */
EV_API int ev_file_init(ev_loop_t* loop, ev_file_t* file);

/**
 * @brief Destroy a file handle
 * @param[in] file      File handle
 * @param[in] cb        Close callback
 */
EV_API void ev_file_exit(ev_file_t* file, ev_file_close_cb cb);

/**
 * @brief Equivalent to [open(2)](https://man7.org/linux/man-pages/man2/open.2.html).
 * 
 * The full list of \p flags are:
 * + #EV_FS_O_APPEND
 * + #EV_FS_O_CREAT
 * + #EV_FS_O_DSYNC
 * + #EV_FS_O_EXCL
 * + #EV_FS_O_SYNC
 * + #EV_FS_O_TRUNC
 * + #EV_FS_O_RDONLY
 * + #EV_FS_O_WRONLY
 * + #EV_FS_O_RDWR
 * 
 * The full list of \p mode are:
 * + #EV_FS_S_IRUSR
 * + #EV_FS_S_IWUSR
 * + #EV_FS_S_IXUSR
 * + #EV_FS_S_IRWXU
 * 
 * @note File always open in binary mode.
 * @param[in] file      File handle.
 * @param[in] req       File token.
 * @param[in] path      File path.
 * @param[in] flags     Open flags
 * @param[in] mode      Open mode.
 * @param[in] cb        Open result callback.
 * @return              #ev_errno_t
 */
EV_API int ev_file_open(ev_file_t* file, ev_fs_req_t* req, const char* path,
    int flags, int mode, ev_file_cb cb);

/**
 * @brief Like #ev_file_open(), but work in synchronous mode.
 * @see ev_file_open()
 * @param[in] file      File handle.
 * @param[in] path      File path.
 * @param[in] flags     Open flags.
 * @param[in] mode      Open mode.
 * @return              #ev_errno_t
 */
EV_API int ev_file_open_sync(ev_file_t* file, const char* path, int flags,
    int mode);

/**
 * @brief Set the file position indicator for the stream pointed to by \p file.
 * @see #EV_FS_SEEK_BEG
 * @see #EV_FS_SEEK_CUR
 * @see #EV_FS_SEEK_END
 * @param[in] file      File handle.
 * @param[in] req       File operation token.
 * @param[in] whence    Direction.
 * @param[in] offset    Offset.
 * @param[in] cb        Result callback.
 * @return              #ev_errno_t
 */
EV_API int ev_file_seek(ev_file_t* file, ev_fs_req_t* req, int whence,
    ssize_t offset, ev_file_cb cb);

/**
 * @brief Read data.
 * @param[in] file      File handle.
 * @param[in] req       File operation token.
 * @param[in] bufs      Buffer list.
 * @param[in] nbuf      Buffer amount.
 * @param[in] cb        Read callback.
 * @return              #ev_errno_t
 */
EV_API int ev_file_read(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
    size_t nbuf, ev_file_cb cb);

/**
 * @brief Like #ev_file_read(), but work in synchronous mode.
 * @see ev_file_read()
 * @param[in] file      File handle.
 * @param[in] bufs      Buffer list.
 * @param[in] nbuf      Buffer amount.
 * @return              #ev_errno_t
 */
EV_API ssize_t ev_file_read_sync(ev_file_t* file, ev_buf_t bufs[], size_t nbuf);

/**
 * @brief Read position data.
 * @param[in] file      File handle.
 * @param[in] req       File operation token.
 * @param[in] bufs      Buffer list.
 * @param[in] nbuf      Buffer amount.
 * @param[in] offset    Offset of file.
 * @param[in] cb        Read callback.
 * @return              #ev_errno_t
 */
EV_API int ev_file_pread(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
    size_t nbuf, ssize_t offset, ev_file_cb cb);

/**
 * @brief Like #ev_file_pread(), but work in synchronous mode.
 * @see ev_file_pread()
 * @param[in] file      File handle.
 * @param[in] bufs      Buffer list.
 * @param[in] nbuf      Buffer amount.
 * @param[in] offset    Offset of file.
 * @return              #ev_errno_t
 */
EV_API ssize_t ev_file_pread_sync(ev_file_t* file, ev_buf_t bufs[], size_t nbuf,
    ssize_t offset);

/**
 * @brief Write data
 * @param[in] file      File handle.
 * @param[in] req       File operation token.
 * @param[in] bufs      Buffer list.
 * @param[in] nbuf      Buffer amount.
 * @param[in] offset    Offset of file.
 * @param[in] cb        Write callback.
 * @return              #ev_errno_t
 */
EV_API int ev_file_write(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
    size_t nbuf, ev_file_cb cb);

/**
 * @brief Like #ev_file_pwrite(), but work in synchronous mode.
 * @see ev_file_write()
 * @param[in] file      File handle.
 * @param[in] bufs      Buffer list.
 * @param[in] nbuf      Buffer amount.
 * @return              #ev_errno_t
 */
EV_API ssize_t ev_file_write_sync(ev_file_t* file, ev_buf_t bufs[], size_t nbuf);

/**
 * @brief Write position data
 * @param[in] file      File handle.
 * @param[in] req       File operation token.
 * @param[in] bufs      Buffer list.
 * @param[in] nbuf      Buffer amount.
 * @param[in] offset    Offset of file.
 * @param[in] cb        Write callback.
 * @return              #ev_errno_t
 */
EV_API int ev_file_pwrite(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
    size_t nbuf, ssize_t offset, ev_file_cb cb);

/**
 * @brief Like #ev_file_pwrite(), but work in synchronous mode.
 * @see ev_file_pwrite()
 * @param[in] file      File handle.
 * @param[in] bufs      Buffer list.
 * @param[in] nbuf      Buffer amount.
 * @param[in] offset    Offset of file.
 * @return              #ev_errno_t
 */
EV_API ssize_t ev_file_pwrite_sync(ev_file_t* file, ev_buf_t bufs[], size_t nbuf,
    ssize_t offset);

/**
 * @brief Get information about a file.
 * @param[in] file      File handle.
 * @param[in] req       File system request.
 * @param[in] cb        Result callback.
 * @return              #ev_errno_t
 */
EV_API int ev_file_stat(ev_file_t* file, ev_fs_req_t* req, ev_file_cb cb);

/**
 * @brief Like #ev_file_stat(), but work in synchronous mode.
 * @see ev_file_stat()
 * @param[in] file      File handle.
 * @param[out] stat     File status.
 * @return              #ev_errno_t
 */
EV_API int ev_file_stat_sync(ev_file_t* file, ev_fs_stat_t* stat);

/**
 * @brief Get all entry in directory.
 *
 * Use #ev_fs_get_first_dirent() and #ev_fs_get_next_dirent() to traverse all
 * the dirent information.
 *
 * The #ev_fs_req_t::result in \p cb means:
 * | Range | Means                      |
 * | ----- | -------------------------- |
 * | >= 0  | The number of dirent nodes |
 * | < 0   | #ev_errno_t                |
 * 
 * @param[in] loop      Event loop.
 * @param[in] req       File system request
 * @param[in] path      Directory path.
 * @param[in] callback  Result callback.
 * @return              #ev_errno_t
 */
EV_API int ev_fs_readdir(ev_loop_t* loop, ev_fs_req_t* req, const char* path,
    ev_file_cb callback);

/**
 * @brief Read file content.
 *
 * Use #ev_fs_get_filecontent() to get file content.
 *
 * @param[in] loop      Event loop.
 * @param[in] req       File system request.
 * @param[in] path      File path.
 * @param[in] cb        Result callback.
 * @return              #ev_errno_t
 */
EV_API int ev_fs_readfile(ev_loop_t* loop, ev_fs_req_t* req, const char* path,
    ev_file_cb cb);

/**
 * @brief Create the DIRECTORY(ies), if they do not already exist.
 *
 * The full list of \p mode are:
 * + #EV_FS_S_IRUSR
 * + #EV_FS_S_IWUSR
 * + #EV_FS_S_IXUSR
 * + #EV_FS_S_IRWXU
 *
 * @param[in] loop      Event loop.
 * @param[in] req       File system request.
 * @param[in] path      Directory path.
 * @param[in] mode      Creation mode.
 * @param[in] cb        Result callback.
 * @return              #ev_errno_t
 */
EV_API int ev_fs_mkdir(ev_loop_t* loop, ev_fs_req_t* req, const char* path,
    int mode, ev_file_cb cb);

/**
 * @brief Like #ev_fs_mkdir(), but work in synchronous mode.
 * @see ev_fs_mkdir()
 * @param[in] path      Directory path.
 * @param[in] mode      Creation mode.
 * @return              #ev_errno_t
 */
EV_API int ev_fs_mkdir_sync(const char* path, int mode);

/**
 * @brief Delete a name for the file system.
 * @param[in] loop      Event loop.
 * @param[in] req       File system request.
 * @param[in] path      File path.
 * @param[in] cb        Result callback.
 * @return              #ev_errno_t
 */
EV_API int ev_fs_remove(ev_loop_t* loop, ev_fs_req_t* req, const char* path,
    int recursion, ev_file_cb cb);

/**
 * @brief Like #ev_fs_remove(), but work in synchronous mode.
 * @param[in] path      File path.
 * @param[in] recursion Recursion delete if path is a directory.
 * @return              #ev_errno_t
 */
EV_API int ev_fs_remove_sync(const char* path, int recursion);

/**
 * @brief Cleanup file system request
 * @param[in] req       File system request
 */
EV_API void ev_fs_req_cleanup(ev_fs_req_t* req);

/**
 * @brief Get file handle from request.
 * @param[in] req       File system request.
 * @return              File handle.
 */
EV_API ev_file_t* ev_fs_get_file(ev_fs_req_t* req);

/**
 * @brief Get stat buffer from \p req.
 * @param[in] req       A finish file system request
 * @return              Stat buf
 */
EV_API ev_fs_stat_t* ev_fs_get_statbuf(ev_fs_req_t* req);

/**
 * @brief Get first dirent information from \p req.
 * @param[in] req       File system request.
 * @return              Dirent information.
 */
EV_API ev_dirent_t* ev_fs_get_first_dirent(ev_fs_req_t* req);

/**
 * @brief Get next dirent information.
 * @param[in] curr      Current dirent information.
 * @return              Next dirent information, or NULL if non-exists.
 */
EV_API ev_dirent_t* ev_fs_get_next_dirent(ev_dirent_t* curr);

/**
 * @brief Get content of file.
 * @param[in] req       A finish file system request
 * @return              File content buffer.
 */
EV_API ev_buf_t* ev_fs_get_filecontent(ev_fs_req_t* req);

/**
 * @} EV_FILESYSTEM
 */

#ifdef __cplusplus
}
#endif
#endif
