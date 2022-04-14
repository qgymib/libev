#ifndef __EV_ASYNC_H__
#define __EV_ASYNC_H__

#include "ev/handle.h"
#include "ev/mutex.h"
#include "ev/queue.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_ASYNC Async
 * @{
 */

struct ev_async;

/**
 * @brief Typedef of #ev_async.
 */
typedef struct ev_async ev_async_t;

/**
 * @brief Type definition for callback passed to #ev_async_init().
 * @param[in] handle    A pointer to #ev_async_t structure
 */
typedef void(*ev_async_cb)(ev_async_t* async);

/**
 * @brief Async handle type.
 */
struct ev_async
{
    ev_handle_t             base;               /**< Base object */
    ev_queue_node_t         node;               /**< #ev_loop_t::wakeup::async::queue */

    struct
    {
        ev_async_cb         active_cb;          /**< Active callback */
        ev_async_cb         close_cb;           /**< Close callback */

        ev_mutex_t          mutex;              /**< Mutex for #ev_async_backend_t::pending */
        int                 pending;            /**< Pending mask */
    }data;
};

/**
 * @brief Static initializer for #ev_async_t.
 * @note A static initialized #ev_async_t is not a valid handle.
 */
#define EV_ASYNC_INVALID    \
    {\
        EV_HANDLE_INVALID,\
        EV_QUEUE_NODE_INVALID,\
        {\
            NULL,\
            NULL,\
            EV_MUTEX_INVALID,\
            0,\
        }\
    }

/**
 * @brief Initialize the handle.
 *
 * A NULL callback is allowed.
 *
 * @param[in] loop      Event loop
 * @param[out] handle   A pointer to the structure
 * @param[in] cb        Active callback
 * @return              #ev_errno_t
 */
int ev_async_init(ev_loop_t* loop, ev_async_t* handle, ev_async_cb cb);

/**
 * @brief Destroy the structure.
 * @param[in] handle    Async handle
 * @param[in] close_cb  Close callback
 */
void ev_async_exit(ev_async_t* handle, ev_async_cb close_cb);

/**
 * @brief Wake up the event loop and call the async handle's callback.
 * @note MT-Safe
 * @param[in] handle    Async handle
 */
void ev_async_wakeup(ev_async_t* handle);

/**
 * @} EV_ASYNC
 */

#ifdef __cplusplus
}
#endif

#endif
