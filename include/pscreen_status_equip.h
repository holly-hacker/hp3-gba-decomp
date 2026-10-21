#pragma once

#include "types.h"
#include "modes.h"
#include "actor.h"

// Pause menu Status/Equip slot select, game mode 0x0E.

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

// Status/equip screen character rotations, indexed by SpawnStatusCharacterActor.
extern const ActorAssetRecord g_aStatusCharacterAssets[3];  // 0x0806B250
extern const StatusEquipSlot g_aStatusEquipSlots[6];  // 0x0806B2FC

extern const ActorAssetRecord g_StatusEquipSlotFrameAsset;        // 0x0806B280
extern const void *const g_pStatusEquipSlotFramePalette;          // 0x0806B290
extern const ActorAssetRecord g_StatusEquipSlotCursorAsset;       // 0x0806B294
extern const void *const g_pStatusEquipSlotCursorPalette;         // 0x0806B2A4
extern const u8 g_abStatusEquipSlotCursorPulseAnim[14];           // 0x0806B2A8
extern const u8 g_abStatusEquipSlotCursorDimAnim[2];              // 0x0806B2B6
extern const u8 g_abStatusCharacterSpinAnim[66];                  // 0x0806B2B8

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
extern Actor *SpawnStatusCharacterActor(u32 character);  // the spinning portrait
extern void DrawStatusEquipStatsPanel(void);
extern void SpawnStatusEquipSlotActors(void);  // slot frames and equipped item icons
extern void FreeStatusEquipSlotActors(void);
extern void TickStatusEquipSlotCursor(Actor *pCursor);
extern void DrawStatusEquipSlotName(void);
extern void CloseStatusEquipSlotSelectScreen(void);
extern void UpdateStatusEquipSlotCursorAnim(void);
extern u32 IsStatusEquipSlotSelectable(void);
