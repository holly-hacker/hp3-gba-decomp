#pragma once

#include "types.h"
#include "modes.h"
#include "actor.h"

// Pause menu Status/Equip slot select, game mode 0x0E; see
// docs/memory-map/game_modes.md.

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

// Status/equip screen character rotations, indexed by sub_0803A030.
extern const ActorAssetRecord g_aStatusCharacterAssets[3];  // 0x0806B250
extern const StatusEquipSlot g_aStatusEquipSlots[6];  // 0x0806B2FC

// Screen actors and state of the slot select screen.
typedef struct {
    Actor *pCursor;               // 0x00
    Actor *pCharacter;            // 0x04: portrait of the chosen member
    Actor *apSlotFrames[6];       // 0x08
    Actor *apSlotItems[6];        // 0x20: equipped item icon per slot, or NULL
    void *apItemGfx[6][2];         // 0x38: tile/frame record passed to SetActorAssetRecord
    GameMode nextMode;             // 0x68: mode pushed once the fade-out finishes
} StatusEquipSlotSelectState;

extern StatusEquipSlotSelectState g_StatusEquipSlotSelect;  // 0x030054F8
extern s8 g_bStatusEquipSlot;  // 0x03005564: selected index into g_aStatusEquipSlots

extern void UpdateStatusEquipSlotSelect(void);
extern void InitializeStatusEquipSlotSelect(void);
extern void ExitStatusEquipSlotSelect(void);
extern void ResetStatusEquipSlot(void);  // selects slot 0
extern Actor *sub_0803A030(u32 character);
extern void DrawStatusEquipStatsPanel(void);
extern void sub_0803A3A0(void);
extern void sub_0803A534(void);
extern void TickStatusEquipSlotCursor(Actor *pCursor);
extern void sub_0803A590(void);
extern void sub_0803A604(void);
extern void sub_0803A630(void);
extern u32 sub_0803A678(void);
