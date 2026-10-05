#pragma once

#include "types.h"
#include "graphics/object.h"

// Per-tile room object constructors, selected by the u16 objType at +8 of a
// tile record; see docs/formats/rooms.md. The caller stores the returned
// object in the record and sets its tile column (+0x10) and row (+0x11).
typedef Object *(*RoomObjectConstructor)(u8 bColumn, u8 bRow);

#define ROOM_OBJECT_TYPE_COUNT 14

// Static tile record returned by sub_08005C38. The layout after nPixelY is
// specific to each objType; every constructor reads it through its own struct.
typedef struct RoomObjectRecordUnk8 {
    u16 wObjType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    u8 bVariant;  // 0x08
    u8 abPairs[16];  // 0x09, eight {A, B} pairs, copied to Object 0x60 (A) and 0x68 (B)
} RoomObjectRecordUnk8;

typedef struct RoomObjectRecordUnkB {
    u16 wObjType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    u16 wArg8;
    u16 wArgA;
    u8 abArgC[3];
} RoomObjectRecordUnkB;

typedef struct RoomObjectRecordUnkA {
    u16 wObjType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    s16 nArg8;
    s16 nArgA;
    u8 bVariant;  // 0x0C
    u8 abArgD[2];
} RoomObjectRecordUnkA;

typedef struct RoomObjectRecordUnkC {
    u16 wObjType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    u8 abArg8[3];
} RoomObjectRecordUnkC;

extern void *sub_08005C38(u8 bColumn, u8 bRow);
extern void sub_08030844(Object *pObj, const void *pEffectData);

extern const RoomObjectConstructor g_apRoomObjectConstructors[ROOM_OBJECT_TYPE_COUNT];  // ROM 0x0804C054 (US)

extern Object *SpawnRoomTileAnimationObject_candidate(u8 bColumn, u8 bRow);
extern Object *sub_0802BB00(u8 bColumn, u8 bRow);
extern Object *sub_08044C00(u8 bColumn, u8 bRow);
extern Object *sub_08026414(u8 bColumn, u8 bRow);
extern Object *sub_08045AE8(u8 bColumn, u8 bRow);
extern Object *sub_0802F500(u8 bColumn, u8 bRow);
extern Object *sub_08026348(u8 bColumn, u8 bRow);
extern Object *sub_08035540(u8 bColumn, u8 bRow);
extern Object *SpawnScriptedOneTimeObject(u8 bColumn, u8 bRow);
extern Object *sub_08040038(u8 bColumn, u8 bRow);
extern Object *sub_08044894(u8 bColumn, u8 bRow);
extern Object *sub_0803B64C(u8 bColumn, u8 bRow);
extern Object *sub_0802BC54(u8 bColumn, u8 bRow);

extern void sub_08044960(Object *pObj);
extern void sub_08044ADC(Object *pSelf, Object *pOther);
extern const ObjectGfxRecord g_aRoomObjUnkBSprites[3];             // ROM 0x0806C12C (US)
extern const ObjectGfxRecord *const g_apRoomObjUnkBAnimFrames[3];  // ROM 0x0806C144 (US)
extern const void *const g_apRoomObjUnkBEffectData[3];             // ROM 0x0806C150 (US)
extern const u8 g_abRoomObjUnkBAnimData[22];                       // ROM 0x0806C15C (US)

extern void sub_08035664(Object *pObj);
extern void sub_08035724(Object *pSelf, Object *pOther);
extern const ObjectGfxRecord g_RoomObjUnk8Sprite;                    // ROM 0x080693CC (US)
extern const ObjectGfxRecord *const g_apRoomObjUnk8AssetRecords[2];  // ROM 0x080693D4 (US)
extern const void *const g_apRoomObjUnk8EffectData[2];               // ROM 0x080693DC (US)

// Object bytes 0x60-0x6F as written by the type 8 constructor.
typedef struct RoomObjectUnk8State {
    u8 abA[8];
    u8 abB[8];
} RoomObjectUnk8State;

#define ROOM_OBJECT_UNK8_STATE(pObj) ((RoomObjectUnk8State *)&(pObj)->scriptState)

// Object bytes 0x60-0x6D as word-sized state, written by the type 10 and 12 constructors.
typedef struct RoomObjectWordState {
    s32 n60;
    s32 n64;
    s32 n68;
    u8 b6C;
    u8 b6D;
    u8 pad_6E;
    u8 b6F;
    u8 b70;
} RoomObjectWordState;

