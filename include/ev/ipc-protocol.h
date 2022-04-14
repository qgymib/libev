#ifndef __EV_IPC_PROTOCOL_H__
#define __EV_IPC_PROTOCOL_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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
    uint32_t    hdr_magic;      /**< Magic code */
    uint8_t     hdr_flags;      /**< Bit OR flags */
    uint8_t     hdr_version;    /**< Protocol version */
    uint16_t    hdr_exsz;       /**< Extra data size */
    uint32_t    hdr_dtsz;       /**< Data size */
    uint32_t    reserved;       /**< Zeros */
}ev_ipc_frame_hdr_t;

#ifdef __cplusplus
}
#endif
#endif
