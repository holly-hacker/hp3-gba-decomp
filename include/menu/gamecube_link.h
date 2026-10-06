#pragma once

#include "types.h"
#include "menu/menu.h"

// Screen state at 0x03003238, the first half of the JOYBUS link state documented in
// docs/memory-map/gcn-link.md. Only the fields the mode itself touches are named.
typedef struct {
    u8 abUnk0[0x30];
    u16 wResultTextId;    // 0x30: dialog text last drawn as the link result; 0xACF = none yet
    u16 wUnk32;
    u16 wStatusTextId;    // 0x34: dialog text last drawn in the status box; 0xACF = none yet
    u16 wUnk36;
} GameCubeLinkScreenState;

extern GameCubeLinkScreenState g_GameCubeLinkScreenState;  // 0x03003238

extern const ListMenuDefinition g_GameCubeLinkMenuDefinition;  // 0x08069A2C: title only, no rows

extern u32 DispatchGameCubeLinkCommand(void *pSendBuf, void *pRecvBuf);
extern void InitJoybusSession(u32 (*pCommandCallback)(void *, void *), u32 bound1, u32 bound2);
extern u32 TickJoybusSession(void);
extern void TeardownJoybusHardware(void);

extern void UpdateGameCubeLinkStatusText(u32 linkEvent);
extern void ShowGameCubeLinkMessage(u32 stringId);
extern void SpawnGameCubeLinkIconObjects(void);
