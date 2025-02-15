#include <assert.h>

static int _ev_udp_setup_socket_attribute_win(ev_loop_t* loop, ev_udp_t* udp, int family)
{
    DWORD yes = 1;
    WSAPROTOCOL_INFOW info;
    int opt_len;
    int ret;

    assert(udp->sock != EV_OS_SOCKET_INVALID);

    /* Set the socket to nonblocking mode */
    if (ioctlsocket(udp->sock, FIONBIO, &yes) == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        goto err;
    }

    /* Make the socket non-inheritable */
    if (!SetHandleInformation((HANDLE)udp->sock, HANDLE_FLAG_INHERIT, 0))
    {
        ret = GetLastError();
        goto err;
    }

    /**
     * Associate it with the I/O completion port. Use uv_handle_t pointer as
     * completion key.
     */
    if (CreateIoCompletionPort((HANDLE)udp->sock, loop->backend.iocp, (ULONG_PTR)udp->sock, 0) == NULL)
    {
        ret = GetLastError();
        goto err;
    }

    /*
     * All known Windows that support SetFileCompletionNotificationModes have a
     * bug that makes it impossible to use this function in conjunction with
     * datagram sockets. We can work around that but only if the user is using
     * the default UDP driver (AFD) and has no other. LSPs stacked on top. Here
     * we check whether that is the case.
     */
    opt_len = sizeof(info);
    if (getsockopt(udp->sock, SOL_SOCKET, SO_PROTOCOL_INFOW, (char*)&info, &opt_len) == SOCKET_ERROR)
    {
        ret = GetLastError();
        goto err;
    }
    if (info.ProtocolChain.ChainLen == 1)
    {
        if (SetFileCompletionNotificationModes((HANDLE)udp->sock,
            FILE_SKIP_SET_EVENT_ON_HANDLE | FILE_SKIP_COMPLETION_PORT_ON_SUCCESS))
        {
            udp->base.data.flags |= EV_HANDLE_UDP_BYPASS_IOCP;
            udp->backend.fn_wsarecv = ev__wsa_recv_workaround;
            udp->backend.fn_wsarecvfrom = ev__wsa_recvfrom_workaround;
        }
        else if ((ret = GetLastError()) != ERROR_INVALID_FUNCTION)
        {
            goto err;
        }
    }

    if (family == AF_INET6)
    {
        udp->base.data.flags |= EV_HANDLE_UDP_IPV6;
    }
    else
    {
        assert(!(udp->base.data.flags & EV_HANDLE_UDP_IPV6));
    }

    return 0;

err:
    return ev__translate_sys_error(ret);
}

static void _ev_udp_on_close_win(ev_handle_t* handle)
{
    ev_udp_t* udp = EV_CONTAINER_OF(handle, ev_udp_t, base);
    ev_udp_cb close_cb = udp->close_cb;
    void     *close_arg = udp->close_arg;

    ev_free(udp);
    if (close_cb != NULL)
    {
        close_cb(udp, close_arg);
    }
}

static int _ev_udp_is_bound_win(ev_udp_t* udp)
{
    struct sockaddr_storage addr;
    size_t addrlen = sizeof(addr);

    int ret = ev_udp_getsockname(udp, (struct sockaddr*)&addr, &addrlen);
    return ret == 0 && addrlen > 0;
}

static int _ev_udp_is_connected_win(ev_udp_t* udp)
{
    struct sockaddr_storage addr;
    size_t addrlen = sizeof(addr);

    int ret = ev_udp_getpeername(udp, (struct sockaddr*)&addr, &addrlen);
    return ret == 0 && addrlen > 0;
}

