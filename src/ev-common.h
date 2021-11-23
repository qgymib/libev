#ifndef __EV_COMMON_INTERNAL_H__
#define __EV_COMMON_INTERNAL_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <assert.h>
#include "ev.h"
#include "ev-platform.h"

#if defined(__GNUC__) || defined(__clang__)
#   define container_of(ptr, type, member) \
        ({ \
            const typeof(((type *)0)->member)*__mptr = (ptr); \
            (type *)((char *)__mptr - offsetof(type, member)); \
        })
#else
#   define container_of(ptr, type, member) \
        ((type *) ((char *) (ptr) - offsetof(type, member)))
#endif

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

#if defined(_MSC_VER)
#   define BREAK_ABORT()        __debugbreak()
#elif (defined(__clang__) || defined(__GNUC__)) && (defined(__x86_64__) || defined(__i386__))
#   define BREAK_ABORT()        __asm__ volatile("int $0x03")
#elif (defined(__clang__) || defined(__GNUC__)) && defined(__thumb__)
#   define BREAK_ABORT()        __asm__ volatile(".inst 0xde01")
#elif (defined(__clang__) || defined(__GNUC__)) && defined(__arm__) && !defined(__thumb__)
#   define BREAK_ABORT()        __asm__ volatile(".inst 0xe7f001f0")
#elif (defined(__clang__) || defined(__GNUC__)) && defined(__aarch64__) && defined(__APPLE__)
#   define BREAK_ABORT()        __builtin_debugtrap()
#elif (defined(__clang__) || defined(__GNUC__)) && defined(__aarch64__)
#   define BREAK_ABORT()        __asm__ volatile(".inst 0xd4200000")
#elif (defined(__clang__) || defined(__GNUC__)) && defined(__powerpc__)
#   define BREAK_ABORT()        __asm__ volatile(".4byte 0x7d821008")
#elif (defined(__clang__) || defined(__GNUC__)) && defined(__riscv)
#   define BREAK_ABORT()        __asm__ volatile(".4byte 0x00100073")
#else
#   define BREAK_ABORT()        *(volatile int*)NULL = 1
#endif

#define ENSURE_LAYOUT(TYPE_A, TYPE_B, FIELD_A_1, FIELD_B_1, FIELD_A_2, FIELD_B_2)   \
    assert(sizeof(TYPE_A) == sizeof(TYPE_B));\
    assert(offsetof(TYPE_A, FIELD_A_1) == offsetof(TYPE_B, FIELD_B_1));\
    assert(sizeof(((TYPE_A*)0)->FIELD_A_1) == sizeof(((TYPE_B*)0)->FIELD_B_1));\
    assert(offsetof(TYPE_A, FIELD_A_2) == offsetof(TYPE_B, FIELD_B_2));\
    assert(sizeof(((TYPE_A*)0)->FIELD_A_2) == sizeof(((TYPE_B*)0)->FIELD_B_2))

typedef enum ev_handle_flag
{
    /* Used by all handles. Bit 0-7. */
    EV_HANDLE_CLOSING       = 0x01 << 0x00,     /**< 1. Handle is going to close */
    EV_HANDLE_CLOSED        = 0x01 << 0x01,     /**< 2. Handle is closed */
    EV_HANDLE_ACTIVE        = 0x01 << 0x02,     /**< 4. Handle is busy */

    /* EV_ROLE_TCP */
    EV_TCP_LISTING          = 0x01 << 0x08,     /**< 256. This is a listen socket and is listening */
    EV_TCP_ACCEPTING        = 0x01 << 0x09,     /**< 512. This is a socket waiting for accept */
    EV_TCP_STREAMING        = 0x01 << 0x0A,     /**< 1024. This is a socket waiting for read or write */
    EV_TCP_CONNECTING       = 0x01 << 0x0B,     /**< 2048. This is a connect and waiting for connect complete */
    EV_TCP_BOUND            = 0x01 << 0x0C,     /**< 4096. Socket is bond to address */

    /* EV_ROLE_PIPE */
    EV_PIPE_STREAMING       = 0x01 << 0x08,     /**< 256. This pipe is initialized by #ev_stream_t */
}ev_handle_flag_t;

/**
 * @brief Initialize a handle
 * @param[in] loop      The loop own the handle
 * @param[out] handle   A pointer to the structure
 * @param[in] role      Who we are
 * @param[in] close_cb  A callback when handle is closed
 */
API_LOCAL void ev__handle_init(ev_loop_t* loop, ev_handle_t* handle, ev_role_t role, ev_close_cb close_cb);

/**
 * @brief Close the handle
 * @note The handle will not closed until close_cb was called, which was given
 *   by #ev__handle_init()
 * @param[in] handle    handler
 */
API_LOCAL void ev__handle_exit(ev_handle_t* handle);

/**
 * @brief Set handle as active
 * @param[in] handle    handler
 */
API_LOCAL void ev__handle_active(ev_handle_t* handle);

/**
 * @brief Set handle as inactive
 * @param[in] handle    handler
 */
API_LOCAL void ev__handle_deactive(ev_handle_t* handle);

/**
 * @brief Check if the handle is in active state
 * @param[in] handle    handler
 * @return              bool
 */
API_LOCAL int ev__handle_is_active(ev_handle_t* handle);

/**
 * @brief Check if the handle is in closing or closed state
 * @param[in] handle    handler
 * @return              bool
 */
API_LOCAL int ev__handle_is_closing(ev_handle_t* handle);

/**
 * @brief Initialize todo token
 * @param[out] token    Todo token
 */
API_LOCAL void ev__todo_init(ev_todo_t* token);

/**
 * @brief Add a pending task
 * @param[in] loop      Event loop
 * @param[in] token     A pointer to the pending token
 * @param[in] cb        A callback when the pending task is active
 */
API_LOCAL void ev__todo_queue(ev_loop_t* loop, ev_todo_t* token, ev_todo_cb cb);

/**
 * @brief Cancel a pending task
 * @param[in] loop      Event loop
 * @param[in] token     A pending token
 */
API_LOCAL void ev__todo_cancel(ev_loop_t* loop, ev_todo_t* token);

#ifdef __cplusplus
}
#endif
#endif
