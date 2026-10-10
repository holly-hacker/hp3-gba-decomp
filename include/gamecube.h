#pragma once

#include "types.h"

// JOYBUS transport for the GameCube link; see docs/memory-map/gcn-link.md.
extern void InitJoybusSession(u32 (*pCommandCallback)(void *, void *), u32 bound1, u32 bound2);
extern u32 TickJoybusSession(void);
extern void TeardownJoybusHardware(void);
