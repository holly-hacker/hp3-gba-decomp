#pragma once

#include "types.h"

// GBA BIOS SWI wrappers -- asm/rt/bios_calls.s (US 0x08049E84-0x08049EC4).
// bios_Div and bios_Mod share SWI 0x6 (BIOS Div); bios_Mod just returns the
// remainder (r1) instead of the quotient (r0).

s16  bios_ArcTan2(s16 x, s16 y);
void bios_BgAffineSet(const void *src, void *dst, s32 count);
void bios_CPUFastSet(const void *src, void *dst, u32 lengthMode);
void bios_CPUSet(const void *src, void *dst, u32 lengthMode);
s32  bios_Div(s32 numerator, s32 denominator);
s32  bios_Mod(s32 numerator, s32 denominator);
void bios_HuffUnComp(const void *src, void *dst);
void bios_LZ77UnCompVRAM(const void *src, void *dst);
void bios_LZ77UnCompWRAM(const void *src, void *dst);
void bios_ObjAffineSet(const void *src, void *dst, s32 count, s32 offset);
void bios_RLUnCompVRAM(const void *src, void *dst);
void bios_RLUnCompReadNormalWrite8bit(const void *src, void *dst);
u32  bios_Sqrt(u32 num);
void bios_VBlankIntrWait(void);
