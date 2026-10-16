#pragma once

#include "types.h"
#include "actor.h"

// Per-tile room actor constructors, selected by the u16 actorType at +8 of a
// tile record; see docs/formats/rooms.md. The caller stores the returned
// actor in the record and sets its tile column (+0x10) and row (+0x11).
typedef Actor *(*RoomActorConstructor)(u8 bColumn, u8 bRow);

#define ROOM_ACTOR_TYPE_COUNT 14

// Static tile record returned by GetRoomActorStaticRecord. The layout after nPixelY is
// specific to each actorType; every constructor reads it through its own struct.
typedef struct RoomActorRecordUnk8 {
    u16 wActorType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    u8 bVariant;  // 0x08
    u8 abPairs[16];  // 0x09, eight {A, B} pairs, copied to Actor 0x60 (A) and 0x68 (B)
} RoomActorRecordUnk8;

typedef struct RoomActorRecordUnkB {
    u16 wActorType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    u16 wArg8;
    u16 wArgA;
    u8 abArgC[3];
} RoomActorRecordUnkB;

typedef struct RoomActorRecordUnkA {
    u16 wActorType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    s16 nArg8;
    s16 nArgA;
    u8 bVariant;  // 0x0C
    u8 abArgD[2];
} RoomActorRecordUnkA;

typedef struct RoomActorRecordUnkC {
    u16 wActorType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    u8 abArg8[3];
} RoomActorRecordUnkC;

extern const RoomActorConstructor g_apRoomActorConstructors[ROOM_ACTOR_TYPE_COUNT];  // ROM 0x0804C054 (US)

extern Actor *SpawnRoomTileAnimationActor_candidate(u8 bColumn, u8 bRow);
extern Actor *SpawnDoorActor(u8 bColumn, u8 bRow);
extern Actor *SpawnSwitchActor(u8 bColumn, u8 bRow);
extern Actor *SpawnTriggerZoneActor(u8 bColumn, u8 bRow);
extern Actor *SpawnPropActor(u8 bColumn, u8 bRow);
extern Actor *SpawnNpcActor(u8 bColumn, u8 bRow);
extern Actor *SpawnTriggerRectActor(u8 bColumn, u8 bRow);
extern Actor *SpawnPushResetButtonActor(u8 bColumn, u8 bRow);
extern Actor *SpawnSpongifyPadActor(u8 bColumn, u8 bRow);
extern Actor *SpawnFlamePillarActor(u8 bColumn, u8 bRow);
extern Actor *SpawnRaisingPlatformActor(u8 bColumn, u8 bRow);
extern Actor *SpawnPortraitDoorActor(u8 bColumn, u8 bRow);

extern void sub_08044960(Actor *pActor);
extern void sub_08044ADC(Actor *pSelf, Actor *pOther);
extern const ActorGfxRecord g_aRoomFlamePillarSprites[3];             // ROM 0x0806C12C (US)
extern const ActorGfxRecord *const g_apRoomFlamePillarAnimFrames[3];  // ROM 0x0806C144 (US)
extern const void *const g_apRoomFlamePillarEffectData[3];             // ROM 0x0806C150 (US)
extern const u8 g_abRoomFlamePillarAnimData[22];                       // ROM 0x0806C15C (US)

extern void sub_08035664(Actor *pActor);
extern void sub_08035724(Actor *pSelf, Actor *pOther);
extern const ActorGfxRecord g_RoomActorUnk8Sprite;                    // ROM 0x080693CC (US)
extern const ActorGfxRecord *const g_apRoomActorUnk8AssetRecords[2];  // ROM 0x080693D4 (US)
extern const void *const g_apRoomActorUnk8EffectData[2];               // ROM 0x080693DC (US)

// Actor bytes 0x60-0x6F as written by the type 8 constructor.
typedef struct RoomActorUnk8State {
    u8 abA[8];
    u8 abB[8];
} RoomActorUnk8State;

#define ROOM_ACTOR_UNK8_STATE(pActor) ((RoomActorUnk8State *)&(pActor)->scriptState)

