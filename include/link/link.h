#pragma once

#include "types.h"

// Serial-link session block at 0x03005A24, written by the link init/teardown
// code and LinkSerialTimer3Intr. See docs/memory-map/link.md. Only the fields
// with a confirmed role are named.
typedef struct LinkPlayerState {
    s32 dwUnk_0x00;         // 0x00, set to -1 by link init and teardown
    u8 bUnk_0x04;           // 0x04, zeroed by link init and teardown
    s8 bPlayerId;           // 0x05, this GBA's multiplayer terminal ID: SIOCNT bits 4-5
                             // (0 = parent, 1-3 = child) sampled by LinkSerialTimer3Intr
                             // while linked; -1 when no session
    u8 pad_06[0x02];        // -> 0x08
    u32 dwUnk_0x08;         // 0x08, zeroed by link init; set by sub_0803FA7C
} LinkPlayerState;

extern LinkPlayerState g_LinkPlayerState;

// Returns g_LinkPlayerState.bPlayerId; -1 when there is no link session.
extern s32 GetLinkPlayerId(void);
