/**
 * MIT License
 * 
 * Copyright (c) 2021 qgymib
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

/**
 * # Changelog
 * 
 * ## v1.0.0 (2024/11/25)
 * 
 * ### Features
 * 1. Support `ev_random()`.
 * 2. Add timeout parameter for `ev_loop_run()`.
 * 2. Add subset of atomic support.
 * 
 * ### Bug Fixes
 * 1. Fix build error when integrate into visual studio unicode build tree.
 * 
 * 
 * ## v0.1.1 (2024/09/19)
 * 
 * ### BREAKING CHANGES
 * 1. merge `ev_file_init()` with `ev_file_open()`.
 * 2. rename `ev_file_exit()` to `ev_file_close()`.
 * 3. merge `ev_file_read_sync()` with `ev_file_read()`.
 * 4. merge `ev_file_pread_sync()` with `ev_file_pread()`.
 * 5. merge `ev_file_write_sync()` with `ev_file_write()`.
 * 6. merge `ev_file_pwrite_sync()` with `ev_file_pwrite()`.
 * 7. merge `ev_file_stat_sync()` with `ev_file_stat()`.
 * 8. merge `ev_fs_mkdir_sync()` with `ev_fs_mkdir()`.
 * 9. merge `ev_fs_remove_sync()` with `ev_fs_remove()`.
 * 10. `ev_file_seek()` now return the resulting offset location as measured in bytes from the beginning of the file.
 * 11. rename `ev_file_pread()` to `ev_file_preadv()`.
 * 12. rename `ev_file_read()` to `ev_file_readv()`.
 * 13. rename `ev_file_pwrite()` to `ev_file_pwritev()`.
 * 14. rename `ev_file_write()` to `ev_file_writev()`.
 * 
 * ### Features
 * 1. `ev_fs_readdir()` is able to operator in synchronous mode.
 * 2. `ev_fs_readfile()` is able to operator in synchronous mode.
 * 3. `ev_file_seek()` is able to operator in synchronous mode.
 * 4. support normal `ev_file_read()` and `ev_file_write()`.
 * 5. support `ev_file_pread()` and `ev_file_pwrite()`.
 * 6. support file mapping.
 * 7. support get system page size.
 * 
 * ### Bug Fixes
 * 1. `ev_hrtime()` no longer require initialize event loop first.
 * 2. can not open file in windows if path contains CJK characters.
 * 3. Use `ev_fs_readfile()` in synchronous mode may crash in windows.
 * 4. `ev_fs_mkdir()` should not fail if already exist in windows.
 * 
 * ## v0.1.0 (2024/08/06)
 * 
 * ### BREAKING CHANGES
 * 1. `ev_hrtime()` now return time in nanoseconds.
 * 
 * ### Features
 * 1. support handle shared library.
 * 
 * ### Bug Fixes
 * 1. only define `dllimport` when `EV_USE_DLL` is defined
 * 
 * 
 * ## v0.0.9 (2024/07/29)
 * 
 * ### BREAKING CHANGES
 * 1. `ev_map_insert()` now return conflict node address
 * 2. remove `active_events` field
 * 
 * ### Bug Fixes
 * 1. fix: loop may wait infinite with EV_LOOP_MODE_ONCE if there are only endgame events
 * 2. fix: memory leak in create process
 * 3. fix: thread leak when process exit
 * 4. fix: wrong format charster in test
 * 
 * 
 * ## v0.0.8 (2023/04/07)
 * 
 * ### BREAKING CHANGES
 * 1. remove `ev_todo_token_t`
 * 2. `ev_process_t` must be exited manually
 * 3. rename position read and write to `pread` and `pwrite`
 * 4. embed default thread pool
 * 5. change thread pool functions
 * 6. expose peeraddr in udp recv callback
 * 7. reduce parameter in udp send callback
 * 
 * ### Features
 * 1. add detail information for `ev_fs_readfile()`
 * 2. use `ev_library_shutdown()` to cleanup global resources
 * 3. use `ev_loop_walk()` to walk through all handles
 * 4. process: support change cwd
 * 5. add amalgamate support
 * 6. submit threadpool task by loop api
 * 7. update test framework to v3.0.0
 * 8. use `ev_hrtime()` to get high-resolution time
 * 9. support normal file read / write / seek operations
 * 10. support remove file and directory
 * 11. expose memory allocate functions
 * 12. redone error number
 * 13. smart convert addr and name
 * 
 * ### Bug Fixes
 * 1. fix: use uninitialised value in `ev_exepath()` on Unix
 * 2. fix: thread pool not unlink when exit loop
 * 3. fix: `ev_process_spawn()` coredump on windows when redirect file
 * 
 * 
 * ## v0.0.7 (2022/06/07)
 * 
 * ### Features
 * 1. Support `ev_getcwd()`
 * 2. Support `ev_exepath()`
 * 
 * ### Bug Fixes
 * 1. fix: use of enum without previous declaration
 * 2. fix: `FindFirstFile()` handle leak
 * 3. fix: `ev_fs_readdir()` not working on windows
 * 
 * 
 * ## v0.0.6 (2022/05/23)
 * 
 * ### BREAKING CHANGES
 * 1. change version code rule.
 * 2. remove return value for `ev_mutex_init()`.
 * 3. remove return value for `ev_sem_init()`.
 * 
 * ### Features
 * 1. Support unlink threadpool
 * 2. publish `ev_todo_submit()`
 * 
 * ### Bug Fixes
 * 1. fix: crash when child process exit
 * 
 * 
 * ## v0.0.5 (2022/05/13)
 * 
 * ### BREAKING CHANGES
 * 1. rename `EV_THREAD_WAIT_INFINITE` to `EV_INFINITE_TIMEOUT`.
 * 2. `ev_pipe_make()` now have flags.
 * 
 * ### Features
 * 1. Support mkdir
 * 2. Support process
 * 3. file: synchronous operations
 * 
 * 
 * ## v0.0.4 (2022/04/12)
 * 
 * ### Bug Fixes
 * 1. build error with glibc version lower than `2.28`
 * 
 * 
 * ## v0.0.3 (2022/04/12)
 * 
 * ### Features
 * 1. Add version code
 * 2. add file support
 * 
 * 
 * ## v0.0.2 (2022/03/10)
 * 
 * ### Features
 * 1. ThreadPool: is able to link to event loop
 * 2. List: support migrate
 * 
 * ### Bug Fixes
 * 1. test failure due to incorrect test sequence
 * 
 * 
 * ## v0.0.1 (2022/02/22)
 * 
 * Initial release
 * 
 */

/**
 * @mainpage libev
 *
 * \section EV_OVERVIEW Overview
 *
 * [libev](https://github.com/qgymib/libev) is a rework of
 * [libuv](https://github.com/libuv/libuv), with following advantages:
 * 1. Strong types without static casts any more.
 * 2. Enhanced IPC features.
 * 3. Easy to use file system operations.
 *
 *
 * \section EV_DOCUMENTATION Documentation
 *
 * Located in the docs/ subdirectory. It use [Doxygen](http://www.doxygen.nl/)
 * to build documents, which means the source code is well documented and can
 * be read directly without build it.
 *
 * To build html-based documents, in the project root, run:
 * ```bash
 * doxygen docs/Doxyfile
 * ```
 *
 * Also documents can be browsed online [here](https://qgymib.github.io/libev/).
 *
 *
 * \section EV_BUILD_INSTRUCTIONS Build Instructions
 *
 * [CMake](https://cmake.org/) is currently the prefer way to build:
 *
 * ```bash
 * # Build:
 * $ mkdir -p build
 * $ (cd build && cmake .. -DBUILD_TESTING=ON) # generate project with tests
 * $ cmake --build build                       # add `-j <n>` with cmake >= 3.12
 * 
 * # Run tests:
 * $ (cd build && ctest -C Debug --output-on-failure)
 * ```
 *
 * \section EV_AMALGAMATE Amalgamate
 * 
 * [libev](https://github.com/qgymib/libev) support amalgamate build, which
 * allow to distribute libev's source code using only two files(`ev.h` and `ev.c`).
 *
 * > Note: Amalgamate requires python3.
 *
 * To use amalgamation, add `-DEV_AMALGAMATE_BUILD=on` when configurate cmake:
 *
 * ```bash
 * $ cmake -DEV_AMALGAMATE_BUILD=on /path/to/libev
 * $ cmake --build .
 * ```
 *
 * In `${CMAKE_CURRENT_BINARY_DIR}/amalgamate` directory, you will find the
 * generated files.
 *
 */
#ifndef __EV_H__
#define __EV_H__

#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdarg.h>

////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/expose.h
// SIZE:    1139
// SHA-256: 6e701e3887d5dc60145e4a44032f7ee7fa37b77cd28cffa7612d4008efd80342
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/expose.h"
#ifndef __EV_EXPOSE_H__
#define __EV_EXPOSE_H__

#if defined(_WIN32) || defined(__CYGWIN__)
#   if defined(EV_USE_DLL)
#       if defined(EV_BUILDING_DLL)
#           if defined(__GNUC__) || defined(__clang__)
#               define EV_API   __attribute__ ((dllexport))
#           else
#               define EV_API   __declspec(dllexport)
#           endif
#       else
#           if defined(__GNUC__) || defined(__clang__)
#               define EV_API   __attribute__ ((dllimport))
#           else
#               define EV_API   __declspec(dllimport)
#           endif
#       endif
#   else
#       define EV_API
#   endif
#elif (defined(__GNUC__) && __GNUC__ >= 4) || defined(__clang__)
#   define EV_API __attribute__((visibility ("default")))
#else
#   define EV_API
#endif

#if defined(EV_AMALGAMATE_BUILD)
#   if defined(__GNUC__) || defined(__clang__)
#       define EV_LOCAL static __attribute__((unused))
#   else
#       define EV_LOCAL static
#   endif
#elif (defined(__GNUC__) || defined(__clang__)) && !defined(_WIN32)
#   define EV_LOCAL __attribute__((visibility ("hidden")))
#else
#   define EV_LOCAL
#endif

#endif

