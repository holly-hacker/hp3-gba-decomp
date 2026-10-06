#pragma once

#include "types.h"
#include "hw/mem.h"
#include "game/save.h"

// Unpacks the preview of a valid slot from the slot buffer, or clears the
// preview of an invalid one.
//
// The ROM calls it out of line from nowhere and inlines it into
// SaveGameToSlot; src/save/refresh_save_slot_preview.c defines
// SAVE_SLOT_PREVIEW_LINKAGE as empty to emit the out-of-line copy.
#ifndef SAVE_SLOT_PREVIEW_LINKAGE
#define SAVE_SLOT_PREVIEW_LINKAGE extern inline
#endif

SAVE_SLOT_PREVIEW_LINKAGE void RefreshSaveSlotPreview(u32 slot)
{
    if (g_saveManager.adwSlotValid[slot])
    {
        g_saveManager.pStreamCursor = g_saveManager.pSlotBuffer;
        g_saveManager.dwStreamBitPos = 0;
        g_saveManager.dwStreamMode = SaveStreamUnpacking;
        UnpackSaveSlotPreview(&g_saveManager.aSlotPreview[slot]);
        g_saveManager.dwStreamMode = SaveStreamIdle;
    }
    else
    {
        memset(&g_saveManager.aSlotPreview[slot], 0, sizeof(SaveSlotPreview));
    }
}