static int _ev_udp_maybe_deferred_socket_win(ev_udp_t* udp, int domain)
{
    int ret;
    if (udp->sock != EV_OS_SOCKET_INVALID)
    {
        return 0;
    }

    if ((udp->sock = socket(domain, SOCK_DGRAM, 0)) == INVALID_SOCKET)
    {
        ret = WSAGetLastError();
        return ev__translate_sys_error(ret);
    }

    if ((ret = _ev_udp_setup_socket_attribute_win(udp->base.loop, udp, domain)) != 0)
    {
        closesocket(udp->sock);
        udp->sock = EV_OS_SOCKET_INVALID;
        return ret;
    }

    return 0;
}

static void _ev_udp_close_socket_win(ev_udp_t* udp)
{
    if (udp->sock != EV_OS_SOCKET_INVALID)
    {
        closesocket(udp->sock);
        udp->sock = EV_OS_SOCKET_INVALID;
    }
}

static int _ev_udp_disconnect_win(ev_udp_t* udp)
{
    struct sockaddr addr;
    memset(&addr, 0, sizeof(addr));

    int ret = connect(udp->sock, (struct sockaddr*)&addr, sizeof(addr));
    if (ret != 0)
    {
        ret = WSAGetLastError();
        return ev__translate_sys_error(ret);
    }

    udp->base.data.flags &= ~EV_HANDLE_UDP_CONNECTED;
    return 0;
}

static int _ev_udp_maybe_deferred_bind_win(ev_udp_t* udp, int domain)
{
    if (udp->base.data.flags & EV_HANDLE_UDP_BOUND)
    {
        return 0;
    }

    struct sockaddr* bind_addr;
    if (domain == AF_INET)
    {
        bind_addr = (struct sockaddr*)&ev_addr_ip4_any_;
    }
    else if (domain == AF_INET6)
    {
        bind_addr = (struct sockaddr*)&ev_addr_ip6_any_;
    }
    else
    {
        return EV_EINVAL;
    }

    return ev_udp_bind(udp, bind_addr, 0);
}

static int _ev_udp_set_membership_ipv4_win(ev_udp_t* udp,
    const struct sockaddr_in* multicast_addr, const char* interface_addr,
    ev_udp_membership_t membership)
{
    int ret;
    struct ip_mreq mreq;
    memset(&mreq, 0, sizeof(mreq));

    if (interface_addr)
    {
        if (inet_pton(AF_INET, interface_addr, &mreq.imr_interface.s_addr) != 1)
        {
            ret = WSAGetLastError();
            return ev__translate_sys_error(ret);
        }
    }
    else
    {
        mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    }

    mreq.imr_multiaddr.s_addr = multicast_addr->sin_addr.s_addr;

    int optname = membership == EV_UDP_ENTER_GROUP ? IP_ADD_MEMBERSHIP : IP_DROP_MEMBERSHIP;
    if (setsockopt(udp->sock, IPPROTO_IP, optname, (char*)&mreq, sizeof(mreq)) != 0)
    {
        ret = WSAGetLastError();
        return ev__translate_sys_error(ret);
    }

    return 0;
}

static int _ev_udp_set_membership_ipv6_win(ev_udp_t* udp,
    const struct sockaddr_in6* multicast_addr, const char* interface_addr,
    ev_udp_membership_t membership)
{
    int ret;
    struct ipv6_mreq mreq;
    struct sockaddr_in6 addr6;

    memset(&mreq, 0, sizeof(mreq));

    if (interface_addr)
    {
        if (ev_ipv6_addr(interface_addr, 0, &addr6))
        {
            return EV_EINVAL;
        }
        mreq.ipv6mr_interface = addr6.sin6_scope_id;
    }
    else
    {
        mreq.ipv6mr_interface = 0;
    }
    mreq.ipv6mr_multiaddr = multicast_addr->sin6_addr;

    int optname = membership == EV_UDP_ENTER_GROUP ? IPV6_ADD_MEMBERSHIP : IPV6_DROP_MEMBERSHIP;
    if (setsockopt(udp->sock, IPPROTO_IPV6, optname, (char*)&mreq, sizeof(mreq)) != 0)
    {
        ret = WSAGetLastError();
        return ev__translate_sys_error(ret);
    }

    return 0;
}