#define ROOM_OBJECT_WORD_STATE(pObj) ((RoomObjectWordState *)&(pObj)->scriptState)

// Three words zeroed whenever a type 10 or 12 object is constructed.
extern u32 g_adwRoomObjUnkACState[3];

extern void sub_08040114(Object *pObj);
extern void sub_08040358(Object *pSelf, Object *pOther);
// [3] is the spell effect sprite of sub_08040680.
extern const ObjectGfxRecord g_aRoomObjUnkASprites[4];                // ROM 0x0806B8DC (US)
extern const ObjectGfxRecord *const g_apRoomObjUnkAAnimFrames[3];     // ROM 0x0806B8FC (US)
extern const void *const g_apRoomObjUnkAEffectData[3];                // ROM 0x0806B908 (US)
extern const u8 g_abRoomObjUnkAAnimData[30];                          // ROM 0x0806B914 (US)

extern void sub_0803B71C(Object *pObj);
extern void sub_0803BA18(Object *pSelf, Object *pOther);
extern const ObjectGfxRecord g_RoomObjUnkCSprite;  // ROM 0x0806B7D4 (US)
extern const u8 g_abRoomObjUnkCAnimData[46];             // ROM 0x0806B7DC (US)

// Types 2, 4 and 7 take their runtime object type from the first word of the record.
typedef struct RoomObjectRecordUnk2 {
    u32 dwObjectType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bHalfWidth;   // 0x08, collision box extents
    u8 bHalfHeight;  // 0x09
    u8 bA;           // 0x0A
    u8 bB;           // 0x0B
    u8 bC;           // 0x0C
    u8 bD;           // 0x0D
} RoomObjectRecordUnk2;

// Shared by types 4 and 7; differ only in where the fields sit in the record.
typedef struct RoomObjectRecordUnk4 {
    u32 dwObjectType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bHalfWidth;   // 0x08
    u8 bHalfHeight;  // 0x09
    u16 wArgA;       // 0x0A, scaled by 30 into Object 0x60
    u8 bKind;        // 0x0C
    u8 bArgD;        // 0x0D
} RoomObjectRecordUnk4;

typedef struct RoomObjectRecordUnk7 {
    u32 dwObjectType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bLeft;        // 0x08
    u8 bTop;         // 0x09
    u8 bRight;       // 0x0A
    u8 bBottom;      // 0x0B
    u16 wArgC;       // 0x0C, scaled by 30 into Object 0x60
    u8 bKind;        // 0x0E
    u8 bArgF;        // 0x0F
} RoomObjectRecordUnk7;

// Object bytes 0x60-0x70 as written by the type 2, 4 and 7 constructors.
typedef struct RoomObjectBoxState {
    u16 w60;
    u8 ab62[2];
} RoomObjectBoxState;

#define ROOM_OBJECT_BOX_STATE(pObj) ((RoomObjectBoxState *)&(pObj)->scriptState)

extern void sub_0800CBF0(Object *pSelf, Object *pOther);
extern void sub_0802BC74(Object *pObj);
extern void sub_0802BBAC(Object *pSelf, Object *pOther);
extern void sub_080265B8(Object *pSelf, Object *pOther);
extern void sub_08026674(Object *pSelf, Object *pOther);
extern void sub_080264F0(Object *pObj);

typedef struct RoomObjectRecordUnk1 {
    u32 dwObjectType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bAnimId;     // 0x08
    u8 bFlag;       // 0x09, nonzero: sub_080203F0, zero: sub_0802042C
} RoomObjectRecordUnk1;

extern void AddRoomTileAnimation_candidate(u8 bAnimId, s32 x, s32 y, u8 bArg);
extern void sub_080203F0(s32 x, s32 y);
extern void sub_0802042C(s32 x, s32 y);
extern void sub_080205F8(Object *pObj);

typedef struct RoomObjectRecordUnk3 {
    u32 dwObjectType;
    s16 nPixelX;
    s16 nPixelY;
    u8 pad_8;
    u8 bVariant;   // 0x09, index into the asset and effect tables; 0-10
    u16 wArgA;     // 0x0A, scaled by 30 into Object 0x60
    u8 bFlagC;     // 0x0C
    u8 bArgD;      // 0x0D
} RoomObjectRecordUnk3;

