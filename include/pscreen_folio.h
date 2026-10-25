#pragma once

#include "types.h"
#include "pause_menu.h"

extern const ListMenuEntry g_aFoliosEntries[2];
extern const ActorAssetRecord g_aFoliosRowActors[2];
extern const ListMenuDefinition g_FoliosMenuDefinition;

extern s8 g_bFoliosMenuCursor;  // 0x030052F8: row restored on re-entry

extern void UpdateFolios(void);
extern void InitializeFolios(void);
extern void ExitFolios(void);