static int _ev_udp_set_source_membership_ipv4(ev_udp_t* udp,
    const struct sockaddr_in* multicast_addr, const char* interface_addr,
    const struct sockaddr_in* source_addr, ev_udp_membership_t membership)
{
    int err;
    struct ip_mreq_source mreq;
    memset(&mreq, 0, sizeof(mreq));

    if (interface_addr != NULL)
    {
        if (inet_pton(AF_INET, interface_addr, &mreq.imr_interface.s_addr) != 1)
        {
            err = WSAGetLastError();
            return ev__translate_sys_error(err);
        }
    }
    else
    {
        mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    }

    mreq.imr_multiaddr.s_addr = multicast_addr->sin_addr.s_addr;
    mreq.imr_sourceaddr.s_addr = source_addr->sin_addr.s_addr;

    int optname = membership == EV_UDP_ENTER_GROUP ? IP_ADD_SOURCE_MEMBERSHIP : IP_DROP_SOURCE_MEMBERSHIP;

    if (setsockopt(udp->sock, IPPROTO_IP, optname, (char*)&mreq, sizeof(mreq)) != 0)
    {
        err = WSAGetLastError();
        return ev__translate_sys_error(err);
    }

    return 0;
}

static int _ev_udp_set_source_membership_ipv6(ev_udp_t* udp,
    const struct sockaddr_in6* multicast_addr, const char* interface_addr,
    const struct sockaddr_in6* source_addr, ev_udp_membership_t membership)
{
    int ret;
    struct group_source_req mreq;
    struct sockaddr_in6 addr6;

    memset(&mreq, 0, sizeof(mreq));

    if (interface_addr != NULL)
    {
        if ((ret = ev_ipv6_addr(interface_addr, 0, &addr6)) != 0)
        {
            return ret;
        }
        mreq.gsr_interface = addr6.sin6_scope_id;
    }
    else
    {
        mreq.gsr_interface = 0;
    }

    memcpy(&mreq.gsr_group, multicast_addr, sizeof(*multicast_addr));
    memcpy(&mreq.gsr_source, source_addr, sizeof(*source_addr));

    int optname = membership == EV_UDP_ENTER_GROUP ? MCAST_JOIN_SOURCE_GROUP : MCAST_LEAVE_SOURCE_GROUP;
    if (setsockopt(udp->sock, IPPROTO_IPV6, optname, (char*)&mreq, sizeof(mreq)) != 0)
    {
        ret = WSAGetLastError();
        return ev__translate_sys_error(ret);
    }

    return 0;
}

static void _ev_udp_smart_deactive(ev_udp_t* udp)
{
    size_t io_sz = 0;

    io_sz += ev_list_size(&udp->send_list);
    io_sz += ev_list_size(&udp->recv_list);

    if (io_sz == 0)
    {
        ev__handle_deactive(&udp->base);
    }
}

static void _ev_udp_w_user_callback_win(ev_udp_write_t* req, ssize_t size)
{
    ev_udp_t* udp = req->backend.owner;
    _ev_udp_smart_deactive(udp);

    ev__write_exit(&req->base);
    ev__handle_exit(&req->handle, NULL);

    req->usr_cb(udp, size, req->usr_cb_arg);
    ev_free(req);
}

static void _ev_udp_r_user_callback_win(ev_udp_read_t* req, const struct sockaddr* addr, ssize_t size)
{
    ev_udp_t* udp = req->backend.owner;
    _ev_udp_smart_deactive(udp);

    ev__read_exit(&req->base);
    ev__handle_exit(&req->handle, NULL);

    req->usr_cb(udp, addr, size, req->usr_cb_arg);
    ev_free(req);
}

static void _ev_udp_on_send_complete_win(ev_udp_t* udp, ev_udp_write_t* req)
{
    ev_list_erase(&udp->send_list, &req->base.node);

    ssize_t result = req->backend.stat;
    if (result >= 0)
    {
        result = req->base.size;
    }
    _ev_udp_w_user_callback_win(req, result);
}

