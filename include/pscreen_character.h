#pragma once

#include "types.h"
#include "modes.h"

// Pause menu Status/Equip character select, game modes 0x0C/0x0D; see
// docs/memory-map/game_modes.md.

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

extern void UpdateStatusEquipCharacterSelect(void);
extern void InitializeStatusEquipCharacterSelect(void);
extern void InitializeStatusEquipCharacterSelectLastCursor(void);
extern void ExitStatusEquipCharacterSelect(void);
extern void sub_08035A34(void);
extern void sub_08035D98(u32 slot);
extern void sub_08035DC0(void);
extern u8 StatusEquipSlotToCharacter(u8 slot);
extern u8 StatusEquipCharacterToSlot(u32 character);
