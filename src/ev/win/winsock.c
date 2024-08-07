
int ev_tcp_non_ifs_lsp_ipv4;
int ev_tcp_non_ifs_lsp_ipv6;

struct sockaddr_in ev_addr_ip4_any_;
struct sockaddr_in6 ev_addr_ip6_any_;

EV_LOCAL void ev__winsock_init(void)
{
#define DETECT_IFS_LSP(AF, flag)    \
    do {\
        flag = 1;\
        SOCKET dummy = socket(AF, SOCK_STREAM, IPPROTO_IP);\
        if (dummy != INVALID_SOCKET) {\
            break;\
        }\
        WSAPROTOCOL_INFOW protocol_info;\
        int opt_len = sizeof(protocol_info);\
        if (getsockopt(dummy, SOL_SOCKET, SO_PROTOCOL_INFOW, (char*)&protocol_info, &opt_len) == 0) {\
            if (protocol_info.dwServiceFlags1 & XP1_IFS_HANDLES) {\
                flag = 0;\
            }\
        }\
        closesocket(dummy);\
    } while (0)

    int ret; (void)ret;

    /* Set implicit binding address used by connectEx */
    if ((ret = ev_ipv4_addr("0.0.0.0", 0, &ev_addr_ip4_any_)) != 0)
    {
        abort();
    }
    if ((ret = ev_ipv6_addr("::", 0, &ev_addr_ip6_any_)) != 0)
    {
        abort();
    }

    /* Skip initialization in safe mode without network support */
    if (GetSystemMetrics(SM_CLEANBOOT) == 1)
    {
        return;
    }

    /* Initialize winsock */
    {
        WSADATA wsa_data;
        if ((ret = WSAStartup(MAKEWORD(2, 2), &wsa_data)) != 0)
        {
            EV_FATAL_SYSCALL(ret, "WSAStartup");
        }
    }
    
    /* Try to detect non-IFS LSPs */
    DETECT_IFS_LSP(AF_INET, ev_tcp_non_ifs_lsp_ipv4);
    /* Try to detect IPV6 support and non-IFS LSPs */
    DETECT_IFS_LSP(AF_INET6, ev_tcp_non_ifs_lsp_ipv6);

#undef DETECT_IFS_LSP
}

EV_LOCAL int WSAAPI ev__wsa_recv_workaround(SOCKET socket, WSABUF* buffers,
    DWORD buffer_count, DWORD* bytes, DWORD* flags, WSAOVERLAPPED* overlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE completion_routine)
{
    NTSTATUS status;
    void* apc_context;
    IO_STATUS_BLOCK* iosb = (IO_STATUS_BLOCK*)&overlapped->Internal;
    AFD_RECV_INFO info;
    DWORD error;

    if (overlapped == NULL || completion_routine != NULL) {
        WSASetLastError(WSAEINVAL);
        return SOCKET_ERROR;
    }

    info.BufferArray = buffers;
    info.BufferCount = buffer_count;
    info.AfdFlags = AFD_OVERLAPPED;
    info.TdiFlags = TDI_RECEIVE_NORMAL;

    if (*flags & MSG_PEEK) {
        info.TdiFlags |= TDI_RECEIVE_PEEK;
    }

    if (*flags & MSG_PARTIAL) {
        info.TdiFlags |= TDI_RECEIVE_PARTIAL;
    }

    if (!((intptr_t)overlapped->hEvent & 1)) {
        apc_context = (void*)overlapped;
    }
    else {
        apc_context = NULL;
    }

    iosb->Status = STATUS_PENDING;
    iosb->Pointer = 0;

    status = ev_winapi.NtDeviceIoControlFile((HANDLE)socket,
        overlapped->hEvent,
        NULL,
        apc_context,
        iosb,
        IOCTL_AFD_RECEIVE,
        &info,
        sizeof(info),
        NULL,
        0);

    *flags = 0;
    *bytes = (DWORD)iosb->Information;

    switch (status) {
    case STATUS_SUCCESS:
        error = ERROR_SUCCESS;
        break;

    case STATUS_PENDING:
        error = WSA_IO_PENDING;
        break;

    case STATUS_BUFFER_OVERFLOW:
        error = WSAEMSGSIZE;
        break;

    case STATUS_RECEIVE_EXPEDITED:
        error = ERROR_SUCCESS;
        *flags = MSG_OOB;
        break;

    case STATUS_RECEIVE_PARTIAL_EXPEDITED:
        error = ERROR_SUCCESS;
        *flags = MSG_PARTIAL | MSG_OOB;
        break;

    case STATUS_RECEIVE_PARTIAL:
        error = ERROR_SUCCESS;
        *flags = MSG_PARTIAL;
        break;

    default:
        error = ev__ntstatus_to_winsock_error(status);
        break;
    }

    WSASetLastError(error);

    if (error == ERROR_SUCCESS)
    {
        return 0;
    }

    return SOCKET_ERROR;
}

