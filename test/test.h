#ifndef __TEST_H__
#define __TEST_H__

#if defined(_WIN32)
#define strdup(s) _strdup(s)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include "ev.h"
#include "cutest.h"
#include "type/__init__.h"
#include "utils/file.h"
#include "utils/memcheck.h"
#if defined(_MSC_VER)
#include <windows.h>
#else
#include <pthread.h>
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(__CYGWIN__)
#if defined(TEST_BUILDING_DLL)
#if defined(__GNUC__) || defined(__clang__)
#define TEST_EXPOSE_API __attribute__((dllexport))
#else
#define TEST_EXPOSE_API __declspec(dllexport)
#endif
#else
#if defined(__GNUC__) || defined(__clang__)
#define TEST_EXPOSE_API __attribute__((dllimport))
#else
#define TEST_EXPOSE_API __declspec(dllimport)
#endif
#endif
#elif (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
#define TEST_EXPOSE_API __attribute__((visibility("default")))
#else
#define TEST_EXPOSE_API
#endif

/**
 * @brief #TEST_F() with timeout
 */
#define TEST_T(fixture_name, case_name, timeout)                               \
    static void TEST_##fixture_name##_##case_name##_timeout(void);             \
    TEST_F(fixture_name, case_name)                                            \
    {                                                                          \
        const uint64_t       timeout_ms = (timeout);                           \
        test_execute_token_t token;                                            \
        ASSERT_EQ_INT(                                                         \
            test_thread_execute(&token,                                        \
                                TEST_##fixture_name##_##case_name##_timeout),  \
            0);                                                                \
        cutest_porting_timespec_t t_start, t_current;                          \
        cutest_porting_clock_gettime(&t_start);                                \
        int ret;                                                               \
        while ((ret = test_thread_wait(&token)) == EV_ETIMEDOUT)               \
        {                                                                      \
            cutest_porting_clock_gettime(&t_current);                          \
            uint64_t spend_time_ms =                                           \
                (t_current.tv_sec - t_start.tv_sec) * 1000 +                   \
                (t_current.tv_nsec - t_start.tv_nsec) / 1000000;               \
            ASSERT_LE_UINT64(spend_time_ms, timeout_ms);                       \
            ev_thread_sleep(1);                                                \
        }                                                                      \
        ASSERT_EQ_INT(ret, 0, "task not finished");                            \
    }                                                                          \
    static void TEST_##fixture_name##_##case_name##_timeout(void)

#ifndef ALIGN_ADDR
#define ALIGN_ADDR(addr, align)                                                \
    (((uintptr_t)(addr) + ((uintptr_t)(align) - 1)) & ~((uintptr_t)(align) - 1))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

#define TEST_PRINT(fmt, ...)                                                   \
    printf("[%s:%d] " fmt "\n", cutest_pretty_file(__FILE__), __LINE__,        \
           ##__VA_ARGS__)

typedef void (*fn_execute)(void);

typedef struct test_execute_token
{
    ev_thread_t *thr;
} test_execute_token_t;

/**
 * @brief Hook for tests.
 */
TEST_EXPOSE_API extern cutest_hook_t test_hook;

int test_thread_execute(test_execute_token_t *token, fn_execute callback);

/**
 * @return EV_SUCCESS / EV_ETIMEDOUT
 */
int test_thread_wait(test_execute_token_t *token);

const char *test_strerror(int errcode);

void test_abort(const char *fmt, ...);

#ifdef __cplusplus
}
#endif
#endif
