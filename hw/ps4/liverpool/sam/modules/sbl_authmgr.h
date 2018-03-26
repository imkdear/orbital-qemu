/*
 * QEMU model of SBL's AuthMgr module.
 *
 * Copyright (c) 2017-2018 Alexandro Sanchez Bach
 *
 * Partially based on research from: flatz
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HW_PS4_LIVERPOOL_SAM_MODULES_SBL_AUTHMGR_H
#define HW_PS4_LIVERPOOL_SAM_MODULES_SBL_AUTHMGR_H

#include "qemu/osdep.h"

#define AUTHMGR_VERIFY_HEADER        0x01
#define AUTHMGR_LOAD_SELF_SEGMENT    0x02
#define AUTHMGR_LOAD_SELF_BLOCK      0x06
#define AUTHMGR_INVOKE_CHECK         0x09
#define AUTHMGR_IS_LOADABLE          0x16

/* structures */
typedef struct authmgr_chunk_entry_t {
    uint64_t data_addr;
    uint64_t data_size;
} authmgr_chunk_entry_t;

typedef struct authmgr_chunk_table_t {
    uint64_t data_addr;
    uint64_t data_size;
    uint64_t num_entries;
    uint64_t reserved;
    authmgr_chunk_entry_t entries[0];
} authmgr_chunk_table_t;

typedef struct self_auth_info_t {
    uint64_t data_addr;
    uint64_t data_size;
} self_auth_info_t;

/* arguments */
typedef struct authmgr_verify_header_t {
    /* <input> */
    uint64_t header_addr;        // @ 0xA8
    uint32_t header_size;        // @ 0xA0
    uint32_t zero_0C;            // @ 0x9C
    uint32_t zero_10;            // @ 0x98
    /* <output> */
    uint32_t context_id;         // @ 0x94
    /* <???> */
    uint64_t unk_18;             // @ 0x90
    uint32_t unk_20;             // @ 0x88 (actually, uint16_t)
    uint32_t key_id;             // @ 0x84
    uint8_t key[0x10];           // @ 0x80
} authmgr_verify_header_t;

typedef struct authmgr_load_self_segment_t {
    /* <input> */
    uint64_t chunk_table_addr;   // @ 0xA8
    uint32_t segment_index;      // @ 0xA0
    uint32_t unk_0C;             // @ 0x9C
    uint64_t zero_10;            // @ 0x98
    uint64_t zero_18;            // @ 0x90
    uint32_t zero_20;            // @ 0x88
    uint32_t zero_24;            // @ 0x84
    uint32_t context_id;         // @ 0x80
    /* <output> */
} authmgr_load_self_segment_t;

typedef struct authmgr_load_self_block_t {
    /* <input> */
    uint64_t pages_ptr;
    uint32_t segment_index;
    uint32_t context_id;
    uint8_t digest[0x20];
    uint32_t block_idx;
    uint32_t data_offset;
    uint32_t data_size;
    uint64_t data_start_ptr;
    uint64_t data_end_ptr;
    uint32_t zero;
    /* <output> */
} authmgr_load_self_block_t;

typedef struct authmgr_invoke_check_t {
    /* <input> */
    /* <output> */
} authmgr_invoke_check_t;

typedef struct authmgr_is_loadable_t {
    /* <input> */
    uint32_t path_id;            // @ 0xA8
    uint32_t zero_04;            // @ 0xA4
    uint32_t context_id;         // @ 0xA0
    uint16_t is_elf;             // @ 0x9C
    uint16_t is_devkit;          // @ 0x9A
    uint64_t auth_info_old_addr; // @ 0x98
    uint64_t auth_info_new_addr; // @ 0x90
    /* <output> */
    uint32_t unk_20;  // @ 0x88
} authmgr_is_loadable_t;

/* functions */
void sbl_authmgr_verify_header(
    const authmgr_verify_header_t *query, authmgr_verify_header_t *reply);
void sbl_authmgr_load_self_segment(
    const authmgr_load_self_segment_t *query, authmgr_load_self_segment_t *reply);
void sbl_authmgr_load_self_block(
    const authmgr_load_self_block_t *query, authmgr_load_self_block_t *reply);
void sbl_authmgr_invoke_check(
    const authmgr_invoke_check_t *query, authmgr_invoke_check_t *reply);
void sbl_authmgr_is_loadable(
    const authmgr_is_loadable_t *query, authmgr_is_loadable_t *reply);

#endif /* HW_PS4_LIVERPOOL_SAM_MODULES_SBL_AUTHMGR_H */