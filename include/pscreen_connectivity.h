#pragma once

#include "types.h"
#include "pause_menu.h"
#include "modes.h"
#include "actor.h"

// Rows of the Connectivity submenu: "Trade Cards" plus a second row that depends on the
// Owl Care Kit's state. InitializeConnectivityMenu points g_ConnectivityMenu.pEntries at
// the matching table.
extern const ListMenuEntry g_aConnectivityGameCubeEntries[2];     // Owl Care Kit locked
extern const ListMenuEntry g_aConnectivityOwlNameEntries[2];      // first visit
extern const ListMenuEntry g_aConnectivityOwlCareEntries[2];      // later visits
extern const ActorAssetRecord g_aConnectivityRowActors[2];
extern const ListMenuDefinition g_ConnectivityMenuTemplate;
extern const ListMenuDefinition g_ConfirmTradeMenuDefinition;

extern s8 g_bConnectivityMenuCursor;           // 0x030052BC: row restored on re-entry

extern void HandleConnectivityMenuTick(void);
extern void InitializeConnectivityMenu(void);
extern void ExitConnectivity(void);
extern void UpdateConfirmTradeScreen(void);
extern void InitializeConfirmTradeScreen(void);
extern void ExitConfirmTradeScreen(void);
