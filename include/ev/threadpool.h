#ifndef __EV_THREADPOOL_H__
#define __EV_THREADPOOL_H__

#include "ev/loop_forward.h"
#include "ev/thread.h"
#include "ev/mutex.h"
#include "ev/sem.h"
#include "ev/list.h"
#include "ev/async.h"
#include "ev/threadpool_forward.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup EV_THREAD_POOL
 * @{
 */

/**
 * @brief Thread pool handle type.
 */
struct ev_threadpool
{
    ev_os_thread_t*                 threads;        /**< Threads */
    size_t                          thrnum;         /**< The number of threads */

    ev_list_t                       loop_table;     /**< Loop table */

    ev_mutex_t                      mutex;          /**< Thread pool mutex */
    ev_sem_t                        p2w_sem;        /**< Semaphore for pool to worker */
    int                             looping;        /**< Looping flag */

    ev_queue_node_t                 work_queue[3];  /**< Work queue. Index is #ev_work_type_t */
};

#define EV_THREADPOOL_INVALID   \
    {\
        NULL,\
        0,\
        EV_LIST_INIT,\
        EV_MUTEX_INVALID,\
        EV_SEM_INVALID,\
        0,\
        {\
            EV_QUEUE_NODE_INVALID,\
            EV_QUEUE_NODE_INVALID,\
            EV_QUEUE_NODE_INVALID,\
        },\
    }

/**
 * @brief Thread pool work token.
 */
struct ev_work
{
    ev_handle_t                     base;           /**< Base object */
    ev_queue_node_t                 node;           /**< List node */

    struct
    {
        ev_threadpool_t*            pool;           /**< Thread pool */

        /**
         * @brief Work status.
         * + #EV_ELOOP:     In queue but not called yet.
         * + #EV_EBUSY:     Already in process
         * + #EV_ECANCELED: Canceled
         * + #EV_SUCCESS:   Done
         */
        int                         status;

		ev_work_cb                  work_cb;        /**< work callback */
		ev_work_done_cb             done_cb;        /**< done callback */
    }data;
};

#define EV_THREADPOOL_WORK_INVALID \
    {\
        EV_HANDLE_INVALID,\
        EV_QUEUE_NODE_INVALID,\
        { NULL, EV_UNKNOWN, NULL, NULL },\
    }

/**
 * @} EV_THREAD_POOL
 */

#ifdef __cplusplus
}
#endif

#endif
