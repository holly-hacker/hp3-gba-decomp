#pragma once

#include "types.h"
#include "actor.h"
#include "gen/graphics/menus.h"

typedef struct {
    Actor *pCursorActor;  // 0x00
    u32 dwRow;              // 0x04: party slot, 0..2
    u32 adwCharacter[3];    // 0x08: chosen character per slot; 0 = empty, else party character id + 1
    u32 dwTileCursor;       // 0x14: text tile cursor after drawing the slot labels
} CheatPartyState;

extern CheatPartyState g_CheatPartyState;  // 0x030021F8
extern const u32 g_dwCheatPartyBg0Control;  // 0x0804C4CC
extern const u32 g_dwCheatPartyBg1Control;  // 0x0804C4D0
extern const ActorAssetRecord g_CheatPartyAnimFrames;  // 0x0804C4D4
extern const u8 g_CheatPartyAnimData[18];    // 0x0804C4E4

extern void DrawCheatPartyRows(void);
extern void ApplyCheatParty(void);
extern void DrawCheatPartyCharacters(void);
extern const u8 sPlayableCharacterNames[9][32];  // 0x0804C4F6
