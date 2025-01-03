#include "ev.h"
#include "test.h"
#include <string.h>

struct test_3615
{
    ev_loop_t  *s_loop;
    ev_timer_t *s_timer;

    int f_on_timer;
    int f_on_timer_close;
};

struct test_3615 g_test_3615;

static void _on_timer_close(ev_timer_t *timer, void *arg)
{
    (void)timer;
    (void)arg;
    g_test_3615.f_on_timer_close = 1;
}

TEST_FIXTURE_SETUP(timer)
{
    memset(&g_test_3615, 0, sizeof(g_test_3615));
    ASSERT_EQ_INT(ev_loop_init(&g_test_3615.s_loop), 0);
    ASSERT_EQ_INT(ev_timer_init(g_test_3615.s_loop, &g_test_3615.s_timer), 0);
}

TEST_FIXTURE_TEARDOWN(timer)
{
    ev_timer_exit(g_test_3615.s_timer, _on_timer_close, NULL);
    ASSERT_EQ_INT(g_test_3615.f_on_timer_close, 0);
    ASSERT_EQ_INT(ev_loop_run(g_test_3615.s_loop, EV_LOOP_MODE_DEFAULT,
                              EV_INFINITE_TIMEOUT),
                  0);
    ASSERT_EQ_INT(g_test_3615.f_on_timer_close, 1);

    ASSERT_EQ_INT(ev_loop_exit(g_test_3615.s_loop), 0);
}

static void _on_timer(ev_timer_t *timer, void *arg)
{
    (void)arg;
    g_test_3615.f_on_timer = 1;
    ev_timer_stop(timer);
}

TEST_F(timer, normal)
{
    ASSERT_EQ_INT(
        ev_timer_start(g_test_3615.s_timer, 1000, 1000, _on_timer, NULL), 0);
    ASSERT_EQ_INT(g_test_3615.f_on_timer, 0);

    ASSERT_EQ_INT(ev_loop_run(g_test_3615.s_loop, EV_LOOP_MODE_DEFAULT,
                              EV_INFINITE_TIMEOUT),
                  0);
    ASSERT_EQ_INT(g_test_3615.f_on_timer, 1);
}
