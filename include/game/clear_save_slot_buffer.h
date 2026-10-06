#pragma once

#include "types.h"
#include "hw/mem.h"
#include "game/save.h"

// Zeroes the slot buffer.
//
// The ROM calls ClearSaveSlotBuffer out of line from InitSaveSystem and
// inlines it into PackAndChecksumSaveSlot; src/save/clear_save_slot_buffer.c
// defines CLEAR_SAVE_SLOT_BUFFER_LINKAGE as empty to emit the out-of-line copy.
#ifndef CLEAR_SAVE_SLOT_BUFFER_LINKAGE
#define CLEAR_SAVE_SLOT_BUFFER_LINKAGE extern inline
#endif

CLEAR_SAVE_SLOT_BUFFER_LINKAGE void ClearSaveSlotBuffer(void)
{
    memset(g_saveManager.pSlotBuffer, 0, SAVE_SLOT_SIZE);
}
