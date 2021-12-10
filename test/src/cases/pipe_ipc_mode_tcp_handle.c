#include "ev.h"
#include "test.h"
#include "utils/sockpair.h"
#include "utils/random.h"
#include <string.h>

struct test_19f1
{
    ev_loop_t       loop;   /**< Runtime loop */

    ev_pipe_t       s_pipe; /**< Server pipe */
    ev_pipe_t       c_pipe; /**< Client pipe */

    ev_tcp_t        s_tcp;  /**< Session, will be transfer to peer */
    ev_tcp_t        c_tcp;  /**< Client */
    ev_tcp_t        d_tcp;  /**< Peer socket to receive handle */

    ev_write_t      w_req;  /**< Write request */
    ev_read_t       r_req;  /**< Read request */

    unsigned        cnt_wcb;
    unsigned        cnt_rcb;

    char            data1[1024];
    char            data2[1024];
};

struct test_19f1    g_test_19f1;

TEST_FIXTURE_SETUP(pipe)
{
    memset(&g_test_19f1, 0, sizeof(g_test_19f1));

    test_random(g_test_19f1.data1, sizeof(g_test_19f1.data1));
    ASSERT_EQ_D32(ev_loop_init(&g_test_19f1.loop), EV_SUCCESS);

    ASSERT_EQ_D32(ev_pipe_init(&g_test_19f1.loop, &g_test_19f1.s_pipe, 1), EV_SUCCESS);
    ASSERT_EQ_D32(ev_pipe_init(&g_test_19f1.loop, &g_test_19f1.c_pipe, 1), EV_SUCCESS);

    ev_os_pipe_t fds[2] = { EV_OS_PIPE_INVALID, EV_OS_PIPE_INVALID };
    ASSERT_EQ_D32(ev_pipe_make(fds), 0);

    ASSERT_EQ_D32(ev_pipe_open(&g_test_19f1.s_pipe, fds[0]), 0);
    ASSERT_EQ_D32(ev_pipe_open(&g_test_19f1.c_pipe, fds[1]), 0);

    ASSERT_EQ_D32(ev_tcp_init(&g_test_19f1.loop, &g_test_19f1.s_tcp), EV_SUCCESS);
    ASSERT_EQ_D32(ev_tcp_init(&g_test_19f1.loop, &g_test_19f1.c_tcp), EV_SUCCESS);
    test_sockpair(&g_test_19f1.loop, &g_test_19f1.s_tcp, &g_test_19f1.c_tcp);
    ASSERT_EQ_D32(ev_tcp_init(&g_test_19f1.loop, &g_test_19f1.d_tcp), EV_SUCCESS);
}

TEST_FIXTURE_TEAREDOWN(pipe)
{
    ev_pipe_exit(&g_test_19f1.s_pipe, NULL);
    ev_pipe_exit(&g_test_19f1.c_pipe, NULL);
    ev_tcp_exit(&g_test_19f1.s_tcp, NULL);
    ev_tcp_exit(&g_test_19f1.c_tcp, NULL);
    ev_tcp_exit(&g_test_19f1.d_tcp, NULL);
    ASSERT_EQ_D32(ev_loop_run(&g_test_19f1.loop, EV_LOOP_MODE_DEFAULT), 0);
    ASSERT_EQ_D32(ev_loop_exit(&g_test_19f1.loop), 0);
}

static void _on_pipe_write_done(ev_write_t* req, size_t size, int stat)
{
    ASSERT_EQ_PTR(req, &g_test_19f1.w_req);
    ASSERT_EQ_D32(stat, EV_SUCCESS);
    ASSERT_EQ_SIZE(size, sizeof(g_test_19f1.data1));

    g_test_19f1.cnt_wcb++;
}

static void _on_pipe_read_done(ev_read_t* req, size_t size, int stat)
{
    (void)size;
    ASSERT_EQ_PTR(req, &g_test_19f1.r_req);
    ASSERT_EQ_D32(stat, EV_SUCCESS);

    g_test_19f1.cnt_rcb++;
}

TEST_F(pipe, ipc_mode_tcp_handle)
{
    ev_buf_t buf;

    /* send data and handle */
    buf = ev_buf_make(g_test_19f1.data1, sizeof(g_test_19f1.data1));
    ASSERT_EQ_D32(ev_write_init_ext(&g_test_19f1.w_req, _on_pipe_write_done,
        &buf, 1, NULL, 0, EV_ROLE_EV_TCP, &g_test_19f1.s_tcp, sizeof(g_test_19f1.s_tcp)), 0);
    ASSERT_EQ_D32(ev_pipe_write(&g_test_19f1.s_pipe, &g_test_19f1.w_req), 0);

    /* recv data and handle */
    buf = ev_buf_make(g_test_19f1.data2, sizeof(g_test_19f1.data2));
    ASSERT_EQ_D32(ev_read_init(&g_test_19f1.r_req, &buf, 1, _on_pipe_read_done), 0);
    ASSERT_EQ_D32(ev_pipe_read(&g_test_19f1.c_pipe, &g_test_19f1.r_req), 0);

    /* communicate */
    ASSERT_EQ_D32(ev_loop_run(&g_test_19f1.loop, EV_LOOP_MODE_DEFAULT), 0);
    ASSERT_EQ_U32(g_test_19f1.cnt_wcb, 1);
    ASSERT_EQ_U32(g_test_19f1.cnt_rcb, 1);

    /* accept handle */
    ASSERT_EQ_D32(ev_pipe_accept(&g_test_19f1.c_pipe, &g_test_19f1.r_req,
        EV_ROLE_EV_TCP, &g_test_19f1.d_tcp, sizeof(g_test_19f1.d_tcp)), 0);

    /* now we are able to send data via d_tcp */
    buf = ev_buf_make(g_test_19f1.data1, sizeof(g_test_19f1.data1));
    ASSERT_EQ_D32(ev_write_init(&g_test_19f1.w_req, &buf, 1, _on_pipe_write_done), 0);
    ASSERT_EQ_D32(ev_tcp_write(&g_test_19f1.d_tcp, &g_test_19f1.w_req), 0);

    buf = ev_buf_make(g_test_19f1.data2, sizeof(g_test_19f1.data2));
    ASSERT_EQ_D32(ev_read_init(&g_test_19f1.r_req, &buf, 1, _on_pipe_read_done), 0);
    ASSERT_EQ_D32(ev_tcp_read(&g_test_19f1.c_tcp, &g_test_19f1.r_req), 0);

    /* communicate */
    ASSERT_EQ_D32(ev_loop_run(&g_test_19f1.loop, EV_LOOP_MODE_DEFAULT), 0);
    ASSERT_EQ_U32(g_test_19f1.cnt_wcb, 2);
    ASSERT_EQ_U32(g_test_19f1.cnt_rcb, 2);
}