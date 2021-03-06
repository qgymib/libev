#ifndef __EV_LOOP_UNIX_H__
#define __EV_LOOP_UNIX_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "ev-common.h"
#include "ev-platform.h"

#include <sys/epoll.h>
#define EV_IO_IN			EPOLLIN		/**< The associated file is available for read(2) operations. */
#define EV_IO_OUT			EPOLLOUT	/**< The associated file is available for write(2) operations. */

/**
 * @brief Initialize io structure
 * @param[out] io	A pointer to the structure
 * @param[in] fd	File descriptor
 * @param[in] cb	IO active callback
 */
void ev__io_init(ev_io_t* io, int fd, ev_io_cb cb);

/**
 * @brief Add events to IO structure
 * @param[in] loop	Event loop
 * @param[in] io	IO structure
 * @param[in] evts	#EV_IO_IN or #EV_IO_OUT
 */
void ev__io_add(ev_loop_t* loop, ev_io_t* io, unsigned evts);

/**
 * @brief Delete events from IO structure
 * @param[in] loop	Event loop
 * @param[in] io	IO structure
 * @param[in] evts	#EV_IO_IN or #EV_IO_OUT
 */
void ev__io_del(ev_loop_t* loop, ev_io_t* io, unsigned evts);

/**
 * @brief Initialize #ev_write_t
 * @param[out] req	A write request to be initialized
 * @param[in] bufs	Buffer list
 * @param[in] nbuf	Buffer list size
 * @param[in] cb	Write complete callback
 */
void ev__write_init(ev_write_t* req, ev_buf_t bufs[], size_t nbuf, ev_write_cb cb);

/**
 * @brief Initialize #ev_read_t
 * @param[out] req	A read request to be initialized
 * @param[in] bufs	Buffer list
 * @param[in] nbuf	Buffer list size
 * @param[in] cb	Read complete callback
 */
void ev__read_init(ev_read_t* req, ev_buf_t bufs[], size_t nbuf, ev_read_cb cb);

/**
 * @brief Initialize stream.
 * @param[in] loop	Event loop
 * @param[out] stream	Stream handler
 * @param[in] fd	File descriptor
 * @param[in] wcb	Write callback
 * @param[in] rcb	Read callback
 */
void ev__stream_init(ev_loop_t* loop, ev_stream_t* stream, int fd, ev_stream_write_cb wcb, ev_stream_read_cb rcb);

/**
 * @brief Do stream write
 * @param[in] stream	Stream handle
 * @param[in] req		Write request
 * @return				#ev_errno_t
 */
int ev__stream_write(ev_stream_t* stream, ev_write_t* req);

/**
 * @brief Do stream read
 * @param[in] stream	Stream handle
 * @param[in] req		Read request
 * @return				#ev_errno_t
 */
int ev__stream_read(ev_stream_t* stream, ev_read_t* req);

/**
 * @brief Get pending action count.
 * @param[in] stream	Stream handle
 * @param[in] evts		#EV_IO_IN or #EV_IO_OUT
 * @return				Action count
 */
size_t ev__stream_size(ev_stream_t* stream, unsigned evts);

/**
 * @brief Abort pending requests
 * @param[in] stream	Stream handle
 * @param[in] evts		#EV_IO_IN or #EV_IO_OUT
 */
void ev__stream_abort(ev_stream_t* stream, unsigned evts);

/**
 * @brief Cleanup pending requests
 * @param[in] stream	Stream handle
 * @param[in] evts		#EV_IO_IN or #EV_IO_OUT
 */
void ev__stream_cleanup(ev_stream_t* stream, unsigned evts);

/**
 * @brief Add or remove FD_CLOEXEC
 * @param[in] fd	File descriptor
 * @param[in] set	bool
 * @return			#ev_errno_t
 */
int ev__cloexec(int fd, int set);

/**
 * @brief Add or remove O_NONBLOCK
 * @param[in] fd	File descriptor
 * @param[in] set	bool
 * @return			#ev_errno_t
 */
int ev__nonblock(int fd, int set);

#ifdef __cplusplus
}
#endif
#endif
