#pragma once

#include "types.h"
#include "actor.h"

// Text actors: SpawnTextActor spawns an actor that draws *ppText and files it in
// g_apTextActors[slot]; SetTextActorCenterPosition_candidate centers it on x.
// The actor draws as a row of anim.unk_DC.wOamStripCount 32x8 or 32x16 sprites
// (bForceOnscreen_candidate set; see UpdateActorOamCells), and keeps its slot in
// wCharacterId_candidate for ClearTextActorSlot.

// Text is drawn at most this many pixels wide and tall.
#define TEXT_ACTOR_MAX_WIDTH 240
#define TEXT_ACTOR_MAX_HEIGHT 16

// SetTextActorAlignedPosition align flags; without them (x, y) is the top left.
typedef enum {
    TextActorAlignCenterX = 0x1,
    TextActorAlignRight   = 0x2,
    TextActorAlignCenterY = 0x4,
    TextActorAlignBottom  = 0x8,
} TextActorAlign;

// A text actor's string size in pixels (at most TEXT_ACTOR_MAX_WIDTH and
// TEXT_ACTOR_MAX_HEIGHT), held where other actors keep the first ActorAnimState
// fields.
#define TEXT_ACTOR_WIDTH(pActor) (*(u16 *)&(pActor)->anim.bAnimFrameCounter)
#define TEXT_ACTOR_HEIGHT(pActor) (*(u16 *)&(pActor)->anim.bAnimFrameIndex_candidate)

// One 4bpp 8x8 tile.
typedef struct Tile4bpp {
    u32 aw[8];
} Tile4bpp;

extern Actor *g_apTextActors[17];  // 0x03005D10
extern u8 SpawnTextActorLines(const u8 **ppText, u32 slot);
extern void ResizeTextActor(Actor *pActor, const u8 *pText);
extern void DrawTextActorText(Actor *pActor, const u8 **ppText);
extern Actor *SpawnTextActor(const u8 **ppText, u32 slot);
// SpawnTextActor without filing the actor in a slot.
extern Actor *SpawnUnslottedTextActor(const u8 **ppText);
// Redraws a text actor with a new string.
extern void SetTextActorString(Actor *pActor, const u8 *pText);
extern void SetTextActorCenterPosition_candidate(Actor *pActor, s16 x, s16 y);
extern void SetTextActorAlignedPosition(Actor *pActor, const u8 *pText, s16 x, s16 y, u32 align);
extern void ClearTextActorSlots(void);
extern void ClearTextActorSlot(Actor *pActor);
