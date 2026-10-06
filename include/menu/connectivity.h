#pragma once

#include "types.h"
#include "menu/menu.h"

// Rows of the Connectivity submenu: "Trade Cards" plus a second row that depends on the
// Owl Care Kit's state. InitializeConnectivityMenu points g_ConnectivityMenu.pEntries at
// the matching table.
extern const ListMenuEntry g_aConnectivityGameCubeEntries[2];     // 0x0806945C: Owl Care Kit locked
extern const ListMenuEntry g_aConnectivityOwlNameEntries[2];      // 0x08069474: first visit
extern const ListMenuEntry g_aConnectivityOwlCareEntries[2];      // 0x0806948C: later visits
extern const ListMenuRowObject g_aConnectivityRowObjects[2];      // 0x080694A4
extern const ListMenuDefinition g_ConnectivityMenuTemplate;       // 0x080694C4
extern const ListMenuDefinition g_ConfirmTradeMenuDefinition;     // 0x080694E8
extern const ListMenuEntry g_aConfirmTradeEntries[2];             // 0x0806B238

extern ListMenuDefinition g_ConnectivityMenu;  // 0x030051F8: RAM copy of g_ConnectivityMenuTemplate
extern s8 g_bConnectivityMenuCursor;           // 0x030052BC: row restored on re-entry
