#pragma once

#include "types.h"

#define ABS(x) ((x) < 0 ? -(x) : (x))

// A position or vector with 16.16 fixed-point coordinates, passed by value.
typedef struct FixedPoint {
    s32 x;
    s32 y;
} FixedPoint;

// A position or vector with integer coordinates, passed by value.
typedef struct IntPoint {
    s32 x;
    s32 y;
} IntPoint;

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

// Angles are 0-255 for a full turn. g_anSineTable is 16.16 fixed point.
extern const s32 g_anSineTable[256];

// Return sin/cos of angle in 8.8 fixed point.
s16 Sin8_8(u8 angle);
s16 Cos8_8(u8 angle);

// 8.8 fixed-point arithmetic.
s16 Multiply8_8(s16 a, s16 b);
s16 Divide8_8(s16 numerator, s16 denominator);
s16 Reciprocal8_8(s16 value);
// Converts 8.8 sign-magnitude (bit 15 sign, bits 0-14 magnitude) to signed 16.16.
s32 SignMagnitude8_8ToFixed(s16 value);

// 16.16 fixed-point arithmetic. FixedMultiply keeps 10 bits of each
// operand's fraction; FixedReciprocal returns only the integer part of 1/value.
s32 FixedMultiply(s32 a, s32 b);
s32 FixedDivide(s32 numerator, s32 denominator);
s32 FixedReciprocal(s32 value);

// value * percent / 100, and value * 100 / total.
s32 ApplyPercent(s32 value, u16 percent);
s32 ToPercent(s32 value, s32 total);

// max(|x|, |y|) + 3/8 * min(|x|, |y|), an approximation of the length.
s32 ApproximateLength(FixedPoint delta);
s32 ApproximateDistance(FixedPoint a, FixedPoint b);
s32 LengthSquared(FixedPoint v);

// Adds (dx, dy) to the two-word point.
void AddOffsetToPoint(s32 dx, s32 dy, s32 *pPoint);
// *pResult = *pPoint + offset.
void AddOffsetToPointInto(FixedPoint offset, FixedPoint *pPoint, FixedPoint *pResult);
// *pOffset = pos - *pPoint.
void GetOffsetFromPoint(FixedPoint pos, FixedPoint *pPoint, FixedPoint *pOffset);
// *pPoint = pos - *pPoint.
void GetOffsetFromPointInPlace(FixedPoint pos, FixedPoint *pPoint);
void FixedToIntPoint(FixedPoint pos, IntPoint *pResult);
void IntToFixedPoint(IntPoint pos, FixedPoint *pResult);

// Products of 16.16 vectors at FixedMultiply's precision.
s32 FixedDotProduct(FixedPoint a, FixedPoint b);
s32 FixedCrossProduct(FixedPoint a, FixedPoint b);

// Returns a Direction, or a Direction4 when fourWay is nonzero.
u8 GetDirectionFromVector(FixedPoint v, u32 fourWay);
u8 GetDirection32FromVector(FixedPoint v);
u8 StepDirection32Toward(u8 direction, u8 target, s8 *pStep);
