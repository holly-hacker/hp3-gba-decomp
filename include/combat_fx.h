#pragma once

#include "battle/battle.h"
#include "battle/effect_script.h"
#include "video.h"

// Battle effect scripts and emitters; see docs/formats/battle_scripts.md.

extern Actor *TriggerBattleEffect(u8 effectId, s32 slotParam, s32 selectedActionIndex, s32 activeFighterIndex, s32 targetIdx, u16 damage);
extern Actor *CreateEffectScriptActor(s32 effectId, s32 kind);  // 0x08018BE0
extern void InterpretActorScript(Actor *actor);
extern ParticleEmitter *CreateBattleEffectEmitter_candidate(Actor *actor, s32 a1, s32 a2, s32 a3,
                                                             s32 a4, s32 a5, s32 a6, s32 a7, s32 a8,
                                                             s32 a9, s32 a10, s32 a11, s32 a12, s32 a13,
                                                             s32 a14, s32 a15, s32 a16);
// Scanline callback of the effect tables.
extern void sub_0801B130(u32 *pPayload0, u32 *pPayload1);
extern ParticleEmitter *sub_0801B204(Actor *actor, u32 a, u32 b);
extern ParticleEmitter *sub_0801B2EC(Actor *actor, u32 a, u32 b);
extern ParticleEmitter *sub_0801B348(Actor *actor, u32 a, u32 b);
extern s32 TryApplyParalysis(BattleFighter *fighter, s32 isEnemyMonster, s32 escapeChance);
extern void sub_0801B4BC(u32 a, void *b, u32 c, u32 d, void *e);
extern void SpawnParalysisEffect(Actor *actor);

// Data tables.
extern const u32 g_adwEffectBgControlOverride_candidate[4];  // 0x080539A8
extern const ScanlineEffectEntry g_aEffectScanlineTable0[6];   // 0x080539B8
extern const ScanlineEffectEntry g_aEffectScanlineTable1[9];   // 0x08053A18
extern const ScanlineEffectEntry g_aEffectScanlineTable2[6];   // 0x08053AA8
extern const ScanlineEffectEntry *const g_apEffectScanlineTables_candidate[3];  // 0x08053B08
extern const u8 g_abEffectScanlineTableSizes_candidate[3];    // 0x08053B14
extern const EffectStreamList32 g_RainStreakList_candidate;  // 0x08053B18
extern const EffectStreamList8 g_RainSplashList_candidate;   // 0x08053C20
extern const ActorOrbit g_aEffectOrbitParams_candidate[16];  // 0x08053C68
extern const u8 g_abEffectRosterIdPair_candidate[2];         // 0x08053D28
extern const u16 g_awBattleSlotPosX_candidate[7];            // 0x08053D2A, per fighter slot
extern const u8 g_abBattleSlotPosY_candidate[7];             // 0x08053D38
extern const ActorAssetRecord g_aEffectActorAssets[17];    // 0x08053D40
extern void *const g_apEffectPalettes[5];                    // 0x08053E50
extern const ActorAssetRecord g_aEffectAnimAssets[65];      // 0x08053E64, opcodes 0x01/0x02
extern const ActorAssetRecord g_aEffectAnimAssets2[38];     // 0x08054274, opcodes 0x03/0x04
extern const EffectBgRecord g_aEffectBgRecords_candidate[166];  // 0x080544D4
extern const u8 g_abScriptOpcodeLengths[168];                // 0x08054F34, operand bytes per opcode
extern const u8 g_abFighterIdleAnimData_candidate[6];        // 0x08054FDC
extern const u8 g_aEffectAnimData_candidate[65][226];        // 0x08054FE2
extern const u8 g_aEffectAnimData2_candidate[38][108];       // 0x08058944
extern const u8 *const g_apEffectScripts[65];                // 0x0805B978, one script per effect id

extern EffectStaging g_effectStaging;
extern u8 g_bReviveInsertCount_candidate;
