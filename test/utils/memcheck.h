#ifndef __TEST_MEMCHECK_H__
#define __TEST_MEMCHECK_H__

#include "ev.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mmc_snapshot_s;
typedef struct mmc_snapshot_s mmc_snapshot_t;

typedef struct memblock_s
{
    ev_list_node_t node; /**< List node */
    size_t         size; /**< Size of payload in bytes */

    mmc_snapshot_t *layer; /**< Snapshot layer */

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4200)
#endif
    /**
     * Data payload
     */
    uint8_t payload[];
#if defined(_MSC_VER)
#pragma warning(pop)
#endif
} memblock_t;

typedef struct mmc_snapshot_s
{
    ev_list_node_t node;   /**< Layer node */
    ev_list_t      mmlist; /**< Memory block list */
    ev_mutex_t    *guard;  /**< Snapshot mutex */
    size_t         refcnt; /**< Reference count */
    uint64_t       idx;    /**< Index */
} mmc_snapshot_t;

typedef struct mmc_info
{
    size_t bytes;  /**< Total memory in bytes */
    size_t blocks; /**< Total memory in blocks */
} mmc_info_t;

typedef void (*mmc_cmp_cb)(memblock_t *, void *);

/**
 * @brief Setup memory leak check.
 * @param[in] replace_allocator Replace allocator for libev.
 */
void mmc_init(int replace_allocator);

/**
 * @brief Cleanup mmc runtime.
 */
void mmc_exit(void);

/**
 * @brief Dump memory leak check result.
 */
void mmc_dump(mmc_info_t *info);

/**
 * @brief Take a snapshot of current managed memory.
 * @param[out] snapshot     A pointer to store snapshot
 */
void mmc_snapshot_take(mmc_snapshot_t **snapshot);

/**
 * @brief Release a snapshot.
 * @param[in] snapshot      A snapshot.
 */
void mmc_snapshot_free(mmc_snapshot_t **snapshot);

/**
 * @brief Compare two snapshots.
 * @param[in] snap1         A snapshot.
 * @param[in] snap2         A snapshot.
 */
void mmc_snapshot_compare(mmc_snapshot_t *snap1, mmc_snapshot_t *snap2,
                          mmc_cmp_cb cb, void *arg);

void mmc_dump_hex(const void *data, size_t size, size_t width);

#ifdef __cplusplus
}
#endif
#endif
