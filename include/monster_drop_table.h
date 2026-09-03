#pragma once

#include "types.h"

typedef struct {
    u8 chance;
    s16 itemId;
} MonsterDropSlot;

typedef struct {
    MonsterDropSlot slot[2];
} MonsterDropEntry;

extern const MonsterDropEntry g_pMonsterDropTable[69];