EV_LOCAL int WSAAPI ev__wsa_recvfrom_workaround(SOCKET socket, WSABUF* buffers,
    DWORD buffer_count, DWORD* bytes, DWORD* flags, struct sockaddr* addr,
    int* addr_len, WSAOVERLAPPED* overlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE completion_routine)
{
    NTSTATUS status;
    void* apc_context;
    IO_STATUS_BLOCK* iosb = (IO_STATUS_BLOCK*)&overlapped->Internal;
    AFD_RECV_DATAGRAM_INFO info;
    DWORD error;

    if (overlapped == NULL || addr == NULL || addr_len == NULL ||
        completion_routine != NULL)
    {
        WSASetLastError(WSAEINVAL);
        return SOCKET_ERROR;
    }

    info.BufferArray = buffers;
    info.BufferCount = buffer_count;
    info.AfdFlags = AFD_OVERLAPPED;
    info.TdiFlags = TDI_RECEIVE_NORMAL;
    info.Address = addr;
    info.AddressLength = addr_len;

    if (*flags & MSG_PEEK) {
        info.TdiFlags |= TDI_RECEIVE_PEEK;
    }

    if (*flags & MSG_PARTIAL) {
        info.TdiFlags |= TDI_RECEIVE_PARTIAL;
    }

    if (!((intptr_t)overlapped->hEvent & 1)) {
        apc_context = (void*)overlapped;
    }
    else {
        apc_context = NULL;
    }

    iosb->Status = STATUS_PENDING;
    iosb->Pointer = 0;

    status = ev_winapi.NtDeviceIoControlFile((HANDLE)socket,
        overlapped->hEvent,
        NULL,
        apc_context,
        iosb,
        IOCTL_AFD_RECEIVE_DATAGRAM,
        &info,
        sizeof(info),
        NULL,
        0);

    *flags = 0;
    *bytes = (DWORD)iosb->Information;

    switch (status)
    {
    case STATUS_SUCCESS:
        error = ERROR_SUCCESS;
        break;

    case STATUS_PENDING:
        error = WSA_IO_PENDING;
        break;

    case STATUS_BUFFER_OVERFLOW:
        error = WSAEMSGSIZE;
        break;

    case STATUS_RECEIVE_EXPEDITED:
        error = ERROR_SUCCESS;
        *flags = MSG_OOB;
        break;

    case STATUS_RECEIVE_PARTIAL_EXPEDITED:
        error = ERROR_SUCCESS;
        *flags = MSG_PARTIAL | MSG_OOB;
        break;

    case STATUS_RECEIVE_PARTIAL:
        error = ERROR_SUCCESS;
        *flags = MSG_PARTIAL;
        break;

    default:
        error = ev__ntstatus_to_winsock_error(status);
        break;
    }

    WSASetLastError(error);

    if (error == ERROR_SUCCESS) {
        return 0;
    }

    return SOCKET_ERROR;
}

