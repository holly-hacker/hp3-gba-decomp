#pragma once

#include "types.h"
#include "actor.h"

// Party member sprites and animations, set by SetPartyMemberAnim. The record arrays are
// indexed by character id, the animation tables by Actor.bFacing.
#define PARTY_CHARACTER_COUNT 9
typedef enum {
    PartyAnimStand = 0,
    PartyAnimWalk = 1,
    PartyAnimCast = 2,  // ends on ANIM_EVENT, which triggers the field spell
    PartyAnim3 = 3,
    PartyAnim4 = 4,
} PartyAnim;
extern void SetPartyMemberAnim(Actor *actor, u8 anim);
extern void ResetPartyState(void);
extern void sub_080248E8(void);
extern void sub_08024918(void);
extern void sub_08024980(u32 characterId);  // fills follower slot 0
extern void sub_080249A4(u32 characterId);  // fills follower slot 1
extern u32 GetPartyPresenceMask(void);
extern u32 GetPartySize(void);
// Starts the player's receive-item action and grants one of the reward (30-60 Sickles for
// REWARD_ID_GOLD).
extern void PlayerReceiveReward(u32 rewardId);
extern void PlayerReceiveRewardAlt(u32 rewardId);  // also sets the action timer to 0x42

extern const ActorGfxRecord g_UnusedPartyGfx;
extern const ActorGfxRecord g_PartyFocusGfx_candidate;
extern const ActorAssetRecord g_aPartyWalkAssets[PARTY_CHARACTER_COUNT];
extern const ActorAssetRecord g_aPartyAnim3Assets[PARTY_CHARACTER_COUNT];
extern const ActorAssetRecord g_aPartyCastAssets[PARTY_CHARACTER_COUNT];
extern const ActorAssetRecord g_aPartyAnim4Assets[PARTY_CHARACTER_COUNT];
extern const u8 g_abPartyStandFrames[8];
extern const u8 g_abPartyStandFramesChar8[8];
extern const u8 g_aPartyWalkAnims[8][18];
extern const u8 g_aPartyWalkAnimsChar8[8][14];
extern const u8 g_aPartyWalkAnimsChar4[8][18];
extern const u8 g_aPartyCastAnims[8][18];
extern const u8 g_aPartyAnim4Anims[8][4];
extern const u8 g_abPartyAnim3Anim[22];
extern const ActorGfxRecord g_UnusedPartyGfx2;
