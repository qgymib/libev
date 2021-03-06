#include <assert.h>
#include <string.h>
#include "ev-common.h"
#include "ev-platform.h"
#include "ev.h"

typedef struct ev_strerror_pair
{
	int				errn;	/**< Error number */
	const char*		info;	/**< Error string */
}ev_strerror_pair_t;

static int _ev_cmp_timer(const ev_map_node_t* key1, const ev_map_node_t* key2, void* arg)
{
	(void)arg;
	ev_timer_t* t1 = container_of(key1, ev_timer_t, node);
	ev_timer_t* t2 = container_of(key2, ev_timer_t, node);

	if (t1->data.active == t2->data.active)
	{
		if (t1 == t2)
		{
			return 0;
		}
		return t1 < t2 ? -1 : 1;
	}

	return t1->data.active < t2->data.active ? -1 : 1;
}

static void _ev_loop_init(ev_loop_t* loop)
{
	ev_map_init(&loop->timer.heap, _ev_cmp_timer, NULL);
	ev_list_init(&loop->todo.queue);
	loop->active_handles = 0;

	memset(&loop->mask, 0, sizeof(loop->mask));
}

static int _ev_loop_alive(ev_loop_t* loop)
{
	return loop->active_handles || ev_list_size(&loop->todo.queue);
}

int ev_loop_init(ev_loop_t* loop)
{
	loop->hwtime = 0;
	ev__loop_update_time(loop);

	int ret = ev__loop_init_backend(loop);
	if (ret < 0)
	{
		return ret;
	}

	_ev_loop_init(loop);

	return EV_SUCCESS;
}

void ev_loop_exit(ev_loop_t* loop)
{
	ev__loop_exit_backend(loop);
}

void ev_loop_stop(ev_loop_t* loop)
{
	loop->mask.b_stop = 1;
}

static int _ev_loop_active_timer(ev_loop_t* loop)
{
	int ret = 0;

	ev_map_node_t* it;
	while ((it = ev_map_begin(&loop->timer.heap)) != NULL)
	{
		ev_timer_t* timer = container_of(it, ev_timer_t, node);
		if (timer->data.active > loop->hwtime)
		{
			break;
		}

		ev_timer_stop(timer);
		if (timer->attr.repeat != 0)
		{
			ev_timer_start(timer, timer->attr.cb, timer->attr.repeat, timer->attr.repeat);
		}
		timer->attr.cb(timer);
		ret++;
	}

	return ret;
}

static void _ev_loop_active_todo(ev_loop_t* loop)
{
	ev_list_node_t* it;
	while ((it = ev_list_pop_front(&loop->todo.queue)) != NULL)
	{
		ev_todo_t* todo = container_of(it, ev_todo_t, node);
		todo->cb(todo);
	}
}

static uint32_t _ev_backend_timeout_timer(ev_loop_t* loop)
{
	ev_map_node_t* it = ev_map_begin(&loop->timer.heap);
	if (it == NULL)
	{
		return 0;
	}

	ev_timer_t* timer = container_of(it, ev_timer_t, node);
	if (timer->data.active <= loop->hwtime)
	{
		return 0;
	}
	uint64_t dif = timer->data.active - loop->hwtime;
	return dif > UINT32_MAX ? UINT32_MAX : (uint32_t)dif;
}

static uint32_t _ev_backend_timeout(ev_loop_t* loop)
{
	uint32_t ret;
	if (loop->mask.b_stop)
	{
		return 0;
	}

	if (ev_list_size(&loop->todo.queue) != 0)
	{
		return 0;
	}

	if ((ret = _ev_backend_timeout_timer(loop)) != 0)
	{
		return ret;
	}

	/* If no active handle, set timeout to max value */
	return loop->active_handles ? (uint32_t)-1 : 0;
}

static void _ev_to_close(ev_todo_t* todo)
{
	ev_handle_t* handle = container_of(todo, ev_handle_t, close_queue);

	handle->flags &= ~EV_HANDLE_CLOSING;
	handle->flags |= EV_HANDLE_CLOSED;

	handle->close_cb(handle);
}

void ev__handle_init(ev_loop_t* loop, ev_handle_t* handle, ev_close_cb close_cb)
{
	assert(close_cb != NULL);
	handle->loop = loop;
	handle->close_cb = close_cb;
	handle->close_queue = (ev_todo_t)EV_TODO_INIT;
	handle->flags = 0;
}

void ev__handle_exit(ev_handle_t* handle)
{
	if (ev__handle_is_closing(handle))
	{
		ABORT();
		return;
	}

	/* Stop if necessary */
	ev__handle_deactive(handle);

	handle->flags |= EV_HANDLE_CLOSING;

	ev__todo(handle->loop, &handle->close_queue, _ev_to_close);
}

void ev__handle_active(ev_handle_t* handle)
{
	if (handle->flags & EV_HANDLE_ACTIVE)
	{
		return;
	}

	handle->flags |= EV_HANDLE_ACTIVE;
	handle->loop->active_handles++;
}

void ev__handle_deactive(ev_handle_t* handle)
{
	if (!(handle->flags & EV_HANDLE_ACTIVE))
	{
		return;
	}

	handle->flags &= ~EV_HANDLE_ACTIVE;
	handle->loop->active_handles--;
}

int ev__handle_is_active(ev_handle_t* handle)
{
	return handle->flags & EV_HANDLE_ACTIVE;
}

int ev__handle_is_closing(ev_handle_t* handle)
{
	return handle->flags & (EV_HANDLE_CLOSING | EV_HANDLE_CLOSED);
}

