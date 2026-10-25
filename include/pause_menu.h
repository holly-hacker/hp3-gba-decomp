#pragma once

#include "types.h"
#include "modes.h"
#include "actor.h"
#include "math.h"

// One row of a list menu, 12 bytes each.
typedef struct {
    GameMode mode;     // 0x00: mode pushed when the row is chosen
    u16 wStringId;     // 0x04: row label
    u32 dwImmediate;   // 0x08: nonzero pushes the mode right away with a screen transition
} ListMenuEntry;

// Layout of a list menu, 0x24 bytes. Rows are drawn at base + row * stride.
typedef struct {
    u16 wTitleStringId;
    u16 wEntryCount;        // 0x02
    u16 wFont;              // 0x04: font id passed to SelectTextFont
    ShortPoint base;        // 0x08
    ShortPoint stride;      // 0x0C
    const ListMenuEntry *pEntries;  // 0x10
    u16 wRowActorCount;     // 0x14: one actor per row, created from pRowActors
    ShortPoint rowActorOffset;  // 0x18
    const ActorAssetRecord *pRowActors;  // 0x1C
    ShortPoint cursorOffset;    // 0x20
} ListMenuDefinition;

typedef struct {
    u8 bInGameMenuCursor;             // 0x00: pause menu row saved by ExitInGameMenu
    const ListMenuDefinition *pDefinition;  // 0x04: definition of the menu on screen
} ListMenuState;

extern ListMenuDefinition g_ConnectivityMenu;  // RAM copy of g_ConnectivityMenuTemplate
extern ListMenuState g_ListMenuState;  // 0x03005220
extern void ListMenuCursorTick(Actor *pActor);
extern void BuildListMenu(const ListMenuDefinition *pDefinition);
extern void MoveListMenuCursor(void);
extern void DrawListMenuRow(u32 row);

extern const ListMenuEntry g_aInGameMenuEntries[6];
extern const ActorAssetRecord g_aInGameMenuRowActors[6];
extern const ListMenuDefinition g_InGameMenuDefinition;

extern void UpdateInGameMenu(void);
extern void InitializeInGameMenu(void);
extern void InitializeInGameMenuFadeIn(void);
extern void ExitInGameMenu(void);
extern void ResumeInGameMenuFromOverlay(void);
extern void BeginPauseMenuScreen(u32 showObjective);  // nonzero draws the objective panel
extern void StartMenuFadeIn(void);
extern void StartMenuOverlayFadeIn(void);
extern void TickMenuFadeIn(void);
extern void StartMenuFadeOut(void);
extern void StartMenuOverlayFadeOut(void);
extern void TickMenuFadeOut(void);
extern void SelectListMenuEntry(void);
extern void ExitPauseMenuScreen(void);
extern void DrawPauseMenuObjective(void);
extern void NoopStatusEquipSelected(void);
extern void NoopStatusEquipReturned(void);