static void _ev_udp_on_send_bypass_iocp(ev_handle_t* handle)
{
    ev_udp_write_t* req = EV_CONTAINER_OF(handle, ev_udp_write_t, handle);
    ev_udp_t* udp = req->backend.owner;

    _ev_udp_on_send_complete_win(udp, req);
}

static void _ev_udp_on_send_iocp_win(ev_iocp_t* iocp, size_t transferred, void* arg)
{
    ev_udp_t* udp = arg;
    ev_udp_write_t* req = EV_CONTAINER_OF(iocp, ev_udp_write_t, backend.io);

    req->base.size = transferred;
    req->backend.stat = NT_SUCCESS(iocp->overlapped.Internal) ?
        0 : ev__translate_sys_error(ev__ntstatus_to_winsock_error((NTSTATUS)iocp->overlapped.Internal));

    _ev_udp_on_send_complete_win(udp, req);
}

static void _ev_udp_do_recv_win(ev_udp_t* udp, ev_udp_read_t* req)
{
    DWORD recv_bytes;
    DWORD flags = 0;
    socklen_t peer_addr_len = sizeof(req->addr);

    int ret = WSARecvFrom(udp->sock, (WSABUF*)req->base.data.bufs, (DWORD)req->base.data.nbuf,
        &recv_bytes, &flags, (struct sockaddr*)&req->addr, &peer_addr_len, NULL, NULL);
    if (ret != SOCKET_ERROR)
    {
        req->base.data.size = recv_bytes;
        req->backend.stat = 0;
    }
    else
    {
        ret = WSAGetLastError();
        req->backend.stat = ev__translate_sys_error(ret);
    }

    ev_list_erase(&udp->recv_list, &req->base.node);

    ssize_t recv_ret = req->backend.stat;
    struct sockaddr* peer_addr = NULL;

    if (recv_ret >= 0)
    {
        recv_ret = req->base.data.size;
        peer_addr = (struct sockaddr*)&req->addr;
    }

    _ev_udp_r_user_callback_win(req, peer_addr, recv_ret);
}

static void _ev_udp_on_recv_iocp_win(ev_iocp_t* iocp, size_t transferred, void* arg)
{
    (void)transferred;
    ev_udp_t* udp = arg;
    ev_udp_read_t* req = EV_CONTAINER_OF(iocp, ev_udp_read_t, backend.io);

    _ev_udp_do_recv_win(udp, req);
}

static void _ev_udp_on_recv_bypass_iocp_win(ev_handle_t* handle)
{
    ev_udp_read_t* req = EV_CONTAINER_OF(handle, ev_udp_read_t, handle);
    ev_udp_t* udp = req->backend.owner;

    _ev_udp_do_recv_win(udp, req);
}

static int _ev_udp_maybe_bind_win(ev_udp_t* udp, const struct sockaddr* addr, unsigned flags)
{
    int ret;
    if (udp->base.data.flags & EV_HANDLE_UDP_BOUND)
    {
        return EV_EALREADY;
    }

    if ((flags & EV_UDP_IPV6_ONLY) && addr->sa_family != AF_INET6)
    {
        return EV_EINVAL;
    }

    if (udp->sock == EV_OS_SOCKET_INVALID)
    {
        if ((udp->sock = socket(addr->sa_family, SOCK_DGRAM, 0)) == EV_OS_SOCKET_INVALID)
        {
            ret = WSAGetLastError();
            return ev__translate_sys_error(ret);
        }

        ret = _ev_udp_setup_socket_attribute_win(udp->base.loop, udp, addr->sa_family);
        if (ret != 0)
        {
            _ev_udp_close_socket_win(udp);
            return ret;
        }
    }

    if (flags & EV_UDP_REUSEADDR)
    {
        if ((ret = ev__reuse_win(udp->sock, 1)) != 0)
        {
            return ret;
        }
    }

    if (addr->sa_family == AF_INET6)
    {
        udp->base.data.flags |= EV_HANDLE_UDP_IPV6;
        if (flags & EV_UDP_IPV6_ONLY)
        {
            if ((ret = ev__ipv6only_win(udp->sock, 1)) != 0)
            {
                _ev_udp_close_socket_win(udp);
                return ret;
            }
        }
    }

    socklen_t addrlen = ev__get_addr_len(addr);
    if ((ret = bind(udp->sock, addr, addrlen)) == SOCKET_ERROR)
    {
        ret = WSAGetLastError();
        return ev__translate_sys_error(ret);
    }

    udp->base.data.flags |= EV_HANDLE_UDP_BOUND;
    return 0;
}