void ev__todo(ev_loop_t* loop, ev_todo_t* todo, ev_todo_cb cb)
{
	todo->cb = cb;
	ev_list_push_back(&loop->todo.queue, &todo->node);
}

void ev__tcp_active(ev_tcp_t* sock)
{
	unsigned flags = sock->base.flags;
	if (flags & (EV_TCP_ACCEPTING | EV_TCP_STREAMING | EV_TCP_CONNECTING))
	{
		ev__handle_active(&sock->base);
	}
}

void ev__tcp_deactive(ev_tcp_t* sock)
{
	unsigned flags = sock->base.flags;
	if (flags & (EV_TCP_ACCEPTING | EV_TCP_STREAMING | EV_TCP_CONNECTING))
	{
		return;
	}

	ev__handle_deactive(&sock->base);
}

int ev_loop_run(ev_loop_t* loop, ev_loop_mode_t mode)
{
	uint32_t timeout;

	int r = _ev_loop_alive(loop);

	while (r != 0 && !loop->mask.b_stop)
	{
		ev__loop_update_time(loop);

		_ev_loop_active_timer(loop);
		_ev_loop_active_todo(loop);

		/* Calculate timeout */
		timeout = mode != ev_loop_mode_nowait ?
			_ev_backend_timeout(loop) : 0;

		ev__poll(loop, timeout);

		/**
		 * #ev_loop_mode_once implies forward progress: at least one callback must have
		 * been invoked when it returns. #_ev_poll_win() can return without doing
		 * I/O (meaning: no callbacks) when its timeout expires - which means we
		 * have pending timers that satisfy the forward progress constraint.
		 *
		 * #ev_loop_mode_nowait makes no guarantees about progress so it's omitted from
		 * the check.
		 */
		if (mode == ev_loop_mode_once)
		{
			ev__loop_update_time(loop);
			_ev_loop_active_timer(loop);
		}

		/* Callback maybe added */
		_ev_loop_active_todo(loop);

		r = _ev_loop_alive(loop);
		if (mode != ev_loop_mode_default)
		{
			break;
		}
	}

	/* Prevent #ev_loop_t::mask::b_stop from compile optimization */
	if (loop->mask.b_stop)
	{
		loop->mask.b_stop = 0;
	}

	return r;
}

int ev_ipv4_addr(const char* ip, int port, struct sockaddr_in* addr)
{
	memset(addr, 0, sizeof(*addr));

	addr->sin_family = AF_INET;
	addr->sin_port = htons((uint16_t)port);

	return inet_pton(AF_INET, ip, &addr->sin_addr) ? EV_SUCCESS : EV_EINVAL;
}

int ev_ipv6_addr(const char* ip, int port, struct sockaddr_in6* addr)
{
	memset(addr, 0, sizeof(*addr));

	addr->sin6_family = AF_INET6;
	addr->sin6_port = htons((uint16_t)port);

	return inet_pton(AF_INET6, ip, &addr->sin6_addr) ? EV_SUCCESS : EV_EINVAL;
}

int ev_ipv4_name(const struct sockaddr_in* addr, int* port, char* ip, size_t len)
{
	if (port != NULL)
	{
		*port = ntohs(addr->sin_port);
	}

	if (ip != NULL)
	{
		return inet_ntop(AF_INET, &addr->sin_addr, ip, len) != NULL ?
			EV_SUCCESS : EV_ENOSPC;
	}

	return EV_SUCCESS;
}

int ev_ipv6_name(const struct sockaddr_in6* addr, int* port, char* ip, size_t len)
{
	if (port != NULL)
	{
		*port = ntohs(addr->sin6_port);
	}

	if (ip != NULL)
	{
		return inet_ntop(AF_INET6, &addr->sin6_addr, ip, len) != NULL ?
			EV_SUCCESS : EV_ENOSPC;
	}

	return EV_SUCCESS;
}

ev_buf_t ev_buf_make(void* buf, size_t len)
{
	ev_buf_t tmp;
	
#if defined(_WIN32)
	tmp.data = (CHAR*)buf;
	tmp.size = (ULONG)len;
#else
	tmp.data = buf;
	tmp.size = len;
#endif
	
	return tmp;
}

void ev_buf_make_n(ev_buf_t bufs[], size_t nbuf, ...)
{
	va_list ap;
	va_start(ap, nbuf);
	ev_buf_make_v(bufs, nbuf, ap);
	va_end(ap);
}

void ev_buf_make_v(ev_buf_t bufs[], size_t nbuf, va_list ap)
{
	size_t i;
	for (i = 0; i < nbuf; i++)
	{
		void* v_b = va_arg(ap, void*);
		size_t v_l = va_arg(ap, size_t);
		bufs[i] = ev_buf_make(v_b, v_l);
	}
}

const char* ev_strerror(int err)
{
	switch (err)
	{
		/* Success */
	case EV_SUCCESS:	return "Success";
		/* Posix compatible error code */
	case EV_EACCES:		return "Permission denied";
	case EV_EBUSY:		return "Device or resource busy";
	case EV_EINVAL:		return "Invalid argument";
	case EV_ENOSPC:		return "No space left on device";
	case EV_EADDRINUSE:	return "Address already in use";
	case EV_EINPROGRESS:	return "Operation in progress";
		/* Extend error code */
	case EV_EOF:		return "End of file";
	case EV_UNKNOWN:
	default:
		break;
	}
	return "Unknown";
}