// Actor bytes 0x60-0x6D as word-sized state, written by the type 10 and 12 constructors.
typedef struct RoomActorWordState {
    s32 n60;
    s32 n64;
    s32 n68;
    u8 b6C;
    u8 b6D;
    u8 pad_6E;
    u8 b6F;
    u8 b70;
} RoomActorWordState;

#define ROOM_ACTOR_WORD_STATE(pActor) ((RoomActorWordState *)&(pActor)->scriptState)

// Three words zeroed whenever a type 10 or 12 actor is constructed.
extern u32 g_adwRoomActorUnkACState[3];

extern void sub_08040114(Actor *pActor);
extern void sub_08040358(Actor *pSelf, Actor *pOther);
// [3] is the spell effect sprite of sub_08040680.
extern const ActorGfxRecord g_aRoomSpongifyPadSprites[4];             // ROM 0x0806B8DC (US)
extern const ActorGfxRecord *const g_apRoomSpongifyPadAnimFrames[3];  // ROM 0x0806B8FC (US)
extern const void *const g_apRoomSpongifyPadEffectData[3];             // ROM 0x0806B908 (US)
extern const u8 g_abRoomSpongifyPadAnimData[30];                       // ROM 0x0806B914 (US)

extern void sub_0803B71C(Actor *pActor);
extern void sub_0803BA18(Actor *pSelf, Actor *pOther);
extern const ActorGfxRecord g_RoomRaisingPlatformSprite;  // ROM 0x0806B7D4 (US)
extern const u8 g_abRoomRaisingPlatformAnimData[46];       // ROM 0x0806B7DC (US)

// Types 2, 4 and 7 take their runtime actor type from the first word of the record.
typedef struct RoomActorRecordUnk2 {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bHalfWidth;   // 0x08, collision box extents
    u8 bHalfHeight;  // 0x09
    u8 bA;           // 0x0A
    u8 bB;           // 0x0B
    u8 bC;           // 0x0C
    u8 bD;           // 0x0D
} RoomActorRecordUnk2;

// Shared by types 4 and 7; differ only in where the fields sit in the record.
typedef struct RoomActorRecordUnk4 {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bHalfWidth;   // 0x08
    u8 bHalfHeight;  // 0x09
    u16 wArgA;       // 0x0A, scaled by 30 into Actor 0x60
    u8 bKind;        // 0x0C
    u8 bArgD;        // 0x0D
} RoomActorRecordUnk4;

typedef struct RoomActorRecordUnk7 {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bLeft;        // 0x08
    u8 bTop;         // 0x09
    u8 bRight;       // 0x0A
    u8 bBottom;      // 0x0B
    u16 wArgC;       // 0x0C, scaled by 30 into Actor 0x60
    u8 bKind;        // 0x0E
    u8 bArgF;        // 0x0F
} RoomActorRecordUnk7;

// Actor bytes 0x60-0x70 as written by the type 2, 4 and 7 constructors.
typedef struct RoomActorBoxState {
    u16 w60;
    u8 ab62[2];
} RoomActorBoxState;

#define ROOM_ACTOR_BOX_STATE(pActor) ((RoomActorBoxState *)&(pActor)->scriptState)

extern void sub_0800CBF0(Actor *pSelf, Actor *pOther);
extern void sub_0802BC74(Actor *pActor);
extern void sub_0802BBAC(Actor *pSelf, Actor *pOther);
extern void sub_080265B8(Actor *pSelf, Actor *pOther);
extern void sub_08026674(Actor *pSelf, Actor *pOther);
extern void sub_080264F0(Actor *pActor);

typedef struct RoomActorRecordUnk1 {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bAnimId;     // 0x08
    u8 bFlag;       // 0x09, nonzero: sub_080203F0, zero: sub_0802042C
} RoomActorRecordUnk1;

extern void AddRoomTileAnimation_candidate(u8 bAnimId, s32 x, s32 y, u8 bArg);
extern void sub_080203F0(s32 x, s32 y);
extern void sub_0802042C(s32 x, s32 y);
extern void sub_080205F8(Actor *pActor);