EV_LOCAL int ev__udp_recv(ev_udp_t* udp, ev_udp_read_t* req)
{
    WSABUF buf;
    buf.buf = g_ev_loop_win_ctx.net.zero_;
    buf.len = 0;

    DWORD bytes = 0;
    DWORD flags = MSG_PEEK;

    req->backend.owner = udp;
    req->backend.stat = EV_EINPROGRESS;
    ev__iocp_init(&req->backend.io, _ev_udp_on_recv_iocp_win, udp);

    ev__handle_active(&udp->base);

    int ret = WSARecv(udp->sock, &buf, 1, &bytes, &flags, &req->backend.io.overlapped, NULL);
    if (ret == 0 && (udp->base.data.flags & EV_HANDLE_UDP_BYPASS_IOCP))
    {
        ev__backlog_submit(&req->handle, _ev_udp_on_recv_bypass_iocp_win);
        return 0;
    }

    int err;
    if (ret == 0 || (err = WSAGetLastError()) == ERROR_IO_PENDING)
    {
        return 0;
    }

    _ev_udp_smart_deactive(udp);
    return ev__translate_sys_error(err);
}

EV_LOCAL int ev__udp_send(ev_udp_t* udp, ev_udp_write_t* req,
    const struct sockaddr* addr, socklen_t addrlen)
{
    int ret, err;

    if (!(udp->base.data.flags & EV_HANDLE_UDP_BOUND))
    {
        if (addr == NULL)
        {
            return EV_EINVAL;
        }

        if ((ret = _ev_udp_maybe_deferred_bind_win(udp, addr->sa_family)) != 0)
        {
            return ret;
        }
    }

    req->backend.owner = udp;
    req->backend.stat = EV_EINPROGRESS;
    ev__iocp_init(&req->backend.io, _ev_udp_on_send_iocp_win, udp);

    DWORD send_bytes;

    ev__handle_active(&udp->base);
    ret = WSASendTo(udp->sock, (WSABUF*)req->base.bufs, (DWORD)req->base.nbuf,
        &send_bytes, 0, addr, addrlen, &req->backend.io.overlapped, NULL);

    if (ret == 0 && (udp->base.data.flags & EV_HANDLE_UDP_BYPASS_IOCP))
    {
        req->base.size += req->base.capacity;
        req->backend.stat = 0;
        ev__backlog_submit(&req->handle, _ev_udp_on_send_bypass_iocp);
        return 0;
    }

    if (ret == 0 || (err = GetLastError()) == ERROR_IO_PENDING)
    {
        req->backend.stat = EV_EINPROGRESS;
        return 0;
    }

    _ev_udp_smart_deactive(udp);
    return ev__translate_sys_error(err);
}

