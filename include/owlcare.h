#pragma once

#include "types.h"

// Per-tick Owl Care Kit clock, a no-op until the care screen has been visited.
// Counts down the Mail flight timer, otherwise advances the elapsed-tick counter;
// each time that passes 0x95 it resets and, if nGrowCounters is set, raises all
// six care counters by 1 (cap 250). See docs/formats/save.md.
void ProcessOwlCareKitTick(s32 nGrowCounters);
