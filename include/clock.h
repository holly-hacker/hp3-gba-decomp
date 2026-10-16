#pragma once

#include "types.h"
#include "game/save.h"

// Playtime arithmetic.

u32 AddPlaytimeDelta(Playtime *playtime, const Playtime *toAdd);
u32 ComparePlaytimeField(const Playtime *playtime, const Playtime *mask, u32 fieldMask);
void InitializePlaytimeStruct(Playtime *playtime);
void CopyPlaytime(Playtime *dst, const Playtime *src);