int ev_udp_init(ev_loop_t* loop, ev_udp_t** udp, int domain)
{
    int err;
    ev_udp_t *new_udp = ev_malloc(sizeof(ev_udp_t));
    if (new_udp == NULL)
    {
        return EV_ENOMEM;
    }

    new_udp->sock = EV_OS_SOCKET_INVALID;
    new_udp->close_cb = NULL;
    new_udp->close_arg = NULL;
    ev_list_init(&new_udp->send_list);
    ev_list_init(&new_udp->recv_list);
    ev__handle_init(loop, &new_udp->base, EV_ROLE_EV_UDP);

    new_udp->backend.fn_wsarecv = WSARecv;
    new_udp->backend.fn_wsarecvfrom = WSARecvFrom;

    if (domain != AF_UNSPEC)
    {
        if ((err = _ev_udp_maybe_deferred_socket_win(new_udp, domain)) != 0)
        {
            ev__handle_exit(&new_udp->base, NULL);
            ev_free(new_udp);
            return err;
        }
    }

    *udp = new_udp;
    return 0;
}

void ev_udp_exit(ev_udp_t *udp, ev_udp_cb close_cb, void *close_arg)
{
    udp->close_cb = close_cb;
    udp->close_arg = close_arg;

    _ev_udp_close_socket_win(udp);
    ev__handle_exit(&udp->base, _ev_udp_on_close_win);
}

int ev_udp_open(ev_udp_t* udp, ev_os_socket_t sock)
{
    int ret;
    if (udp->sock != EV_OS_SOCKET_INVALID)
    {
        return EV_EBUSY;
    }

    WSAPROTOCOL_INFOW protocol_info;
    int opt_len = sizeof(protocol_info);
    if (getsockopt(sock, SOL_SOCKET, SO_PROTOCOL_INFOW, (char*)&protocol_info, &opt_len) != 0)
    {
        int err = WSAGetLastError();
        return ev__translate_sys_error(err);
    }

    udp->sock = sock;
    if ((ret = _ev_udp_setup_socket_attribute_win(udp->base.loop, udp,
        protocol_info.iAddressFamily)) != 0)
    {
        udp->sock = EV_OS_SOCKET_INVALID;
        return ret;
    }

    if (_ev_udp_is_bound_win(udp))
    {
        udp->base.data.flags |= EV_HANDLE_UDP_BOUND;
    }

    if (_ev_udp_is_connected_win(udp))
    {
        udp->base.data.flags |= EV_HANDLE_UDP_CONNECTED;
    }

    return 0;
}

int ev_udp_bind(ev_udp_t* udp, const struct sockaddr* addr, unsigned flags)
{
    return _ev_udp_maybe_bind_win(udp, addr, flags);
}

int ev_udp_connect(ev_udp_t* udp, const struct sockaddr* addr)
{
    int ret;
    if (addr == NULL)
    {
        if (!(udp->base.data.flags & EV_HANDLE_UDP_CONNECTED))
        {
            return EV_ENOTCONN;
        }

        return _ev_udp_disconnect_win(udp);
    }

    if (!(udp->base.data.flags & EV_HANDLE_UDP_BOUND))
    {
        struct sockaddr* bind_addr = addr->sa_family == AF_INET ?
            (struct sockaddr*)&ev_addr_ip4_any_ : (struct sockaddr*)&ev_addr_ip6_any_;
        if ((ret = _ev_udp_maybe_bind_win(udp, bind_addr, 0)) != 0)
        {
            return ret;
        }
    }

    socklen_t addrlen = ev__get_addr_len(addr);
    if (addrlen == (socklen_t)-1)
    {
        return EV_EINVAL;
    }

    if ((ret = connect(udp->sock, addr, addrlen)) != 0)
    {
        ret = WSAGetLastError();
        return ev__translate_sys_error(ret);
    }

    return 0;
}

int ev_udp_getsockname(ev_udp_t* udp, struct sockaddr* name, size_t* len)
{
    int wrap_len = (int)*len;
    if (getsockname(udp->sock, name, &wrap_len) != 0)
    {
        int err = WSAGetLastError();
        return ev__translate_sys_error(err);
    }

    *len = wrap_len;
    return 0;
}

