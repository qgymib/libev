#ifndef __EV_HANDLE_INTERNAL_H__
#define __EV_HANDLE_INTERNAL_H__

#include "ev/handle.h"
#include "ev-platform.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ev_handle_flag
{
    /* Used by all handles. Bit 0-7. */
    EV_HANDLE_CLOSING           = 0x01 << 0x00,     /**< 1. Handle is going to close */
    EV_HANDLE_CLOSED            = 0x01 << 0x01,     /**< 2. Handle is closed */
    EV_HANDLE_ACTIVE            = 0x01 << 0x02,     /**< 4. Handle is busy */

    /* #EV_ROLE_EV_TCP */
    EV_HANDLE_TCP_LISTING       = 0x01 << 0x08,     /**< 256. This is a listen socket and is listening */
    EV_HANDLE_TCP_ACCEPTING     = 0x01 << 0x09,     /**< 512. This is a socket waiting for accept */
    EV_HANDLE_TCP_STREAMING     = 0x01 << 0x0A,     /**< 1024. This is a socket waiting for read or write */
    EV_HANDLE_TCP_CONNECTING    = 0x01 << 0x0B,     /**< 2048. This is a connect and waiting for connect complete */
    EV_HABDLE_TCP_BOUND         = 0x01 << 0x0C,     /**< 4096. Socket is bond to address */

    /* #EV_ROLE_EV_UDP */
    EV_HANDLE_UDP_IPV6          = 0x01 << 0x08,     /**< 256. This socket have IPv6 ability */
    EV_HANDLE_UDP_CONNECTED     = 0x01 << 0x09,     /**< 512. This socket is connected */
    EV_HANDLE_UDP_BOUND         = 0x01 << 0x0A,     /**< 1024. Socket is bond to address */
    EV_HANDLE_UDP_BYPASS_IOCP   = 0x01 << 0x0B,     /**< 2048. FILE_SKIP_SET_EVENT_ON_HANDLE | FILE_SKIP_COMPLETION_PORT_ON_SUCCESS */

    /* #EV_ROLE_EV_PIPE */
    EV_HANDLE_PIPE_IPC          = 0x01 << 0x08,     /**< 256. This pipe is support IPC */
    EV_HANDLE_PIPE_STREAMING    = 0x01 << 0x09,     /**< 512. This pipe is initialized by #ev_stream_t */
}ev_handle_flag_t;

/**
 * @brief Initialize a handle
 * @param[in] loop      The loop own the handle
 * @param[out] handle   A pointer to the structure
 * @param[in] role      Who we are
 * @param[in] close_cb  A callback when handle is closed
 */
API_LOCAL void ev__handle_init(ev_loop_t* loop, ev_handle_t* handle, ev_role_t role, ev_close_cb close_cb);

/**
 * @brief Close the handle
 * @note The handle will not closed until close_cb was called, which was given
 *   by #ev__handle_init()
 * @param[in] handle    handler
 * @param[in] force     Force exit, without async callback
 */
API_LOCAL void ev__handle_exit(ev_handle_t* handle, int force);

/**
 * @brief Set handle as active
 * @param[in] handle    handler
 */
API_LOCAL void ev__handle_active(ev_handle_t* handle);

/**
 * @brief Set handle as inactive
 * @param[in] handle    handler
 */
API_LOCAL void ev__handle_deactive(ev_handle_t* handle);

/**
 * @brief Check if the handle is in active state
 * @param[in] handle    handler
 * @return              bool
 */
API_LOCAL int ev__handle_is_active(ev_handle_t* handle);

/**
 * @brief Check if the handle is in closing or closed state
 * @param[in] handle    handler
 * @return              bool
 */
API_LOCAL int ev__handle_is_closing(ev_handle_t* handle);

#ifdef __cplusplus
}
#endif

#endif