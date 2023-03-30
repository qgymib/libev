#ifndef __EV_UDP_FORWARD_H__
#define __EV_UDP_FORWARD_H__

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_UDP UDP
 * @{
 */

/**
 * @brief Multicast operation.
 */
enum ev_udp_membership
{
    EV_UDP_LEAVE_GROUP  = 0,    /**< Leave multicast group */
    EV_UDP_ENTER_GROUP  = 1,    /**< Join multicast group */
};

/**
 * @brief Typedef of #ev_udp_membership.
 */
typedef enum ev_udp_membership ev_udp_membership_t;

/**
 * @brief UDP socket flags.
 */
enum ev_udp_flags
{
    EV_UDP_IPV6_ONLY    = 1,    /**< Do not bound to IPv4 address */
    EV_UDP_REUSEADDR    = 2,    /**< Reuse address. Only the last one can receive message. */
};

/**
 * @brief Typedef of #ev_udp_flags.
 */
typedef enum ev_udp_flags ev_udp_flags_t;

struct ev_udp;

/**
 * @brief Typedef of #ev_udp.
 */
typedef struct ev_udp ev_udp_t;

struct ev_udp_write;

/**
 * @brief Typedef of #ev_udp_write.
 */
typedef struct ev_udp_write ev_udp_write_t;

struct ev_udp_read;

/**
 * @brief Typedef of #ev_udp_read.
 */
typedef struct ev_udp_read ev_udp_read_t;

/**
 * @brief Callback for #ev_udp_t
 * @param[in] udp   UDP handle
 */
typedef void (*ev_udp_cb)(ev_udp_t* udp);

/**
 * @brief Write callback
 * @param[in] req       Write request.
 * @param[in] size      Write result.
 */
typedef void (*ev_udp_write_cb)(ev_udp_write_t* req, ssize_t size);

/**
 * @brief Read callback
 * @param[in] req       Read callback.
 * @param[in] addr      Peer address.
 * @param[in] size      Read result.
 */
typedef void (*ev_udp_recv_cb)(ev_udp_read_t* req, const struct sockaddr* addr, ssize_t size);

/**
 * @} EV_UDP
 */

#ifdef __cplusplus
}
#endif
#endif
