#pragma once

#include "types.h"
#include "game_modes.h"
#include "object.h"

// Pause menu Status/Equip screen, game modes 0x0C-0x0F; see
// docs/memory-map/game_modes.md.

// Character select (modes 0x0C/0x0D). Its three slots show, left to right,
// Hermione, Harry and Ron.
typedef struct {
    u32 adwSlotPresent[3];  // 0x00: nonzero when the slot's member is in the party
    GameMode nextMode;      // 0x0C: mode pushed once the fade-out finishes
} StatusEquipCharacterSelectState;

extern StatusEquipCharacterSelectState g_StatusEquipCharacterSelect;  // 0x030052A8
extern u8 g_bStatusEquipCharacterSlot;  // 0x030052B8: cursor slot (0-2)
extern u32 g_dwStatusEquipCharacter;    // 0x030052A0: FighterType chosen in character select

extern void sub_08035A34(void);
extern void sub_08035D98(u32 slot);
extern void sub_08035DC0(void);
extern u8 StatusEquipSlotToCharacter(u8 slot);
extern u8 StatusEquipCharacterToSlot(u32 character);

// Slot select (mode 0x0E): one entry per equipment slot, in a 2x3 grid.
typedef struct {
    s16 nX;        // 0x00: slot frame position
    s16 nY;        // 0x02
    u32 dwType;    // 0x04: equipment type (0-5), see StatusEquipItemSelect
    u32 dwTextId;  // 0x08: slot name (0x5A0 + dwType)
    u8 bUp;        // 0x0C: neighbouring slot index for each direction
    u8 bDown;      // 0x0D
    u8 bLeft;      // 0x0E
    u8 bRight;     // 0x0F
} StatusEquipSlot;

extern const StatusEquipSlot g_aStatusEquipSlots[6];  // 0x0806B2FC
extern const u8 g_StatusEquipSlotCursorSpawnData[];   // 0x080CD814

// Screen objects and state of the slot select screen.
typedef struct {
    Object *pCursor;               // 0x00
    Object *pCharacter;            // 0x04: portrait of the chosen member
    Object *apSlotFrames[6];       // 0x08
    Object *apSlotItems[6];        // 0x20: equipped item icon per slot, or NULL
    void *apItemGfx[6][2];         // 0x38: tile/frame record passed to SetObjectAssetRecord
    GameMode nextMode;             // 0x68: mode pushed once the fade-out finishes
} StatusEquipSlotSelectState;

extern StatusEquipSlotSelectState g_StatusEquipSlotSelect;  // 0x030054F8
extern s8 g_bStatusEquipSlot;  // 0x03005564: selected index into g_aStatusEquipSlots

extern Object *sub_0803A030(u32 character);
extern void DrawStatusEquipStatsPanel(void);
extern void sub_0803A3A0(void);
extern void sub_0803A534(void);
extern void TickStatusEquipSlotCursor(Object *pCursor);
extern void sub_0803A590(void);
extern void sub_0803A604(void);
extern void sub_0803A630(void);
extern u32 sub_0803A678(void);
extern void sub_080368CC(u32 slotType);  // sets g_dwStatusEquipSlotType
extern void sub_08026FE0(Object *obj, u32 blendLevel);

// Item select (mode 0x0F).
typedef struct {
    u32 dwUnk0;                // 0x00
    GameMode nextMode;         // 0x04: mode pushed once the fade-out finishes
    u32 dwTextCursor;          // 0x08: text tile cursor after the stat labels
    u32 dwUnkC;                // 0x0C
    u32 dwHasItems;            // 0x10: nonzero when an item list was built
    void *pItemList;           // 0x14: item list menu, or NULL
    u32 dwUnk18;               // 0x18
    Object *apStatArrows[3];   // 0x1C: Def/Agi/M.Def up/down arrows
    u16 awSavedPalette[3];     // 0x28: BG palette colors 4-6, restored on exit
} StatusEquipItemSelectState;

extern StatusEquipItemSelectState g_StatusEquipItemSelect;  // 0x030052C8
extern u32 g_dwStatusEquipSlotType;  // 0x030052C0: equipment type of the chosen slot

extern void sub_080362D8(void);
extern u32 sub_080368E4(void);
extern void sub_08027048(void);
extern void sub_08027BA4(void);
extern void sub_08032138(void);
