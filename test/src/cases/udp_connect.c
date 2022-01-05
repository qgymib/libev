#include "test.h"
#include "utils/random.h"
#include <string.h>

struct test_5295
{
    ev_loop_t       loop;           /**< Event loop */
    ev_udp_t        client;         /**< Client UDP socket */
    ev_udp_t        server;         /**< Server UDP socket */

    ev_udp_write_t  w_req;
    ev_udp_read_t   r_req;

    uint8_t         w_buf[1024];
    uint8_t         r_buf[2048];
};

struct test_5295    g_test_5295;

TEST_FIXTURE_SETUP(udp)
{
    memset(&g_test_5295, 0, sizeof(g_test_5295));
    test_random(&g_test_5295.w_buf, sizeof(g_test_5295.w_buf));

    ASSERT_EQ_D32(ev_loop_init(&g_test_5295.loop), 0);
    ASSERT_EQ_D32(ev_udp_init(&g_test_5295.loop, &g_test_5295.client, AF_INET), 0);
    ASSERT_EQ_D32(ev_udp_init(&g_test_5295.loop, &g_test_5295.server, AF_INET), 0);
}

TEST_FIXTURE_TEAREDOWN(udp)
{
    ev_udp_exit(&g_test_5295.client, NULL);
    ev_udp_exit(&g_test_5295.server, NULL);

    ASSERT_EQ_D32(ev_loop_run(&g_test_5295.loop, EV_LOOP_MODE_DEFAULT), 0);
    ASSERT_EQ_D32(ev_loop_exit(&g_test_5295.loop), 0);
}

static void _on_test_write_done_5295(ev_write_t* req, size_t size, int stat)
{
    ASSERT_EQ_PTR(&g_test_5295.w_req.req, req);
    ASSERT_EQ_SIZE(size, sizeof(g_test_5295.w_buf));
    ASSERT_EQ_D32(stat, EV_SUCCESS);
}

static void _on_test_read_done_5295(ev_read_t* req, size_t size, int stat)
{
    ASSERT_EQ_PTR(req, &g_test_5295.r_req.req);
    ASSERT_EQ_SIZE(size, sizeof(g_test_5295.w_buf));
    ASSERT_EQ_D32(stat, EV_SUCCESS);

    ASSERT_EQ_D32(memcmp(g_test_5295.w_buf, g_test_5295.r_buf, size), 0);
}

TEST_F(udp, connect)
{
    /* Bind to an available address */
    struct sockaddr_in bind_addr;
    ASSERT_EQ_D32(ev_ipv4_addr("0.0.0.0", 0, &bind_addr), 0);
    ASSERT_EQ_D32(ev_udp_bind(&g_test_5295.server, (struct sockaddr*)&bind_addr, 0), 0);

    /* Get bind address */
    size_t namelen = sizeof(bind_addr);
    ASSERT_EQ_D32(ev_udp_getsockname(&g_test_5295.server, (struct sockaddr*)&bind_addr, &namelen), 0);
    int port = 0;
    ASSERT_EQ_D32(ev_ipv4_name(&bind_addr, &port, NULL, 0), 0);

    /* Connect to address */
    ASSERT_EQ_D32(ev_ipv4_addr("127.0.0.1", port, &bind_addr), 0);
    ASSERT_EQ_D32(ev_udp_connect(&g_test_5295.client, (struct sockaddr*)&bind_addr), 0);

    /* Send data */
    {
        ev_buf_t buf = ev_buf_make(g_test_5295.w_buf, sizeof(g_test_5295.w_buf));
        ASSERT_EQ_D32(ev_udp_send(&g_test_5295.client, &g_test_5295.w_req, &buf, 1,
            NULL, _on_test_write_done_5295), 0);
    }

    /* Recv data */
    {
        ev_buf_t buf = ev_buf_make(&g_test_5295.r_buf, sizeof(g_test_5295.r_buf));
        ASSERT_EQ_D32(ev_udp_recv(&g_test_5295.server, &g_test_5295.r_req, &buf, 1,
            _on_test_read_done_5295), 0);
    }

    ASSERT_EQ_D32(ev_loop_run(&g_test_5295.loop, EV_LOOP_MODE_DEFAULT), 0);
}