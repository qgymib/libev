#include "ev.h"
#include "test.h"

struct test_a850
{
    ev_loop_t       s_loop;
};

struct test_a850    g_test_a850;

TEST_FIXTURE_SETUP(loop)
{
    ASSERT_EQ_D32(ev_loop_init(&g_test_a850.s_loop), 0);
}

TEST_FIXTURE_TEAREDOWN(loop)
{
    ASSERT_EQ_D32(ev_loop_run(&g_test_a850.s_loop, EV_LOOP_MODE_DEFAULT), 0);
    ASSERT_EQ_D32(ev_loop_exit(&g_test_a850.s_loop), 0);
}

TEST_T(loop, empty, 1000)
{
    ASSERT_EQ_D32(ev_loop_run(&g_test_a850.s_loop, EV_LOOP_MODE_DEFAULT), 0);
}
