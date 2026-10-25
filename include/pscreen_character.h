#pragma once

#include "types.h"
#include "modes.h"
#include "actor.h"

// Pause menu Status/Equip character select, game modes 0x0C/0x0D.

extern GameMode g_StatusEquipReturnMode;  // 0x03005298: StatusEquipCharacterSelect's B target
extern GameMode g_StatusEquipNextMode;    // 0x0300529C: StatusEquipCharacterSelect's A target

// Its three slots show, left to right, Hermione, Harry and Ron.
typedef struct {
    u32 adwSlotPresent[3];  // 0x00: nonzero when the slot's member is in the party
    GameMode nextMode;      // 0x0C: mode pushed once the fade-out finishes
} StatusEquipCharacterSelectState;

extern StatusEquipCharacterSelectState g_StatusEquipCharacterSelect;  // 0x030052A8
extern u8 g_bStatusEquipCharacterSlot;  // 0x030052B8: cursor slot (0-2)
extern u32 g_dwStatusEquipCharacter;    // 0x030052A0: FighterType chosen in character select

extern const ActorAssetRecord g_aUnusedPartyAssetRecords[4];
extern const u32 g_adwStatusEquipCharacterNameTextIds[3];  // by FighterType
extern const u32 g_dwStatusEquipCharacterSelectBg3Control;  // BG3, the character panels

extern void UpdateStatusEquipCharacterSelect(void);
extern void InitializeStatusEquipCharacterSelect(void);
extern void InitializeStatusEquipCharacterSelectLastCursor(void);
extern void ExitStatusEquipCharacterSelect(void);
// Draws a slot's level, Exp, Next, SP and MP rows; the color argument is unused.
extern void DrawStatusEquipCharacterStats(u32 slot, u32 color);
extern void BeginStatusEquipCharacterSelectScreen(void);
extern void NoopStatusEquipCharacterSelectDrawn(void);
extern void TickStatusEquipCharacterCursor(Actor *pCursor);
// Moves the cursor to a slot and redraws the two affected stat panels.
extern void SetStatusEquipCharacterSlot(u32 slot);
extern void CloseStatusEquipCharacterSelectScreen(void);
extern u8 StatusEquipSlotToCharacter(u8 slot);
extern u8 StatusEquipCharacterToSlot(u32 character);
// Screen column (0-2) of a slot's panel: one member is centred, two use the outer columns.
extern u8 StatusEquipSlotToColumn(u8 slot);
