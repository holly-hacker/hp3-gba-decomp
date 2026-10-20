#pragma once

#include "types.h"
#include "map.h"

// The ROM inlines this into TrySetWanderingMonsterMoveTarget and also keeps an
// out-of-line copy; the file that emits that copy defines the linkage macro as empty.
#ifndef GET_ENCOUNTER_KIND_TERRAIN_TYPE_LINKAGE
#define GET_ENCOUNTER_KIND_TERRAIN_TYPE_LINKAGE extern inline
#endif

GET_ENCOUNTER_KIND_TERRAIN_TYPE_LINKAGE u32 GetEncounterKindTerrainType(u32 kind)
{
    return g_adwEncounterKindTerrainTypes[kind];
}