int ev_udp_getpeername(ev_udp_t* udp, struct sockaddr* name, size_t* len)
{
    int wrap_len = (int)*len;
    if (getpeername(udp->sock, name, &wrap_len) != 0)
    {
        int err = WSAGetLastError();
        return ev__translate_sys_error(err);
    }

    *len = wrap_len;
    return 0;
}

int ev_udp_set_membership(ev_udp_t* udp, const char* multicast_addr,
    const char* interface_addr, ev_udp_membership_t membership)
{
    int ret;
    struct sockaddr_storage addr;

    if (membership != EV_UDP_LEAVE_GROUP && membership != EV_UDP_ENTER_GROUP)
    {
        return EV_EINVAL;
    }

    if ((ret = ev_ipv4_addr(multicast_addr, 0, (struct sockaddr_in*)&addr)) == 0)
    {
        if (udp->base.data.flags & EV_HANDLE_UDP_IPV6)
        {
            return EV_EINVAL;
        }
        if ((ret = _ev_udp_maybe_deferred_bind_win(udp, AF_INET)) != 0)
        {
            return ret;
        }
        return _ev_udp_set_membership_ipv4_win(udp, (struct sockaddr_in*)&addr,
            interface_addr, membership);
    }

    if ((ret = ev_ipv6_addr(multicast_addr, 0, (struct sockaddr_in6*)&addr)) == 0)
    {
        if ((udp->base.data.flags & EV_HANDLE_UDP_BOUND) && !(udp->base.data.flags & EV_HANDLE_UDP_IPV6))
        {
            return EV_EINVAL;
        }
        if ((ret = _ev_udp_maybe_deferred_bind_win(udp, AF_INET6)) != 0)
        {
            return ret;
        }
        return _ev_udp_set_membership_ipv6_win(udp, (struct sockaddr_in6*)&addr,
            interface_addr, membership);
    }

    return ret;
}

int ev_udp_set_source_membership(ev_udp_t* udp, const char* multicast_addr,
    const char* interface_addr, const char* source_addr, ev_udp_membership_t membership)
{
    int ret;
    struct sockaddr_storage mcast_addr;
    struct sockaddr_storage src_addr;

    if (membership != EV_UDP_LEAVE_GROUP && membership != EV_UDP_ENTER_GROUP)
    {
        return EV_EINVAL;
    }

    if ((ret = ev_ipv4_addr(multicast_addr, 0, (struct sockaddr_in*)&mcast_addr)) == 0)
    {
        if ((ret = ev_ipv4_addr(source_addr, 0, (struct sockaddr_in*)&src_addr)) != 0)
        {
            return ret;
        }
        if (udp->base.data.flags & EV_HANDLE_UDP_IPV6)
        {
            return EV_EINVAL;
        }
        if ((ret = _ev_udp_maybe_deferred_bind_win(udp, AF_INET)) != 0)
        {
            return ret;
        }
        return _ev_udp_set_source_membership_ipv4(udp, (struct sockaddr_in*)&mcast_addr,
            interface_addr, (struct sockaddr_in*)&src_addr, membership);
    }

    if ((ret = ev_ipv6_addr(multicast_addr, 0, (struct sockaddr_in6*)&mcast_addr)) == 0)
    {
        if ((ret = ev_ipv6_addr(source_addr, 0, (struct sockaddr_in6*)&src_addr)) != 0)
        {
            return ret;
        }
        if ((udp->base.data.flags & EV_HANDLE_UDP_BOUND) && !(udp->base.data.flags & EV_HANDLE_UDP_IPV6))
        {
            return EV_EINVAL;
        }
        if ((ret = _ev_udp_maybe_deferred_bind_win(udp, AF_INET6)) != 0)
        {
            return ret;
        }
        return _ev_udp_set_source_membership_ipv6(udp, (struct sockaddr_in6*)&mcast_addr,
            interface_addr, (struct sockaddr_in6*)&src_addr, membership);
    }

    return ret;
}

