#ifndef __EV_LOOP_WIN_INTERNAL_H__
#define __EV_LOOP_WIN_INTERNAL_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "winapi.h"

#define EV_INVALID_PID_WIN  0

typedef struct ev_loop_win_ctx
{
    /**
     * Frequency of the high-resolution clock.
     */
    uint64_t                    hrtime_frequency_;

    struct
    {
        struct sockaddr_in      addr_any_ip4;               /**< 0.0.0.0:0 */
        struct sockaddr_in6     addr_any_ip6;               /**< :::0 */
        char                    zero_[1];                   /**< A zero length buffer */
    }net;

    struct
    {
        ev_tls_t                thread_key;                 /**< Thread handle */
    }thread;

    fn_NtQueryInformationFile   NtQueryInformationFile;
    fn_RtlNtStatusToDosError    RtlNtStatusToDosError;
}ev_loop_win_ctx_t;

extern ev_loop_win_ctx_t        g_ev_loop_win_ctx;          /**< Global runtime for Windows */

/**
 * @brief Initialize windows context.
 */
API_LOCAL void ev__init_once_win(void);

/**
 * @brief Initialize IOCP request
 * @param[out] req      A pointer to the IOCP request
 * @param[in] callback  A callback when the request is finish
 * @param[in] arg       User defined argument passed to callback
 */
API_LOCAL void ev__iocp_init(ev_iocp_t* req, ev_iocp_cb callback, void* arg);

/**
 * @brief Initialize #ev_write_t
 * @param[out] req      A write request to be initialized
 * @param[in] owner     Who own this object
 * @param[in] stat      Initial status
 * @param[in] iocp_cb   IOCP completion callback
 * @param[in] iocp_arg  User defined argument passed to #iocp_cb
 */
API_LOCAL void ev__write_init_win(ev_write_t* req, void* owner, int stat,
    ev_iocp_cb iocp_cb, void* iocp_arg);

/**
 * @brief Initialize #ev_read_t
 * @param[out] req      A read request to be initialized
 * @param[in] owner     Who own this object
 * @param[in] stat      Initial status
 * @param[in] iocp_cb   IOCP completion callback
 * @param[in] iocp_arg  User defined argument passed to #iocp_cb
 */
API_LOCAL void ev__read_init_win(ev_read_t* req, void* owner, int stat,
    ev_iocp_cb iocp_cb, void* iocp_arg);

API_LOCAL int ev__ntstatus_to_winsock_error(NTSTATUS status);

API_LOCAL int ev__reuse_win(SOCKET sock, int opt);

API_LOCAL int ev__ipv6only_win(SOCKET sock, int opt);

#ifdef __cplusplus
}
#endif
#endif
