#ifndef __EV_ASYNC_COMMON_H__
#define __EV_ASYNC_COMMON_H__

#include "ev/async.h"
#include "ev-platform.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Force destroy #ev_async_t.
 * @param[in] handle    A initialized #ev_async_t handler.
 */
API_LOCAL void ev__async_exit_force(ev_async_t* handle);

#ifdef __cplusplus
}
#endif
#endif