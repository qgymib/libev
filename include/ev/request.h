#ifndef __EV_REQUEST_H__
#define __EV_REQUEST_H__

#include "ev/backend.h"
#include "ev/handle.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Read request
 */
struct ev_read
{
    ev_list_node_t          node;               /**< Intrusive node */
    struct
    {
        ev_read_cb          cb;                 /**< Read complete callback */
        ev_buf_t*           bufs;               /**< Buffer list */
        size_t              nbuf;               /**< Buffer list count */
        size_t              capacity;           /**< Total bytes of buffer */
        size_t              size;               /**< Data size */
        ev_buf_t            bufsml[EV_IOV_MAX]; /**< Bound buffer list */
    }data;
    ev_read_backend_t       backend;            /**< Back-end */
};
#define EV_READ_INVALID     \
    {\
        EV_LIST_NODE_INIT,/* .node */\
        {/* .data */\
            NULL,                                                   /* .data.cb */\
            NULL,                                                   /* .data.bufs */\
            0,                                                      /* .data.nbuf */\
            0,                                                      /* .data.capacity */\
            0,                                                      /* .data.size */\
            { EV_INIT_REPEAT(EV_IOV_MAX, EV_BUF_INIT(NULL, 0)), },  /* .data.bufsml */\
        },\
        EV_READ_BACKEND_INIT\
    }

/**
 * @brief Write request
 */
struct ev_write
{
    ev_list_node_t          node;               /**< Intrusive node */
    struct
    {
        ev_write_cb         cb;                 /**< Write complete callback */
        ev_buf_t*           bufs;               /**< Buffer list */
        size_t              nbuf;               /**< Buffer list count */
        size_t              size;               /**< Write size */
        size_t              capacity;           /**< Total bytes need to send */
        ev_buf_t            bufsml[EV_IOV_MAX]; /**< Bound buffer list */
    }data;
    ev_write_backend_t      backend;            /**< Back-end */
};
#define EV_WRITE_INVALID    \
    {\
        EV_LIST_NODE_INIT,                                          /* .node */\
        {/* .data */\
            NULL,                                                   /* .data.cb */\
            NULL,                                                   /* .data.bufs */\
            0,                                                      /* .data.nbuf */\
            0,                                                      /* .data.size */\
            0,                                                      /* .data.capacity */\
            { EV_INIT_REPEAT(EV_IOV_MAX, EV_BUF_INIT(NULL, 0)), }   /* .data.bufsml */\
        },\
        EV_WRITE_BACKEND_INIT                                       /* .backend */\
    }

#ifdef __cplusplus
}
#endif

#endif
