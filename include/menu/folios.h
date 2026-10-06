#pragma once

#include "types.h"
#include "menu/menu.h"

extern const ListMenuEntry g_aFoliosEntries[2];             // 0x0806950C
extern const ListMenuRowObject g_aFoliosRowObjects[2];      // 0x08069524
extern const ListMenuDefinition g_FoliosMenuDefinition;     // 0x08069544

extern s8 g_bFoliosMenuCursor;  // 0x030052F8: row restored on re-entry
