#ifndef __EV_TCP_H__
#define __EV_TCP_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_TCP TCP
 *
 * TCP layer.
 *
 * @{
 */

/**
 * @example tcp_echo_server.c
 * This is an example for how to use #ev_tcp_t as tcp server.
 */

/**
 * @brief Typedef of #ev_tcp.
 */
typedef struct ev_tcp ev_tcp_t;

/**
 * @brief Typedef of #ev_tcp_read_req.
 */
typedef struct ev_tcp_read_req ev_tcp_read_req_t;

/**
 * @brief Typedef of #ev_tcp_write_req.
 */
typedef struct ev_tcp_write_req ev_tcp_write_req_t;

/**
 * @brief Close callback for #ev_tcp_t
 * @param[in] sock      A closed socket
 */
typedef void(*ev_tcp_close_cb)(ev_tcp_t* sock);

/**
 * @brief Accept callback
 * @param[in] lisn      Listen socket
 * @param[in] conn      Accepted socket
 * @param[in] stat      #ev_errno_t
 */
typedef void(*ev_tcp_accept_cb)(ev_tcp_t* lisn, ev_tcp_t* conn, int stat);

/**
 * @brief Connect callback
 * @param[in] sock      Connect socket
 * @param[in] stat      #ev_errno_t
 */
typedef void(*ev_tcp_connect_cb)(ev_tcp_t* sock, int stat);

/**
 * @brief Write callback
 * @param[in] req       Write request token
 * @param[in] size      Write result
 */
typedef void (*ev_tcp_write_cb)(ev_tcp_write_req_t* req, ssize_t size);

/**
 * @brief Read callback
 * @param[in] req       Read callback
 * @param[in] size      Read result
 */
typedef void (*ev_tcp_read_cb)(ev_tcp_read_req_t* req, ssize_t size);

/**
 * @brief TCP socket.
 */
struct ev_tcp
{
    ev_handle_t             base;               /**< Base object */
    ev_tcp_close_cb         close_cb;           /**< User close callback */

    ev_os_socket_t          sock;               /**< Socket handle */
    EV_TCP_BACKEND          backend;            /**< Platform related implementation */
};
/**
 * @brief Initialize #ev_tcp_t to an invalid value.
 * @see ev_tcp_init()
 */
#define EV_TCP_INVALID      \
    {\
        EV_HANDLE_INVALID,\
        NULL,\
        EV_OS_SOCKET_INVALID,\
        EV_TCP_BACKEND_INIT,\
    }

/**
 * @brief Read request token for TCP socket.
 */
struct ev_tcp_read_req
{
    ev_read_t               base;               /**< Base object */
    ev_tcp_read_cb          user_callback;      /**< User callback */
    EV_TCP_READ_BACKEND     backend;            /**< Backend */
};

/**
 * @brief Write request token for TCP socket.
 */
struct ev_tcp_write_req
{
    ev_write_t              base;               /**< Base object */
    ev_tcp_write_cb         user_callback;      /**< User callback */
    EV_TCP_WRITE_BACKEND    backend;            /**< Backend */
};

/**
 * @brief Initialize a tcp socket
 * @param[in] loop      Event loop
 * @param[out] tcp      TCP handle
 */
EV_API int ev_tcp_init(ev_loop_t* loop, ev_tcp_t* tcp);

/**
 * @brief Destroy socket
 * @param[in] sock      Socket
 * @param[in] cb        Destroy callback
 */
EV_API void ev_tcp_exit(ev_tcp_t* sock, ev_tcp_close_cb cb);

/**
 * @brief Bind the handle to an address and port.
 * addr should point to an initialized struct sockaddr_in or struct sockaddr_in6.
 * @param[in] tcp       Socket handler
 * @param[in] addr      Bind address
 * @param[in] addrlen   Address length
 * @return              #ev_errno_t
 */
EV_API int ev_tcp_bind(ev_tcp_t* tcp, const struct sockaddr* addr, size_t addrlen);

/**
 * @brief Start listening for incoming connections.
 * @param[in] sock      Listen socket
 * @param[in] backlog   The number of connections the kernel might queue
 * @return              #ev_errno_t
 */
EV_API int ev_tcp_listen(ev_tcp_t* sock, int backlog);

/**
 * @brief Accept a connection from listen socket
 * @param[in] acpt  Listen socket
 * @param[in] conn  The socket to store new connection
 * @param[in] cb    Accept callback
 * @return          #ev_errno_t
 */
EV_API int ev_tcp_accept(ev_tcp_t* acpt, ev_tcp_t* conn, ev_tcp_accept_cb cb);

/**
 * @brief Connect to address
 * @param[in] sock  Socket handle
 * @param[in] addr  Address
 * @param[in] size  Address size
 * @param[in] cb    Connect callback
 * @return          #ev_errno_t
 */
EV_API int ev_tcp_connect(ev_tcp_t* sock, struct sockaddr* addr, size_t size,
    ev_tcp_connect_cb cb);

/**
 * @brief Write data
 * 
 * Once #ev_tcp_write() return #EV_SUCCESS, it take the ownership of \p req, so
 * you should not modify the content of it until bounded callback is called.
 * 
 * It is a guarantee that every bounded callback of \p req will be called, with
 * following scene:
 *   + If write success or failure. The callback will be called with write status.
 *   + If \p pipe is exiting but there are pending write request. The callback
 *     will be called with status #EV_ECANCELED.
 * 
 * @param[in] sock  Socket handle
 * @param[in] req   Write request
 * @param[in] bufs  Buffer list
 * @param[in] nbuf  Buffer number
 * @param[in] cb    Send result callback
 * @return          #ev_errno_t
 */
EV_API int ev_tcp_write(ev_tcp_t* sock, ev_tcp_write_req_t* req,
    ev_buf_t* bufs, size_t nbuf, ev_tcp_write_cb cb);

/**
 * @brief Read data
 * 
 * Once #ev_tcp_read() return #EV_SUCCESS, it take the ownership of \p req, so
 * you should not modify the content of it until bounded callback is called.
 * 
 * It is a guarantee that every bounded callback of \p req will be called, with
 * following scene:
 *   + If read success or failure. The callback will be called with read status.
 *   + If \p pipe is exiting but there are pending read request. The callback
 *     will be called with status #EV_ECANCELED.
 * 
 * @param[in] sock  Socket handle
 * @param[in] req   Read request
 * @param[in] bufs  Buffer list
 * @param[in] nbuf  Buffer number
 * @param[in] cb    Read result callback
 * @return          #ev_errno_t
 */
EV_API int ev_tcp_read(ev_tcp_t* sock, ev_tcp_read_req_t* req,
    ev_buf_t* bufs, size_t nbuf, ev_tcp_read_cb cb);

/**
 * @brief Get the current address to which the socket is bound.
 * @param[in] sock  Socket handle
 * @param[out] name A buffer to store address
 * @param[in,out] len   buffer size
 * @return          #ev_errno_t
 */
EV_API int ev_tcp_getsockname(ev_tcp_t* sock, struct sockaddr* name, size_t* len);

/**
 * @brief Get the address of the peer connected to the socket.
 * @param[in] sock  Socket handle
 * @param[out] name A buffer to store address
 * @param[in,out] len   buffer size
 * @return          #ev_errno_t
 */
EV_API int ev_tcp_getpeername(ev_tcp_t* sock, struct sockaddr* name, size_t* len);

/**
 * @} EV_TCP
 */

#ifdef __cplusplus
}
#endif
#endif
