#include <string.h>

EV_LOCAL int ev__udp_interface_addr_to_sockaddr(struct sockaddr_storage *dst,
                                                const char *interface_addr,
                                                int         is_ipv6)
{
    struct sockaddr_in  *addr_4 = (struct sockaddr_in *)dst;
    struct sockaddr_in6 *addr_6 = (struct sockaddr_in6 *)dst;

    if (interface_addr == NULL)
    {
        memset(dst, 0, sizeof(*dst));
        if (is_ipv6)
        {
            dst->ss_family = AF_INET6;
            addr_6->sin6_scope_id = 0;
        }
        else
        {
            dst->ss_family = AF_INET;
            addr_4->sin_addr.s_addr = htonl(INADDR_ANY);
        }
    }
    else if (ev_ipv4_addr(interface_addr, 0, addr_4) == 0)
    {
        /* do nothing, address was parsed */
    }
    else if (ev_ipv6_addr(interface_addr, 0, addr_6) == 0)
    {
        /* do nothing, address was parsed */
    }
    else
    {
        return EV_EINVAL;
    }

    return 0;
}

int ev_udp_try_send(ev_udp_t *udp, ev_buf_t *bufs, size_t nbuf,
                    const struct sockaddr *addr, ev_udp_write_cb cb, void *arg)
{
    if (ev_list_size(&udp->send_list) != 0)
    {
        return EV_EAGAIN;
    }

    return ev_udp_send(udp, bufs, nbuf, addr, cb, arg);
}

int ev_udp_recv(ev_udp_t *udp, ev_buf_t *bufs, size_t nbuf, ev_udp_recv_cb cb,
                void *arg)
{
    int ret;
    if (udp->sock == EV_OS_SOCKET_INVALID)
    {
        return EV_EPIPE;
    }

    ev_udp_read_t *req = ev_malloc(sizeof(ev_udp_read_t));
    if (req == NULL)
    {
        return EV_ENOMEM;
    }

    req->usr_cb = cb;
    req->usr_cb_arg = arg;
    ev__handle_init(udp->base.loop, &req->handle, EV_ROLE_EV_REQ_UDP_R);

    if ((ret = ev__read_init(&req->base, bufs, nbuf)) != 0)
    {
        goto err;
    }
    ev_list_push_back(&udp->recv_list, &req->base.node);

    if ((ret = ev__udp_recv(udp, req)) != 0)
    {
        ev__read_exit(&req->base);
        ev_list_erase(&udp->recv_list, &req->base.node);
        goto err;
    }

    return 0;

err:
    ev__handle_exit(&req->handle, NULL);
    ev_free(req);
    return ret;
}

int ev_udp_send(ev_udp_t *udp, ev_buf_t *bufs, size_t nbuf,
                const struct sockaddr *addr, ev_udp_write_cb cb, void *arg)
{
    int             ret;
    ev_udp_write_t *req = ev_malloc(sizeof(ev_udp_write_t));
    if (req == NULL)
    {
        return EV_ENOMEM;
    }

    req->usr_cb = cb;
    req->usr_cb_arg = arg;
    ev__handle_init(udp->base.loop, &req->handle, EV_ROLE_EV_REQ_UDP_W);

    if ((ret = ev__write_init(&req->base, bufs, nbuf)) != 0)
    {
        goto err;
    }
    ev_list_push_back(&udp->send_list, &req->base.node);

    socklen_t addrlen = addr != NULL ? ev__get_addr_len(addr) : 0;
    if ((ret = ev__udp_send(udp, req, addr, addrlen)) != 0)
    {
        goto err_cleanup_write;
    }

    return 0;

err_cleanup_write:
    ev_list_erase(&udp->send_list, &req->base.node);
    ev__write_exit(&req->base);
err:
    ev__handle_exit(&req->handle, NULL);
    ev_free(req);
    return ret;
}
