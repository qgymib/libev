#include "udp-common.h"
#include <string.h>

int ev__udp_interface_addr_to_sockaddr(struct sockaddr_storage* dst,
    const char* interface_addr, int is_ipv6)
{
    struct sockaddr_in* addr_4 = (struct sockaddr_in*)dst;
    struct sockaddr_in6* addr_6 = (struct sockaddr_in6*)dst;

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
    else if (ev_ipv4_addr(interface_addr, 0, addr_4) == EV_SUCCESS)
    {
        /* do nothing, address was parsed */
    }
    else if (ev_ipv6_addr(interface_addr, 0, addr_6) == EV_SUCCESS)
    {
        /* do nothing, address was parsed */
    }
    else
    {
        return EV_EINVAL;
    }

    return EV_SUCCESS;
}