int ev_udp_set_multicast_loop(ev_udp_t* udp, int on)
{
    DWORD optval = on;
    if (udp->sock == EV_OS_SOCKET_INVALID)
    {
        return EV_EBADF;
    }

    int level = IPPROTO_IP;
    int optname = IP_MULTICAST_LOOP;
    if (udp->base.data.flags & EV_HANDLE_UDP_IPV6)
    {
        level = IPPROTO_IPV6;
        optname = IPV6_MULTICAST_LOOP;
    }

    if (setsockopt(udp->sock, level, optname, (char*)&optval, sizeof(optval)) != 0)
    {
        int ret = WSAGetLastError();
        return ev__translate_sys_error(ret);
    }

    return 0;
}

int ev_udp_set_multicast_ttl(ev_udp_t* udp, int ttl)
{
    DWORD optval = (DWORD)ttl;
    if (ttl < -1 || ttl > 255)
    {
        return EV_EINVAL;
    }
    if (udp->sock == EV_OS_SOCKET_INVALID)
    {
        return EV_EBADF;
    }

    int level = IPPROTO_IP;
    int optname = IP_MULTICAST_TTL;
    if (udp->base.data.flags & EV_HANDLE_UDP_IPV6)
    {
        level = IPPROTO_IPV6;
        optname = IPV6_MULTICAST_HOPS;
    }

    if (setsockopt(udp->sock, level, optname, (char*)&optval, sizeof(optval)) != 0)
    {
        int ret = WSAGetLastError();
        return ev__translate_sys_error(ret);
    }

    return 0;
}

int ev_udp_set_multicast_interface(ev_udp_t* udp, const char* interface_addr)
{
    int ret;
    struct sockaddr_storage addr_st;
    struct sockaddr_in* addr_4 = (struct sockaddr_in*)&addr_st;
    struct sockaddr_in6* addr_6 = (struct sockaddr_in6*)&addr_st;

    if (udp->sock == EV_OS_SOCKET_INVALID)
    {
        return EV_EBADF;
    }

    int is_ipv6 = udp->base.data.flags & EV_HANDLE_UDP_IPV6;
    if ((ret = ev__udp_interface_addr_to_sockaddr(&addr_st, interface_addr, is_ipv6)) != 0)
    {
        return ret;
    }

    int level = IPPROTO_IP;
    int optname = IP_MULTICAST_IF;
    char* optval = (char*)&addr_4->sin_addr;
    int optlen = sizeof(addr_4->sin_addr);
    if (addr_st.ss_family == AF_INET6)
    {
        optval = (char*)&addr_6->sin6_scope_id;
        optlen = sizeof(addr_6->sin6_scope_id);
    }

    if (setsockopt(udp->sock, level, optname, optval, optlen) != 0)
    {
        ret = WSAGetLastError();
        return ev__translate_sys_error(ret);
    }

    return 0;
}

int ev_udp_set_broadcast(ev_udp_t* udp, int on)
{
    BOOL optval = !!on;

    if (udp->sock == EV_OS_SOCKET_INVALID)
    {
        return EV_EBADF;
    }

    if (setsockopt(udp->sock, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(optval)) != 0)
    {
        int err = WSAGetLastError();
        return ev__translate_sys_error(err);
    }

    return 0;
}

int ev_udp_set_ttl(ev_udp_t* udp, int ttl)
{
    DWORD optval = ttl;
    if (optval < 1 || optval > 255)
    {
        return EV_EINVAL;
    }
    if (udp->sock == EV_OS_SOCKET_INVALID)
    {
        return EV_EBADF;
    }

    int level = IPPROTO_IP;
    int optname = IP_TTL;
    if (udp->base.data.flags & EV_HANDLE_UDP_IPV6)
    {
        level = IPPROTO_IPV6;
        optname = IPV6_HOPLIMIT;
    }

    if (setsockopt(udp->sock, level, optname, (char*)&optval, sizeof(optval)) != 0)
    {
        int err = WSAGetLastError();
        return ev__translate_sys_error(err);
    }

    return 0;
}
