#pragma once

#include "types.h"

// Thumb veneer to the IWRAM copy of DivideSignedRemainder: returns
// numerator / denominator and stores the remainder in *pRemainder.
extern s32 iwramDivideSignedRemainder(s32 numerator, s32 denominator, s32 *pRemainder);
