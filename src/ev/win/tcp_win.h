#ifndef __EV_TCP_WIN_INTERNAL_H__
#define __EV_TCP_WIN_INTERNAL_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Open fd for read/write.
 * @param[in] tcp   TCP handle
 * @param[in] fd    fd
 * @return          #ev_errno_t
 */
EV_LOCAL int ev__tcp_open_win(ev_tcp_t* tcp, SOCKET fd);

#ifdef __cplusplus
}
#endif
#endif