extern void sub_08044D24(Object *pObj);
extern void sub_08044F54(Object *pSelf, Object *pOther);
extern const ObjectGfxRecord g_aRoomObjUnk3Sprites[5];               // ROM 0x0806C178 (US)
extern const ObjectGfxRecord *const g_apRoomObjUnk3AssetRecords[12];  // ROM 0x0806C1A0 (US)
extern const void *const g_apRoomObjUnk3EffectData[12];               // ROM 0x0806C1D0 (US)

// Scripted trigger object. bKind (0-82) selects the sprite, draw flags and
// collision behavior; the remaining record bytes become Object bytes 0x62-0x68.
typedef struct RoomObjectRecordUnk5 {
    u32 dwObjectType;
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
} RoomObjectRecordUnk5;

// Object bytes 0x60-0x6A as written by the type 5 constructor.
typedef struct RoomObjectTriggerState {
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
} RoomObjectTriggerState;

#define ROOM_OBJECT_TRIGGER_STATE(pObj) ((RoomObjectTriggerState *)&(pObj)->scriptState)

extern Object *sub_0802FD5C(Object *pObj);
extern void sub_08045ECC(Object *pObj);
extern void sub_080465D4(Object *pSelf, Object *pOther);
extern void sub_0804651C(Object *pSelf, Object *pOther);
extern const ObjectGfxRecord g_aRoomObjTriggerSprites[80];                // ROM 0x0806C304 (US)
extern const ObjectGfxRecord *const g_apRoomObjTriggerAnimFrames[91];     // ROM 0x0806C584 (US)
extern const void *const g_apRoomObjTriggerEffectData[91];                // ROM 0x0806C6F0 (US)
extern const s32 g_aRoomObjTriggerPushVelocity[8][2];                     // ROM 0x0806C85C (US)
extern const u32 g_adwRoomObjTriggerPushFacing[8];                        // ROM 0x0806C89C (US)
extern const ObjectGfxRecord g_aRoomObjTriggerEffectSprites[7];           // ROM 0x0806C8BC (US)
extern const u8 g_abRoomObjTriggerAnimData[91][90];                       // ROM 0x0806C8F4 (US)
extern const u8 g_abRoomObjTriggerFacingFrames[8];                        // ROM 0x0806E8F2 (US)
extern const u8 g_abRoomObjTriggerFacingAnimStart[8];                     // ROM 0x0806E8FA (US)

typedef struct RoomObjectRecordUnk6 {
    u32 dwObjectType;
    s16 nPixelX;
    s16 nPixelY;
    u8 bKind;      // 0x08, index into the asset tables
    u8 bFacing;    // 0x09, stored halved
    u8 pad_A[2];
    union {
        u32 dwWord;
        u8 bFirst;
    } argC;        // 0x0C; bFirst goes to Object 0x8C, bytes 1 and 2 are tested as a pair
} RoomObjectRecordUnk6;

extern void sub_0802F7F0(Object *pObj);
extern void sub_0802FCC0(Object *pSelf, Object *pOther);
extern const u32 g_adwRoomObjUnk6FrameRows[110];          // ROM 0x08066E44 (US)
extern const ObjectAssetRecord g_aObjectTypeAssets[137];  // ROM 0x08066FFC (US), indexed by an object kind
extern const u8 g_abRoomObjUnk6Frames[12][4];             // ROM 0x0806788C (US)

// One-time scripted object (chests and similar pickups). wScriptPc is the
// object's bit in g_abTriggeredScriptFlags.
typedef struct RoomObjectRecordUnk9 {
    u16 wObjType;
    u16 wUnk2;
    s16 nPixelX;
    s16 nPixelY;
    u16 wScriptPc;   // 0x08
    u8 bKind;        // 0x0A, 0-3; 2 despawns once triggered
    u8 bArgB;        // 0x0B
    u8 bArgC;        // 0x0C
    u8 bArgD;        // 0x0D
} RoomObjectRecordUnk9;

extern u8 g_abTriggeredScriptFlags[32];
extern void sub_0800BDCC(Object *pObj);
extern void sub_0800BF20(Object *pSelf, Object *pOther);
extern const ObjectGfxRecord g_RoomObjUnk9Sprite;                 // ROM 0x0804D524 (US)
extern const ObjectGfxRecord *const g_apRoomObjUnk9AnimFrames[4];  // ROM 0x0804D52C (US)
extern const u8 g_abRoomObjUnk9AnimData[4][100];                   // ROM 0x0804D53C (US)
