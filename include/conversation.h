#pragma once

#include "types.h"

// Room script dialog blocks: each shows its lines' text ids in turn. A block with
// no lines still shows pTextIds[0].
typedef struct DialogBlock {
    const u32 *pTextIds;
    u8 bLineCount;
} DialogBlock;

extern const u32 g_adwDialogBlockTextIds[979];  // US 0x0805BC04
extern const DialogBlock g_aDialogBlocks[666];   // US 0x0805CB50
