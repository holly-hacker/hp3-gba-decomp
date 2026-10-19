#pragma once

#include "types.h"
#include "save.h"

// Playtime arithmetic.

u32 AddPlaytimeDelta(Playtime *playtime, const Playtime *toAdd);
u8 *FormatPlaytimeText(const Playtime *playtime, u8 *out, s32 textId);
u32 ComparePlaytimeField(const Playtime *playtime, const Playtime *mask, u32 fieldMask);
void InitializePlaytimeStruct(Playtime *playtime);
void CopyPlaytime(Playtime *dst, const Playtime *src);
void SumPlaytime(const Playtime *playtime, const Playtime *toAdd, Playtime *sum);
u32 PlaytimeFieldsEqual(const Playtime *left, const Playtime *right, u32 fieldMask);
u32 IsPlaytimeInRange(const Playtime *start, const Playtime *end, const Playtime *playtime,
                      u32 fieldMask);
