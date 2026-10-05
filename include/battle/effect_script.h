#pragma once

#include "types.h"
#include "graphics/object.h"
#include "graphics/graphics.h"
#include "battle/battle.h"
#include "graphics/scanline_effects.h"

// Battle-effect script interpreter; see docs/formats/battle_scripts.md.

// Whole-pixel screen position pair.
typedef struct ScreenPoint {
    s32 x;
    s32 y;
} ScreenPoint;

// One 0x10-byte background record read by script opcodes 0x7F, 0x8A and 0x8B.
typedef struct EffectBgRecord {
    void *pGfx;         // 0x00
    u16 wUnk04;         // 0x04
    u16 wUnk06;         // 0x06
    void *pControls;    // 0x08
    u16 wUnk0C;         // 0x0C
    u16 pad_0E;         // 0x0E
} EffectBgRecord;

// What EffectBgRecord::pControls points at: an 8-byte control block, then streams.
typedef struct {
    const void *pStream;
    u32 dwTag;
} EffectStreamEntry;
typedef struct {
    u32 adwControls[2];
    EffectStreamEntry entries[32];
} EffectStreamList32;
typedef struct {
    u32 adwControls[2];
    EffectStreamEntry entries[8];
} EffectStreamList8;
extern const EffectStreamList32 g_RainStreakList_candidate;  // 0x08053B18
extern const EffectStreamList8 g_RainSplashList_candidate;   // 0x08053C20

extern const u8 *const g_apEffectScripts[65];                // 0x0805B978, one script per effect id
extern const u8 g_abScriptOpcodeLengths[168];                // 0x08054F34, operand bytes per opcode
extern const ObjectAssetRecord g_aEffectObjectAssets[17];    // 0x08053D40
extern void *const g_apEffectPalettes[5];                    // 0x08053E50
extern const ObjectAssetRecord g_aEffectAnimAssets[65];      // 0x08053E64, opcodes 0x01/0x02
extern const ObjectAssetRecord g_aEffectAnimAssets2[38];     // 0x08054274, opcodes 0x03/0x04
extern const u8 g_aEffectAnimData_candidate[65][226];        // 0x08054FE2
extern const u8 g_aEffectAnimData2_candidate[38][108];       // 0x08058944
extern const u8 g_abFighterIdleAnimData_candidate[6];        // 0x08054FDC
extern const u32 g_adwEffectBgControlOverride_candidate[4];  // 0x080539A8
extern const ScanlineEffectEntry g_aEffectScanlineTable0[6];   // 0x080539B8
extern const ScanlineEffectEntry g_aEffectScanlineTable1[9];   // 0x08053A18
extern const ScanlineEffectEntry g_aEffectScanlineTable2[6];   // 0x08053AA8
extern const ScanlineEffectEntry *const g_apEffectScanlineTables_candidate[3];  // 0x08053B08
extern const u8 g_abEffectScanlineTableSizes_candidate[3];    // 0x08053B14

// Scanline callbacks of the effect tables.
extern void sub_0801B130(u32 *pPayload0, u32 *pPayload1);
extern void sub_0801B950(u32 *pPayload0, u32 *pPayload1);
extern void sub_0801B998(u32 *pPayload0, u32 *pPayload1);
extern void sub_0801B9BC(u32 *pPayload0, u32 *pPayload1);
extern void sub_0801B9F4(u32 *pPayload0, u32 *pPayload1);
extern void sub_0801BA2C(u32 *pPayload0, u32 *pPayload1);
extern void sub_0801BA44(u32 *pPayload0, u32 *pPayload1);
extern const s16 g_aEffectOrbitParams_candidate[16][6];      // 0x08053C68
extern const u8 g_abEffectRosterIdPair_candidate[2];         // 0x08053D28
extern const u16 g_awBattleSlotPosX_candidate[7];            // 0x08053D2A, per fighter slot
extern const u8 g_abBattleSlotPosY_candidate[7];             // 0x08053D38
extern const EffectBgRecord g_aEffectBgRecords_candidate[166];  // 0x080544D4

extern void InterpretObjectScript(Object *obj);
extern void WaitFramesTick(Object *obj);
extern void WaitForCounterTick(Object *obj);
extern void WaitForFieldClearTick(Object *obj);
extern void WaitForCasterField86Tick_candidate(Object *obj);
extern ScreenPoint ComputeEffectSpawnPosition(void);
extern void CopyOrbitParamsFromTable(Object *obj, const void *row);
extern s32 IsObjectFlippedX(Object *obj);
extern s32 sub_08003954(Object *obj);
extern void sub_08003788(Object *obj, s32 flip);
extern s32 sub_08001AA8(Object *obj, u32 index, ScreenPoint *out);  // returns 0 when the frame has no such anchor
extern void sub_0801B710(Object *obj, u8 label);  // jumps the script to the Label opcode with this id
extern void sub_08030A1C(u32 a, u32 b, const void *rec);
extern void sub_080075A8(u32 a, u32 b, u32 c, u32 d, u32 e);
extern void sub_0800D244(void *a, u32 b, u32 c);
extern void sub_0800D4A4(u32 a, u32 b, u32 c, u32 d);
extern void sub_0801B4BC(u32 a, void *b, u32 c, u32 d, void *e);
extern void sub_080454F4(u16 a, u16 b, u32 c);
extern void sub_08012A00(void);
extern void *sub_08012A84(void);
extern void sub_080065D4(u32 a, void *b, u32 c);
extern void sub_08037104(u32 a);
extern void sub_0800E890(u32 fighterIndex);
extern s32 sub_080189C8(u32 rosterIndex);  // per-monster XP reward
extern s32 sub_08018AB8(u32 rosterIndex);  // per-monster gold reward
extern ParticleEmitter *sub_0801B204(Object *obj, u32 a, u32 b);
extern ParticleEmitter *sub_0801B2EC(Object *obj, u32 a, u32 b);
extern ParticleEmitter *sub_0801B348(Object *obj, u32 a, u32 b);
extern ParticleEmitter *sub_0801B774(Object *obj, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h, u32 i, u32 j, u32 k, u32 l);
extern ParticleEmitter *sub_0801B870(Object *obj, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h);
extern ParticleEmitter *CreateBattleEffectEmitter_candidate(Object *obj, s32 a1, s32 a2, s32 a3,
                                                             s32 a4, s32 a5, s32 a6, s32 a7, s32 a8,
                                                             s32 a9, s32 a10, s32 a11, s32 a12, s32 a13,
                                                             s32 a14, s32 a15, s32 a16);
extern void DarkenScreenPalette(void);
extern void RestoreScreenPalette(void);
