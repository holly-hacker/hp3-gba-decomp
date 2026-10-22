#pragma once

#include "types.h"
#include "pause_menu.h"

extern const ListMenuEntry g_aFoliosEntries[2];             // 0x0806950C
extern const ActorAssetRecord g_aFoliosRowActors[2];      // 0x08069524
extern const ListMenuDefinition g_FoliosMenuDefinition;     // 0x08069544

extern s8 g_bFoliosMenuCursor;  // 0x030052F8: row restored on re-entry

extern void UpdateFolios(void);
extern void InitializeFolios(void);
extern void ExitFolios(void);
