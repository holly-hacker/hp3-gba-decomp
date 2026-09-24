#pragma once

#include "types.h"
#include "game_modes.h"
#include "object.h"

// One row of a list menu, 12 bytes each.
typedef struct {
    GameMode mode;     // 0x00: mode pushed when the row is chosen
    u16 wStringId;     // 0x04: row label
    u16 wUnk6;
    u32 dwImmediate;   // 0x08: nonzero pushes the mode right away with a screen transition
} ListMenuEntry;

// One 16-byte record of a list menu's row objects, read by sub_08001690.
typedef struct {
    u32 dwUnk0;
    u32 dwUnk4;
    const ObjPalette *pPalette;  // 0x08
    u32 dwUnkC;
} ListMenuRowObject;

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
    ListMenuEntry *pEntries;  // 0x10
    u16 wRowObjectCount;    // 0x14: one object per row, created from pRowObjects
    u16 wUnk16;
    u16 wRowObjectOffsetX;  // 0x18
    u16 wRowObjectOffsetY;  // 0x1A
    const ListMenuRowObject *pRowObjects;  // 0x1C
    u16 wCursorOffsetX;     // 0x20
    u16 wCursorOffsetY;     // 0x22
} ListMenuDefinition;

typedef struct {
    u8 bInGameMenuCursor;             // 0x00: pause menu row saved by ExitInGameMenu
    const ListMenuDefinition *pDefinition;  // 0x04: definition of the menu on screen
} ListMenuState;

extern ListMenuState g_ListMenuState;  // 0x03005220

extern const u32 g_dwCommonBg2Control;  // 0x0805E10C: BG2 control word, the text target for list menu rows

extern void ListMenuCursorTick_candidate(Object *pObject);
extern void BuildListMenu(const ListMenuDefinition *pDefinition);
extern void MoveListMenuCursor(void);
extern void DrawListMenuRow(u32 row);
