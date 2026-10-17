#pragma once

#include "types.h"

#define MT_N 624
#define MT_STATE_WORDS (MT_N + 1)

extern u32 *gMt19937StatePtr;
extern u32 *gMt19937CurPtr;
extern s32 gMt19937RemainingIndices;
extern u32 *gMt19937CurPtr2;
extern s32 gMt19937RemainingIndices2;
extern u32 gMt19937DrawIndex;
extern u8 gMt19937LastRollByte;
extern u32 gMt19937SeedValue;
extern u32 gMt19937AutoSeedCallCount;

void Mt19937AllocState(void);
u32 Mt19937Regenerate(void);
void Mt19937AutoSeed(void);
void Mt19937SetSeed(u32 seed);
s32 Mt19937RandRange(s32 min, s32 max);
s32 Mt19937RandRange2(s32 min, s32 max);
u16 Mt19937RandMax(u16 max);
u16 Mt19937RandMax2(u16 max);
s16 Mt19937RandSigned(s16 max);
s16 Mt19937RandSigned2(s16 max);
s32 Mt19937Chance(u16 percent);
s32 Mt19937Chance2(u16 percent);
s32 Mt19937ChanceNoisy(u16 percent);
void Mt19937SeedArray(u32 seed);
s32 Mt19937Next(void);
s32 Mt19937Next2(void);
