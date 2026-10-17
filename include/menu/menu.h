#pragma once

#include "types.h"
#include "modes.h"
#include "actor.h"

// One row of a list menu, 12 bytes each.
typedef struct {
    GameMode mode;     // 0x00: mode pushed when the row is chosen
    u16 wStringId;     // 0x04: row label
    u16 wUnk6;
    u32 dwImmediate;   // 0x08: nonzero pushes the mode right away with a screen transition
} ListMenuEntry;

// One 16-byte record of a list menu's row actors, read by SetActorSprite.
typedef struct {
    void *pTileGfx;
    void *pFrameData;            // 0x04
    const ObjPalette *pPalette;  // 0x08
    u32 dwUnkC;
} ListMenuRowActor;

// Layout of a list menu, 0x24 bytes. Rows are drawn at
// (wBaseX + row * wStrideX, wBaseY + row * wStrideY).
typedef struct {
    u16 wTitleStringId;
    u16 wEntryCount;        // 0x02
    u16 wFont;              // 0x04: font id passed to SelectTextFont
    u16 wUnk6;
    u16 wBaseX;             // 0x08
    u16 wBaseY;             // 0x0A
    u16 wStrideX;           // 0x0C
    u16 wStrideY;           // 0x0E
    const ListMenuEntry *pEntries;  // 0x10
    u16 wRowActorCount;    // 0x14: one actor per row, created from pRowActors
    u16 wUnk16;
    u16 wRowActorOffsetX;  // 0x18
    u16 wRowActorOffsetY;  // 0x1A
    const ListMenuRowActor *pRowActors;  // 0x1C
    u16 wCursorOffsetX;     // 0x20
    u16 wCursorOffsetY;     // 0x22
} ListMenuDefinition;

typedef struct {
    u8 bInGameMenuCursor;             // 0x00: pause menu row saved by ExitInGameMenu
    const ListMenuDefinition *pDefinition;  // 0x04: definition of the menu on screen
} ListMenuState;

extern ListMenuState g_ListMenuState;  // 0x03005220


extern void ListMenuCursorTick_candidate(Actor *pActor);
extern void BuildListMenu(const ListMenuDefinition *pDefinition);
extern void MoveListMenuCursor(void);
extern void DrawListMenuRow(u32 row);
