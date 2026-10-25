#pragma once

#include "types.h"

// GBA BIOS SWI wrappers -- asm/rt/bios_calls.s.
// bios_Div and bios_Mod share SWI 0x6 (BIOS Div); bios_Mod just returns the
// remainder (r1) instead of the quotient (r0).

// BgAffineSet source: texture point (19.8) shown at screen point, scale (8.8), angle.
typedef struct BgAffineSrc {
    s32 texX;    // 0x00
    s32 texY;    // 0x04
    s16 scrX;    // 0x08
    s16 scrY;    // 0x0A
    s16 sx;      // 0x0C
    s16 sy;      // 0x0E
    u16 alpha;   // 0x10; 0x10000 per turn, only the high byte used
} BgAffineSrc;

// BgAffineSet output: one BG's PA..PD and reference point, in register order.
typedef struct BgAffineDst {
    s16 pa;   // 0x00
    s16 pb;   // 0x02
    s16 pc;   // 0x04
    s16 pd;   // 0x06
    s32 x;    // 0x08
    s32 y;    // 0x0C
} BgAffineDst;

s16  bios_ArcTan2(s16 x, s16 y);
void bios_BgAffineSet(const void *src, void *dst, s32 count);
void bios_CPUFastSet(const volatile void *src, volatile void *dst, u32 lengthMode);
void bios_CPUSet(const volatile void *src, volatile void *dst, u32 lengthMode);
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
