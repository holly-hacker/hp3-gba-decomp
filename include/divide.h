#pragma once

#include "types.h"

// Hand-written ARM divide routines in ROM (asm/rt/), copied to IWRAM by
// InstallIwramDivideRoutines.
extern void DivideSignedQuotient(void);

extern u8 g_abIwramDivideCode[0x340];
extern s32 (*g_pfnIwramDivideSignedQuotient)(s32 numerator, s32 denominator);
extern s32 (*g_pfnIwramDivideSignedRemainder)(s32 numerator, s32 denominator, s32 *pRemainder);
extern u32 (*g_pfnIwramDivideUnsigned)(u32 numerator, u32 denominator);

void InstallIwramDivideRoutines(void);

// Thumb veneers to the IWRAM copies: return numerator / denominator.
// iwramDivideSignedRemainder also stores the remainder in *pRemainder.
s32 iwramDivideSignedQuotient(s32 numerator, s32 denominator);
s32 iwramDivideSignedRemainder(s32 numerator, s32 denominator, s32 *pRemainder);
u32 iwramDivideUnsigned_unused(u32 numerator, u32 denominator);
