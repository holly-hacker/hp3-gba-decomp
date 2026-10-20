#pragma once

#include "types.h"
#include "actor.h"
#include "camera.h"
#include "overworld/overworld.h"

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
extern Actor *SpawnPartyFollowerActor(u8 characterId);
extern void TickPlayerActor(Actor *actor);
extern void TickPartyFollowerActor(Actor *actor);
extern void TickPartySecondFollowerActor(Actor *actor);
extern Actor *SwapPartyMemberCharacters(Actor *a, Actor *b);  // returns b
extern void ResetPartyState(void);
extern void SpawnPartyFollowers(void);
extern void FreePartyActors(void);
extern Actor *SpawnFollowerActor0(u32 characterId);  // fills follower slot 0
extern Actor *SpawnFollowerActor1(u32 characterId);  // fills follower slot 1
// ItemCharacterMask of a character id; -1 for an unknown id.
extern s32 GetCharPresenceBit(u8 characterId);
extern u32 GetPartyPresenceMask(void);
extern u32 GetPartySize(void);
// Starts the player's receive-item action and grants one of the reward (30-60 Sickles for
// REWARD_ID_GOLD).
extern void PlayerReceiveReward(u32 rewardId);
extern void PlayerReceiveRewardAlt(u32 rewardId);  // also sets the action timer to 0x42

extern const ActorGfxRecord g_UnusedPartyGfx;
extern const ActorGfxRecord g_PartyLumosGfx;
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

extern const CameraFocusOffset g_PlayerCameraFocusOffset;

extern OverworldControlState g_OverworldControlState;
// Signed camera Y offset in pixels, added to quest event state 0x1B (sub_0803E45C).
extern s8 g_nCameraYOffset;
extern u8 g_abRoomScriptExitParams_candidate[2];
extern Actor *g_pPlayerActor;
// The two party followers' actors; NULL while the slot is empty.
extern Actor *g_pFollowerActor0;
extern Actor *g_pFollowerActor1;
// Character ids of the leader and the two follower slots.
extern u8 g_bPartyCharId0;
extern u8 g_bPartyCharId1;
extern u8 g_bPartyCharId2;
// Spells cast outside battle, in name text order (0x51B + id).
typedef enum {
    FieldSpellFlipendo  = 0,
    FieldSpellLumos     = 1,
    FieldSpellReparo    = 2,
    FieldSpellAlohomora = 3,
    FieldSpellGlacius   = 4,
    FieldSpellSpongify  = 5,
    FieldSpellDiffindo  = 6,
    FieldSpellWingardiumLeviosa = 7,  // no g_aFieldSpells entry selects it; its effect,
                                      // icon and name remain
} FieldSpell;

// Three field spells per party character, selected by g_bSelectedFieldSpell.
#define FIELD_SPELL_COUNT 9
typedef struct FieldSpellEntry {
    u32 dwSpell;          // FieldSpell
    u8 bFighterType;      // FighterType of the character casting it
    u8 bMinKnownSpells;   // bKnownSpellCount needed to select it
} FieldSpellEntry;
extern const FieldSpellEntry g_aFieldSpells[FIELD_SPELL_COUNT];
// Indexed by FieldSpell; FieldSpellWingardiumLeviosa's icon is a copy of Reparo's.
extern const ActorAssetRecord g_aFieldSpellIconAssets[8];
// Face portraits by FighterType; Buckbeak's repeats Ron's.
extern const ActorAssetRecord g_aFieldSpellPortraitAssets[4];
// The 240x16 bar behind the room name.
extern const ActorAssetRecord g_MapNamePopupAsset;

// Index into g_aFieldSpells. CycleSelectedFieldSpell steps it; it is
// saved with the party.
extern u8 g_bSelectedFieldSpell;
extern Actor *g_pPlayerShadowActor_candidate;

// One step of the player's movement. The followers replay the steps a fixed number of
// entries behind: follower 0 16 steps, follower 1 31.
#define PARTY_TRAIL_LENGTH 45
typedef struct PartyTrailStep {
    FixedPoint delta;  // the player's position change, 16.16
    u16 wFacing;
    u16 wAnimPaused;   // the player's ActorFlagAnimPaused
} PartyTrailStep;
extern PartyTrailStep *g_pPartyTrail;
extern u8 g_bPartyTrailWriteIndex;
extern u8 g_bPartyTrailReadIndex0;
extern u8 g_bPartyTrailReadIndex1;
extern FixedPoint g_PartyTrailLastPos;

// HUD actors, cleared by ResetPartyState and freed by FreeFieldHudActors.
extern Actor *g_pFieldSpellNameActor;       // selected spell's name text (DrawFieldSpellHud)
extern Actor *g_pMapNameTextActor;          // room name text (ShowMapNamePopup)
extern u32 g_dwUnk030033A8;  // zeroed by ResetPartyState and SpawnPartyFollowers; no reader found
extern Actor *g_pFieldSpellPortraitActor;   // face portrait of the spell's character (DrawFieldSpellHud)
extern Actor *g_pMapNamePopupActor;         // 240x16 bar sprite behind the room name (ShowMapNamePopup)
extern Actor *g_pFieldSpellIconActor;       // selected spell's icon (RefreshFieldSpellHud)

// Spawns g_pFieldSpellIconActor and shows the selected field spell.
extern Actor *SpawnFieldSpellIconActor(void);
// Shows the selected spell's name and fieldSpell's character portrait.
extern void DrawFieldSpellHud(u32 fieldSpell);
// pfnTick of the room name popup actors.
extern void TickMapNameActor(Actor *actor);
