#ifndef __EV_PIPE_INTERNAL_H__
#define __EV_PIPE_INTERNAL_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Write request token for pipe.
 */
typedef struct ev_pipe_write_req
{
    ev_write_t       base;    /**< Base object */
    ev_pipe_write_cb ucb;     /**< User callback */
    void            *ucb_arg; /**< User defined argument. */
    struct
    {
        ev_role_t role; /**< The type of handle to send */
        union {
            ev_os_socket_t os_socket; /**< A EV handle instance */
        } u;
    } handle;
    EV_PIPE_WRITE_BACKEND backend; /**< Backend */
} ev_pipe_write_req_t;

struct ev_pipe
{
    ev_handle_t     base;      /**< Base object */
    ev_pipe_cb      close_cb;  /**< User close callback */
    void           *close_arg; /**< Close argument. */
    ev_os_pipe_t    pipfd;     /**< Pipe handle */
    EV_PIPE_BACKEND backend;   /**< Platform related implementation */
};

/**
 * @brief Initialize #ev_pipe_read_req_t
 * @param[out] req  A read request to be initialized
 * @param[in] bufs  Buffer list
 * @param[in] nbuf  Buffer list size, can not larger than #EV_IOV_MAX.
 * @param[in] cb    Read complete callback
 * @return          #ev_errno_t
 */
EV_LOCAL int ev__pipe_read_init(ev_pipe_read_req_t *req, ev_buf_t *bufs,
                                size_t nbuf, ev_pipe_read_cb cb);

/**
 * @brief Initialize #ev_pipe_write_req_t
 * @param[out] req  A write request to be initialized
 * @param[in] bufs  Buffer list
 * @param[in] nbuf  Buffer list size, can not larger than #EV_IOV_MAX.
 * @param[in] cb    Write complete callback
 * @param[in] arg   User defined argument.
 * @return          #ev_errno_t
 */
EV_LOCAL int ev__pipe_write_init(ev_pipe_write_req_t *req, ev_buf_t *bufs,
                                 size_t nbuf, ev_pipe_write_cb cb, void* arg);

/**
 * @brief Initialize #ev_pipe_write_req_t
 *
 * The extend version of #ev__pipe_write_init(). You should use this function if
 * any of following condition is meet:
 *
 *   + The value of \p nbuf is larger than #EV_IOV_MAX.<br>
 *     In this case you should pass \p iov_bufs as storage, the minimum value of
 *     \p iov_size can be calculated by #EV_IOV_BUF_SIZE(). \p take the
 * ownership of \p iov_bufs, so you cannot modify or free \p iov_bufs until \p
 * callback is called.
 *
 *   + Need to transfer a handle to peer.<br>
 *     In this case you should set the type of handle via \p handle_role and
 * pass the address of the handle via \p handle_addr. \p req does not take the
 * ownership of the handle, but the handle should not be closed or destroy until
 * \p callback is called.
 *
 * @param[out] req          A write request to be initialized
 * @param[in] cb            Write complete callback
 * @param[in] arg           User defined argument.
 * @param[in] bufs          Buffer list
 * @param[in] nbuf          Buffer list size
 * @param[in] handle_role   The type of handle to send
 * @param[in] handle_addr   The address of handle to send
 * @return                  #ev_errno_t
 */
EV_LOCAL int ev__pipe_write_init_ext(ev_pipe_write_req_t *req,
                                     ev_pipe_write_cb cb, void *arg,
                                     ev_buf_t *bufs, size_t nbuf,
                                     ev_role_t handle_role, void *handle_addr);

#ifdef __cplusplus
}
#endif
#endif
