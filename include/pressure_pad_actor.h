#pragma once

#include "types.h"
#include "actor.h"

// Room actor of tile actorType 8, a button that a Flipendo spell presses to respawn
// a push puzzle's actors.

// Static tile record of actorType 8, returned by GetRoomActorStaticRecord.
typedef struct RoomActorRecordPushResetButton {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bVariant;  // 0x08
    u8 abTargets[16];  // 0x09, eight {group, member} pairs; see PushResetButtonTargets
} RoomActorRecordPushResetButton;

extern Actor *SpawnPushResetButtonActor(u8 bColumn, u8 bRow);
extern void TickPushResetButtonActor(Actor *pActor);
extern void HandlePushResetButtonTouch(Actor *pSelf, Actor *pOther);
extern const ActorGfxRecord g_PushResetButtonSprite;
extern const ActorGfxRecord *const g_apPushResetButtonSprites[2];
extern const void *const g_apPushResetButtonPalettes[2];
extern const u8 g_aabPushResetButtonPressAnims[2][20];

// Actor bytes 0x60-0x6F: the room records the button frees and respawns, as
// GetRoomActorPtr/SpawnRoomGroupMember arguments. (0, 0) entries are unused.
typedef struct PushResetButtonTargets {
    u8 abGroups[8];
    u8 abMembers[8];
} PushResetButtonTargets;

#define PUSH_RESET_BUTTON_TARGETS(pActor) ((PushResetButtonTargets *)&(pActor)->scriptState)