// #line 68 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/version.h
// SIZE:    1020
// SHA-256: d305de0458fd00e9caef834cb7f503cb0c02421e84bf48ebb35a6d54b4b402f8
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/version.h"
#ifndef __EV_VERSION_H__
#define __EV_VERSION_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_VERSION Version
 * @{
 */

/**
 * @brief Major version.
 */
#define EV_VERSION_MAJOR            2

/**
 * @brief Minor version.
 */
#define EV_VERSION_MINOR            0

/**
 * @brief Patch version.
 */
#define EV_VERSION_PATCH            0

/**
 * @brief Version calculate helper macro.
 * @param[in] a     Major version.
 * @param[in] b     Minor version.
 * @param[in] c     Patch version.
 */
#define EV_VERSION(a, b, c)      (((a) << 24) + ((b) << 16) + (c))

/**
 * @brief Current version code.
 */
#define EV_VERSION_CODE             \
    EV_VERSION(EV_VERSION_MAJOR, EV_VERSION_MINOR, EV_VERSION_PATCH)

/**
 * @brief Get version code as c string.
 * @return      Version code.
 */
EV_API const char* ev_version_str(void);

/**
 * @brief Get version code as number.
 * @return      Version code
 */
EV_API unsigned ev_version_code(void);

/**
 * @} EV_VERSION
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 69 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/list.h
// SIZE:    4329
// SHA-256: a71299aca04efa9160eaa9a748345df2c826bffd67181543c71f6403c12871ad
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/list.h"
#ifndef __EV_LIST_H__
#define __EV_LIST_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_UTILS_LIST List
 * @ingroup EV_UTILS
 * @{
 */

/**
 * @brief Static initializer for #ev_list_t
 * @see ev_list_t
 */
#define EV_LIST_INIT            { NULL, NULL, 0 }

/**
 * @brief Static initializer for #ev_list_node_t
 * @see ev_list_node_t
 */
#define EV_LIST_NODE_INIT       { NULL, NULL }

/**
 * @brief The list node.
 * This node must put in your struct.
 * @see EV_LIST_NODE_INIT
 */
typedef struct ev_list_node
{
    struct ev_list_node*    p_after;    /**< Pointer to next node */
    struct ev_list_node*    p_before;   /**< Pointer to previous node */
}ev_list_node_t;

/**
 * @brief Double Linked List
 * @see EV_LIST_INIT
 */
typedef struct ev_list
{
    ev_list_node_t*         head;       /**< Pointer to HEAD node */
    ev_list_node_t*         tail;       /**< Pointer to TAIL node */
    size_t                  size;       /**< The number of total nodes */
}ev_list_t;

/**
 * @brief Initialize Double Linked List.
 * @note It is guarantee that memset() to zero have the same affect.
 * @param[out] handler  Pointer to list
 */
EV_API void ev_list_init(ev_list_t* handler);

/**
 * @brief Insert a node to the head of the list.
 * @warning the node must not exist in any list.
 * @param[in,out] handler   Pointer to list
 * @param[in,out] node      Pointer to a new node
 */
EV_API void ev_list_push_front(ev_list_t* handler, ev_list_node_t* node);

/**
 * @brief Insert a node to the tail of the list.
 * @warning the node must not exist in any list.
 * @param[in,out] handler   Pointer to list
 * @param[in,out] node      Pointer to a new node
 */
EV_API void ev_list_push_back(ev_list_t* handler, ev_list_node_t* node);

/**
 * @brief Insert a node in front of a given node.
 * @warning the node must not exist in any list.
 * @param[in,out] handler   Pointer to list
 * @param[in,out] pos       Pointer to a exist node
 * @param[in,out] node      Pointer to a new node
 */
EV_API void ev_list_insert_before(ev_list_t* handler, ev_list_node_t* pos, ev_list_node_t* node);

/**
 * @brief Insert a node right after a given node.
 * @warning the node must not exist in any list.
 * @param[in,out] handler   Pointer to list
 * @param[in,out] pos       Pointer to a exist node
 * @param[in,out] node      Pointer to a new node
 */
EV_API void ev_list_insert_after(ev_list_t* handler, ev_list_node_t* pos, ev_list_node_t* node);

/**
 * @brief Delete a exist node
 * @warning The node must already in the list.
 * @param[in,out] handler   Pointer to list
 * @param[in,out] node      The node you want to delete
 */
EV_API void ev_list_erase(ev_list_t* handler, ev_list_node_t* node);

/**
 * @brief Get the number of nodes in the list.
 * @param[in] handler   Pointer to list
 * @return              The number of nodes
 */
EV_API size_t ev_list_size(const ev_list_t* handler);

/**
 * @brief Get the first node and remove it from the list.
 * @param[in,out] handler   Pointer to list
 * @return                  The first node
 */
EV_API ev_list_node_t* ev_list_pop_front(ev_list_t* handler);

/**
 * @brief Get the last node and remove it from the list.
 * @param[in,out] handler   Pointer to list
 * @return                  The last node
 */
EV_API ev_list_node_t* ev_list_pop_back(ev_list_t* handler);

/**
 * @brief Get the first node.
 * @param[in] handler   Pointer to list
 * @return              The first node
 */
EV_API ev_list_node_t* ev_list_begin(const ev_list_t* handler);

/**
 * @brief Get the last node.
 * @param[in] handler   The handler of list
 * @return              The last node
 */
EV_API ev_list_node_t* ev_list_end(const ev_list_t* handler);

/**
* @brief Get next node.
* @param[in] node   Current node
* @return           The next node
*/
EV_API ev_list_node_t* ev_list_next(const ev_list_node_t* node);

/**
 * @brief Get previous node.
 * @param[in] node  current node
 * @return          previous node
 */
EV_API ev_list_node_t* ev_list_prev(const ev_list_node_t* node);

/**
 * @brief Move all elements from \p src into the end of \p dst.
 * @param[in] dst   Destination list.
 * @param[in] src   Source list.
 */
EV_API void ev_list_migrate(ev_list_t* dst, ev_list_t* src);

/**
 * @} EV_UTILS/EV_UTILS_LIST
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 70 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/map.h
// SIZE:    4416
// SHA-256: 542ea54deebd4836d4f60f717aa45fd177de855895e66df51c0f637e5d5ed47a
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/map.h"
#ifndef __EV_MAP_H__
#define __EV_MAP_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_UTILS_MAP Map
 * @ingroup EV_UTILS
 * @{
 */         

/**
 * @brief The node for map
 * @see eaf_map_t
 * @see EV_MAP_NODE_INIT
 */
typedef struct ev_map_node
{
    struct ev_map_node* __rb_parent_color;  /**< parent node | color */
    struct ev_map_node* rb_right;           /**< right node */
    struct ev_map_node* rb_left;            /**< left node */
} ev_map_node_t;

/**
 * @brief Static initializer for #ev_map_t
 * @see ev_map_t
 * @param[in] cmp   Compare function
 * @param[in] arg   Argument for compare function
 */
#define EV_MAP_INIT(cmp, arg)   { NULL, { cmp, arg }, 0 }

/**
 * @brief Static initializer for #ev_map_node_t
 * @see ev_map_node_t
 */
#define EV_MAP_NODE_INIT        { NULL, NULL, NULL }

/**
 * @brief Compare function.
 * @param key1  The key in the map
 * @param key2  The key user given
 * @param arg   User defined argument
 * @return      -1 if key1 < key2. 1 if key1 > key2. 0 if key1 == key2.
 */
typedef int(*ev_map_cmp_fn)(const ev_map_node_t* key1, const ev_map_node_t* key2, void* arg);

/**
 * @brief Map implemented as red-black tree
 * @see EV_MAP_INIT
 */
typedef struct ev_map
{
    ev_map_node_t*      rb_root;            /**< root node */

    struct
    {
        ev_map_cmp_fn   cmp;        /**< Pointer to compare function */
        void*           arg;        /**< User defined argument, which will passed to compare function */
    }cmp;                           /**< Compare function data */

    size_t              size;       /**< The number of nodes */
} ev_map_t;

/**
 * @brief Initialize the map referenced by handler.
 * @param handler   The pointer to the map
 * @param cmp       The compare function. Must not NULL
 * @param arg       User defined argument. Can be anything
 */
EV_API void ev_map_init(ev_map_t* handler, ev_map_cmp_fn cmp, void* arg);

/**
 * @brief Insert the node into map.
 * @warning the node must not exist in any map.
 * @param handler   The pointer to the map
 * @param node      The node
 * @return          NULL if success, otherwise return the conflict node address.
 */
EV_API ev_map_node_t* ev_map_insert(ev_map_t* handler, ev_map_node_t* node);

/**
 * @brief Delete the node from the map.
 * @warning The node must already in the map.
 * @param handler   The pointer to the map
 * @param node      The node
 */
EV_API void ev_map_erase(ev_map_t* handler, ev_map_node_t* node);

/**
 * @brief Get the number of nodes in the map.
 * @param handler   The pointer to the map
 * @return          The number of nodes
 */
EV_API size_t ev_map_size(const ev_map_t* handler);

/**
 * @brief Finds element with specific key
 * @param handler   The pointer to the map
 * @param key       The key
 * @return          An iterator point to the found node
 */
EV_API ev_map_node_t* ev_map_find(const ev_map_t* handler,
    const ev_map_node_t* key);

/**
 * @brief Returns an iterator to the first element not less than the given key
 * @param handler   The pointer to the map
 * @param key       The key
 * @return          An iterator point to the found node
 */
EV_API ev_map_node_t* ev_map_find_lower(const ev_map_t* handler,
    const ev_map_node_t* key);

/**
 * @brief Returns an iterator to the first element greater than the given key
 * @param handler   The pointer to the map
 * @param key       The key
 * @return          An iterator point to the found node
 */
EV_API ev_map_node_t* ev_map_find_upper(const ev_map_t* handler,
    const ev_map_node_t* key);

/**
 * @brief Returns an iterator to the beginning
 * @param handler   The pointer to the map
 * @return          An iterator
 */
EV_API ev_map_node_t* ev_map_begin(const ev_map_t* handler);

/**
 * @brief Returns an iterator to the end
 * @param handler   The pointer to the map
 * @return          An iterator
 */
EV_API ev_map_node_t* ev_map_end(const ev_map_t* handler);

/**
 * @brief Get an iterator next to the given one.
 * @param node      Current iterator
 * @return          Next iterator
 */
EV_API ev_map_node_t* ev_map_next(const ev_map_node_t* node);

/**
 * @brief Get an iterator before the given one.
 * @param node      Current iterator
 * @return          Previous iterator
 */
EV_API ev_map_node_t* ev_map_prev(const ev_map_node_t* node);

/**
 * @} EV_UTILS/EV_UTILS_MAP
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 71 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/defines.h
// SIZE:    3268
// SHA-256: def87553c746184a16b6fbcaabae80b298f4a50e485e6098525402a19524ce60
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/defines.h"
#ifndef __EV_DEFINES_H__
#define __EV_DEFINES_H__

/**
 * @defgroup EV_DEFINE Defines
 * @{
 */

/**
 * @brief The maximum number of iov buffers can be support.
 */
#define EV_IOV_MAX              16

/**
 * @brief Expand macro.
 * @param[in] ...   Code to expand.
 */
#define EV_EXPAND(...)          __VA_ARGS__

/**
 * @brief Repeat code for \p n times.
 * @param[in] n     How many times to repeat.
 * @param[in] ...   Code fragment to repeat.
 */
#define EV_INIT_REPEAT(n, ...)   EV_INIT_REPEAT2(n, __VA_ARGS__)
/** @cond */
#define EV_INIT_REPEAT2(n, ...)  EV_INIT_REPEAT_##n(__VA_ARGS__)
#define EV_INIT_REPEAT_1(...)    EV_EXPAND(__VA_ARGS__)
#define EV_INIT_REPEAT_2(...)    EV_INIT_REPEAT_1(__VA_ARGS__),  EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_3(...)    EV_INIT_REPEAT_2(__VA_ARGS__),  EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_4(...)    EV_INIT_REPEAT_3(__VA_ARGS__),  EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_5(...)    EV_INIT_REPEAT_4(__VA_ARGS__),  EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_6(...)    EV_INIT_REPEAT_5(__VA_ARGS__),  EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_7(...)    EV_INIT_REPEAT_6(__VA_ARGS__),  EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_8(...)    EV_INIT_REPEAT_7(__VA_ARGS__),  EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_9(...)    EV_INIT_REPEAT_8(__VA_ARGS__),  EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_10(...)   EV_INIT_REPEAT_9(__VA_ARGS__),  EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_11(...)   EV_INIT_REPEAT_10(__VA_ARGS__), EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_12(...)   EV_INIT_REPEAT_11(__VA_ARGS__), EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_13(...)   EV_INIT_REPEAT_12(__VA_ARGS__), EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_14(...)   EV_INIT_REPEAT_13(__VA_ARGS__), EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_15(...)   EV_INIT_REPEAT_14(__VA_ARGS__), EV_INIT_REPEAT_1(__VA_ARGS__)
#define EV_INIT_REPEAT_16(...)   EV_INIT_REPEAT_15(__VA_ARGS__), EV_INIT_REPEAT_1(__VA_ARGS__)
/** @endcond */

/**
 * @def EV_OFFSETOF
 * @brief The offset of \p member in \p type.
 */
#if defined(offsetof)
#   define EV_OFFSETOF(type, member)    offsetof(type, member)
#else
#   define EV_OFFSETOF(type, member)    ((size_t)&(((type*)0)->member))
#endif

/**
 * @def EV_CONTAINER_OF
 * @brief cast a member of a structure out to the containing structure.
 */
#if defined(container_of)
#   define EV_CONTAINER_OF(ptr, type, member)   \
        container_of(ptr, type, member)
#elif defined(__GNUC__) || defined(__clang__)
#   define EV_CONTAINER_OF(ptr, type, member)   \
        ({ \
            const typeof(((type *)0)->member)*__mptr = (ptr); \
            (type *)((char *)__mptr - offsetof(type, member)); \
        })
#else
#   define EV_CONTAINER_OF(ptr, type, member)   \
        ((type *) ((char *) (ptr) - EV_OFFSETOF(type, member)))
#endif

 /**
  * @brief Align \p size to \p align, who's value is larger or equal to \p size
  *   and can be divided with no remainder by \p align.
  * @note \p align must equal to 2^n
  */
#define EV_ALIGN_SIZE(size, align) \
    (((uintptr_t)(size) + ((uintptr_t)(align) - 1)) & ~((uintptr_t)(align) - 1))

/**
 * @} EV_DEFINE
 */

#endif

// #line 72 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/errno.h
// SIZE:    11153
// SHA-256: 9b13fa73f471ea05908f531a23470f18711bc8f14e558bfb6226fd1d18457ef7
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/errno.h"
#ifndef __EV_ERRNO_H__
#define __EV_ERRNO_H__

#include <errno.h>

#if EDOM > 0
#define EV__ERR(x)              (-(x))
#else
#define EV__ERR(x)              (x)
#endif

#if defined(EPERM) && !defined(_WIN32)
#   define EV__EPERM            EV__ERR(EPERM)
#else
#   define EV__EPERM            (-4093)
#endif

#if defined(ENOENT) && !defined(_WIN32)
#   define EV__ENOENT           EV__ERR(ENOENT)
#else
#   define EV__ENOENT           (-4092)
#endif

#if defined(EIO) && !defined(_WIN32)
#   define EV__EIO              EV__ERR(EIO)
#else
#   define EV__EIO              (-4089)
#endif

#if defined(E2BIG) && !defined(_WIN32)
#   define EV__E2BIG            EV__ERR(E2BIG)
#else
#   define EV__E2BIG            (-4087)
#endif

#if defined(EBADF) && !defined(_WIN32)
#   define EV__EBADF            EV__ERR(EBADF)
#else
#   define EV__EBADF            (-4085)
#endif

#if defined(EAGAIN) && !defined(_WIN32)
#   define EV__EAGAIN           EV__ERR(EAGAIN)
#else
#   define EV__EAGAIN           (-4083)
#endif

#if defined(ENOMEM) && !defined(_WIN32)
#   define EV__ENOMEM           EV__ERR(ENOMEM)
#else
#   define EV__ENOMEM           (-4082)
#endif

#if defined(EACCES) && !defined(_WIN32)
#   define EV__EACCES           EV__ERR(EACCES)
#else
#   define EV__EACCES           (-4081)
#endif

#if defined(EFAULT) && !defined(_WIN32)
#   define EV__EFAULT           EV__ERR(EFAULT)
#else
#   define EV__EFAULT           (-4080)
#endif

#if defined(EBUSY) && !defined(_WIN32)
#   define EV__EBUSY            EV__ERR(EBUSY)
#else
#   define EV__EBUSY            (-4078)
#endif

#if defined(EEXIST) && !defined(_WIN32)
#   define EV__EEXIST           EV__ERR(EEXIST)
#else
#   define EV__EEXIST           (-4077)
#endif

#if defined(EXDEV) && !defined(_WIN32)
#   define EV__EXDEV            EV__ERR(EXDEV)
#else
#   define EV__EXDEV            (-4076)
#endif

#if defined(ENOTDIR) && !defined(_WIN32)
#   define EV__ENOTDIR          EV__ERR(ENOTDIR)
#else
#   define EV__ENOTDIR          (-4074)
#endif

#if defined(EISDIR) && !defined(_WIN32)
#   define EV__EISDIR           EV__ERR(EISDIR)
#else
#   define EV__EISDIR           (-4073)
#endif

#if defined(EINVAL) && !defined(_WIN32)
#   define EV__EINVAL           EV__ERR(EINVAL)
#else
#   define EV__EINVAL           (-4072)
#endif

#if defined(ENFILE) && !defined(_WIN32)
#   define EV__ENFILE           EV__ERR(ENFILE)
#else
#   define EV__ENFILE           (-4071)
#endif

#if defined(EMFILE) && !defined(_WIN32)
#   define EV__EMFILE           EV__ERR(EMFILE)
#else
#   define EV__EMFILE           (-4070)
#endif

#if defined(ENOSPC) && !defined(_WIN32)
#   define EV__ENOSPC           EV__ERR(ENOSPC)
#else
#   define EV__ENOSPC           (-4066)
#endif

#if defined(EROFS) && !defined(_WIN32)
#   define EV__EROFS            EV__ERR(EROFS)
#else
#   define EV__EROFS            (-4064)
#endif

#if defined(EPIPE) && !defined(_WIN32)
#   define EV__EPIPE            EV__ERR(EPIPE)
#else
#   define EV__EPIPE            (-4062)
#endif

#if defined(ENAMETOOLONG) && !defined(_WIN32)
#   define EV__ENAMETOOLONG     EV__ERR(ENAMETOOLONG)
#else
#   define EV__ENAMETOOLONG     (-4058)
#endif

#if defined(ENOSYS) && !defined(_WIN32)
#   define EV__ENOSYS           EV__ERR(ENOSYS)
#else
#   define EV__ENOSYS           (-4056)
#endif

#if defined(ENOTEMPTY) && !defined(_WIN32)
#   define EV__ENOTEMPTY        EV__ERR(ENOTEMPTY)
#else
#   define EV__ENOTEMPTY        (-4055)
#endif

#if defined(ELOOP) && !defined(_WIN32)
#   define EV__ELOOP            EV__ERR(ELOOP)
#else
#   define EV__ELOOP            (-4054)
#endif

#if defined(EPROTO) && !defined(_WIN32)
#   define EV__EPROTO           EV__ERR(EPROTO)
#else
#   define EV__EPROTO           (-4023)
#endif

#if defined(ENOTSOCK) && !defined(_WIN32)
#   define EV__ENOTSOCK         EV__ERR(ENOTSOCK)
#else
#   define EV__ENOTSOCK         (-4006)
#endif

#if defined(EMSGSIZE) && !defined(_WIN32)
#   define EV__EMSGSIZE         EV__ERR(EMSGSIZE)
#else
#   define EV__EMSGSIZE         (-4004)
#endif

#if defined(EPROTONOSUPPORT) && !defined(_WIN32)
#   define EV__EPROTONOSUPPORT  EV__ERR(EPROTONOSUPPORT)
#else
#   define EV__EPROTONOSUPPORT  (-4001)
#endif

#if defined(ENOTSUP) && !defined(_WIN32)
#   define EV__ENOTSUP          EV__ERR(ENOTSUP)
#else
#   define EV__ENOTSUP          (-3999)
#endif

#if defined(EAFNOSUPPORT) && !defined(_WIN32)
#   define EV__EAFNOSUPPORT     EV__ERR(EAFNOSUPPORT)
#else
#   define EV__EAFNOSUPPORT     (-3997)
#endif

#if defined(EADDRINUSE) && !defined(_WIN32)
#   define EV__EADDRINUSE       EV__ERR(EADDRINUSE)
#else
#   define EV__EADDRINUSE       (-3996)
#endif

#if defined(EADDRNOTAVAIL) && !defined(_WIN32)
#   define EV__EADDRNOTAVAIL    EV__ERR(EADDRNOTAVAIL)
#else
#   define EV__EADDRNOTAVAIL    (-3995)
#endif

#if defined(ENETUNREACH) && !defined(_WIN32)
#   define EV__ENETUNREACH      EV__ERR(ENETUNREACH)
#else
#   define EV__ENETUNREACH      (-3993)
#endif

#if defined(ECONNABORTED) && !defined(_WIN32)
#   define EV__ECONNABORTED     EV__ERR(ECONNABORTED)
#else
#   define EV__ECONNABORTED     (-3991)
#endif

#if defined(ECONNRESET) && !defined(_WIN32)
#   define EV__ECONNRESET       EV__ERR(ECONNRESET)
#else
#   define EV__ECONNRESET       (-3990)
#endif

#if defined(ENOBUFS) && !defined(_WIN32)
#   define EV__ENOBUFS          EV__ERR(ENOBUFS)
#else
#   define EV__ENOBUFS          (-3989)
#endif

#if defined(EISCONN) && !defined(_WIN32)
#   define EV__EISCONN          EV__ERR(EISCONN)
#else
#   define EV__EISCONN          (-3988)
#endif

#if defined(ENOTCONN) && !defined(_WIN32)
#   define EV__ENOTCONN         EV__ERR(ENOTCONN)
#else
#   define EV__ENOTCONN         (-3987)
#endif

#if defined(ETIMEDOUT) && !defined(_WIN32)
#   define EV__ETIMEDOUT        EV__ERR(ETIMEDOUT)
#else
#   define EV__ETIMEDOUT        (-3984)
#endif

#if defined(ECONNREFUSED) && !defined(_WIN32)
#   define EV__ECONNREFUSED     EV__ERR(ECONNREFUSED)
#else
#   define EV__ECONNREFUSED     (-3983)
#endif

#if defined(EHOSTUNREACH) && !defined(_WIN32)
#   define EV__EHOSTUNREACH     EV__ERR(EHOSTUNREACH)
#else
#   define EV__EHOSTUNREACH     (-3981)
#endif

#if defined(EALREADY) && !defined(_WIN32)
#   define EV__EALREADY         EV__ERR(EALREADY)
#else
#   define EV__EALREADY         (-3980)
#endif

#if defined(EINPROGRESS) && !defined(_WIN32)
#   define EV__EINPROGRESS      EV__ERR(EINPROGRESS)
#else
#   define EV__EINPROGRESS      (-3979)
#endif

#if defined(ECANCELED) && !defined(_WIN32)
#   define EV__ECANCELED        EV__ERR(ECANCELED)
#else
#   define EV__ECANCELED        (-3969)
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_ERRNO Error number
 * @{
 */

/**
 * @brief Error number
 */
typedef enum ev_errno
{
    /* POSIX compatible error code */
    EV_EPERM            = EV__EPERM,            /**< Operation not permitted (POSIX.1-2001) */
    EV_ENOENT           = EV__ENOENT,           /**< No such file or directory (POSIX.1-2001) */
    EV_EIO              = EV__EIO,              /**< Host is unreachable (POSIX.1-2001) */
    EV_E2BIG            = EV__E2BIG,            /**< Argument list too long (POSIX.1-2001) */
    EV_EBADF            = EV__EBADF,            /**< Bad file descriptor (POSIX.1-2001) */
    EV_EAGAIN           = EV__EAGAIN,           /**< Resource temporarily unavailable (POSIX.1-2001) */
    EV_ENOMEM           = EV__ENOMEM,           /**< Not enough space/cannot allocate memory (POSIX.1-2001) */
    EV_EACCES           = EV__EACCES,           /**< Permission denied (POSIX.1-2001) */
    EV_EFAULT           = EV__EFAULT,           /**< Bad address (POSIX.1-2001) */
    EV_EBUSY            = EV__EBUSY,            /**< Device or resource busy (POSIX.1-2001) */
    EV_EEXIST           = EV__EEXIST,           /**< File exists (POSIX.1-2001) */
    EV_EXDEV            = EV__EXDEV,            /**< Improper link (POSIX.1-2001) */
    EV_ENOTDIR          = EV__ENOTDIR,          /**< Not a directory (POSIX.1-2001) */
    EV_EISDIR           = EV__EISDIR,           /**< Is a directory (POSIX.1-2001) */
    EV_EINVAL           = EV__EINVAL,           /**< Invalid argument (POSIX.1-2001) */
    EV_ENFILE           = EV__ENFILE,           /**< Too many open files in system (POSIX.1-2001) */
    EV_EMFILE           = EV__EMFILE,           /**< Too many open files (POSIX.1-2001) */
    EV_ENOSPC           = EV__ENOSPC,           /**< No space left on device (POSIX.1-2001) */
    EV_EROFS            = EV__EROFS,            /**< Read-only filesystem (POSIX.1-2001) */
    EV_EPIPE            = EV__EPIPE,            /**< Broken pipe (POSIX.1-2001) */
    EV_ENAMETOOLONG     = EV__ENAMETOOLONG,     /**< Filename too long (POSIX.1-2001) */
    EV_ENOSYS           = EV__ENOSYS,           /**< Function not implemented (POSIX.1-2001) */
    EV_ENOTEMPTY        = EV__ENOTEMPTY,        /**< Directory not empty (POSIX.1-2001) */
    EV_ELOOP            = EV__ELOOP,            /**< Too many levels of symbolic links (POSIX.1-2001) */
    EV_EPROTO           = EV__EPROTO,           /**< Protocol error (POSIX.1-2001) */
    EV_ENOTSOCK         = EV__ENOTSOCK,         /**< Not a socket (POSIX.1-2001) */
    EV_EMSGSIZE         = EV__EMSGSIZE,         /**< Message too long (POSIX.1-2001) */
    EV_EPROTONOSUPPORT  = EV__EPROTONOSUPPORT,  /**< Protocol not supported (POSIX.1-2001) */
    EV_ENOTSUP          = EV__ENOTSUP,          /**< Operation not supported (POSIX.1-2001) */
    EV_EAFNOSUPPORT     = EV__EAFNOSUPPORT,     /**< Address family not supported (POSIX.1-2001) */
    EV_EADDRINUSE       = EV__EADDRINUSE,       /**< Address already in use (POSIX.1-2001) */
    EV_EADDRNOTAVAIL    = EV__EADDRNOTAVAIL,    /**< Address not available (POSIX.1-2001) */
    EV_ENETUNREACH      = EV__ENETUNREACH,      /**< Network unreachable (POSIX.1-2001) */
    EV_ECONNABORTED     = EV__ECONNABORTED,     /**< Connection aborted (POSIX.1-2001) */
    EV_ECONNRESET       = EV__ECONNRESET,       /**< Connection reset (POSIX.1-2001) */
    EV_ENOBUFS          = EV__ENOBUFS,          /**< No buffer space available (POSIX.1 (XSI STREAMS option)) */
    EV_EISCONN          = EV__EISCONN,          /**< Socket is connected (POSIX.1-2001) */
    EV_ENOTCONN         = EV__ENOTCONN,         /**< The socket is not connected (POSIX.1-2001) */
    EV_ETIMEDOUT        = EV__ETIMEDOUT,        /**< Operation timed out (POSIX.1-2001) */
    EV_ECONNREFUSED     = EV__ECONNREFUSED,     /**< Connection refused (POSIX.1-2001) */
    EV_EHOSTUNREACH     = EV__EHOSTUNREACH,     /**< Host is unreachable (POSIX.1-2001) */
    EV_EALREADY         = EV__EALREADY,         /**< Connection already in progress (POSIX.1-2001) */
    EV_EINPROGRESS      = EV__EINPROGRESS,      /**< Operation in progress (POSIX.1-2001) */
    EV_ECANCELED        = EV__ECANCELED,        /**< Operation canceled (POSIX.1-2001) */

    /* Extend error code */
    EV_EOF              = -4095,
    EV_EUNKNOWN         = -4094,
} ev_errno_t;

/**
 * @brief Describe the error code
 * @param[in] err   Error code
 * @return          Describe string
 */
EV_API const char* ev_strerror(int err);

/**
 * @} EV_ERRNO
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 73 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/allocator.h
// SIZE:    1933
// SHA-256: d094345d9727bfdbeb994b3906bf0788c71f24dcf651ff0432c120bf7efd2c73
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/allocator.h"
#ifndef __EV_ALLOCATOR_H__
#define __EV_ALLOCATOR_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_ALLOCATOR Allocator
 * @{
 */

/**
 * @brief Replacement function for realloc.
 * @see https://man7.org/linux/man-pages/man3/realloc.3.html
 */
typedef void *(*ev_realloc_fn)(void *ptr, size_t size);

/**
 * @brief Override the use of the standard library's malloc(3), calloc(3),
 *   realloc(3), free(3), memory allocation functions.
 *
 * This function must be called before any other function is called or after
 * all resources have been freed and thus doesn't reference any allocated
 * memory chunk.
 *
 * @warning There is no protection against changing the allocator multiple
 *   times. If the user changes it they are responsible for making sure the
 *   allocator is changed while no memory was allocated with the previous
 *   allocator, or that they are compatible.
 * @warngin Allocator must be thread-safe.
 *
 * @param[in] new_allocator   Replacement function..
 * @param[out] old_allocator  Old allocator functions.
 * @return #ev_errno_t.
 */
EV_API int ev_replace_allocator(ev_realloc_fn  new_allocator,
                                 ev_realloc_fn *old_allocator);

/**
 * @brief Same as [malloc(3)](https://man7.org/linux/man-pages/man3/free.3.html)
 */
EV_API void *ev_malloc(size_t size);

/**
 * @brief Same as [calloc(3)](https://man7.org/linux/man-pages/man3/free.3.html)
 */
EV_API void *ev_calloc(size_t nmemb, size_t size);

/**
 * @brief Same as
 * [realloc(3)](https://man7.org/linux/man-pages/man3/free.3.html)
 */
EV_API void *ev_realloc(void *ptr, size_t size);

/**
 * @brief Same as [free(3)](https://man7.org/linux/man-pages/man3/free.3.html)
 */
EV_API void ev_free(void *ptr);

/**
 * @brief Same as
 * [strdup(3)](https://man7.org/linux/man-pages/man3/strdup.3.html)
 */
EV_API char *ev__strdup(const char *str);

/**
 * @} EV_ALLOCATOR
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 74 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/queue.h
// SIZE:    2422
// SHA-256: ee1ffba7c2a219684e6824c96b2da060e3aba5a69a49338e3d91c7c39e0814da
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/queue.h"
#ifndef __EV_QUEUE_H__
#define __EV_QUEUE_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_UTILS_QUEUE Queue
 * @ingroup EV_UTILS
 * @{
 */

/**
 * @brief Static initializer for #ev_queue_node_t.
 * @note A static initialized queue node is not a valid node.
 */

/**
 * @brief Queue node type.
 */
typedef struct ev_queue_node
{
    struct ev_queue_node* p_prev;
    struct ev_queue_node* p_next;
} ev_queue_node_t;
#define EV_QUEUE_NODE_INVALID  \
    {\
        NULL,\
        NULL,\
    }

/**
 * @brief Initialize circular linked list
 * @param[out] head     List handle
 */
EV_API void ev_queue_init(ev_queue_node_t* head);

/**
 * @brief Insert a node to the tail of the list.
 * @warning the node must not exist in any list.
 * @param[in,out] head  Pointer to list
 * @param[in,out] node  Pointer to a new node
 */
EV_API void ev_queue_push_back(ev_queue_node_t* head, ev_queue_node_t* node);

/**
 * @brief Insert a node to the head of the list.
 * @warning the node must not exist in any list.
 * @param[in,out] head      Pointer to list
 * @param[in,out] node      Pointer to a new node
 */
EV_API void ev_queue_push_front(ev_queue_node_t* head, ev_queue_node_t* node);

/**
 * @brief Delete a exist node
 * @param[in,out] node      The node you want to delete
 */
EV_API void ev_queue_erase(ev_queue_node_t* node);

/**
 * @brief Check whether list is empty
 * @param[in] node          Any node in list
 * @return                  bool
 */
EV_API int ev_queue_empty(const ev_queue_node_t* node);

/**
 * @brief Get the first node and remove it from the list.
 * @param[in,out] head      Pointer to list
 * @return                  The first node
 */
EV_API ev_queue_node_t* ev_queue_pop_front(ev_queue_node_t* head);

/**
 * @brief Get the last node and remove it from the list.
 * @param[in,out] head      Pointer to list
 * @return                  The last node
 */
EV_API ev_queue_node_t* ev_queue_pop_back(ev_queue_node_t* head);

/**
 * @brief Get the first node.
 * @param[in] head      Pointer to list
 * @return              The first node
 */
EV_API ev_queue_node_t* ev_queue_head(ev_queue_node_t* head);

/**
* @brief Get next node.
* @param[in] head   Queue head
* @param[in] node   Current node
* @return           The next node
*/
EV_API ev_queue_node_t* ev_queue_next(ev_queue_node_t* head, ev_queue_node_t* node);

/**
 * @} EV_UTILS_QUEUE
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 75 "ev.h"

#if defined(_WIN32)
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/win.h
// SIZE:    12778
// SHA-256: 8edeb81f8edb1015c0b5b3a5e59ef5ef14c6cd94b69a56503c9d35d7b13c43ce
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/win.h"
/**
 * @file
 */
#ifndef __EV_BACKEND_WIN_H__
#define __EV_BACKEND_WIN_H__

#ifndef _WIN32_WINNT
#    define _WIN32_WINNT   0x0600
#endif
#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

#   if !defined(_SSIZE_T_) && !defined(_SSIZE_T_DEFINED)
typedef intptr_t ssize_t;
#       define SSIZE_MAX INTPTR_MAX
#       define _SSIZE_T_
#       define _SSIZE_T_DEFINED
#   endif

/**
 * @addtogroup EV_FILESYSTEM
 * @{
 */

/**
 * @brief The file is opened in append mode. Before each write, the file offset
 *   is positioned at the end of the file.
 */
#define EV_FS_O_APPEND          _O_APPEND

/**
 * @brief The file is created if it does not already exist.
 */
#define EV_FS_O_CREAT           _O_CREAT

/**
 * @brief The file is opened for synchronous I/O. Write operations will complete
 *   once all data and a minimum of metadata are flushed to disk.
 */
#define EV_FS_O_DSYNC           FILE_FLAG_WRITE_THROUGH

/**
 * @brief If the `O_CREAT` flag is set and the file already exists, fail the open.
 */
#define EV_FS_O_EXCL            _O_EXCL

/**
 * @brief The file is opened for synchronous I/O. Write operations will complete
 *   once all data and all metadata are flushed to disk.
 */
#define EV_FS_O_SYNC            FILE_FLAG_WRITE_THROUGH

/**
 * @brief If the file exists and is a regular file, and the file is opened
 *   successfully for write access, its length shall be truncated to zero.
 */
#define EV_FS_O_TRUNC           _O_TRUNC

/**
 * @brief Open the file for read-only access.
 */
#define EV_FS_O_RDONLY          _O_RDONLY

/**
 * @brief Open the file for write-only access.
 */
#define EV_FS_O_WRONLY          _O_WRONLY

/**
 * @def EV_FS_O_RDWR
 * @brief Open the file for read-write access.
 */
#define EV_FS_O_RDWR            _O_RDWR

/**
 * @brief User has read permission.
 */
#define EV_FS_S_IRUSR           _S_IREAD

/**
 * @brief User has write permission.
 */
#define EV_FS_S_IWUSR           _S_IWRITE

/**
 * @brief User has execute permission.
 */
#define EV_FS_S_IXUSR           _S_IEXEC

/**
 * @brief user (file owner) has read, write, and execute permission.
 */
#define EV_FS_S_IRWXU           (EV_FS_S_IRUSR | EV_FS_S_IWUSR | EV_FS_S_IXUSR)

/**
 * @brief The starting point is zero or the beginning of the file.
 */
#define EV_FS_SEEK_BEG           FILE_BEGIN

/**
 * @brief The starting point is the current value of the file pointer.
 */
#define EV_FS_SEEK_CUR           FILE_CURRENT

/**
 * @brief The starting point is the current end-of-file position.
 */
#define EV_FS_SEEK_END           FILE_END

/**
 * @brief Windows system define of file.
 */
typedef HANDLE                   ev_os_file_t;

/**
 * @brief Invalid valid of #ev_os_file_t.
 */
#define EV_OS_FILE_INVALID      INVALID_HANDLE_VALUE

/**
 * @} EV_FILESYSTEM
 */

/**
 * @addtogroup EV_PROCESS
 * @{
 */

typedef HANDLE                  ev_os_pid_t;
#define EV_OS_PID_INVALID       INVALID_HANDLE_VALUE

/**
 * @} EV_PROCESS
 */

typedef HANDLE                  ev_os_pipe_t;
#define EV_OS_PIPE_INVALID      INVALID_HANDLE_VALUE

typedef SOCKET                  ev_os_socket_t;
#define EV_OS_SOCKET_INVALID    INVALID_SOCKET

typedef DWORD                   ev_os_tid_t;
#define EV_OS_TID_INVALID       ((DWORD)(-1))

typedef HANDLE                  ev_os_shdlib_t;
#define EV_OS_SHDLIB_INVALID    (NULL)

/**
 * @brief Buffer
 * @internal Must share the same layout with WSABUF
 */
typedef struct ev_buf
{
    ULONG                       size;               /**< Data size */
    CHAR*                       data;               /**< Data address */
} ev_buf_t;

/**
 * @brief Initialize #ev_buf_t.
 * @param[in] buf   Data address.
 * @param[in] len   Data length.
 */
#define EV_BUF_INIT(buf, len)   { (ULONG)len, (CHAR*)buf }

struct ev_once
{
    INIT_ONCE                   guard;              /**< Once token */
};

/**
 * @brief Initialize #ev_once_t to Windows specific structure.
 */
#define EV_ONCE_INIT            { INIT_ONCE_STATIC_INIT }

struct ev_iocp;

/**
 * @brief Typedef of #ev_iocp.
 */
typedef struct ev_iocp ev_iocp_t;

/**
 * @brief IOCP complete callback
 * @param[in] iocp  IOCP request
 */
typedef void(*ev_iocp_cb)(ev_iocp_t* iocp, size_t transferred, void* arg);

/**
 * @brief IOCP structure.
 */
struct ev_iocp
{
    void*                       arg;                /**< Index */
    ev_iocp_cb                  cb;                 /**< Callback */
    OVERLAPPED                  overlapped;         /**< IOCP field */
};

/**
 * @brief Initialize #ev_iocp_t to invalid value.
 */
#define EV_IOCP_INIT            { NULL, NULL, { 0, 0, { { 0, 0 } }, NULL } }

/**
 * @brief Windows backend for #ev_async_t.
 */
#define EV_ASYNC_BACKEND    \
    struct ev_async_plt {\
        LONG volatile               async_sent;\
        ev_iocp_t                   io;\
    }

/**
 * @brief Initialize #EV_ASYNC_BACKEND to an Windows specific invalid value.
 */
#define EV_ASYNC_PLT_INVALID    { 0, EV_IOCP_INIT }

#define EV_LOOP_BACKEND \
    struct ev_loop_plt {\
        HANDLE                      iocp;               /**< IOCP handle */\
        struct {\
            ev_iocp_t               io;                 /**< Wakeup token */\
        } threadpool;\
    }

/**
 * @brief Initialize #EV_LOOP_BACKEND to Windows specific invalid value.
 */
#define EV_LOOP_PLT_INIT        { NULL, { EV_IOCP_INIT } }

/**
 * @brief Windows backend for #ev_tcp_read_req_t.
 */
#define EV_TCP_READ_BACKEND \
    struct ev_tcp_read_backend {\
        ev_tcp_t*                   owner;              /**< Owner */\
        ev_iocp_t                   io;                 /**< IOCP */\
        int                         stat;               /**< Read result */\
    }

/**
 * @brief Initialize #EV_TCP_BACKEND to Windows specific invalid value.
 */
#define EV_TCP_BACKEND_INIT     \
    {\
        0,\
        EV_IOCP_INIT,\
        { 0 },\
        { { EV_LIST_INIT, EV_LIST_INIT } },\
    }

typedef int (WSAAPI* ev_wsarecvfrom_fn)(
    SOCKET socket,
    LPWSABUF buffers,
    DWORD buffer_count,
    LPDWORD bytes,
    LPDWORD flags,
    struct sockaddr* addr,
    LPINT addr_len,
    LPWSAOVERLAPPED overlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE completion_routine);

typedef int (WSAAPI* ev_wsarecv_fn)(
    SOCKET socket,
    LPWSABUF buffers,
    DWORD buffer_count,
    LPDWORD bytes,
    LPDWORD flags,
    LPWSAOVERLAPPED overlapped,
    LPWSAOVERLAPPED_COMPLETION_ROUTINE completion_routine);

/**
 * @brief Windows backend for #ev_udp_write_t.
 */
#define EV_UDP_WRITE_BACKEND    \
    struct ev_udp_write_backend {\
        ev_iocp_t                   io;                 /**< IOCP handle */\
        int                         stat;               /**< Write result */\
        ev_udp_t*                   owner;              /**< Owner */\
    }

/**
 * @brief Windows backend for #ev_udp_read_t.
 */
#define EV_UDP_READ_BACKEND \
    struct ev_udp_read_backend {\
        ev_udp_t*                   owner;              /**< Owner */\
        ev_iocp_t                   io;                 /**< IOCP handle */\
        int                         stat;               /**< Read result */\
    }

/**
 * @brief Windows backend for #ev_udp_t.
 */
#define EV_UDP_BACKEND  \
    struct ev_udp_backend {\
        ev_wsarecv_fn               fn_wsarecv;\
        ev_wsarecvfrom_fn           fn_wsarecvfrom;     /**< WSARecvFrom() */\
    }

typedef enum ev_pipe_win_ipc_info_type
{
    EV_PIPE_WIN_IPC_INFO_TYPE_STATUS,               /**< #ev_pipe_win_ipc_info_t::data::as_status */
    EV_PIPE_WIN_IPC_INFO_TYPE_PROTOCOL_INFO,        /**< #ev_pipe_win_ipc_info_t::data::as_protocol_info */
}ev_pipe_win_ipc_info_type_t;

/**
 * @brief Windows IPC frame information.
 */
typedef struct ev_pipe_win_ipc_info
{
    ev_pipe_win_ipc_info_type_t type;               /**< Type */
    union
    {
        struct
        {
            DWORD               pid;                /**< PID */
        }as_status;

        WSAPROTOCOL_INFOW       as_protocol_info;   /**< Protocol info */
    }data;
} ev_pipe_win_ipc_info_t;

#define EV_PIPE_WRITE_BACKEND   \
    struct ev_pipe_write_backend {\
        ev_pipe_t*                  owner;              /**< Owner */\
        int                         stat;               /**< Write result */\
    }

/**
 * @brief Windows backend for #ev_pipe_read_req_t.
 */
#define EV_PIPE_READ_BACKEND    \
    struct ev_pipe_read_backend {\
        ev_pipe_t*                  owner;              /**< Owner */\
        int                         stat;               /**< Read result */\
    }

#define EV_PIPE_BACKEND_BUFFER_SIZE    \
        (sizeof(ev_ipc_frame_hdr_t) + sizeof(ev_pipe_win_ipc_info_t))

#define EV_PIPE_BACKEND \
    union ev_pipe_backend {\
        struct {\
            struct {\
                ev_iocp_t                   io;                 /**< IOCP backend */\
                ev_list_t                   r_pending;          /**< Request queue to be read */\
                ev_pipe_read_req_t*         r_doing;            /**< Request queue in reading */\
            }rio;\
            struct {\
                struct ev_pipe_backend_data_mode_wio {\
                    size_t                  idx;                /**< Index. Must not change. */\
                    ev_iocp_t               io;                 /**< IOCP backend */\
                    ev_pipe_write_req_t*    w_req;              /**< The write request mapping for IOCP */\
                    size_t                  w_buf_idx;          /**< The write buffer mapping for IOCP */\
                }iocp[EV_IOV_MAX];\
                unsigned                    w_io_idx;           /**< Usable index */\
                unsigned                    w_io_cnt;           /**< Busy count */\
                ev_list_t                   w_pending;          /**< Request queue to be write */\
                ev_list_t                   w_doing;            /**< Request queue in writing */\
                ev_pipe_write_req_t*        w_half;\
                size_t                      w_half_idx;\
            }wio;\
        } data_mode;\
        struct {\
            int                             iner_err;           /**< Internal error code */\
            DWORD                           peer_pid;           /**< Peer process ID */\
            struct {\
                struct {\
                    unsigned                rio_pending : 1;    /**< There is a IOCP request pending */\
                }mask;\
                struct {\
                    ev_pipe_read_req_t*     reading;            /**< Request for read */\
                    DWORD                   buf_idx;            /**< Buffer for read */\
                    DWORD                   buf_pos;            /**< Available position */\
                }reading;\
                ev_list_t                   pending;            /**< Buffer list to be filled */\
                int                         r_err;              /**< Error code if read failure */\
                DWORD                       remain_size;        /**< How many data need to read (bytes) */\
                ev_iocp_t                   io;                 /**< IOCP read backend */\
                uint8_t                     buffer[EV_PIPE_BACKEND_BUFFER_SIZE];\
            }rio;\
            struct {\
                struct {\
                    unsigned                iocp_pending : 1;   /**< There is a IOCP request pending */\
                }mask;\
                struct {\
                    ev_pipe_write_req_t*    w_req;              /**< The write request sending */\
                    size_t                  donecnt;            /**< Success send counter */\
                }sending;\
                ev_list_t                   pending;            /**< FIFO queue of write request */\
                int                         w_err;              /**< Error code if write failure */\
                ev_iocp_t                   io;                 /**< IOCP write backend, with #ev_write_t */\
                uint8_t                     buffer[EV_PIPE_BACKEND_BUFFER_SIZE];\
            }wio;\
        } ipc_mode;\
    }

/**
 * @brief Initialize #EV_PIPE_BACKEND to Windows specific invalid value.
 */
#define EV_PIPE_BACKEND_INVALID         { 0 }

/**
 * @brief Windows backend for #ev_process_t.
 */
#define EV_PROCESS_BACKEND  \
    struct ev_process_backend_s {\
        HANDLE                              wait_handle;\
    }

typedef struct ev_file_map_backend
{
    HANDLE  file_map_obj;
} ev_file_map_backend_t;
#define EV_FILE_MAP_BACKEND_INVALID     { NULL }

#ifdef __cplusplus
}
#endif

#endif

// #line 78 "ev.h"
#else
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/unix.h
// SIZE:    11287
// SHA-256: 1056acdf3ff770b9d6c5f6c1c182af2df13ee2b881f5b38e17e2586c31d28a4a
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/unix.h"
/**
 * @file
 */
#ifndef __EV_BACKEND_UNIX_H__
#define __EV_BACKEND_UNIX_H__

#include <netinet/in.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <errno.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(O_APPEND)
#   define EV_FS_O_APPEND       O_APPEND
#else
#   define EV_FS_O_APPEND       0
#endif

#if defined(O_CREAT)
#   define EV_FS_O_CREAT        O_CREAT
#else
#   define EV_FS_O_CREAT        0
#endif

#if defined(O_DSYNC)
#   define EV_FS_O_DSYNC        O_DSYNC
#else
#   define EV_FS_O_DSYNC        0
#endif

#if defined(O_EXCL)
#   define EV_FS_O_EXCL         O_EXCL
#else
#   define EV_FS_O_EXCL         0
#endif

#if defined(O_SYNC)
#   define EV_FS_O_SYNC         O_SYNC
#else
#   define EV_FS_O_SYNC         0
#endif

#if defined(O_TRUNC)
#   define EV_FS_O_TRUNC        O_TRUNC
#else
#   define EV_FS_O_TRUNC        0
#endif

#if defined(O_RDONLY)
#   define EV_FS_O_RDONLY       O_RDONLY
#else
#   define EV_FS_O_RDONLY       0
#endif

#if defined(O_WRONLY)
#   define EV_FS_O_WRONLY       O_WRONLY
#else
#   define EV_FS_O_WRONLY       0
#endif

#if defined(O_RDWR)
#   define EV_FS_O_RDWR         O_RDWR
#else
#   define EV_FS_O_RDWR         0
#endif

#define EV_FS_S_IRUSR           S_IRUSR
#define EV_FS_S_IWUSR           S_IWUSR
#define EV_FS_S_IXUSR           S_IXUSR
#define EV_FS_S_IRWXU           S_IRWXU

#define EV_FS_SEEK_BEG          SEEK_SET
#define EV_FS_SEEK_CUR          SEEK_CUR
#define EV_FS_SEEK_END          SEEK_END

typedef pid_t                   ev_os_pid_t;
#define EV_OS_PID_INVALID       ((pid_t)-1)

typedef int                     ev_os_pipe_t;
#define EV_OS_PIPE_INVALID      (-1)

typedef int                     ev_os_socket_t;
#define EV_OS_SOCKET_INVALID    (-1)

typedef pid_t                   ev_os_tid_t;
#define EV_OS_TID_INVALID       ((pid_t)(-1))

typedef int                     ev_os_file_t;
#define EV_OS_FILE_INVALID      (-1)

typedef void*                   ev_os_shdlib_t;
#define EV_OS_SHDLIB_INVALID    (NULL)

struct ev_write;
struct ev_read;

struct ev_nonblock_stream;

/**
 * @brief Typedef of #ev_nonblock_stream.
 */
typedef struct ev_nonblock_stream ev_nonblock_stream_t;

/**
 * @brief Write callback
 * @param[in] req       Write request
 * @param[in] size      Write size
 * @param[in] stat      Write result
 */
typedef void(*ev_stream_write_cb)(ev_nonblock_stream_t* stream, struct ev_write* req, ssize_t size);

/**
 * @brief Read callback
 * @param[in] req       Read callback
 * @param[in] size      Read size
 * @param[in] stat      Read result
 */
typedef void(*ev_stream_read_cb)(ev_nonblock_stream_t* stream, struct ev_read* req, ssize_t size);

/**
 * @brief Buffer
 * @internal Must share the same layout with `struct iovec`.
 */
typedef struct ev_buf
{
    void*                       data;               /**< Data address */
    size_t                      size;               /**< Data size */
} ev_buf_t;

/**
 * @brief Initialize #ev_buf_t.
 * @param[in] buf   Data address.
 * @param[in] len   Data length.
 */
#define EV_BUF_INIT(buf, len)   { (void*)buf, (size_t)len }

/**
 * @brief Unix implementation of once token.
 */
struct ev_once
{
    pthread_once_t              guard;              /**< Once token */
};

/**
 * @brief Initialize #ev_once_t to Unix specific structure.
 */
#define EV_ONCE_INIT            { PTHREAD_ONCE_INIT }

struct ev_nonblock_io;

/**
 * @brief Typedef of #ev_nonblock_io.
 */
typedef struct ev_nonblock_io ev_nonblock_io_t;

/**
 * @brief IO active callback
 * @param[in] io    IO object
 * @param[in] evts  IO events
 */
typedef void(*ev_nonblock_io_cb)(ev_nonblock_io_t* io, unsigned evts, void* arg);

/**
 * @brief Nonblock IO.
 */
struct ev_nonblock_io
{
    ev_map_node_t               node;               /**< #EV_LOOP_BACKEND::io */
    struct
    {
        int                     fd;                 /**< File descriptor */
        unsigned                c_events;           /**< Current events */
        unsigned                n_events;           /**< Next events */
        ev_nonblock_io_cb       cb;                 /**< IO active callback */
        void*                   arg;                /**< User data */
    }data;
};

/**
 * @brief Initialize #ev_nonblock_io_t to an invalid value.
 */
#define EV_NONBLOCK_IO_INVALID  \
    {\
        EV_MAP_NODE_INIT,\
        {\
            0,\
            0,\
            0,\
            NULL,\
            NULL,\
        }\
    }

/**
 * @brief Unix backend for #ev_async_t.
 */
#define EV_ASYNC_BACKEND    \
    struct ev_async_plt {\
        /**\
         * @brief pipefd for wakeup.\
         * To wakeup, write data to pipfd[1].\
         */\
        int                         pipfd[2];\
        ev_nonblock_io_t            io;\
    }

/**
 * @brief Initialize #EV_ASYNC_BACKEND to an Unix specific invalid value.
 */
#define EV_ASYNC_PLT_INVALID    { { -1, -1 }, EV_NONBLOCK_IO_INVALID }

/**
 * @brief Unix backend for #ev_loop_t.
 */
#define EV_LOOP_BACKEND \
    struct ev_loop_plt {\
        int                         pollfd;             /**< Multiplexing */\
        ev_map_t                    io;                 /**< table for #ev_nonblock_io_t */\
        struct {\
            int                     evtfd[2];           /**< [0] for read, [1] for write. */\
            ev_nonblock_io_t        io;\
        } threadpool;\
    }

/**
 * @brief Initialize #EV_LOOP_BACKEND to Unix specific invalid value.
 */
#define EV_LOOP_PLT_INIT        \
    {\
        -1,\
        EV_MAP_INIT(NULL, NULL),\
        {\
            { EV_OS_PIPE_INVALID, EV_OS_PIPE_INVALID },\
            EV_NONBLOCK_IO_INVALID,\
        }\
    }

/**
 * @brief Unix backend for #ev_tcp_read_req_t.
 */
#define EV_TCP_READ_BACKEND \
    struct ev_tcp_read_backend {\
        int                         _useless[0];        /**< Useless field */\
    }

/**
 * @brief Unix backend for #ev_tcp_write_req_t.
 */
#define EV_TCP_WRITE_BACKEND    \
    struct ev_tcp_write_backend {\
        int                         _useless[0];        /**< Useless field */\
    }

/**
 * @brief Unix backend for #ev_udp_read_t.
 */
#define EV_UDP_READ_BACKEND \
    struct ev_udp_read_backend {\
        int                         _useless[0];        /**< Useless field */\
    }

/**
 * @brief Unix backend for #ev_udp_write_t.
 */
#define EV_UDP_WRITE_BACKEND    \
    struct ev_udp_write_backend {\
        struct sockaddr_storage     peer_addr;          /**< Peer address */\
    }

/**
 * @brief Nonblock stream.
 */
struct ev_nonblock_stream
{
    struct ev_loop*             loop;               /**< Event loop */

    struct
    {
        unsigned                io_abort : 1;       /**< No futher IO allowed */
        unsigned                io_reg_r : 1;       /**< IO registered read event */
        unsigned                io_reg_w : 1;       /**< IO registered write event */
    }flags;

    ev_nonblock_io_t            io;                 /**< IO object */

    struct
    {
        ev_list_t               w_queue;            /**< Write queue */
        ev_list_t               r_queue;            /**< Read queue */
    }pending;

    struct
    {
        ev_stream_write_cb      w_cb;               /**< Write callback */
        ev_stream_read_cb       r_cb;               /**< Read callback */
    }callbacks;
};

/**
 * @brief Initialize #ev_nonblock_stream_t to Unix specific invalid value.
 */
#define EV_NONBLOCK_STREAM_INIT \
    {\
        NULL,                           /* .loop */\
        { 0, 0, 0, 0, 0 },              /* .flags */\
        EV_NONBLOCK_IO_INVALID,         /* .io */\
        { EV_LIST_INIT, EV_LIST_INIT }, /* .pending */\
        { NULL, NULL }                  /* .callbacks */\
    }

/**
 * @brief Initialize #EV_TCP_BACKEND to Unix specific invalid value.
 */
#define EV_TCP_BACKEND_INIT         { { { EV_NONBLOCK_IO_INVALID, EV_LIST_INIT } } }

/**
 * @brief Unix backend for #ev_udp_t.
 */
#define EV_UDP_BACKEND  \
    struct ev_udp_backend {\
        ev_nonblock_io_t                    io;                 /**< Backend IO */\
    }

/**
 * @brief Unix backend for #ev_pipe_read_req_t.
 */
#define EV_PIPE_READ_BACKEND    \
    struct ev_pipe_read_backend {\
        int                                 _useless[0];        /**< Useless field */\
    }

/**
 * @brief Unix backend for #ev_pipe_write_req_t.
 */
#define EV_PIPE_WRITE_BACKEND   \
    struct ev_pipe_write_backend {\
        int                                 _useless[0];        /**< Useless field */\
    }

/**
 * @brief Unix backend for #ev_pipe_t.
 */
#define EV_PIPE_BACKEND \
    union ev_pipe_backend {\
        struct {\
            ev_nonblock_stream_t            stream;             /**< Stream */\
        }data_mode;\
        struct {\
            ev_nonblock_io_t                io;                 /**< IO object */\
            struct {\
                unsigned                    wio_pending : 1;    /**< Write pending */\
                unsigned                    rio_pending : 1;    /**< Read pending */\
                unsigned                    no_cmsg_cloexec : 1;/**< No MSG_CMSG_CLOEXEC */\
            }mask;\
            struct {\
                struct {\
                    size_t                  head_read_size;     /**< Head read size */\
                    size_t                  data_remain_size;   /**< Data remain to read */\
                    size_t                  buf_idx;            /**< Buffer index to fill */\
                    size_t                  buf_pos;            /**< Buffer position to fill */\
                    ev_pipe_read_req_t*     reading;            /**< Current handling request */\
                }curr;\
                ev_list_t                   rqueue;             /**< #ev_pipe_read_req_t */\
                uint8_t                     buffer[sizeof(ev_ipc_frame_hdr_t)];\
            }rio;\
            struct {\
                struct {\
                    size_t                  head_send_capacity; /**< Head send capacity */\
                    size_t                  head_send_size;     /**< Head send size */\
                    size_t                  buf_idx;            /**< Buffer index to send */\
                    size_t                  buf_pos;            /**< Buffer position to send */\
                    ev_pipe_write_req_t*    writing;            /**< Currernt handling request */\
                }curr;\
                ev_list_t                   wqueue;             /**< #ev_pipe_write_req_t */\
                uint8_t                     buffer[sizeof(ev_ipc_frame_hdr_t)];\
            }wio;\
        }ipc_mode;\
    }

/**
 * @brief Initialize #EV_PIPE_BACKEND to Unix specific invalid value.
 */
#define EV_PIPE_BACKEND_INVALID         { 0 }

/**
 * @brief Unix backend for #ev_process_t.
 */
#define EV_PROCESS_BACKEND  \
    struct ev_process_backend_s {\
        struct {\
            int                             waitpid : 1;     /**< Already call waitpid() */\
        } flags;\
    }

typedef struct ev_file_map_backend
{
    int                                     _useless;       /**< Ignored. */
} ev_file_map_backend_t;
#define EV_FILE_MAP_BACKEND_INVALID     { 0 }

#ifdef __cplusplus
}
#endif