EV_LOCAL int ev__ntstatus_to_winsock_error(NTSTATUS status)
{
    switch (status)
    {
    case STATUS_SUCCESS:
        return ERROR_SUCCESS;

    case STATUS_PENDING:
        return ERROR_IO_PENDING;

    case STATUS_INVALID_HANDLE:
    case STATUS_OBJECT_TYPE_MISMATCH:
        return WSAENOTSOCK;

    case STATUS_INSUFFICIENT_RESOURCES:
    case STATUS_PAGEFILE_QUOTA:
    case STATUS_COMMITMENT_LIMIT:
    case STATUS_WORKING_SET_QUOTA:
    case STATUS_NO_MEMORY:
    case STATUS_QUOTA_EXCEEDED:
    case STATUS_TOO_MANY_PAGING_FILES:
    case STATUS_REMOTE_RESOURCES:
        return WSAENOBUFS;

    case STATUS_TOO_MANY_ADDRESSES:
    case STATUS_SHARING_VIOLATION:
    case STATUS_ADDRESS_ALREADY_EXISTS:
        return WSAEADDRINUSE;

    case STATUS_LINK_TIMEOUT:
    case STATUS_IO_TIMEOUT:
    case STATUS_TIMEOUT:
        return WSAETIMEDOUT;

    case STATUS_GRACEFUL_DISCONNECT:
        return WSAEDISCON;

    case STATUS_REMOTE_DISCONNECT:
    case STATUS_CONNECTION_RESET:
    case STATUS_LINK_FAILED:
    case STATUS_CONNECTION_DISCONNECTED:
    case STATUS_PORT_UNREACHABLE:
    case STATUS_HOPLIMIT_EXCEEDED:
        return WSAECONNRESET;

    case STATUS_LOCAL_DISCONNECT:
    case STATUS_TRANSACTION_ABORTED:
    case STATUS_CONNECTION_ABORTED:
        return WSAECONNABORTED;

    case STATUS_BAD_NETWORK_PATH:
    case STATUS_NETWORK_UNREACHABLE:
    case STATUS_PROTOCOL_UNREACHABLE:
        return WSAENETUNREACH;

    case STATUS_HOST_UNREACHABLE:
        return WSAEHOSTUNREACH;

    case STATUS_CANCELLED:
    case STATUS_REQUEST_ABORTED:
        return WSAEINTR;

    case STATUS_BUFFER_OVERFLOW:
    case STATUS_INVALID_BUFFER_SIZE:
        return WSAEMSGSIZE;

    case STATUS_BUFFER_TOO_SMALL:
    case STATUS_ACCESS_VIOLATION:
        return WSAEFAULT;

    case STATUS_DEVICE_NOT_READY:
    case STATUS_REQUEST_NOT_ACCEPTED:
        return WSAEWOULDBLOCK;

    case STATUS_INVALID_NETWORK_RESPONSE:
    case STATUS_NETWORK_BUSY:
    case STATUS_NO_SUCH_DEVICE:
    case STATUS_NO_SUCH_FILE:
    case STATUS_OBJECT_PATH_NOT_FOUND:
    case STATUS_OBJECT_NAME_NOT_FOUND:
    case STATUS_UNEXPECTED_NETWORK_ERROR:
        return WSAENETDOWN;

    case STATUS_INVALID_CONNECTION:
        return WSAENOTCONN;

    case STATUS_REMOTE_NOT_LISTENING:
    case STATUS_CONNECTION_REFUSED:
        return WSAECONNREFUSED;

    case STATUS_PIPE_DISCONNECTED:
        return WSAESHUTDOWN;

    case STATUS_CONFLICTING_ADDRESSES:
    case STATUS_INVALID_ADDRESS:
    case STATUS_INVALID_ADDRESS_COMPONENT:
        return WSAEADDRNOTAVAIL;

    case STATUS_NOT_SUPPORTED:
    case STATUS_NOT_IMPLEMENTED:
        return WSAEOPNOTSUPP;

    case STATUS_ACCESS_DENIED:
        return WSAEACCES;

    default:
        if ((status & (FACILITY_NTWIN32 << 16)) == (FACILITY_NTWIN32 << 16) &&
            (status & (ERROR_SEVERITY_ERROR | ERROR_SEVERITY_WARNING)))
        {
            /*
             * It's a windows error that has been previously mapped to an ntstatus
             * code.
             */
            return (DWORD)(status & 0xffff);
        }
        else
        {
            /* The default fallback for unmappable ntstatus codes. */
            return WSAEINVAL;
        }
    }
}