typedef struct RoomActorRecordUnk3 {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 pad_8;
    u8 bVariant;   // 0x09, index into the asset and effect tables; 0-10
    u16 wArgA;     // 0x0A, scaled by 30 into Actor 0x60
    u8 bFlagC;     // 0x0C
    u8 bArgD;      // 0x0D
} RoomActorRecordUnk3;

extern void sub_08044D24(Actor *pActor);
extern void sub_08044F54(Actor *pSelf, Actor *pOther);
extern const ActorGfxRecord g_aRoomSwitchSprites[5];                // ROM 0x0806C178 (US)
extern const ActorGfxRecord *const g_apRoomSwitchAssetRecords[12];  // ROM 0x0806C1A0 (US)
extern const void *const g_apRoomSwitchEffectData[12];               // ROM 0x0806C1D0 (US)

// Scripted trigger actor. bKind (0-82) selects the sprite, draw flags and
// collision behavior; the remaining record bytes become Actor bytes 0x62-0x68.
typedef struct RoomActorRecordUnk5 {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 pad_8[4];
    u8 bKind;      // 0x0C
    u8 bFacing;    // 0x0D
    u8 b62;        // 0x0E
    u8 b63;        // 0x0F
    u8 b64;        // 0x10
    u8 b65;        // 0x11
    u8 b66;        // 0x12
    u8 pad_13;
    u8 b68;        // 0x14
} RoomActorRecordUnk5;

// Actor bytes 0x60-0x6A as written by the type 5 constructor.
typedef struct RoomActorTriggerState {
    u8 b60;
    u8 bKind;
    u8 b62;
    u8 b63;
    u8 b64;
    u8 b65;
    u8 b66;
    u8 b67;
    u8 b68;
    u8 b69;
    u8 b6A;
} RoomActorTriggerState;

#define ROOM_ACTOR_TRIGGER_STATE(pActor) ((RoomActorTriggerState *)&(pActor)->scriptState)

extern Actor *sub_0802FD5C(Actor *pActor);
extern void sub_08045ECC(Actor *pActor);
extern void sub_080465D4(Actor *pSelf, Actor *pOther);
extern void sub_0804651C(Actor *pSelf, Actor *pOther);
extern const ActorGfxRecord g_aRoomActorTriggerSprites[80];             // ROM 0x0806C304 (US)
extern const ActorGfxRecord *const g_apRoomActorTriggerAnimFrames[91];  // ROM 0x0806C584 (US)
extern const void *const g_apRoomActorTriggerEffectData[91];             // ROM 0x0806C6F0 (US)
extern const s32 g_aRoomActorTriggerPushVelocity[8][2];                  // ROM 0x0806C85C (US)
extern const u32 g_adwRoomActorTriggerPushFacing[8];                     // ROM 0x0806C89C (US)
extern const ActorGfxRecord g_aRoomActorTriggerEffectSprites[7];        // ROM 0x0806C8BC (US)
extern const u8 g_abRoomActorTriggerAnimData[91][90];                    // ROM 0x0806C8F4 (US)
extern const u8 g_abRoomActorTriggerFacingFrames[8];                     // ROM 0x0806E8F2 (US)
extern const u8 g_abRoomActorTriggerFacingAnimStart[8];                  // ROM 0x0806E8FA (US)

typedef struct RoomActorRecordUnk6 {
    u32 dwActorType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bKind;      // 0x08, index into the asset tables
    u8 bFacing;    // 0x09, stored halved
    u8 pad_A[2];
    union {
        u32 dwWord;
        u8 bFirst;
    } argC;        // 0x0C; bFirst goes to Actor 0x8C, bytes 1 and 2 are tested as a pair
} RoomActorRecordUnk6;

extern void sub_0802F7F0(Actor *pActor);
extern void sub_0802FCC0(Actor *pSelf, Actor *pOther);
extern const u32 g_adwRoomActorUnk6FrameRows[110];          // ROM 0x08066E44 (US)
extern const ActorAssetRecord g_aActorTypeAssets[137];  // ROM 0x08066FFC (US), indexed by an actor kind
extern const u8 g_abRoomActorUnk6Frames[12][4];             // ROM 0x0806788C (US)

extern void sub_0802E2BC(Actor *pSpell, Actor *pTarget);  // overworld spell effect hits a room actor