#endif

// #line 80 "ev.h"
#endif

////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/atomic.h
// SIZE:    11780
// SHA-256: fe46c5ee3b14d2e88af2e8a46548890db6bcd86001b6da8022689a7acefd5074
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/atomic.h"
#ifndef __EV_ATOMIC_H__
#define __EV_ATOMIC_H__

#if __STDC_VERSION__ >= 201112L && !defined(__STDC_NO_ATOMICS__)
/*
 * For compiler that support C11 and atomic, just use the standard header.
 */
#include <stdatomic.h>

typedef atomic_int_fast32_t ev_atomic32_t;
typedef atomic_int_fast64_t ev_atomic64_t;

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_init
 * @{
 */
#define ev_atomic32_init(obj, desired)  atomic_init(obj, desired)
#define ev_atomic64_init(obj, desired)  atomic_init(obj, desired)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_store
 * @{
 */
#define ev_atomic32_store(obj, desired) atomic_store(obj, desired)
#define ev_atomic64_store(obj, desired) atomic_store(obj, desired)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_load
 * @{
 */
#define ev_atomic32_load(obj) atomic_load(obj)
#define ev_atomic64_load(obj) atomic_load(obj)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_exchange
 * @{
 */
#define ev_atomic32_exchange(obj, desired) atomic_exchange(obj, desired)
#define ev_atomic64_exchange(obj, desired) atomic_exchange(obj, desired)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_compare_exchange
 * @{
 */
#define ev_atomic32_compare_exchange_strong(obj, expected, desired) atomic_compare_exchange_strong(obj, expected, desired)  
#define ev_atomic64_compare_exchange_strong(obj, expected, desired) atomic_compare_exchange_strong(obj, expected, desired)
#define ev_atomic32_compare_exchange_weak(obj, expected, desired) atomic_compare_exchange_weak(obj, expected, desired)
#define ev_atomic64_compare_exchange_weak(obj, expected, desired) atomic_compare_exchange_weak(obj, expected, desired)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_add
 * @{
 */
#define ev_atomic32_fetch_add(obj, arg) atomic_fetch_add(obj, arg)
#define ev_atomic64_fetch_add(obj, arg) atomic_fetch_add(obj, arg)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_sub
 * @{
 */
#define ev_atomic32_fetch_sub(obj, arg) atomic_fetch_sub(obj, arg)
#define ev_atomic64_fetch_sub(obj, arg) atomic_fetch_sub(obj, arg)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_or
 * @{
 */
#define ev_atomic32_fetch_or(obj, arg)  atomic_fetch_or(obj, arg)
#define ev_atomic64_fetch_or(obj, arg)  atomic_fetch_or(obj, arg)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_xor
 * @{
 */
#define ev_atomic32_fetch_xor(obj, arg) atomic_fetch_xor(obj, arg)
#define ev_atomic64_fetch_xor(obj, arg) atomic_fetch_xor(obj, arg)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_and
 * @{
 */
#define ev_atomic32_fetch_and(obj, arg) atomic_fetch_and(obj, arg)
#define ev_atomic64_fetch_and(obj, arg) atomic_fetch_and(obj, arg)
/**
 * @}
 */

#elif defined(_WIN32)

#define EV_ATOMIC_WIN32 1

#include <Windows.h>

typedef LONG ev_atomic32_t;
typedef LONG64 ev_atomic64_t;

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_init
 * @{
 */
#define ev_atomic32_init(obj, desired)  (*(obj) = (desired))
#define ev_atomic64_init(obj, desired)  (*(obj) = (desired))
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_store
 * @{
 */
#define ev_atomic32_store(obj, desired) ((void)InterlockedExchange(obj, desired))
#define ev_atomic64_store(obj, desired) ((void)InterlockedExchange64(obj, desired))
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_load
 * @{
 */
#define ev_atomic32_load(obj) InerlockedOr(obj, 0)
#define ev_atomic64_load(obj) InerlockedOr64(obj, 0)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_exchange
 * @{
 */
#define ev_atomic32_exchange(obj, desired) InterlockedExchange(obj, desired)
#define ev_atomic64_exchange(obj, desired) InterlockedExchange64(obj, desired)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_compare_exchange
 * @{
 */
EV_API int ev_atomic32_compare_exchange_strong(volatile ev_atomic32_t* obj, int32_t* expected, int32_t desired);
EV_API int ev_atomic64_compare_exchange_strong(volatile ev_atomic64_t* obj, int64_t* expected, int64_t desired);
#define ev_atomic32_compare_exchange_weak(obj, expected, desired) ev_atomic32_compare_exchange_strong(obj, expected, desired)
#define ev_atomic64_compare_exchange_weak(obj, expected, desired) ev_atomic64_compare_exchange_strong(obj, expected, desired)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_add
 * @{
 */
#define ev_atomic32_fetch_add(obj, arg) (InterlockedAdd((obj), (arg)) - (arg))
#define ev_atomic64_fetch_add(obj, arg) (InterlockedAdd64((obj), (arg)) - (arg))
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_sub
 * @{
 */
#define ev_atomic32_fetch_sub(obj, arg) (InterlockedAdd(obj, -(arg)) + (arg))
#define ev_atomic64_fetch_sub(obj, arg) (InterlockedAdd64(obj, -(arg)) + (arg))
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_or
 * @{
 */
#define ev_atomic32_fetch_or(obj, arg)  InterlockedOr(obj, arg)
#define ev_atomic64_fetch_or(obj, arg)  InterlockedOr64(obj, arg)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_xor
 * @{
 */
#define ev_atomic32_fetch_xor(obj, arg) InterlockedXor(obj, arg)
#define ev_atomic64_fetch_xor(obj, arg) InterlockedXor64(obj, arg)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_and
 * @{
 */
#define ev_atomic32_fetch_and(obj, arg) InterlockedAnd(obj, arg)
#define ev_atomic64_fetch_and(obj, arg) InterlockedAnd64(obj, arg)
/**
 * @}
 */

#elif defined(__GNUC__) || defined(__clang__)

typedef int32_t ev_atomic32_t;
typedef int64_t ev_atomic64_t;

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_init
 * @{
 */
#define ev_atomic32_init(obj, desired)  ev_atomic32_store(obj, desired)
#define ev_atomic64_init(obj, desired)  ev_atomic64_store(obj, desired)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_store
 * @{
 */
#define ev_atomic32_store(obj, desired) __atomic_store_n(obj, desired, __ATOMIC_SEQ_CST)
#define ev_atomic64_store(obj, desired) __atomic_store_n(obj, desired, __ATOMIC_SEQ_CST)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_load
 * @{
 */
#define ev_atomic32_load(obj) __atomic_load_n(obj, __ATOMIC_SEQ_CST)
#define ev_atomic64_load(obj) __atomic_load_n(obj, __ATOMIC_SEQ_CST)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_exchange
 * @{
 */
#define ev_atomic32_exchange(obj, desired) __atomic_exchange_n(obj, desired, __ATOMIC_SEQ_CST)
#define ev_atomic64_exchange(obj, desired) __atomic_exchange_n(obj, desired, __ATOMIC_SEQ_CST)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_compare_exchange
 * @{
 */
#define ev_atomic32_compare_exchange_strong(obj, expected, desired) __atomic_compare_exchange_n(obj, expected, desired, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define ev_atomic64_compare_exchange_strong(obj, expected, desired) __atomic_compare_exchange_n(obj, expected, desired, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define ev_atomic32_compare_exchange_weak(obj, expected, desired)   __atomic_compare_exchange_n(obj, expected, desired, 1, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define ev_atomic64_compare_exchange_weak(obj, expected, desired)   __atomic_compare_exchange_n(obj, expected, desired, 1, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_add
 * @{
 */
#define ev_atomic32_fetch_add(obj, arg) __atomic_fetch_add(obj, arg, __ATOMIC_SEQ_CST)
#define ev_atomic64_fetch_add(obj, arg) __atomic_fetch_add(obj, arg, __ATOMIC_SEQ_CST)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_sub
 * @{
 */
#define ev_atomic32_fetch_sub(obj, arg) __atomic_fetch_sub(obj, arg, __ATOMIC_SEQ_CST)
#define ev_atomic64_fetch_sub(obj, arg) __atomic_fetch_sub(obj, arg, __ATOMIC_SEQ_CST)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_or
 * @{
 */
#define ev_atomic32_fetch_or(obj, arg)  __atomic_fetch_or(obj, arg, __ATOMIC_SEQ_CST)
#define ev_atomic64_fetch_or(obj, arg)  __atomic_fetch_or(obj, arg, __ATOMIC_SEQ_CST)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_xor
 * @{
 */
#define ev_atomic32_fetch_xor(obj, arg) __atomic_fetch_xor(obj, arg, __ATOMIC_SEQ_CST)
#define ev_atomic64_fetch_xor(obj, arg) __atomic_fetch_xor(obj, arg, __ATOMIC_SEQ_CST)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_and
 * @{
 */
#define ev_atomic32_fetch_and(obj, arg) __atomic_fetch_and(obj, arg, __ATOMIC_SEQ_CST)
#define ev_atomic64_fetch_and(obj, arg) __atomic_fetch_and(obj, arg, __ATOMIC_SEQ_CST)
/**
 * @}
 */

#else

#define EV_ATOMIC_LOCK_SIMULATION   1

typedef int32_t ev_atomic32_t;
typedef int64_t ev_atomic64_t;

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_init
 * @{
 */
EV_API void ev_atomic32_init(volatile ev_atomic32_t* obj, int32_t desired);
EV_API void ev_atomic64_init(volatile ev_atomic64_t* obj, int64_t desired);
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_store
 * @{
 */
EV_API void ev_atomic32_store(volatile ev_atomic32_t* obj, int32_t desired);
EV_API void ev_atomic64_store(volatile ev_atomic64_t* obj, int64_t desired);
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_load
 * @{
 */
EV_API int32_t ev_atomic32_load(volatile ev_atomic32_t* obj);
EV_API int64_t ev_atomic64_load(volatile ev_atomic64_t* obj);
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_exchange
 * @{
 */
EV_API int32_t ev_atomic32_exchange(volatile ev_atomic32_t* obj, int32_t desired);
EV_API int64_t ev_atomic64_exchange(volatile ev_atomic64_t* obj, int64_t desired);
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_compare_exchange
 * @{
 */
EV_API int ev_atomic32_compare_exchange_strong(volatile ev_atomic32_t* obj, int32_t* expected, int32_t desired);
EV_API int ev_atomic64_compare_exchange_strong(volatile ev_atomic64_t* obj, int64_t* expected, int64_t desired);
#define ev_atomic32_compare_exchange_weak(obj, expected, desired) ev_atomic32_compare_exchange_strong(obj, expected, desired)
#define ev_atomic64_compare_exchange_weak(obj, expected, desired) ev_atomic64_compare_exchange_strong(obj, expected, desired)
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_add
 * @{
 */
EV_API int32_t ev_atomic32_fetch_add(volatile ev_atomic32_t* obj, int32_t arg);
EV_API int64_t ev_atomic64_fetch_add(volatile ev_atomic64_t* obj, int64_t arg);
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_sub
 * @{
 */
EV_API int32_t ev_atomic32_fetch_sub(volatile ev_atomic32_t* obj, int32_t arg);
EV_API int64_t ev_atomic64_fetch_sub(volatile ev_atomic64_t* obj, int64_t arg);
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_or
 * @{
 */
EV_API int32_t ev_atomic32_fetch_or(volatile ev_atomic32_t* obj, int32_t arg);
EV_API int64_t ev_atomic64_fetch_or(volatile ev_atomic64_t* obj, int64_t arg);
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_xor
 * @{
 */
EV_API int32_t ev_atomic32_fetch_xor(volatile ev_atomic32_t* obj, int32_t arg);
EV_API int64_t ev_atomic32_fetch_xor(volatile ev_atomic64_t* obj, int64_t arg);
/**
 * @}
 */

/**
 * @see https://en.cppreference.com/w/c/atomic/atomic_fetch_and
 * @{
 */
EV_API int32_t ev_atomic32_fetch_and(volatile ev_atomic32_t* obj, int32_t arg);
EV_API int64_t ev_atomic64_fetch_and(volatile ev_atomic64_t* obj, int64_t arg);
/**
 * @}
 */

#endif

#endif

// #line 83 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/thread.h
// SIZE:    2457
// SHA-256: e80b6ec45afc023c374dd1d963bef792e3a5bb54a1e26a73372e960cf51281e9
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/thread.h"
#ifndef __EV_THREAD_H__
#define __EV_THREAD_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_Thread Thread
 * @{
 */

/**
 * @brief Thread callback
 * @param[in] arg       User data
 */
typedef void (*ev_thread_cb)(void *arg);

/**
 * @brief Thread attribute.
 */
typedef struct ev_thread_opt
{
    struct
    {
        unsigned have_stack_size : 1; /**< Enable stack size */
    } flags;
    size_t stack_size; /**< Stack size. */
} ev_thread_opt_t;

/**
 * @brief Thread.
 */
typedef struct ev_thread ev_thread_t;

/**
 * @brief Thread local storage.
 */
typedef struct ev_thread_key ev_thread_key_t;

/**
 * @brief Create thread
 * @param[out] thr  Thread handle
 * @param[in] opt   Option
 * @param[in] cb    Thread body
 * @param[in] arg   User data
 * @return          #ev_errno_t
 */
EV_API int ev_thread_init(ev_thread_t **thr, const ev_thread_opt_t *opt,
                          ev_thread_cb cb, void *arg);

/**
 * @brief Exit thread
 * @warning Cannot be called in thread body.
 * @param[in] thr       Thread handle
 * @param[in] timeout   Timeout in milliseconds. #EV_INFINITE_TIMEOUT to wait
 * infinite.
 * @return              #EV_ETIMEDOUT if timed out before thread terminated,
 *                      #EV_SUCCESS if thread terminated.
 */
EV_API int ev_thread_exit(ev_thread_t *thr, unsigned long timeout);

/**
 * @brief Get current thread id,
 * @return          Thread ID
 */
EV_API ev_os_tid_t ev_thread_id(void);

/**
 * @brief Suspends the execution of the calling thread.
 * @param[in] timeout   Timeout in milliseconds.
 */
EV_API void ev_thread_sleep(uint32_t timeout);

/**
 * @brief Initialize thread local storage.
 * @param[out] key  A pointer to thread local storage.
 * @return          #ev_errno_t
 */
EV_API int ev_thread_key_init(ev_thread_key_t **key);

/**
 * @brief Destroy thread local storage.
 * @param[in] key   A initialized thread local storage handler.
 */
EV_API void ev_thread_key_exit(ev_thread_key_t *key);

/**
 * @brief Set thread local value.
 * @param[in] key   A initialized thread local storage handler.
 * @param[in] val   A thread specific value.
 */
EV_API void ev_thread_key_set(ev_thread_key_t *key, void *val);

/**
 * @brief Get thread local value.
 * @param[in] key   A initialized thread local storage handler.
 * @return          A thread specific value.
 */
EV_API void *ev_thread_key_get(ev_thread_key_t *key);

/**
 * @} EV_Thread
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 84 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/request.h
// SIZE:    2347
// SHA-256: db89b3769d91bcbba58356b36b5a0092d51eb0666a5d78a7842de1cb3285d73f
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/request.h"
#ifndef __EV_REQUEST_H__
#define __EV_REQUEST_H__
#ifdef __cplusplus
extern "C" {
#endif

struct ev_loop;

/**
 * @brief Read request
 */
typedef struct ev_read
{
    ev_list_node_t          node;               /**< Intrusive node */
    struct
    {
        ev_buf_t*           bufs;               /**< Buffer list */
        size_t              nbuf;               /**< Buffer list count */
        size_t              capacity;           /**< Total bytes of buffer */
        size_t              size;               /**< Data size */
        ev_buf_t            bufsml[EV_IOV_MAX]; /**< Bound buffer list */
    }data;                                      /**< Data field */
} ev_read_t;
#define EV_READ_INVALID     \
    {\
        EV_LIST_NODE_INIT,/* .node */\
        {/* .data */\
            NULL,                                                   /* .data.bufs */\
            0,                                                      /* .data.nbuf */\
            0,                                                      /* .data.capacity */\
            0,                                                      /* .data.size */\
            { EV_INIT_REPEAT(EV_IOV_MAX, EV_BUF_INIT(NULL, 0)), },  /* .data.bufsml */\
        },\
    }

/**
 * @brief Write request
 */
typedef struct ev_write
{
    ev_list_node_t          node;               /**< Intrusive node */
    ev_buf_t*               bufs;               /**< Buffer list */
    size_t                  nbuf;               /**< Buffer list count */
    size_t                  size;               /**< Write size */
    size_t                  capacity;           /**< Total bytes need to send */
    ev_buf_t                bufsml[EV_IOV_MAX]; /**< Bound buffer list */
} ev_write_t;
#define EV_WRITE_INVALID    \
    {\
        EV_LIST_NODE_INIT,                                          /* .node */\
        NULL,                                                       /* .data.bufs */\
        0,                                                          /* .data.nbuf */\
        0,                                                          /* .data.size */\
        0,                                                          /* .data.capacity */\
        { EV_INIT_REPEAT(EV_IOV_MAX, EV_BUF_INIT(NULL, 0)), }       /* .data.bufsml */\
    }

#ifdef __cplusplus
}
#endif
#endif

// #line 85 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/mutex.h
// SIZE:    1500
// SHA-256: a5601678145d8d6cdc8de0e9d25213c9f39086da7da073b7c0d8260807256f94
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/mutex.h"
#ifndef __EV_MUTEX_H__
#define __EV_MUTEX_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_MUTEX Mutex
 * @{
 */

/**
 * @brief Mutex handle type.
 */
typedef struct ev_mutex ev_mutex_t;

/**
 * @brief Initialize the mutex.
 * @param[out] handle   Mutex handle
 * @param[in] recursive Force recursive mutex. Set to non-zero to force create a
 *   recursive mutex. However, a value of zero does not means it is a non-
 *   recursive mutex, it is implementation depend.
 */
EV_API void ev_mutex_init(ev_mutex_t **handle, int recursive);

/**
 * @brief Destroy the mutex object referenced by \p handle
 * @param[in] handle    Mutex object
 */
EV_API void ev_mutex_exit(ev_mutex_t *handle);

/**
 * @brief The mutex object referenced by \p handle shall be locked.
 * @param[in] handle    Mutex object
 */
EV_API void ev_mutex_enter(ev_mutex_t *handle);

/**
 * @brief Release the mutex object referenced by \p handle.
 * @param[in] handle    Mutex object
 */
EV_API void ev_mutex_leave(ev_mutex_t *handle);

/**
 * @brief If the mutex object referenced by \p handle is currently locked, the
 *   call shall return immediately.
 * @param[in] handle    Mutex object.
 * @return              #EV_SUCCESS: a lock on the mutex object referenced by \p
 * handle is acquired.
 * @return              #EV_EBUSY: The \p handle could not be acquired because
 * it was already locked.
 */
EV_API int ev_mutex_try_enter(ev_mutex_t *handle);

/**
 * @} EV_MUTEX
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 86 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/sem.h
// SIZE:    1290
// SHA-256: ded2be40fb62d14dbe7663825024c416ea7d6c86440ece968ed9b907ee54851e
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/sem.h"
#ifndef __EV_SEMAPHORE_H__
#define __EV_SEMAPHORE_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_SEMAPHORE Semaphore
 * @{
 */

/**
 * @brief Semaphore handle type.
 */
typedef struct ev_sem_s ev_sem_t;

/**
 * @brief Initializes the unnamed semaphore at the address pointed to by \p sem.
 * @param[out] sem      Semaphore to be initialized.
 * @param[in] value     Initial value
 */
EV_API void ev_sem_init(ev_sem_t** sem, unsigned value);

/**
 * @brief Destroy the unnamed semaphore at the address pointed to by \p sem.
 * @param[in] sem       Semaphore handle
 */
EV_API void ev_sem_exit(ev_sem_t* sem);

/**
 * @brief Increments (unlocks)  the  semaphore pointed to by \p sem.
 * @param[in] sem       Semaphore handle
 */
EV_API void ev_sem_post(ev_sem_t* sem);

/**
 * @brief Decrements (locks) the semaphore pointed to by \p sem.
 * @param[in] sem       Semaphore handle
 */
EV_API void ev_sem_wait(ev_sem_t* sem);

/**
 * @brief If the decrement cannot be immediately performed, then call returns an
 *   error #EV_EAGAIN instead of blocking.
 * @param[in] sem       Semaphore handle
 * @return              #EV_SUCCESS if success, #EV_EAGAIN if failed.
 */
EV_API int ev_sem_try_wait(ev_sem_t* sem);

/**
 * @} EV_SEMAPHORE
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 87 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/once.h
// SIZE:    906
// SHA-256: ba57dd7e547b66796c6bf4dcd9e63ad01d89c6a542f9125bb9fa35b29ee4e0d6
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/once.h"
#ifndef __EV_ONCE_H__
#define __EV_ONCE_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_ONCE Once
 * @{
 */

/**
 * @brief Typedef of #ev_once.
 */
typedef struct ev_once ev_once_t;

/**
 * @brief An application-defined callback function.
 *
 * Specify a pointer to this function when calling the #ev_once_execute function.
 */
typedef void(*ev_once_cb)(void);

/**
 * @brief Executes the specified function one time.
 *
 * No other threads that specify the same one-time initialization structure can
 * execute the specified function while it is being executed by the current thread.
 *
 * @see #EV_ONCE_INIT
 * @param[in] guard     A pointer to the one-time initialized structure.
 * @param[in] cb        A pointer to an application-defined #ev_once_cb function.
 */
EV_API void ev_once_execute(ev_once_t* guard, ev_once_cb cb);

/**
 * @} EV_ONCE
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 88 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/shmem.h
// SIZE:    1252
// SHA-256: 8af4ad69977271692db5c5c1a93933d2cf66db5b76dbcf5b6fdcca07e12dac3f
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/shmem.h"
#ifndef __EV_SHARD_MEMORY_H__
#define __EV_SHARD_MEMORY_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_SHARED_MEMORY Shared memory
 * @{
 */

/**
 * @brief Shared memory type.
 */
typedef struct ev_shmem ev_shmem_t;

/**
 * @brief Create a new shared memory
 * @param[out] shm  Shared memory token
 * @param[in] key   Shared memory key
 * @param[in] size  Shared memory size
 * @return          #ev_errno_t
 */
EV_API int ev_shmem_init(ev_shmem_t **shm, const char *key, size_t size);

/**
 * @brief Open a existing shared memory
 * @param[out] shm  Shared memory token
 * @param[in] key   Shared memory key
 * @return          #ev_errno_t
 */
EV_API int ev_shmem_open(ev_shmem_t **shm, const char *key);

/**
 * @brief Close shared memory
 * @param[in] shm   Shared memory token
 */
EV_API void ev_shmem_exit(ev_shmem_t *shm);

/**
 * @brief Get shared memory address
 * @param[in] shm   Shared memory token
 * @return          Shared memory address
 */
EV_API void *ev_shmem_addr(ev_shmem_t *shm);

/**
 * @brief Get shared memory size
 * @param[in] shm   Shared memory token
 * @return          Shared memory size
 */
EV_API size_t ev_shmem_size(ev_shmem_t *shm);

/**
 * @} EV_SHARED_MEMORY
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 89 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/shdlib.h
// SIZE:    1351
// SHA-256: bbfed6c3850d1af246dfec8c518af2af159cd6c6187bfc0dcaa7967acbec3f78
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/shdlib.h"
#ifndef __EV_SHARED_LIBRARY_H__
#define __EV_SHARED_LIBRARY_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_SHAREDLIBRARY Shared library
 * @{
 */

/**
 * @brief Shared library handle.
 */
typedef struct ev_shdlib
{
    ev_os_shdlib_t  handle; /**< OS shared library handles */
} ev_shdlib_t;

/**
 * @brief Static initializer for #ev_shdlib_t.
 */
#define EV_SHDLIB_INVALID   { EV_OS_SHDLIB_INVALID }

/**
 * @brief Opens a shared library.
 * @param[out] lib - The opened library handle.
 * @param[in] filename - The name of the shared library. Encoding in UTF-8.
 * @param[out] errmsg - The error message if this function failed (the return
 *   value is non-zero). Use #ev_free() to release it.
 * @return #ev_errno_t
 */
int ev_dlopen(ev_shdlib_t* lib, const char* filename, char** errmsg);

/**
 * @brief Close the shared library.
 * @param[in] lib - The opened library handle.
 */
void ev_dlclose(ev_shdlib_t* lib);

/**
 * @brief Retrieves a data pointer from a dynamic library.
 * @note It is legal for a symbol to map to `NULL`.
 * @param[in] lib - The opened library handle.
 * @param[in] name - The name of the symbol.
 * @param[out] ptr - The address of the symbol.
 * @return #ev_errno_t
 */
int ev_dlsym(ev_shdlib_t* lib, const char* name, void** ptr);

/**
 * @} EV_SHAREDLIBRARY
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 90 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/time.h
// SIZE:    787
// SHA-256: 9fc3e35ec688b95caa98f8d5edf76ed0b4f7ed6309381f4cd18d18e6a361d721
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/time.h"
#ifndef __EV_TIME_H__
#define __EV_TIME_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_TIME Time
 * @{
 */

/**
 * @brief Infinite timeout.
 */
#define EV_INFINITE_TIMEOUT         ((uint32_t)-1)

/**
 * @brief Time spec
 */
struct ev_timespec_s;

/**
 * @brief Typedef of #ev_timespec_s.
 */
typedef struct ev_timespec_s ev_timespec_t;

/**
 * @brief High-accuracy time type.
 */
struct ev_timespec_s
{
    uint64_t    tv_sec;     /**< seconds */
    uint32_t    tv_nsec;    /**< nanoseconds */
};
#define EV_TIMESPEC_INVALID \
    {\
        0,\
        0,\
    }

/**
 * @brief Returns the current high-resolution real time in nanoseconds.
 * @return Time in nanoseconds.
 */
EV_API uint64_t ev_hrtime(void);

/**
 * @} EV_TIME
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 91 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/handle.h
// SIZE:    3412
// SHA-256: 0f125dc97a9228af87f8e33bfb974e19d1ae70208f1782d5626a9270b2e28ee8
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/handle.h"
#ifndef __EV_HANDLE_H__
#define __EV_HANDLE_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_HANDLE Handle
 * @{
 */

typedef enum ev_role
{
    EV_ROLE_UNKNOWN         = -1,                   /**< Unknown type */

    EV_ROLE_EV_HANDLE       = 0,                    /**< Type of #ev_handle_t */
    EV_ROLE_EV_TIMER        = 1,                    /**< Type of #ev_timer_t */
    EV_ROLE_EV_ASYNC        = 2,                    /**< Type of #ev_async_t */
    EV_ROLE_EV_PIPE         = 3,                    /**< Type of #ev_pipe_t */
    EV_ROLE_EV_TCP          = 4,                    /**< Type of #ev_tcp_t */
    EV_ROLE_EV_UDP          = 5,                    /**< Type of #ev_udp_t */
    EV_ROLE_EV_WORK         = 6,                    /**< Type of #ev_work_t */
    EV_ROLE_EV_FILE         = 7,                    /**< Type of #ev_file_t */
    EV_ROLE_EV_REQ_UDP_R    = 100,                  /**< Type of #ev_udp_read_t */
    EV_ROLE_EV_REQ_UDP_W    = 101,                  /**< Type of #ev_udp_write_t */
    EV_ROLE_EV__RANGE_BEG   = EV_ROLE_EV_HANDLE,
    EV_ROLE_EV__RANGE_END   = EV_ROLE_EV_REQ_UDP_W,

    EV_ROLE_OS_SOCKET       = 1000,                 /**< OS socket */
    EV_ROLE_OS__RANGE_BEG   = EV_ROLE_OS_SOCKET,
    EV_ROLE_OS__RANGE_END   = EV_ROLE_OS_SOCKET,
} ev_role_t;

struct ev_handle;
typedef struct ev_handle ev_handle_t;

/**
 * @brief Called when a object is closed
 * @param[in] handle    A base handle
 */
typedef void(*ev_handle_cb)(ev_handle_t* handle);

/**
 * @brief Base class for all major object.
 */
struct ev_handle
{
    struct ev_loop*         loop;               /**< The event loop belong to */
    ev_list_node_t          handle_queue;       /**< Node for #ev_loop_t::handles */

    struct
    {
        ev_role_t           role;               /**< The type of this object */
        unsigned            flags;              /**< Handle flags */
    } data;                                     /**< Data field */

    struct
    {
        /**
         * @brief Backlog status.
         * | Status         | Meaning                     |
         * | -------------- | --------------------------- |
         * | EV_ENOENT      | Not in backlog queue        |
         * | EV_EEXIST      | In backlog queue            |
         */
        int                 status;
        ev_handle_cb        cb;                 /**< Callback */
        ev_list_node_t      node;               /**< Node for #ev_loop_t::backlog */
    } backlog;

    struct
    {
        ev_handle_cb        close_cb;           /**< Close callback */
        ev_list_node_t      node;               /**< Close queue token */
    } endgame;
};

/**
 * @brief Initialize #ev_handle_t to an invalid value.
 */
#define EV_HANDLE_INVALID       \
    {\
        NULL,                       /* .loop */\
        EV_LIST_NODE_INIT,          /* .handle_queue */\
        {/* .data */\
            EV_ROLE_UNKNOWN,        /* .role */\
            0,                      /* .flags */\
        },\
        {/* .backlog */\
            EV_ECANCELED,           /* .status */\
            NULL,                   /* .cb */\
            EV_LIST_NODE_INIT,      /* .node */\
        },\
        {/* .endgame */\
            NULL,                   /* .close_cb */\
            EV_LIST_NODE_INIT,      /* .node */\
        },\
    }

/**
 * @} EV_HANDLE
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 92 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/loop.h
// SIZE:    5622
// SHA-256: a4851098894e725931c7e0c628d5ae5e6c714299755d0ab6d029d7d6a5e14ab4
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/loop.h"
#ifndef __EV_LOOP_H__
#define __EV_LOOP_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_EVENT_LOOP Event loop
 * @{
 */

/**
 * @brief Running mode of event loop.
 */
typedef enum ev_loop_mode
{
    /**
     * @brief Runs the event loop until there are no more active and referenced
     *   handles or requests.
     *
     * Returns non-zero if #ev_loop_stop() was called and there are
     * still active handles or requests. Returns zero in all other cases.
     */
    EV_LOOP_MODE_DEFAULT,

    /**
     * @brief Poll for I/O once.
     *
     * Note that this function blocks if there are no pending callbacks. Returns
     * zero when done (no active handles or requests left), or non-zero if more
     * callbacks are expected (meaning you should run the event loop again sometime
     * in the future).
     */
    EV_LOOP_MODE_ONCE,

    /**
     * @brief Poll for i/o once but don't block if there are no pending callbacks.
     *
     * Returns zero if done (no active handles or requests left), or non-zero if
     * more callbacks are expected (meaning you should run the event loop again
     * sometime in the future).
     */
    EV_LOOP_MODE_NOWAIT,
} ev_loop_mode_t;

typedef struct ev_work ev_work_t;

/**
 * @brief Thread pool task
 * @param[in] work  Work token
 */
typedef void (*ev_work_cb)(ev_work_t* work);

/**
 * @brief Work done callback in event loop
 * @param[in] work      Work token
 * @param[in] status    Work status
 */
typedef void (*ev_work_done_cb)(ev_work_t* work, int status);

/**
 * @brief Thread pool work token.
 */
struct ev_work
{
    ev_handle_t                     base;           /**< Base object */
    ev_queue_node_t                 node;           /**< List node */

    struct
    {
        struct ev_threadpool*       pool;           /**< Thread pool */

        /**
         * @brief Work status.
         * + #EV_ELOOP:     In queue but not called yet.
         * + #EV_EBUSY:     Already in process
         * + #EV_ECANCELED: Canceled
         * + #EV_SUCCESS:   Done
         */
        int                         status;

        ev_work_cb                  work_cb;        /**< work callback */
        ev_work_done_cb             done_cb;        /**< done callback */
    }data;
};
#define EV_WORK_INVALID \
    {\
        EV_HANDLE_INVALID,\
        EV_QUEUE_NODE_INVALID,\
        { NULL, EV_EINPROGRESS, NULL, NULL },\
    }

/**
 * @brief Typedef of #ev_loop.
 */
typedef struct ev_loop ev_loop_t;

/**
 * @brief Type definition for callback passed to #ev_loop_walk().
 * @param[in] handle    Object handle.
 * @param[in] arg       User defined argument.
 * @return              0 to continue, otherwise stop walk.
 */
typedef int (*ev_walk_cb)(ev_handle_t* handle, void* arg);

/**
 * @brief Initializes the given structure.
 * @param[out] loop     Event loop handler
 * @return              #ev_errno_t
 */
EV_API int ev_loop_init(ev_loop_t** loop);

/**
 * @brief Releases all internal loop resources.
 *
 * Call this function only when the loop has finished executing and all open
 * handles and requests have been closed, or it will return #EV_EBUSY. After
 * this function returns, the user can free the memory allocated for the loop.
 *
 * @param[in] loop      Event loop handler.
 * @return #ev_errno_t
 */
EV_API int ev_loop_exit(ev_loop_t* loop);

/**
 * @brief Stop the event loop, causing ev_loop_run() to end as soon as possible.
 *
 * This will happen not sooner than the next loop iteration. If this function
 * was called before blocking for i/o, the loop won't block for i/o on this
 * iteration.
 *
 * @param[in] loop      Event loop handler
 */
EV_API void ev_loop_stop(ev_loop_t* loop);

/**
 * @brief This function runs the event loop.
 * 
 * The \p mode can be one of:
 *
 * + #EV_LOOP_MODE_DEFAULT: Run the event loop until one of following conditions
 *   is met:
 *   1. there are no more active and referenced handles or requests. 
 *   2. \p timeout is reached.
 *
 * + #EV_LOOP_MODE_ONCE: Poll for I/O once. Returns either events are tiggered
 *   or \p timeout is reached.
 *
 * + #EV_LOOP_MODE_NOWAIT: Poll for i/o once but don't block if there are no
 *   pending callbacks. Parameter \p timeout is ignored.
 * 
 * @param[in] loop      Event loop handler
 * @param[in] mode      Running mode.
 * @param[in] timeout   Timeout in milliseconds. Use #EV_INFINITE_TIMEOUT to wait
 *   infinite.
 * @return              Returns zero when no active handles or requests left,
 *                      otherwise return non-zero
 * @see ev_loop_mode_t
 */
EV_API int ev_loop_run(ev_loop_t* loop, ev_loop_mode_t mode, uint32_t timeout);

/**
 * @brief Submit task into thread pool.
 * @param[in] loop      Event loop.
 * @param[in] token     Work token.
 * @param[in] work_cb   Work callback in thread pool.
 * @param[in] done_cb   Work done callback in event loop.
 * @return              #ev_errno_t
 */
EV_API int ev_loop_queue_work(ev_loop_t* loop, ev_work_t* token,
    ev_work_cb work_cb, ev_work_done_cb done_cb);

/**
 * @brief Cancel task.
 * @note No matter the task is canceled or not, the task always callback in the
 *   event loop.
 * @param[in] token     Work token
 * @return              #ev_errno_t
 */
EV_API int ev_loop_cancel(ev_work_t* token);

/**
 * @brief Walk the list of handles.
 * \p cb will be executed with the given arg.
 * @param[in] loop      The event loop.
 * @param[in] cb        Walk callback.
 * @param[in] arg       User defined argument.
 */
EV_API void ev_loop_walk(ev_loop_t* loop, ev_walk_cb cb, void* arg);

/**
 * @} EV_EVENT_LOOP
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 93 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/async.h
// SIZE:    1507
// SHA-256: 72110a9b21df7b574a0366c6e45c90500985718e56071ad4a16fe2f9954f839a
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/async.h"
#ifndef __EV_ASYNC_H__
#define __EV_ASYNC_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_ASYNC Async
 * @{
 */

/**
 * @brief Async handle type.
 */
typedef struct ev_async ev_async_t;

/**
 * @brief Type definition for callback passed to #ev_async_init().
 * @param[in] async   A pointer to #ev_async_t structure
 * @param[in] arg     User defined argument.
 */
typedef void (*ev_async_cb)(ev_async_t *async, void *arg);

/**
 * @brief Initialize the handle.
 *
 * A NULL callback is allowed.
 *
 * @param[in] loop          Event loop
 * @param[out] handle       A pointer to the structure
 * @param[in] activate_cb   Activate callback
 * @param[in] activate_arg  Activate argument.
 * @return                  #ev_errno_t
 */
EV_API int ev_async_init(ev_loop_t *loop, ev_async_t **handle,
                         ev_async_cb activate_cb, void *activate_arg);

/**
 * @brief Destroy the structure.
 * @param[in] handle    Async handle.
 * @param[in] close_cb  [Optional] Close callback.
 * @param[in] close_arg Close argument.
 * @note When \p close_cb is called, the \p handle object is already released.
 *   Do not access it.
 */
EV_API void ev_async_exit(ev_async_t *handle, ev_async_cb close_cb,
                          void *close_arg);

/**
 * @brief Wake up the event loop and call the async handle's callback.
 * @note MT-Safe
 * @param[in] handle    Async handle
 */
EV_API void ev_async_wakeup(ev_async_t *handle);

/**
 * @} EV_ASYNC
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 94 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/timer.h
// SIZE:    1852
// SHA-256: 69f3279b440218b37c34face176bf082cf18e48ddf0ff2fb23e568ce7bc478be
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/timer.h"
#ifndef __EV_TIMER_H__
#define __EV_TIMER_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_TIMER Timer
 * @{
 */

/**
 * @brief Timer handle type.
 */
typedef struct ev_timer ev_timer_t;

/**
 * @brief Type definition for callback passed to #ev_timer_start().
 * @param[in] timer     A pointer to #ev_timer_t structure
 */
typedef void (*ev_timer_cb)(ev_timer_t *timer, void* arg);

/**
 * @brief Initialize the handle.
 * @param[in] loop      A pointer to the event loop
 * @param[out] handle   The structure to initialize
 * @return              #ev_errno_t
 */
EV_API int ev_timer_init(ev_loop_t *loop, ev_timer_t **handle);

/**
 * @brief Destroy the timer
 * @warning The timer structure cannot be freed until close_cb is called.
 * @param[in] handle    Timer handle
 * @param[in] cb        Close callback.
 * @param[in] arg       User defined argument.
 */
EV_API void ev_timer_exit(ev_timer_t *handle, ev_timer_cb cb, void* arg);

/**
 * @brief Start the timer. timeout and repeat are in milliseconds.
 *
 * If timeout is zero, the callback fires on the next event loop iteration. If
 * repeat is non-zero, the callback fires first after timeout milliseconds and
 * then repeatedly after repeat milliseconds.
 *
 * @param[in] handle    Timer handle
 * @param[in] timeout   The first callback timeout
 * @param[in] repeat    Repeat timeout
 * @param[in] cb        Active callback
 * @param[in] arg       User defined argument.
 * @return              #ev_errno_t
 */
EV_API int ev_timer_start(ev_timer_t *handle, uint64_t timeout,
                          uint64_t repeat, ev_timer_cb cb, void* arg);

/**
 * @brief Stop the timer.
 *
 * the callback will not be called anymore.
 *
 * @param[in] handle    Timer handle
 */
EV_API void ev_timer_stop(ev_timer_t *handle);

/**
 * @} EV_TIMER
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 95 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/tcp.h
// SIZE:    5797
// SHA-256: 9ba2320f8106d7d52451cf6a21782ecf54984d92e2b547945d50a27ea6b7278b
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/tcp.h"
#ifndef __EV_TCP_H__
#define __EV_TCP_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_TCP TCP
 *
 * TCP layer.
 *
 * @{
 */

/**
 * @example tcp_echo_server.c
 * This is an example for how to use #ev_tcp_t as tcp server.
 */

/**
 * @brief TCP socket.
 */
typedef struct ev_tcp ev_tcp_t;

/**
 * @brief Close callback for #ev_tcp_t
 * @param[in] sock      A closed socket
 * @param[in] arg       User defined argument.
 */
typedef void (*ev_tcp_close_cb)(ev_tcp_t *sock, void *arg);

/**
 * @brief Accept callback
 * @param[in] lisn      Listen socket
 * @param[in] conn      Accepted socket
 * @param[in] stat      #ev_errno_t
 * @param[in] arg       User defined argument.
 */
typedef void (*ev_tcp_accept_cb)(ev_tcp_t *lisn, ev_tcp_t *conn, int stat,
                                 void *arg);

/**
 * @brief Connect callback
 * @param[in] sock      Connect socket
 * @param[in] stat      #ev_errno_t
 */
typedef void (*ev_tcp_connect_cb)(ev_tcp_t *sock, int stat, void *arg);

/**
 * @brief Write callback
 * @param[in] sock      Socket.
 * @param[in] size      Write result
 * @param[in] arg       User defined argument.
 */
typedef void (*ev_tcp_write_cb)(ev_tcp_t *sock, ssize_t size, void *arg);

/**
 * @brief Read callback
 * @param[in] sock      Socket.
 * @param[in] size      Read result.
 * @param[in] arg       User defined argument.
 */
typedef void (*ev_tcp_read_cb)(ev_tcp_t *sock, ssize_t size, void *arg);

/**
 * @brief Initialize a tcp socket
 * @param[in] loop      Event loop
 * @param[out] tcp      TCP handle
 */
EV_API int ev_tcp_init(ev_loop_t *loop, ev_tcp_t **tcp);

/**
 * @brief Destroy socket
 * @param[in] sock      Socket
 * @param[in] cb        Destroy callback
 * @param[in] arg       User defined argument.
 */
EV_API void ev_tcp_exit(ev_tcp_t *sock, ev_tcp_close_cb cb, void *arg);

/**
 * @brief Bind the handle to an address and port.
 * addr should point to an initialized struct sockaddr_in or struct
 * sockaddr_in6.
 * @param[in] tcp       Socket handler
 * @param[in] addr      Bind address
 * @param[in] addrlen   Address length
 * @return              #ev_errno_t
 */
EV_API int ev_tcp_bind(ev_tcp_t *tcp, const struct sockaddr *addr,
                       size_t addrlen);

/**
 * @brief Start listening for incoming connections.
 * @param[in] sock      Listen socket
 * @param[in] backlog   The number of connections the kernel might queue
 * @return              #ev_errno_t
 */
EV_API int ev_tcp_listen(ev_tcp_t *sock, int backlog);

/**
 * @brief Accept a connection from listen socket
 * @param[in] acpt          Listen socket
 * @param[in] conn          The socket to store new connection
 * @param[in] cb            Accept callback
 * @param[in] arg           User defined argument pass to \p cb.
 * @return                  #ev_errno_t
 */
EV_API int ev_tcp_accept(ev_tcp_t *acpt, ev_tcp_t *conn, ev_tcp_accept_cb cb,
                         void *arg);

/**
 * @brief Connect to address
 * @param[in] sock          Socket handle
 * @param[in] addr          Address
 * @param[in] size          Address size
 * @param[in] cb            Connect callback
 * @param[in] arg           Connect argument.
 * @return                  #ev_errno_t
 */
EV_API int ev_tcp_connect(ev_tcp_t *sock, struct sockaddr *addr, size_t size,
                          ev_tcp_connect_cb cb, void *arg);

/**
 * @brief Write data
 *
 * Once #ev_tcp_write() return #EV_SUCCESS, it take the ownership of \p req, so
 * you should not modify the content of it until bounded callback is called.
 *
 * It is a guarantee that every bounded callback of \p req will be called, with
 * following scene:
 *   + If write success or failure. The callback will be called with write
 * status.
 *   + If \p pipe is exiting but there are pending write request. The callback
 *     will be called with status #EV_ECANCELED.
 *
 * @param[in] sock      Socket handle
 * @param[in] bufs      Buffer list
 * @param[in] nbuf      Buffer number
 * @param[in] cb        Send result callback
 * @param[in] arg       User defined argument.
 * @return              #ev_errno_t
 */
EV_API int ev_tcp_write(ev_tcp_t *sock, ev_buf_t *bufs, size_t nbuf,
                        ev_tcp_write_cb cb, void *arg);

/**
 * @brief Read data
 *
 * Once #ev_tcp_read() return #EV_SUCCESS, it take the ownership of \p req, so
 * you should not modify the content of it until bounded callback is called.
 *
 * It is a guarantee that every bounded callback of \p req will be called, with
 * following scene:
 *   + If read success or failure. The callback will be called with read status.
 *   + If \p pipe is exiting but there are pending read request. The callback
 *     will be called with status #EV_ECANCELED.
 *
 * @param[in] sock  Socket handle
 * @param[in] bufs  Buffer list
 * @param[in] nbuf  Buffer number
 * @param[in] cb    Read result callback
 * @param[in] arg   User defined argument.
 * @return          #ev_errno_t
 */
EV_API int ev_tcp_read(ev_tcp_t *sock, ev_buf_t *bufs, size_t nbuf,
                       ev_tcp_read_cb cb, void *arg);

/**
 * @brief Get the current address to which the socket is bound.
 * @param[in] sock  Socket handle
 * @param[out] name A buffer to store address
 * @param[in,out] len   buffer size
 * @return          #ev_errno_t
 */
EV_API int ev_tcp_getsockname(ev_tcp_t *sock, struct sockaddr *name,
                              size_t *len);

/**
 * @brief Get the address of the peer connected to the socket.
 * @param[in] sock  Socket handle
 * @param[out] name A buffer to store address
 * @param[in,out] len   buffer size
 * @return          #ev_errno_t
 */
EV_API int ev_tcp_getpeername(ev_tcp_t *sock, struct sockaddr *name,
                              size_t *len);

/**
 * @} EV_TCP
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 96 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/udp.h
// SIZE:    8161
// SHA-256: a4395c06ff06bce34a4b8f0f2cb03e51dc4a669fa5b2d489960d03ed4fed6527
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/udp.h"
#ifndef __EV_UDP_H__
#define __EV_UDP_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_UDP UDP
 * @{
 */

/**
 * @brief Multicast operation.
 */
typedef enum ev_udp_membership
{
    EV_UDP_LEAVE_GROUP = 0, /**< Leave multicast group */
    EV_UDP_ENTER_GROUP = 1, /**< Join multicast group */
} ev_udp_membership_t;

/**
 * @brief UDP socket flags.
 */
typedef enum ev_udp_flags
{
    /**
     * @brief Do not bound to IPv4 address.
     */
    EV_UDP_IPV6_ONLY = 1,

    /**
     * @brief Reuse address. Only the last one can receive message.
     */
    EV_UDP_REUSEADDR = 2,
} ev_udp_flags_t;

/**
 * @brief UDP socket type.
 */
typedef struct ev_udp ev_udp_t;

/**
 * @brief Callback for #ev_udp_t
 * @param[in] udp   UDP handle
 * @param[in] arg   User defined argument.
 */
typedef void (*ev_udp_cb)(ev_udp_t *udp, void *arg);

/**
 * @brief Write callback
 * @param[in] udp       UDP socket.
 * @param[in] size      Write result.
 * @param[in] arg       User defined argument.
 */
typedef void (*ev_udp_write_cb)(ev_udp_t *udp, ssize_t size, void *arg);

/**
 * @brief Read callback
 * @param[in] udp       UDP socket.
 * @param[in] addr      Peer address.
 * @param[in] size      Read result.
 * @param[in] arg       User defined argument.
 */
typedef void (*ev_udp_recv_cb)(ev_udp_t *udp, const struct sockaddr *addr,
                               ssize_t size, void *arg);

/**
 * @brief Initialize a UDP handle.
 * @param[in] loop      Event loop
 * @param[out] udp      A UDP handle to initialize
 * @param[in] domain    AF_INET / AF_INET6 / AF_UNSPEC
 * @return              #ev_errno_t
 */
EV_API int ev_udp_init(ev_loop_t *loop, ev_udp_t **udp, int domain);

/**
 * @brief Close UDP handle
 * @param[in] udp       A UDP handle
 * @param[in] close_cb  Close callback
 * @param[in] close_arg User defined argument.
 */
EV_API void ev_udp_exit(ev_udp_t *udp, ev_udp_cb close_cb, void *close_arg);

/**
 * @brief Open a existing UDP socket
 * @note \p udp must be a initialized handle
 * @param[in] udp       A initialized UDP handle
 * @param[in] sock      A system UDP socket
 * @return              #ev_errno_t
 */
EV_API int ev_udp_open(ev_udp_t *udp, ev_os_socket_t sock);

/**
 * @brief Bind the UDP handle to an IP address and port.
 * @param[in] udp       A UDP handle
 * @param[in] addr      struct sockaddr_in or struct sockaddr_in6 with the
 *   address and port to bind to.
 * @param[in] flags     #ev_udp_flags_t
 * @return              #ev_errno_t
 */
EV_API int ev_udp_bind(ev_udp_t *udp, const struct sockaddr *addr,
                       unsigned flags);

/**
 * @brief Associate the UDP handle to a remote address and port, so every
 * message sent by this handle is automatically sent to that destination.
 * @param[in] udp       A UDP handle
 * @param[in] addr      Remote address
 * @return              #ev_errno_t
 */
EV_API int ev_udp_connect(ev_udp_t *udp, const struct sockaddr *addr);

/**
 * @brief Get the local IP and port of the UDP handle.
 * @param[in] udp       A UDP handle
 * @param[out] name     Pointer to the structure to be filled with the address
 * data. In order to support IPv4 and IPv6 struct sockaddr_storage should be
 * used.
 * @param[in,out] len   On input it indicates the data of the name field.
 *   On output it indicates how much of it was filled.
 * @return              #ev_errno_t
 */
EV_API int ev_udp_getsockname(ev_udp_t *udp, struct sockaddr *name,
                              size_t *len);

/**
 * @brief Get the remote IP and port of the UDP handle on connected UDP handles.
 * @param[in] udp       A UDP handle
 * @param[out] name     Pointer to the structure to be filled with the address
 * data. In order to support IPv4 and IPv6 struct sockaddr_storage should be
 * used.
 * @param[in,out] len   On input it indicates the data of the name field.
 *   On output it indicates how much of it was filled.
 * @return              #ev_errno_t
 */
EV_API int ev_udp_getpeername(ev_udp_t *udp, struct sockaddr *name,
                              size_t *len);

/**
 * @brief Set membership for a multicast address.
 * @param[in] udp               A UDP handle
 * @param[in] multicast_addr    Multicast address to set membership for.
 * @param[in] interface_addr    Interface address.
 * @param[in] membership        #ev_udp_membership_t
 * @return                      #ev_errno_t
 */
EV_API int ev_udp_set_membership(ev_udp_t *udp, const char *multicast_addr,
                                 const char         *interface_addr,
                                 ev_udp_membership_t membership);

/**
 * @brief Set membership for a source-specific multicast group.
 * @param[in] udp               A UDP handle
 * @param[in] multicast_addr    Multicast address to set membership for.
 * @param[in] interface_addr    Interface address.
 * @param[in] source_addr       Source address.
 * @param[in] membership        #ev_udp_membership_t
 * @return                      #ev_errno_t
 */
EV_API int ev_udp_set_source_membership(ev_udp_t           *udp,
                                        const char         *multicast_addr,
                                        const char         *interface_addr,
                                        const char         *source_addr,
                                        ev_udp_membership_t membership);

/**
 * @brief Set IP multicast loop flag. Makes multicast packets loop back to local
 * sockets.
 * @param[in] udp   A UDP handle
 * @param[in] on    bool
 * @return          #ev_errno_t
 */
EV_API int ev_udp_set_multicast_loop(ev_udp_t *udp, int on);

/**
 * @brief Set the multicast ttl.
 * @param[in] udp   A UDP handle
 * @param[in] ttl   1 through 255
 * @return          #ev_errno_t
 */
EV_API int ev_udp_set_multicast_ttl(ev_udp_t *udp, int ttl);

/**
 * @brief Set the multicast interface to send or receive data on.
 * @param[in] udp               A UDP handle
 * @param[in] interface_addr    interface address.
 * @return                      #ev_errno_t
 */
EV_API int ev_udp_set_multicast_interface(ev_udp_t   *udp,
                                          const char *interface_addr);

/**
 * @brief Set broadcast on or off.
 * @param[in] udp   A UDP handle
 * @param[in] on    1 for on, 0 for off
 * @return          #ev_errno_t
 */
EV_API int ev_udp_set_broadcast(ev_udp_t *udp, int on);

/**
 * @brief Set the time to live.
 * @param[in] udp   A UDP handle
 * @param[in] ttl   1 through 255.
 * @return          #ev_errno_t
 */
EV_API int ev_udp_set_ttl(ev_udp_t *udp, int ttl);

/**
 * @brief Send data over the UDP socket.
 *
 * If the socket has not previously been bound with #ev_udp_bind() it will be
 * bound to 0.0.0.0 (the "all interfaces" IPv4 address) and a random port
 * number.
 *
 * @param[in] udp   A UDP handle
 * @param[in] bufs  Buffer list
 * @param[in] nbuf  Buffer number
 * @param[in] addr  Peer address
 * @param[in] cb    Send result callback
 * @param[in] arg   User defined argument.
 * @return          #ev_errno_t
 */
EV_API int ev_udp_send(ev_udp_t *udp, ev_buf_t *bufs, size_t nbuf,
                       const struct sockaddr *addr, ev_udp_write_cb cb,
                       void *arg);

/**
 * @brief Same as #ev_udp_send(), but won't queue a send request if it can't be
 *   completed immediately.
 * @param[in] udp   A UDP handle
 * @param[in] bufs  Buffer list
 * @param[in] nbuf  Buffer number
 * @param[in] addr  Peer address
 * @param[in] cb    Send result callback
 * @param[in] arg   User defined argument.
 * @return          #ev_errno_t
 */
EV_API int ev_udp_try_send(ev_udp_t *udp, ev_buf_t *bufs, size_t nbuf,
                           const struct sockaddr *addr, ev_udp_write_cb cb,
                           void *arg);

/**
 * @brief Queue a read request.
 * @param[in] udp   A UDP handle
 * @param[in] bufs  Receive buffer
 * @param[in] nbuf  Buffer number
 * @param[in] cb    Receive callback
 * @param[in] arg   User defined argument.
 * @return          #ev_errno_t
 */
EV_API int ev_udp_recv(ev_udp_t *udp, ev_buf_t *bufs, size_t nbuf,
                       ev_udp_recv_cb cb, void *arg);

/**
 * @} EV_UDP
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 97 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/pipe.h
// SIZE:    9184
// SHA-256: d7f29f52292c03dae4de9e27eeb231e9e85eeca8db652a00dca3e7c30d971379
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/pipe.h"
#ifndef __EV_PIPE_H__
#define __EV_PIPE_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_PIPE Pipe
 * @{
 */

typedef enum ev_pipe_flags_e
{
    EV_PIPE_READABLE = 0x01, /**< Pipe is readable */
    EV_PIPE_WRITABLE = 0x02, /**< Pipe is writable */
    EV_PIPE_NONBLOCK = 0x04, /**< Pipe is nonblock */
    EV_PIPE_IPC = 0x08,      /**< Enable IPC */
} ev_pipe_flags_t;

/**
 * @brief PIPE
 */
typedef struct ev_pipe ev_pipe_t;

struct ev_pipe_read_req;

/**
 * @brief Typedef of #ev_pipe_read_req.
 */
typedef struct ev_pipe_read_req ev_pipe_read_req_t;

/**
 * @brief Callback for #ev_pipe_t
 * @param[in] handle    A pipe
 * @param[in] arg       User defined argument.
 */
typedef void (*ev_pipe_cb)(ev_pipe_t *handle, void *arg);

/**
 * @brief Write callback
 * @param[in] req       Write request
 * @param[in] result    Write result
 */
typedef void (*ev_pipe_write_cb)(ev_pipe_t *pipe, ssize_t result, void *arg);

/**
 * @brief Read callback
 * @param[in] req       Read callback
 * @param[in] result    Read result
 */
typedef void (*ev_pipe_read_cb)(ev_pipe_read_req_t *req, ssize_t result);

/**
 * @brief IPC frame header.
 *
 * Frame layout:
 *  [LOW ADDR] | ------------------------ |
 *             | Frame header             | -> 16 bytes
 *             | ------------------------ |
 *             | Information              | -> #ev_ipc_frame_hdr_t::hdr_exsz
 *             | ------------------------ |
 *             | Data                     | -> #ev_ipc_frame_hdr_t::hdr_dtsz
 * [HIGH ADDR] | ------------------------ |
 *
 * Frame header layout:
 *  -------------------------------------------------------------------------
 *  | 00     | 01     | 02     | 03     | 04     | 05     | 06     | 07     |
 *  -------------------------------------------------------------------------
 *  | MAGIC                             | FLAGS  | VER.   | INFO SIZE       |
 *  -------------------------------------------------------------------------
 *  | 0x45   | 0x56   | 0x46   | 0x48   |I       | 0x00   | native endian   |
 *  -------------------------------------------------------------------------
 *  -------------------------------------------------------------------------
 *  | 08     | 09     | 10     | 11     | 12     | 13     | 14     | 15     |
 *  -------------------------------------------------------------------------
 *  | DATA SIZE                         | RESERVED                          |
 *  -------------------------------------------------------------------------
 *  | native endian                     | 0x00   | 0x00   | 0x00   | 0x00   |
 *  -------------------------------------------------------------------------
 *
 * FLAG layout (8 bits) :
 * | bit  | 0                   | 1                 |
 * | ---- | ------------------- | ----------------- |
 * | [00] | without information | have information  |
 */
typedef struct ev_ipc_frame_hdr
{
    uint32_t hdr_magic;   /**< Magic code */
    uint8_t  hdr_flags;   /**< Bit OR flags */
    uint8_t  hdr_version; /**< Protocol version */
    uint16_t hdr_exsz;    /**< Extra data size */
    uint32_t hdr_dtsz;    /**< Data size */
    uint32_t reserved;    /**< Zeros */
} ev_ipc_frame_hdr_t;

/**
 * @brief Read request token for pipe.
 */
struct ev_pipe_read_req
{
    ev_read_t       base; /**< Base object */
    ev_pipe_read_cb ucb;  /**< User callback */
    struct
    {
        ev_os_socket_t os_socket; /**< Socket handler */
    } handle;
    EV_PIPE_READ_BACKEND backend; /**< Backend */
};

/**
 * @brief Initialize a pipe handle.
 *
 * A pipe can be initialized as `IPC` mode, which is a special mode for
 * inter-process communication. The `IPC` mode have following features:
 * 1. You can transfer system resource (like a tcp socket or pipe handle) in
 *   pipe.
 * 2. The data in pipe is datagrams (like a UDP socket). Each block of data
 *   transfer in pipe will be package as a special designed data frame, so you
 *   don't need to manually split data.
 *
 * @warning Due to special features of `IPC` mode, it is significantly slower
 *   than normal mode, so don't use `IPC` mode to transmit large data.
 *
 * @param[in] loop      Event loop
 * @param[out] pipe     Pipe handle
 * @param[in] ipc       Initialize as IPC mode.
 * @return              #ev_errno_t
 */
EV_API int ev_pipe_init(ev_loop_t *loop, ev_pipe_t **pipe, int ipc);

/**
 * @brief Destroy pipe.
 *
 * The \p pipe will close in some time. Once it is closed, \p close_cb is
 * called.
 *
 * @param[in] pipe      Pipe handle.
 * @param[in] close_cb  [Optional] Destroy callback.
 * @param[in] close_arg Destroy argument.
 * @note Even if \p close_cb is set to NULL, it does not mean \p pipe is
 *   release after this call. The only way to ensure \p pipe is check in \p
 *   close_cb.
 */
EV_API void ev_pipe_exit(ev_pipe_t *pipe, ev_pipe_cb close_cb, void *close_arg);

/**
 * @brief Open an existing file descriptor or HANDLE as a pipe.
 * @note The pipe must have established connection.
 * @param[in] pipe      Pipe handle
 * @param[in] handle    File descriptor or HANDLE
 * @return              #ev_errno_t
 */
EV_API int ev_pipe_open(ev_pipe_t *pipe, ev_os_pipe_t handle);

/**
 * @brief Write data
 *
 * Once #ev_pipe_write() return #EV_SUCCESS, it take the ownership of \p req, so
 * you should not modify the content of it until bounded callback is called.
 *
 * It is a guarantee that every bounded callback of \p req will be called, with
 * following scene:
 *   + If write success or failure. The callback will be called with write
 * status.
 *   + If \p pipe is exiting but there are pending write request. The callback
 *     will be called with status #EV_ECANCELED.
 *
 * @param[in] pipe  Pipe handle
 * @param[in] bufs  Buffer list
 * @param[in] nbuf  Buffer number
 * @param[in] cb    Write result callback
 * @param[in] arg   User defined argument.
 * @return          #ev_errno_t
 */
EV_API int ev_pipe_write(ev_pipe_t *pipe, ev_buf_t *bufs, size_t nbuf,
                         ev_pipe_write_cb cb, void *arg);

/**
 * @brief Like #ev_pipe_write(), with following difference:
 *
 * + It has the ability to send OS resource to peer side.
 * + It is able to handle large amount of \p nbuf event it is larger than
 *   #EV_IOV_MAX.
 *
 * @param[in] pipe          Pipe handle
 * @param[in] req           Write request
 * @param[in] bufs          Buffer list
 * @param[in] nbuf          Buffer number
 * @param[in] handle_role   The type of handle to send
 * @param[in] handle_addr   The address of handle to send
 * @param[in] cb            Write result callback
 * @param[in] arg           User defined argument.
 * @return                  #ev_errno_t
 */
EV_API int ev_pipe_write_ex(ev_pipe_t *pipe, ev_buf_t *bufs, size_t nbuf,
                            ev_role_t handle_role, void *handle_addr,
                            ev_pipe_write_cb cb, void *arg);

/**
 * @brief Read data
 *
 * Once #ev_pipe_read() return #EV_SUCCESS, it take the ownership of \p req, so
 * you should not modify the content of it until bounded callback is called.
 *
 * It is a guarantee that every bounded callback of \p req will be called, with
 * following scene:
 *   + If read success or failure. The callback will be called with read status.
 *   + If \p pipe is exiting but there are pending read request. The callback
 *     will be called with status #EV_ECANCELED.
 *
 * @param[in] pipe  Pipe handle
 * @param[in] req   Read request
 * @param[in] bufs  Buffer list
 * @param[in] nbuf  Buffer number
 * @param[in] cb    Receive callback
 * @return          #ev_errno_t
 */
EV_API int ev_pipe_read(ev_pipe_t *pipe, ev_pipe_read_req_t *req,
                        ev_buf_t *bufs, size_t nbuf, ev_pipe_read_cb cb);

/**
 * @brief Accept handle from peer.
 * @param[in] pipe          Pipe handle.
 * @param[in] req           Read request.
 * @param[in] handle_role   Handle type.
 * @param[in] handle_addr   Handle address.
 * @return  #EV_SUCCESS: Operation success.
 * @return  #EV_EINVAL: \p pipe is not initialized with IPC, or \p handle_role
 * is not support, or \p handle_addr is NULL.
 * @return  #EV_ENOENT: \p req does not receive a handle.
 * @return  #EV_ENOMEM: \p handle_size is too small.
 */
EV_API int ev_pipe_accept(ev_pipe_t *pipe, ev_pipe_read_req_t *req,
                          ev_role_t handle_role, void *handle_addr);

/**
 * @brief Make a pair of pipe.
 *
 * Close pipe by #ev_pipe_close() when no longer need it.
 *
 * @note #EV_PIPE_READABLE and #EV_PIPE_WRITABLE are silently ignored.
 * @note If pipe is create for IPC usage, both \p rflags and \p wflags must
 *   have #EV_PIPE_IPC set. Only set one of \p rflags or \p wflags will return
 *   #EV_EINVAL.
 *
 * @param[out] fds      fds[0] for read, fds[1] for write
 * @param[in] rflags    Bit-OR of #ev_pipe_flags_t for read pipe.
 * @param[in] wflags    Bit-OR of #ev_pipe_flags_t for write pipe.
 * @return          #ev_errno_t
 */
EV_API int ev_pipe_make(ev_os_pipe_t fds[2], int rflags, int wflags);

/**
 * @brief Close OS pipe.
 * @param[in] fd    pipe create by #ev_pipe_make().
 */
EV_API void ev_pipe_close(ev_os_pipe_t fd);

/**
 * @} EV_PIPE
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 98 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/fs.h
// SIZE:    21150
// SHA-256: dbd2203f29e2726b0bfabaf788869a036edcf2f57b1192ff6ae0e63f1a281706
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/fs.h"
#ifndef __EV_FILE_SYSTEM_H__
#define __EV_FILE_SYSTEM_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_FILESYSTEM File System
 * @{
 */

/**
 * @brief Directory type.
 */
typedef enum ev_dirent_type_e
{
    EV_DIRENT_UNKNOWN,
    EV_DIRENT_FILE,
    EV_DIRENT_DIR,
    EV_DIRENT_LINK,
    EV_DIRENT_FIFO,
    EV_DIRENT_SOCKET,
    EV_DIRENT_CHR,
    EV_DIRENT_BLOCK
} ev_dirent_type_t;

/**
 * @brief File system request type.
 */
typedef enum ev_fs_req_type_e
{
    EV_FS_REQ_UNKNOWN,
    EV_FS_REQ_OPEN,
    EV_FS_REQ_SEEK,
    EV_FS_REQ_READ,
    EV_FS_REQ_WRITE,
    EV_FS_REQ_FSTAT,
    EV_FS_REQ_READDIR,
    EV_FS_REQ_READFILE,
    EV_FS_REQ_MKDIR,
    EV_FS_REQ_REMOVE,
} ev_fs_req_type_t;

struct ev_file_s;

/**
 * @brief Typedef of #ev_file_s.
 */
typedef struct ev_file_s ev_file_t;

struct ev_fs_req_s;

/**
 * @brief Typedef of #ev_fs_req_s.
 */
typedef struct ev_fs_req_s ev_fs_req_t;

struct ev_fs_stat_s;

/**
 * @brief Typedef of #ev_fs_stat_s.
 */
typedef struct ev_fs_stat_s ev_fs_stat_t;

struct ev_dirent_s;

/**
 * @brief Typedef of #ev_dirent_s.
 */
typedef struct ev_dirent_s ev_dirent_t;

/**
 * @brief File close callback
 * @param[in] file      File handle
 */
typedef void (*ev_file_close_cb)(ev_file_t* file);

/**
 * @brief File operation callback
 * @note Always call #ev_fs_req_cleanup() to free resource in \p req.
 * @warning Missing call to #ev_fs_req_cleanup() will cause resource leak.
 * @param[in] req       Request token
 */
typedef void (*ev_file_cb)(ev_fs_req_t* req);

/**
 * @brief File type.
 */
struct ev_file_s
{
    ev_handle_t                 base;           /**< Base object */
    ev_os_file_t                file;           /**< File handle */
    ev_file_close_cb            close_cb;       /**< Close callback */
    ev_list_t                   work_queue;     /**< Work queue */
};
#define EV_FILE_INVALID \
    {\
        EV_HANDLE_INVALID,\
        EV_OS_FILE_INVALID,\
        NULL,\
        EV_LIST_INIT,\
    }

typedef struct ev_file_map
{
    void*                       addr;       /**< The mapped address. */
    uint64_t                    size;       /**< The size of mapped address. */
    ev_file_map_backend_t       backend;    /**< Backend */
} ev_file_map_t;
#define EV_FILE_MAP_INVALID \
    {\
        NULL,\
        0,\
        EV_FILE_MAP_BACKEND_INVALID,\
    }

/**
 * @brief File status information.
 */
struct ev_fs_stat_s
{
    uint64_t                    st_dev;         /**< ID of device containing file */
    uint64_t                    st_ino;         /**< Inode number */
    uint64_t                    st_mode;        /**< File type and mode */
    uint64_t                    st_nlink;       /**< Number of hard links */
    uint64_t                    st_uid;         /**< User ID of owner */
    uint64_t                    st_gid;         /**< Group ID of owner */
    uint64_t                    st_rdev;        /**< Device ID (if special file) */

    uint64_t                    st_size;        /**< Total size, in bytes */
    uint64_t                    st_blksize;     /**< Block size for filesystem I/O */
    uint64_t                    st_blocks;      /**< Number of 512B blocks allocated */
    uint64_t                    st_flags;       /**< File flags */
    uint64_t                    st_gen;         /**< Generation number of this i-node. */

    ev_timespec_t               st_atim;        /**< Time of last access */
    ev_timespec_t               st_mtim;        /**< Time of last modification */
    ev_timespec_t               st_ctim;        /**< Time of last status change */
    ev_timespec_t               st_birthtim;    /**< Time of file creation */
};
#define EV_FS_STAT_INVALID  \
    {\
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,\
        EV_TIMESPEC_INVALID,\
        EV_TIMESPEC_INVALID,\
        EV_TIMESPEC_INVALID,\
        EV_TIMESPEC_INVALID,\
    }

/**
 * @brief Directory entry.
 */
struct ev_dirent_s
{
    char*                       name;           /**< Entry name */
    ev_dirent_type_t            type;           /**< Entry type */
};

/**
 * @brief File system request token.
 */
struct ev_fs_req_s
{
    ev_fs_req_type_t            req_type;       /**< Request type */
    ev_list_node_t              node;           /**< Queue node */
    ev_work_t                   work_token;     /**< Thread pool token */
    ev_file_t*                  file;           /**< File handle */
    ev_file_cb                  cb;             /**< File operation callback */
    int64_t                     result;         /**< Result */

    union
    {
        struct
        {
            char*               path;           /**< File path */
            int                 flags;          /**< File flags */
            int                 mode;           /**< File mode */
        } as_open;

        struct
        {
            int                 whence;         /**< Directive */
            int64_t             offset;         /**< Offset */
        } as_seek;

        struct
        {
            int64_t             offset;         /**< File offset */
            ev_read_t           read_req;       /**< Read token */
        } as_read;

        struct
        {
            int64_t             offset;         /**< File offset */
            ev_write_t          write_req;      /**< Write token */
        } as_write;

        struct
        {
            char*               path;           /**< Directory path */
        } as_readdir;

        struct
        {
            char*               path;           /**< File path */
        } as_readfile;

        struct
        {
            char*               path;           /**< Directory path */
            int                 mode;           /**< The mode for the new directory */
        } as_mkdir;

        struct
        {
            char*               path;           /**< Path */
            int                 recursion;      /**< Recursion delete */
        } as_remove;
    } req;

    union
    {
        ev_fs_stat_t*           stat;           /**< File information */
        ev_list_t               dirents;        /**< Dirent list */
        ev_buf_t                filecontent;    /**< File content */
    } rsp;
};

#define EV_FS_REQ_INVALID \
    {\
        EV_FS_REQ_UNKNOWN,\
        EV_LIST_NODE_INIT,\
        EV_WORK_INVALID,\
        NULL,\
        NULL,\
        EV_EINPROGRESS,\
        { { NULL, 0, 0 } },\
        { NULL },\
    }

/**
 * @brief Equivalent to [open(2)](https://man7.org/linux/man-pages/man2/open.2.html).
 * 
 * The full list of \p flags are:
 * + #EV_FS_O_APPEND
 * + #EV_FS_O_CREAT
 * + #EV_FS_O_DSYNC
 * + #EV_FS_O_EXCL
 * + #EV_FS_O_SYNC
 * + #EV_FS_O_TRUNC
 * + #EV_FS_O_RDONLY
 * + #EV_FS_O_WRONLY
 * + #EV_FS_O_RDWR
 * 
 * The full list of \p mode are:
 * + #EV_FS_S_IRUSR
 * + #EV_FS_S_IWUSR
 * + #EV_FS_S_IXUSR
 * + #EV_FS_S_IRWXU
 * 
 * @note File always open in binary mode.
 * @param[in] loop      Event loop. Must set to NULL if \p cb is NULL.
 * @param[out] file     File handle.
 * @param[in] req       File token. Must set to NULL if \p cb is NULL.
 * @param[in] path      File path.
 * @param[in] flags     Open flags.
 * @param[in] mode      Open mode. Only applies to future accesses of the newly
 *   created file. Ignored when \p flags does not contains #EV_FS_O_CREAT.
 * @param[in] cb        Open result callback. If set to NULL, the \p file is
 *   open in synchronous mode, so \p loop, \p req must also be NULL.
 * @return              #ev_errno_t
 */
EV_API int ev_file_open(ev_loop_t* loop, ev_file_t* file, ev_fs_req_t* req, const char* path,
    int flags, int mode, ev_file_cb cb);

/**
 * @brief Close a file handle.
 * 
 * If the file is open in synchronous mode (the callback in #ev_file_open() is
 * set to NULL), then this is a synchronous call. In this case \p cb must be NULL.
 * 
 * If the file is open in asynchronous mode, this call is also asynchronous,
 * you must wait for \p cb to actually called to release the resource.
 * 
 * @param[in] file      File handle
 * @param[in] cb        Close callback. Must set to NULL if \p file open in
 *   synchronous mode.
 */
EV_API void ev_file_close(ev_file_t* file, ev_file_close_cb cb);

/**
 * @brief Set the file position indicator for the stream pointed to by \p file.
 * @see #EV_FS_SEEK_BEG
 * @see #EV_FS_SEEK_CUR
 * @see #EV_FS_SEEK_END
 * @param[in] file      File handle.
 * @param[in] req       File operation token. Must set to NULL if \p file open
 *   in synchronous mode.
 * @param[in] whence    Direction.
 * @param[in] offset    Offset.
 * @param[in] cb        Result callback. Must set to NULL if \p file open in
 *   synchronous mode.
 * @return              In asynchronous mode, return 0 if success, or #ev_errno_t
 *   if failure. In synchronous, return the resulting offset location as measured
 *   in bytes from the beginning of the file, or #ev_errno_t if failure.
 */
EV_API int64_t ev_file_seek(ev_file_t* file, ev_fs_req_t* req, int whence,
    int64_t offset, ev_file_cb cb);

/**
 * @brief Read data.
 * @param[in] file      File handle.
 * @param[in] req       File operation token. Must set to NULL if \p file open
 *   in synchronous mode.
 * @param[out] buff     Buffer to store data.
 * @param[in] size      Buffer size.
 * @param[in] cb        Result callback. Must set to NULL if \p file open in
 *   synchronous mode.
 * @return              In asynchronous mode, return 0 if success, or #ev_errno_t
 *   if failure. In synchronous, return the number of bytes read, or #ev_errno_t
 *   if failure.
 */
EV_API ssize_t ev_file_read(ev_file_t* file, ev_fs_req_t* req, void* buff,
    size_t size, ev_file_cb cb);

/**
 * @brief Read data.
 * @param[in] file      File handle.
 * @param[in] req       File operation token. Must set to NULL if \p file open
 *   in synchronous mode.
 * @param[in] bufs      Buffer list.
 * @param[in] nbuf      Buffer amount.
 * @param[in] cb        Read callback. Must set to NULL if \p file open in
 *   synchronous mode.
 * @return              In asynchronous mode, return 0 if success, or #ev_errno_t
 *   if failure. In synchronous, return the number of bytes read, or #ev_errno_t
 *   if failure.
 */
EV_API ssize_t ev_file_readv(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
    size_t nbuf, ev_file_cb cb);

/**
 * @brief Read data.
 * @param[in] file      File handle.
 * @param[in] req       File operation token. Must set to NULL if \p file open
 *   in synchronous mode.
 * @param[out] buff     Buffer to store data.
 * @param[in] size      Buffer size.
 * @param[in] offset    Offset of file (from the start of the file). The file
 *   offset is not changed.
 * @param[in] cb        Result callback. Must set to NULL if \p file open in
 *   synchronous mode.
 * @return              In asynchronous mode, return 0 if success, or #ev_errno_t
 *   if failure. In synchronous, return the number of bytes read, or #ev_errno_t
 *   if failure.
 */
EV_API ssize_t ev_file_pread(ev_file_t* file, ev_fs_req_t* req, void* buff,
    size_t size, int64_t offset, ev_file_cb cb);

/**
 * @brief Read position data.
 * @param[in] file      File handle.
 * @param[in] req       File operation token. Must set to NULL if \p file open
 *   in synchronous mode.
 * @param[in] bufs      Buffer list.
 * @param[in] nbuf      Buffer amount.
 * @param[in] offset    Offset of file (from the start of the file). The file
 *   offset is not changed.
 * @param[in] cb        Read callback. Must set to NULL if \p file open in
 *   synchronous mode.
 * @return              In asynchronous mode, return 0 if success, or #ev_errno_t
 *   if failure. In synchronous, return the number of bytes read, or #ev_errno_t
 *   if failure.
 */
EV_API ssize_t ev_file_preadv(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
    size_t nbuf, int64_t offset, ev_file_cb cb);

/**
 * @brief Write data
 * @param[in] file      File handle.
 * @param[in] req       File operation token. Must set to NULL if \p file open
 *   in synchronous mode.
 * @param[in] data      Data to write.
 * @param[in] size      Data size.
 * @param[in] cb        Write callback. Must set to NULL if \p file open in
 *   synchronous mode.
 * @return              In asynchronous mode, return 0 if success, or #ev_errno_t
 *   if failure. In synchronous, return the number of bytes written, or #ev_errno_t
 *   if failure.
 */
EV_API ssize_t ev_file_write(ev_file_t* file, ev_fs_req_t* req, const void* data,
    size_t size, ev_file_cb cb);

/**
 * @brief Write data
 * @param[in] file      File handle.
 * @param[in] req       File operation token. Must set to NULL if \p file open
 *   in synchronous mode.
 * @param[in] bufs      Buffer list.
 * @param[in] nbuf      Buffer amount.
 * @param[in] cb        Write callback. Must set to NULL if \p file open in
 *   synchronous mode.
 * @return              In asynchronous mode, return 0 if success, or #ev_errno_t
 *   if failure. In synchronous, return the number of bytes written, or #ev_errno_t
 *   if failure.
 */
EV_API ssize_t ev_file_writev(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
    size_t nbuf, ev_file_cb cb);

/**
 * @brief Write data
 * @param[in] file      File handle.
 * @param[in] req       File operation token. Must set to NULL if \p file open
 *   in synchronous mode.
 * @param[in] data      Data to write.
 * @param[in] size      Data size.
 * @param[in] offset    Offset of file (from the start of the file). The file
 *   offset is not changed.
 * @param[in] cb        Write callback. Must set to NULL if \p file open in
 *   synchronous mode.
 * @return              In asynchronous mode, return 0 if success, or #ev_errno_t
 *   if failure. In synchronous, return the number of bytes written, or #ev_errno_t
 *   if failure.
 */
EV_API ssize_t ev_file_pwrite(ev_file_t* file, ev_fs_req_t* req, const void* data,
    size_t size, int64_t offset, ev_file_cb cb);

/**
 * @brief Write position data
 * @param[in] file      File handle.
 * @param[in] req       File operation token. Must set to NULL if \p file open
 *   in synchronous mode.
 * @param[in] bufs      Buffer list.
 * @param[in] nbuf      Buffer amount.
 * @param[in] offset    Offset of file (from the start of the file). The file
 *   offset is not changed.s
 * @param[in] cb        Write callback. Must set to NULL if \p file open in
 *   synchronous mode.
 * @return              In asynchronous mode, return 0 if success, or #ev_errno_t
 *   if failure. In synchronous, return the number of bytes written, or #ev_errno_t
 *   if failure.
 */
EV_API ssize_t ev_file_pwritev(ev_file_t* file, ev_fs_req_t* req, ev_buf_t bufs[],
    size_t nbuf, int64_t offset, ev_file_cb cb);

/**
 * @brief Get information about a file.
 * @param[in] file      File handle.
 * @param[in] req       File system request. Must set to NULL if \p file open
 *   in synchronous mode.
 * @param[in] cb        Result callback. Must set to NULL if \p file open in
 *   synchronous mode.
 * @return              #ev_errno_t
 */
EV_API int ev_file_stat(ev_file_t* file, ev_fs_req_t* req, ev_fs_stat_t* stat,
    ev_file_cb cb);

/**
 * @brief Maps a view of a file mapping into the address space of a calling
 *   process.
 * @param[out] view     The mapped object.
 * @param[in] file      The file to map. The file is safe to close after this
 *   call.
 * @param[in] offset    The offset where the view is to begin. It must be a
 *   multiple of the value of #ev_os_mmap_offset_granularity(). You can use
 *   #EV_ALIGN_SIZE() to align the offset to requirements. The \p offset can
 *   larger than the file size, in this case the gapping data is undefined.
 * @param[in] size      The maximum size of the file mapping object.
 *   + If \p offset is in range of \p file, set to 0 to use the range from
 *     \p offset to the end of the file.
 *   + If \p offset is not less than file size, it must larger than 0.
 * @param[in] flags     Map flags. Can be one or more of the following attributes:
 *   + #EV_FS_S_IRUSR: Pages may be read.
 *   + #EV_FS_S_IWUSR: Pages may be written.
 *   + #EV_FS_S_IXUSR: Pages may be executed.
 *   + #EV_FS_S_IRWXU: Combine of read, write and execute.
 *   Please note that this is a best effort attempt, which means you may get extra
 *   permissions than declaration. For example, in win32 if you declare #EV_FS_S_IXUSR
 *   only, you will also get read access.
 * @return              #ev_errno_t
 */
EV_API int ev_file_mmap(ev_file_map_t* view, ev_file_t* file, uint64_t offset,
    size_t size, int flags);

/**
 * @brief Unmap the file.
 * @param[in] view      The mapped object.
 */
EV_API void ev_file_munmap(ev_file_map_t* view);

/**
 * @brief Get all entry in directory.
 *
 * Use #ev_fs_get_first_dirent() and #ev_fs_get_next_dirent() to traverse all
 * the dirent information.
 *
 * The #ev_fs_req_t::result in \p cb means:
 * | Range | Means                      |
 * | ----- | -------------------------- |
 * | >= 0  | The number of dirent nodes |
 * | < 0   | #ev_errno_t                |
 * 
 * @param[in] loop      Event loop. Must set to NULL if operator in synchronous
 *   mode.
 * @param[in] req       File system request. If operation success, use
 *   #ev_fs_req_cleanup() to cleanup \p req. Missing this cause lead to memory
 *   leak.
 * @param[in] path      Directory path.
 * @param[in] cb        Result callback, set to NULL to operator in synchronous
 *   mode. In synchronous mode, \p loop must also set to NULL.
 * @return              In asynchronous mode, return 0 if success, or #ev_errno_t
 *   if failure. In synchronous, return the number of items in the \p path, or
 *   #ev_errno_t if failure.
 */
EV_API ssize_t ev_fs_readdir(ev_loop_t* loop, ev_fs_req_t* req, const char* path,
    ev_file_cb cb);

/**
 * @brief Read file content.
 *
 * Use #ev_fs_get_filecontent() to get file content.
 *
 * @param[in] loop      Event loop. Must set to NULL if \p cb is NULL.
 * @param[in] req       File system request. If operation success, use
 *   #ev_fs_req_cleanup() to cleanup \p req. Missing this cause lead to memory
 *   leak.
 * @param[in] path      File path.
 * @param[in] cb        Result callback. Set to NULL to operator in synchronous
 *   mode. In synchronous mode, \p loop must also set to NULL.
 * @return              In asynchronous mode, return 0 if success, or #ev_errno_t
 *   if failure. In synchronous, return the number of bytes for the file, or
 *   #ev_errno_t if failure.
 */
EV_API int64_t ev_fs_readfile(ev_loop_t* loop, ev_fs_req_t* req, const char* path,
    ev_file_cb cb);

/**
 * @brief Create the DIRECTORY(ies), if they do not already exist.
 *
 * The full list of \p mode are:
 * + #EV_FS_S_IRUSR
 * + #EV_FS_S_IWUSR
 * + #EV_FS_S_IXUSR
 * + #EV_FS_S_IRWXU
 *
 * @param[in] loop      Event loop. Must set to NULL if \p cb is NULL.
 * @param[in] req       File system request. Must set to NULL if \p cb is NULL.
 * @param[in] path      Directory path.
 * @param[in] mode      Creation mode.
 * @param[in] cb        Result callback. Set to NULL to operator in synchronous
 *   mode. In synchronous mode, \p loop and \p req must also set to NULL.
 * @return              #ev_errno_t
 */
EV_API int ev_fs_mkdir(ev_loop_t* loop, ev_fs_req_t* req, const char* path,
    int mode, ev_file_cb cb);

/**
 * @brief Delete a name for the file system.
 * @param[in] loop      Event loop. Must set to NULL if \p cb is NULL.
 * @param[in] req       File system request. Must set to NULL if \p cb is NULL.
 * @param[in] path      File path.
 * @param[in] recursion If \p path is a directory, recursively delete all child items.
 * @param[in] cb        Result callback. Set to NULL to operator in synchronous
 *   mode. In synchronous mode, \p loop and \p req must also set to NULL.
 * @return              #ev_errno_t
 */
EV_API int ev_fs_remove(ev_loop_t* loop, ev_fs_req_t* req, const char* path,
    int recursion, ev_file_cb cb);

/**
 * @brief Cleanup file system request
 * @param[in] req       File system request
 */
EV_API void ev_fs_req_cleanup(ev_fs_req_t* req);

/**
 * @brief Get file handle from request.
 * @param[in] req       File system request.
 * @return              File handle.
 */
EV_API ev_file_t* ev_fs_get_file(ev_fs_req_t* req);

/**
 * @brief Get stat buffer from \p req.
 * @param[in] req       A finish file system request
 * @return              Stat buf
 */
EV_API ev_fs_stat_t* ev_fs_get_statbuf(ev_fs_req_t* req);

/**
 * @brief Get first dirent information from \p req.
 * @param[in] req       File system request.
 * @return              Dirent information.
 */
EV_API ev_dirent_t* ev_fs_get_first_dirent(ev_fs_req_t* req);

/**
 * @brief Get next dirent information.
 * @param[in] curr      Current dirent information.
 * @return              Next dirent information, or NULL if non-exists.
 */
EV_API ev_dirent_t* ev_fs_get_next_dirent(ev_dirent_t* curr);

/**
 * @brief Get content of file.
 * @param[in] req       A finish file system request
 * @return              File content buffer.
 */
EV_API ev_buf_t* ev_fs_get_filecontent(ev_fs_req_t* req);

/**
 * @} EV_FILESYSTEM
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 99 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/process.h
// SIZE:    6793
// SHA-256: a54c168eb76953399a45755ff303790f7a0fca009a053fb76e6f1d6bf44e9341
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/process.h"
#ifndef __EV_PROCESS_H__
#define __EV_PROCESS_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_PROCESS Process
 * @{
 */

/**
 * @brief Typedef of #ev_process_exit_status_e.
 */
typedef enum ev_process_exit_status_e
{
    /**
     * @brief The child terminated, but we don't known how or why.
     */
    EV_PROCESS_EXIT_UNKNOWN,

    /**
     * @brief The child terminated normally, that is, by calling exit(3) or
     *   _exit(2), or by returning from main().
     */
    EV_PROCESS_EXIT_NORMAL,

    /**
     * @brief The child process was terminated by a signal.
     */
    EV_PROCESS_EXIT_SIGNAL,
} ev_process_exit_status_t;

/**
 * @brief Typedef of #ev_process_stdio_flags_e.
 */
typedef enum ev_process_stdio_flags_e
{
    /**
     * @brief Ignore this field.
     */
    EV_PROCESS_STDIO_IGNORE         = 0x00,

    /**
     * @brief Redirect stdio from/to `/dev/null`.
     */
    EV_PROCESS_STDIO_REDIRECT_NULL  = 0x01,

    /**
     * @brief Redirect stdio from/to file descriptor.
     * @note The fd will not closed automatically, so you need to do it by
     *   yourself.
     */
    EV_PROCESS_STDIO_REDIRECT_FD    = 0x02,

    /**
     * @brief Redirect stdio from/to #ev_pipe_t.
     *
     * The #ev_process_stdio_container_t::data::pipe field must point to a
     * #ev_pipe_t object that has been initialized with #ev_pipe_init() but not
     * yet opened or connected.
     */
    EV_PROCESS_STDIO_REDIRECT_PIPE  = 0x04,
} ev_process_stdio_flags_t;

/**
 * @brief Typedef of #ev_process_s.
 */
typedef struct ev_process_s ev_process_t;

/**
 * @brief Child process exit callback
 * @param[in] handle        Process handle.
 * @param[in] exit_status   Exit status
 *   +EV_PROCESS_EXIT_UNKNOWN: \p exit_code is meaninglessness.
 *   +EV_PROCESS_EXIT_NORMAL: \p exit_code is the exit status of the child.
 *     This consists of the least significant 8 bits of the status argument
 *     that the child specified in a call to exit(3) or _exit(2) or as the
 *     argument for a return state‐ment in main().
 *   +EV_PROCESS_EXIT_SIGNAL: \p exit_code is the number of the signal that
 *     caused the child process to terminate.
 * @param[in] exit_code     Exit code.
 */
typedef void (*ev_process_sigchld_cb)(ev_process_t* handle,
        ev_process_exit_status_t exit_status, int exit_code);

/**
 * @brief Handle exit callback.
 * @param[in] handle    Process handle.
 */
typedef void (*ev_process_exit_cb)(ev_process_t* handle);

/**
 * @brief Process stdio container.
 */
typedef struct ev_process_stdio_container_s
{
    /**
     * @brief Bit-OR of #ev_process_stdio_flags_t controls how a stdio should
     *   be transmitted to the child process.
     */
    ev_process_stdio_flags_t        flag;

    /**
     * @brief Set data according to ev_process_stdio_container_t::flag.
     */
    union
    {
        /**
         * @brief Valid if #ev_process_stdio_container_t::flag set to
         *   #EV_PROCESS_STDIO_REDIRECT_FD.
         * You must close it when no longer needed.
         */
        ev_os_pipe_t                fd;

        /**
         * @brief Valid if #ev_process_stdio_container_t::flag set to
         *   #EV_PROCESS_STDIO_REDIRECT_PIPE.
         */
        ev_pipe_t*                  pipe;
    } data;
} ev_process_stdio_container_t;

/**
 * @brief Process executable options.
 */
typedef struct ev_process_options_s
{
    /**
     * @brief (Optional) Child process exit callback.
     */
    ev_process_sigchld_cb           on_exit;

    /**
     * @brief Execute file.
     */
    const char*                     file;

    /**
     * @brief Execute command line.
     */
    char* const*                    argv;

    /**
     * @brief (Optional) Environment list.
     */
    char* const*                    envp;

    /**
     * @brief (Optional) Current working directory.
     */
    const char*                     cwd;

    /**
     * @brief (Optional) Pipe for redirect stdin / stdout / stderr.
     */
    ev_process_stdio_container_t    stdios[3];
} ev_process_options_t;

/**
 * @brief Process context.
 */
struct ev_process_s
{
    ev_list_node_t                  node;           /**< List node */

    ev_process_sigchld_cb           sigchild_cb;    /**< Process exit callback */
    ev_process_exit_cb              exit_cb;        /**< Exit callback. */

    ev_os_pid_t                     pid;            /**< Process ID */
    ev_process_exit_status_t        exit_status;    /**< Exit status */
    int                             exit_code;      /**< Exit code or termainl signal  */
    ev_async_t*                     sigchld;        /**< SIGCHLD notifier */

    EV_PROCESS_BACKEND              backend;
};

/**
 * @brief Execute process.
 * @param[in] loop      Event loop handler.
 * @param[out] handle   Child Process Identifier.
 * @param[in] opt       Process options.
 * @return              #ev_errno_t
 */
EV_API int ev_process_spawn(ev_loop_t* loop, ev_process_t* handle,
    const ev_process_options_t* opt);

/**
 * @brief Exit process handle.
 * @param[in] handle    Process handle.
 * @param[in] cb        Exit callback.
 */
EV_API void ev_process_exit(ev_process_t* handle, ev_process_exit_cb cb);

/**
 * @brief Notify when process receive SIGCHLD.
 * 
 * Signal SIGCHLD must be register by user application to known child process
 * exit status. If not register, waitpid() may fail with `ECHILD`.
 *
 * By default we register SIGCHLD on initialize so you don't need to care about
 * it. But there are some situation you might to register SIGCHLD yourself, so
 * when you do it, remember to call #ev_process_sigchld() in your SIGCHLD
 * handler.
 *
 * @param[in] signum    Must always SIGCHLD.
 */
EV_API void ev_process_sigchld(int signum);

/**
 * @brief Get current working directory.
 * @note The trailing slash is always removed.
 * @param[out] buffer   Buffer to store string. The terminating null byte is
 *   always appended.
 * @param[in] size      Buffer size.
 * @return The number of bytes would have been written to the buffer (excluding
 *   the terminating null byte). Thus, a return value of \p size or more means
 *   that the output was truncated.
 * @return #ev_errno_t if error occur.
 */
EV_API ssize_t ev_getcwd(char* buffer, size_t size);

/**
 * @brief Gets the executable path.
 * @param[out] buffer   Buffer to store string. The terminating null byte is
 *   always appended.
 * @param[in] size      Buffer size.
 * @return The number of bytes would have been written to the buffer (excluding
 *   the terminating null byte). Thus, a return value of \p size or more means
 *   that the output was truncated.
 * @return #ev_errno_t if error occur.
 */
EV_API ssize_t ev_exepath(char* buffer, size_t size);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 100 "ev.h"
////////////////////////////////////////////////////////////////////////////////
// FILE:    ev/misc.h
// SIZE:    5389
// SHA-256: 6db616ea2a7fe659b9e43d2f191df9e37b252b3d382f97e8a9acecb22c1d5e08
////////////////////////////////////////////////////////////////////////////////
// #line 1 "ev/misc.h"
#ifndef __EV_MISC_H__
#define __EV_MISC_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup EV_MISC Miscellaneous utilities
 * @{
 */

/**
 * @defgroup EV_MISC_NET Network
 * @{
 */

/**
 * @brief Convert IPv4 ip and port into network address
 * @param[in] ip    Character string contains IP
 * @param[in] port  Port
 * @param[out] addr network address structure
 * @return          #ev_errno_t
 */
EV_API int ev_ipv4_addr(const char* ip, int port, struct sockaddr_in* addr);

/**
 * @brief Convert IPv6 ip and port into network address
 * @param[in] ip    Character string contains IP
 * @param[in] port  Port
 * @param[out] addr network address structure
 * @return          #ev_errno_t
 */
EV_API int ev_ipv6_addr(const char* ip, int port, struct sockaddr_in6* addr);

/**
 * @brief Convert ip and port into network address
 * @param[in] ip    Character string contains IP
 * @param[in] port  Port
 * @param[out] addr network address structure
 * @return          #ev_errno_t
 */
EV_API int ev_ip_addr(const char* ip, int port, struct sockaddr* addr, size_t size);

/**
 * @brief Convert IPv4 network address into ip and port
 * @param[in] addr  network address structure
 * @param[out] port Port
 * @param[out] ip   A buffer to store IP string
 * @param[in] len   Buffer length
 * @return          #ev_errno_t
 */
EV_API int ev_ipv4_name(const struct sockaddr_in* addr, int* port, char* ip, size_t len);

/**
 * @brief Convert IPv6 network address into ip and port
 * @param[in] addr  network address structure
 * @param[out] port Port
 * @param[out] ip   A buffer to store IP string
 * @param[in] len   Buffer length
 * @return          #ev_errno_t
 */
EV_API int ev_ipv6_name(const struct sockaddr_in6* addr, int* port, char* ip, size_t len);

/**
 * @brief Convert network address into ip and port
 * @param[in] addr  network address structure
 * @param[out] port Port
 * @param[out] ip   A buffer to store IP string
 * @param[in] len   Buffer length
 * @return          #ev_errno_t
 */
EV_API int ev_ip_name(const struct sockaddr* addr, int* port, char* ip, size_t len);

/**
 * @} EV_MISC_NET
 */

/**
 * @brief Constructor for #ev_buf_t
 * @param[in] buf   Buffer
 * @param[in] len   Buffer length
 * @return          A buffer
 */
EV_API ev_buf_t ev_buf_make(void* buf, size_t len);

/**
 * @brief Constructor for #ev_buf_t list
 * 
 * Example:
 * @code
 * void foo_bar(void)
 * {
 *     ev_buf_t bufs[2];
 * 
 *     void* buf_1 = some_address;
 *     size_t len_1 = length_of_buf_1;
 * 
 *     void* buf_2 = some_address;
 *     size_t len_2 = length_of_buf_2;
 * 
 *     ev_buf_make_n(bufs, 2, buf_1, len_1, buf_2, len_2);
 * }
 * @endcode
 *
 * @param[out] bufs Buffer array
 * @param[in] nbuf  Buffer number
 * @param[in] ...   Buffer info, must a pair of (void*, size_t)
 */
EV_API void ev_buf_make_n(ev_buf_t bufs[], size_t nbuf, ...);

/**
 * @brief Constructor for #ev_buf_t list
 * 
 * Like #ev_buf_make_n(), but accept a va_list for argument.
 * @param[out] bufs Buffer array
 * @param[in] nbuf  Buffer number
 * @param[in] ap    va_list for Buffer array
 */
EV_API void ev_buf_make_v(ev_buf_t bufs[], size_t nbuf, va_list ap);

/**
 * @brief Release any global state that holding onto.
 * @warning Only call #ev_library_shutdown() once.
 * @warning Don’t call #ev_library_shutdown() when there are still event loops
 *   or I/O requests active.
 * @warning Don’t call libev functions after calling #ev_library_shutdown().
 */
EV_API void ev_library_shutdown(void);

/**
 * @brief Get system page size.
 * @return The page size of this system.
 */
EV_API size_t ev_os_page_size(void);

/**
 * @brief Offset granularity for #ev_file_mmap().
 * @note The Offset granularity does not always equal to system page size.
 * @return Offset granularity.
 */
EV_API size_t ev_os_mmap_offset_granularity(void);

/**
 * @defgroup EV_MISC_RANDOM Random
 * @{
 */

/**
 * @brief Typedef of random token.
 */
typedef struct ev_random_req ev_random_req_t;

/**
 * @brief Random callback.
 * @param[in] req       The request passed to #ev_random().
 * @param[in] status    Operation result. See #ev_errno_t.
 * @param[in] buf       The buf passed to #ev_random().
 * @param[in] len       The len passed to #ev_random().
 */
typedef void (*ev_random_cb)(ev_random_req_t* req, int status, void* buf, size_t len);

/**
 * @brief Asynchronous random request token.
 */
struct ev_random_req
{
    ev_work_t       work;
    void*           buf;
    size_t          len;
    int             flags;
    ev_random_cb    cb;
    int             ret;
};

/**
 * @brief Fill \p buf with exactly \p len cryptographically strong randoms
 *   bytes acquired from the system CSPRNG.
 * @param[in] loop  Event loop. If set to NULL, this function operation in
 *   synchronous mode.
 * @param[in] req   Random request. In synchronous mode, it must set to NULL.
 * @param[in] buf   The buffer to fill.
 * @param[in] len   The number of bytes to fill.
 * @param[in] flags Reserved for future extension and must currently be 0.
 * @param[in] cb    Result callback. In synchronous mode, it must set to NULL.
 * @return          #ev_errno_t. When success, short reads are not possible.
 */
EV_API int ev_random(ev_loop_t* loop, ev_random_req_t* req, void* buf,
    size_t len, int flags, ev_random_cb cb);

/**
 * @} EV_MISC_RANDOM
 */

/**
 * @} EV_MISC
 */

#ifdef __cplusplus
}
#endif
#endif

// #line 101 "ev.h"

#endif

