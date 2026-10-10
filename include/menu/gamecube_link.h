#pragma once

#include "types.h"
#include "gamecube.h"
#include "menu/menu.h"

// The mode's text ids live in g_JoybusLinkState (gamecube.h).

extern const ListMenuDefinition g_GameCubeLinkMenuDefinition;  // 0x08069A2C: title only, no rows

extern u32 DispatchGameCubeLinkCommand(u32 command, u16 *pLength, u16 *pBuffer);

extern void UpdateGameCubeLinkStatusText(u32 linkEvent);
extern void ShowGameCubeLinkMessage(u32 stringId);
extern void SpawnGameCubeLinkIconObjects(void);
