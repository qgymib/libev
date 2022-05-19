#ifndef __EV_THREADPOOL_INTERNAL_H__
#define __EV_THREADPOOL_INTERNAL_H__

#include "ev/threadpool.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Submit task to threadpool.
 * @param[in] loop      Event loop.
 * @param[in] work      Work token.
 * @param[in] type      Work type.
 * @param[in] work_cb   Work callback.
 * @param[in] done_cb   Work done callback.
 * @return              #ev_errno_t
 */
int ev__loop_submit_threadpool(ev_loop_t* loop, ev_threadpool_work_t* work,
    ev_threadpool_work_type_t type, ev_threadpool_work_cb work_cb,
    ev_threadpool_work_done_cb done_cb);

#ifdef __cplusplus
}
#endif

#endif