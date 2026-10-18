#pragma once

#include "combat.h"
#include "video.h"

// Battle effect scripts and emitters; see docs/formats/battle_scripts.md.

// Battle-effect staging area at 0x03002750. TriggerBattleEffect fills the
// fields below before spawning the effect actor; the low bytes belong to
// other battle state.
typedef struct EffectStaging {
    ParticleEmitter *pEmitter_candidate;  // 0x00, emitter spawned by the last emitter opcode
    u8 pad_04[0x02];
    u16 awSavedOrbit[6];    // 0x06, orbit parameters saved by script opcode 0x43
    u8 pad_12[0x08];
    u16 wTimer_candidate;
    u16 wTimerMax_candidate;
    u16 wContextValue;
    u8 bScriptParam;
    u8 bSlotParam;
    u8 bTargetIndex;
    u8 bCasterIndex;
    u8 bBgEffectId_candidate;
    u8 bStateA_candidate;
    u8 bStateB_candidate;
    u8 bIdStaged_candidate;
} EffectStaging;

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

// Battle-effect script bytecode.
// Each BS_<Name>(...) macro expands to the opcode byte followed by its
// operand bytes; the operand count is fixed per opcode and checked by
// the preprocessor.

enum BattleScriptOpcode {
    BSOP_End = 0x00,
    BSOP_SetActorAnim = 0x01,
    BSOP_SetActorAnimAndPalette = 0x02,
    BSOP_SetActorAnimFromTable2 = 0x03,
    BSOP_SetActorAnimFromTable2AndPalette = 0x04,
    BSOP_SetEffectPalette = 0x05,
    BSOP_PlaySound = 0x06,
    BSOP_UnmuteMusic = 0x07,
    BSOP_WaitFrames = 0x08,
    BSOP_WaitForCounter = 0x09,
    BSOP_WaitForFieldClear = 0x0A,
    BSOP_MoveToAbsolute = 0x0B,
    BSOP_MoveTo = 0x0C,
    BSOP_StopMove = 0x0D,
    BSOP_SpawnEffectDetached = 0x0E,
    BSOP_SpawnEffect = 0x0F,
    BSOP_SpawnEffectAtSelfDetached = 0x10,
    BSOP_SpawnEffectAtSelf = 0x11,
    BSOP_SpawnEffectOffsetDetached = 0x12,
    BSOP_SpawnEffectOffset = 0x13,
    BSOP_Unk14 = 0x14,
    BSOP_Unk15 = 0x15,
    BSOP_SpawnEffectSharedTiles = 0x16,
    BSOP_ToggleActorFlipX = 0x17,
    BSOP_ToggleActorFlipY = 0x18,
    BSOP_MoveBy = 0x19,
    BSOP_MoveBy_2 = 0x1A,
    BSOP_SnapToCaster = 0x1B,
    BSOP_TeleportToSlotPosition = 0x1C,
    BSOP_SetVelocity = 0x1D,
    BSOP_SetVelocity16 = 0x1E,
    BSOP_Unk1F = 0x1F,
    BSOP_SetLocal = 0x20,
    BSOP_IncrementLocal = 0x21,
    BSOP_SkipBytes = 0x22,
    BSOP_GotoIfContextLow = 0x23,
    BSOP_GotoIfLocalAEqual = 0x24,
    BSOP_GotoIfScriptParamEqual = 0x25,
    BSOP_GotoIfLocalANotEqual = 0x26,
    BSOP_GotoIfFighterRosterMatches = 0x27,
    BSOP_GotoIfLocalAEqual_2 = 0x28,
    BSOP_GotoIfScriptParamEqual_2 = 0x29,
    BSOP_GotoIfLocalANotEqual_2 = 0x2A,
    BSOP_GotoIfFighterRosterMatches_2 = 0x2B,
    BSOP_GotoIfLocalBEqual = 0x2C,
    BSOP_GotoIfLocalBNotEqual = 0x2D,
    BSOP_GotoIfLocalBEqual_2 = 0x2E,
    BSOP_GotoIfLocalBNotEqual_2 = 0x2F,
    BSOP_AdvanceAttackOutcome = 0x30,
    BSOP_CreateEmitter12 = 0x31,
    BSOP_CreateEmitter8 = 0x32,
    BSOP_CreateEmitterOnSelf = 0x33,
    BSOP_CreateEmitterOnTarget = 0x34,
    BSOP_Unk35 = 0x35,
    BSOP_Unk36 = 0x36,
    BSOP_FreeAllParticles = 0x37,
    BSOP_ReleaseWindupEmitter = 0x38,
    BSOP_ReleaseKind2Emitters = 0x39,
    BSOP_Unk3A = 0x3A,
    BSOP_SetBehaviorFlags = 0x3B,
    BSOP_ClearBehaviorFlags = 0x3C,
    BSOP_BlendEffectPalette = 0x3D,
    BSOP_SetOamPalette = 0x3E,
    BSOP_Unk3F = 0x3F,
    BSOP_Unk40 = 0x40,
    BSOP_StartOrbitMotion = 0x41,
    BSOP_StartOrbitMotionRandom = 0x42,
    BSOP_SaveOrbit = 0x43,
    BSOP_RestoreOrbit = 0x44,
    BSOP_StartCasterOrbitMotion = 0x45,
    BSOP_SetAffineScale1 = 0x46,
    BSOP_SetAffineScale3 = 0x47,
    BSOP_StartAffineWobble = 0x48,
    BSOP_StopAffineWobble = 0x49,
    BSOP_SetAffineScaleTween = 0x4A,
    BSOP_SetAffineRotation1 = 0x4B,
    BSOP_SetAffineRotation3 = 0x4C,
    BSOP_SetAffineScaleRotation1 = 0x4D,
    BSOP_SetAffineScaleRotation3 = 0x4E,
    BSOP_ReleaseAffineSlot = 0x4F,
    BSOP_ClearAnimFlag = 0x50,
    BSOP_SetAnimFlag = 0x51,
    BSOP_HideActor = 0x52,
    BSOP_ShowActor = 0x53,
    BSOP_SetOamPriority = 0x54,
    BSOP_SetTargetOamPriority = 0x55,
    BSOP_SetEnemiesOamPriority = 0x56,
    BSOP_SetAlliesOamPriority = 0x57,
    BSOP_IncrementActionVariant = 0x58,
    BSOP_SnapToRandomAroundSlot = 0x59,
    BSOP_SnapToRandomAroundSpawn = 0x5A,
    BSOP_JitterPosition = 0x5B,
    BSOP_EnableSemiTransparency = 0x5C,
    BSOP_DisableBlendMode = 0x5D,
    BSOP_StartAlphaFade = 0x5E,
    BSOP_SetAlphaBlend = 0x5F,
    BSOP_Label = 0x60,
    BSOP_Goto = 0x61,
    BSOP_Goto_2 = 0x62,
    BSOP_GotoLocalIndexedLabel = 0x63,
    BSOP_FreeTileAllocation = 0x64,
    BSOP_StartDelayedChain = 0x65,
    BSOP_Unk66 = 0x66,
    BSOP_SetLocalRandomRange = 0x67,
    BSOP_SetDepthBiasZero = 0x68,
    BSOP_SetDepthBiasMax = 0x69,
    BSOP_SetDepthBias = 0x6A,
    BSOP_SetDepthBiasInverseLocalA = 0x6B,
    BSOP_SetDepthBiasLocalA = 0x6C,
    BSOP_Unk6D = 0x6D,
    BSOP_Unk6E = 0x6E,
    BSOP_ScrollBgUp = 0x6F,
    BSOP_ScrollBgDown = 0x70,
    BSOP_SetTargetVelocityScaled = 0x71,
    BSOP_SetTargetVelocity = 0x72,
    BSOP_SetCasterVelocityProduct = 0x73,
    BSOP_NudgeCaster = 0x74,
    BSOP_NudgeTarget = 0x75,
    BSOP_SetCasterPosition = 0x76,
    BSOP_SetTargetPosition = 0x77,
    BSOP_SnapTargetToSlot = 0x78,
    BSOP_SnapCasterToSpawn = 0x79,
    BSOP_MoveFighterTo = 0x7A,
    BSOP_MoveFighterToSlotPosition = 0x7B,
    BSOP_MoveCasterTo = 0x7C,
    BSOP_WaitForCasterField86 = 0x7D,
    BSOP_SetCasterAnim = 0x7E,
    BSOP_LoadBgEffect = 0x7F,
    BSOP_QueueScanlineEffect = 0x80,
    BSOP_SetBgEffectId = 0x81,
    BSOP_TeleportTo = 0x82,
    BSOP_KillTarget = 0x83,
    BSOP_RampBlendUp = 0x84,
    BSOP_RampBlendDown = 0x85,
    BSOP_GotoIfLocalAGreater = 0x86,
    BSOP_GotoIfLocalALess = 0x87,
    BSOP_GotoIfLocalAInRange = 0x88,
    BSOP_GotoIfLocalAOutOfRange = 0x89,
    BSOP_SetBgPaletteColors = 0x8A,
    BSOP_SetBgPaletteColorsAdjust = 0x8B,
    BSOP_SetBgPriority = 0x8C,
    BSOP_SetEffectTimers = 0x8D,
    BSOP_StartFadeCounter = 0x8E,
    BSOP_SetWindowLayers = 0x8F,
    BSOP_SetWindowRect = 0x90,
    BSOP_SetBehaviorFlag10 = 0x91,
    BSOP_HideWindow = 0x92,
    BSOP_ResetBgState = 0x93,
    BSOP_Unk94 = 0x94,
    BSOP_Unk95 = 0x95,
    BSOP_FlipTargetFacing = 0x96,
    BSOP_StatusEffect = 0x97,
    BSOP_Unk98 = 0x98,
    BSOP_SetLocalAToPartySize = 0x99,
    BSOP_Unk9A = 0x9A,
    BSOP_SetDispcntBit15 = 0x9B,
    BSOP_ClearDispcntBit15 = 0x9C,
    BSOP_SelectFirstAlly = 0x9D,
    BSOP_SelectNextAlly = 0x9E,
    BSOP_SelectFirstLiveEnemy = 0x9F,
    BSOP_SelectNextLiveEnemy = 0xA0,
    BSOP_UnkA1 = 0xA1,
    BSOP_SetLocalRandom = 0xA2,
    BSOP_ReloadBattleBackgroundTiles = 0xA3,
    BSOP_PlaySoundOrDefault = 0xA4,
    BSOP_DarkenScreenPalette = 0xA5,
    BSOP_RestoreScreenPalette = 0xA6,
    BSOP_PlaySoundEffect = 0xA7,
    BSOP_COUNT = 0xA8,
};

// StatusEffect (0x97) first operand: selects the effect applied.
enum BattleStatusEffect {
    BSSTATUS_SpawnEffectA = 0,
    BSSTATUS_SpawnEffectB = 1,
    BSSTATUS_ExtraExpBonus = 2,
    BSSTATUS_GrantExtraXp = 3,
    BSSTATUS_UnusedWinoutWrite = 4,
    BSSTATUS_Poisoned = 5,
    BSSTATUS_AttackWeakened = 6,
    BSSTATUS_PoisonImmune = 7,
    BSSTATUS_HiddenSecondary = 8,
    BSSTATUS_HiddenMain = 9,
    BSSTATUS_Paralyze25 = 10,
    BSSTATUS_DefenseBoost = 11,
    BSSTATUS_BumpMonsterDocLevel = 12,
    BSSTATUS_SetPostActionFlashFlag = 13,
    BSSTATUS_ClearPostActionFlashFlag = 14,
    BSSTATUS_CurePoison = 15,
    BSSTATUS_ToggleUltimateVisual = 16,
    BSSTATUS_Paralyze99 = 17,
    BSSTATUS_Paralyze80 = 18,
    BSSTATUS_SpellPowerBoost = 19,
    BSSTATUS_CureAilments = 20,
    BSSTATUS_SpawnEffectC = 21,
    BSSTATUS_ParalyzeMonster = 22,
    BSSTATUS_ParalyzeMonsterChance = 23,
    BSSTATUS_PaletteFlash = 24,
    BSSTATUS_ReplenishPartySp = 25,
    BSSTATUS_ReplenishTargetMp = 26,
    BSSTATUS_ForceItemDrop = 27,
    BSSTATUS_Revive = 28,
};

// Operand conventions: most operands are raw bytes. Where the interpreter reads an operand as a
// signed byte the macro takes a signed value, and where it reads two bytes as an 8.8 fixed-point
// number (whole byte first) the macro takes one 16-bit value, e.g. 0x0180 for 1.5.

#define BS_End() BSOP_End
#define BS_SetActorAnim(a, b) BSOP_SetActorAnim, (a), (b)
#define BS_SetActorAnimAndPalette(a, b) BSOP_SetActorAnimAndPalette, (a), (b)
#define BS_SetActorAnimFromTable2(a, b) BSOP_SetActorAnimFromTable2, (a), (b)
#define BS_SetActorAnimFromTable2AndPalette(a, b) BSOP_SetActorAnimFromTable2AndPalette, (a), (b)
#define BS_SetEffectPalette(a) BSOP_SetEffectPalette, (a)
#define BS_PlaySound(a) BSOP_PlaySound, (a)
#define BS_UnmuteMusic() BSOP_UnmuteMusic
#define BS_WaitFrames(a) BSOP_WaitFrames, (a)
#define BS_WaitForCounter() BSOP_WaitForCounter
#define BS_WaitForFieldClear() BSOP_WaitForFieldClear
#define BS_MoveToAbsolute(a, b, c) BSOP_MoveToAbsolute, (a), (b), (c)
#define BS_MoveTo(a, b, c, d, e) BSOP_MoveTo, ((a) & 0xFF), ((b) & 0xFF), (c), (d), (e)
#define BS_StopMove() BSOP_StopMove
#define BS_SpawnEffectDetached(a) BSOP_SpawnEffectDetached, (a)
#define BS_SpawnEffect(a) BSOP_SpawnEffect, (a)
#define BS_SpawnEffectAtSelfDetached(a) BSOP_SpawnEffectAtSelfDetached, (a)
#define BS_SpawnEffectAtSelf(a) BSOP_SpawnEffectAtSelf, (a)
#define BS_SpawnEffectOffsetDetached(a, b, c, d, e) BSOP_SpawnEffectOffsetDetached, (a), ((b) & 0xFF), (c), ((d) & 0xFF), (e)
#define BS_SpawnEffectOffset(a, b, c, d, e) BSOP_SpawnEffectOffset, (a), ((b) & 0xFF), (c), ((d) & 0xFF), (e)
#define BS_Unk14(a) BSOP_Unk14, (a)
#define BS_Unk15(a, b, c, d, e) BSOP_Unk15, (a), (b), (c), (d), (e)
#define BS_SpawnEffectSharedTiles(a) BSOP_SpawnEffectSharedTiles, (a)
#define BS_ToggleActorFlipX() BSOP_ToggleActorFlipX
#define BS_ToggleActorFlipY() BSOP_ToggleActorFlipY
#define BS_MoveBy(a, b) BSOP_MoveBy, ((a) & 0xFF), ((b) & 0xFF)
#define BS_MoveBy_2(a, b) BSOP_MoveBy_2, ((a) & 0xFF), ((b) & 0xFF)
#define BS_SnapToCaster(a) BSOP_SnapToCaster, (a)
#define BS_TeleportToSlotPosition(a) BSOP_TeleportToSlotPosition, (a)
#define BS_SetVelocity(a, b) BSOP_SetVelocity, ((a) & 0xFF), ((b) & 0xFF)
#define BS_SetVelocity16(a, b, c, d) BSOP_SetVelocity16, (a), (((b) >> 8) & 0xFF), ((b) & 0xFF), (c), (((d) >> 8) & 0xFF), ((d) & 0xFF)
#define BS_Unk1F(a, b, c) BSOP_Unk1F, (a), (b), (c)
#define BS_SetLocal(a, b) BSOP_SetLocal, (a), (b)
#define BS_IncrementLocal(a) BSOP_IncrementLocal, (a)
#define BS_SkipBytes(a) BSOP_SkipBytes, (a)
#define BS_GotoIfContextLow(a) BSOP_GotoIfContextLow, (a)
#define BS_GotoIfLocalAEqual(a, b) BSOP_GotoIfLocalAEqual, (a), (b)
#define BS_GotoIfScriptParamEqual(a, b) BSOP_GotoIfScriptParamEqual, (a), (b)
#define BS_GotoIfLocalANotEqual(a, b) BSOP_GotoIfLocalANotEqual, (a), (b)
#define BS_GotoIfFighterRosterMatches(a) BSOP_GotoIfFighterRosterMatches, (a)
#define BS_GotoIfLocalAEqual_2(a, b) BSOP_GotoIfLocalAEqual_2, (a), (b)
#define BS_GotoIfScriptParamEqual_2(a, b) BSOP_GotoIfScriptParamEqual_2, (a), (b)
#define BS_GotoIfLocalANotEqual_2(a, b) BSOP_GotoIfLocalANotEqual_2, (a), (b)
#define BS_GotoIfFighterRosterMatches_2(a) BSOP_GotoIfFighterRosterMatches_2, (a)
#define BS_GotoIfLocalBEqual(a, b) BSOP_GotoIfLocalBEqual, (a), (b)
#define BS_GotoIfLocalBNotEqual(a, b) BSOP_GotoIfLocalBNotEqual, (a), (b)
#define BS_GotoIfLocalBEqual_2(a, b) BSOP_GotoIfLocalBEqual_2, (a), (b)
#define BS_GotoIfLocalBNotEqual_2(a, b) BSOP_GotoIfLocalBNotEqual_2, (a), (b)
#define BS_AdvanceAttackOutcome() BSOP_AdvanceAttackOutcome
#define BS_CreateEmitter12(a, b, c, d, e, f, g, h, i, j, k, l) BSOP_CreateEmitter12, (a), (b), (c), (d), (e), (f), (g), (h), (i), (j), (k), (l)
#define BS_CreateEmitter8(a, b, c, d, e, f, g, h) BSOP_CreateEmitter8, (a), (b), (c), (d), (e), (f), (g), (h)
#define BS_CreateEmitterOnSelf(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) BSOP_CreateEmitterOnSelf, (a), (b), (c), (d), (e), (f), (g), (h), (i), (j), (k), (l), (m), (n), (o), (p)
#define BS_CreateEmitterOnTarget(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) BSOP_CreateEmitterOnTarget, (a), (b), (c), (d), (e), (f), (g), (h), (i), (j), (k), (l), (m), (n), (o), (p)
#define BS_Unk35(a, b, c) BSOP_Unk35, (a), (b), (c)
#define BS_Unk36(a, b) BSOP_Unk36, (a), (b)
#define BS_FreeAllParticles() BSOP_FreeAllParticles
#define BS_ReleaseWindupEmitter() BSOP_ReleaseWindupEmitter
#define BS_ReleaseKind2Emitters() BSOP_ReleaseKind2Emitters
#define BS_Unk3A() BSOP_Unk3A
#define BS_SetBehaviorFlags(a) BSOP_SetBehaviorFlags, (a)
#define BS_ClearBehaviorFlags(a) BSOP_ClearBehaviorFlags, (a)
#define BS_BlendEffectPalette(a, b, c) BSOP_BlendEffectPalette, (a), (b), (c)
#define BS_SetOamPalette(a) BSOP_SetOamPalette, (a)
#define BS_Unk3F() BSOP_Unk3F
#define BS_Unk40() BSOP_Unk40
#define BS_StartOrbitMotion(a, b) BSOP_StartOrbitMotion, (a), (b)
#define BS_StartOrbitMotionRandom(a) BSOP_StartOrbitMotionRandom, (a)
#define BS_SaveOrbit() BSOP_SaveOrbit
#define BS_RestoreOrbit() BSOP_RestoreOrbit
#define BS_StartCasterOrbitMotion(a, b) BSOP_StartCasterOrbitMotion, (a), (b)
#define BS_SetAffineScale1(a, b) BSOP_SetAffineScale1, (((a) >> 8) & 0xFF), ((a) & 0xFF), (((b) >> 8) & 0xFF), ((b) & 0xFF)
#define BS_SetAffineScale3(a, b) BSOP_SetAffineScale3, (((a) >> 8) & 0xFF), ((a) & 0xFF), (((b) >> 8) & 0xFF), ((b) & 0xFF)
#define BS_StartAffineWobble(a, b, c, d, e, f) BSOP_StartAffineWobble, (((a) >> 8) & 0xFF), ((a) & 0xFF), (((b) >> 8) & 0xFF), ((b) & 0xFF), (c), (d), (e), (f)
#define BS_StopAffineWobble() BSOP_StopAffineWobble
#define BS_SetAffineScaleTween(a, b, c, d, e, f, g, h, i) BSOP_SetAffineScaleTween, ((a) & 0xFF), (((b) >> 8) & 0xFF), ((b) & 0xFF), ((c) & 0xFF), (((d) >> 8) & 0xFF), ((d) & 0xFF), ((e) & 0xFF), (((f) >> 8) & 0xFF), ((f) & 0xFF), ((g) & 0xFF), (((h) >> 8) & 0xFF), ((h) & 0xFF), (i)
#define BS_SetAffineRotation1(a) BSOP_SetAffineRotation1, (a)
#define BS_SetAffineRotation3(a) BSOP_SetAffineRotation3, (a)
#define BS_SetAffineScaleRotation1(a, b, c) BSOP_SetAffineScaleRotation1, (a), (((b) >> 8) & 0xFF), ((b) & 0xFF), (((c) >> 8) & 0xFF), ((c) & 0xFF)
#define BS_SetAffineScaleRotation3(a, b, c) BSOP_SetAffineScaleRotation3, (a), (((b) >> 8) & 0xFF), ((b) & 0xFF), (((c) >> 8) & 0xFF), ((c) & 0xFF)
#define BS_ReleaseAffineSlot() BSOP_ReleaseAffineSlot
#define BS_ClearAnimFlag() BSOP_ClearAnimFlag
#define BS_SetAnimFlag() BSOP_SetAnimFlag
#define BS_HideActor() BSOP_HideActor
#define BS_ShowActor() BSOP_ShowActor
#define BS_SetOamPriority(a) BSOP_SetOamPriority, (a)
#define BS_SetTargetOamPriority(a) BSOP_SetTargetOamPriority, (a)
#define BS_SetEnemiesOamPriority(a) BSOP_SetEnemiesOamPriority, (a)
#define BS_SetAlliesOamPriority(a) BSOP_SetAlliesOamPriority, (a)
#define BS_IncrementActionVariant() BSOP_IncrementActionVariant
#define BS_SnapToRandomAroundSlot(a, b, c) BSOP_SnapToRandomAroundSlot, (a), (b), (c)
#define BS_SnapToRandomAroundSpawn(a, b, c) BSOP_SnapToRandomAroundSpawn, (a), (b), (c)
#define BS_JitterPosition(a, b) BSOP_JitterPosition, (a), (b)
#define BS_EnableSemiTransparency() BSOP_EnableSemiTransparency
#define BS_DisableBlendMode() BSOP_DisableBlendMode
#define BS_StartAlphaFade(a) BSOP_StartAlphaFade, (a)
#define BS_SetAlphaBlend(a, b) BSOP_SetAlphaBlend, (a), (b)
#define BS_Label(a) BSOP_Label, (a)
#define BS_Goto(a) BSOP_Goto, (a)
#define BS_Goto_2(a) BSOP_Goto_2, (a)
#define BS_GotoLocalIndexedLabel(a, b, c, d, e, f, g, h) BSOP_GotoLocalIndexedLabel, (a), (b), (c), (d), (e), (f), (g), (h)
#define BS_FreeTileAllocation() BSOP_FreeTileAllocation
#define BS_StartDelayedChain(a, b, c) BSOP_StartDelayedChain, (a), (b), (c)
#define BS_Unk66() BSOP_Unk66
#define BS_SetLocalRandomRange(a, b, c) BSOP_SetLocalRandomRange, (a), (b), (c)
#define BS_SetDepthBiasZero() BSOP_SetDepthBiasZero
#define BS_SetDepthBiasMax() BSOP_SetDepthBiasMax
#define BS_SetDepthBias(a) BSOP_SetDepthBias, (a)
#define BS_SetDepthBiasInverseLocalA() BSOP_SetDepthBiasInverseLocalA
#define BS_SetDepthBiasLocalA() BSOP_SetDepthBiasLocalA
#define BS_Unk6D() BSOP_Unk6D
#define BS_Unk6E() BSOP_Unk6E
#define BS_ScrollBgUp(a) BSOP_ScrollBgUp, (a)
#define BS_ScrollBgDown(a) BSOP_ScrollBgDown, (a)
#define BS_SetTargetVelocityScaled(a, b) BSOP_SetTargetVelocityScaled, ((a) & 0xFF), ((b) & 0xFF)
#define BS_SetTargetVelocity(a, b) BSOP_SetTargetVelocity, ((a) & 0xFF), ((b) & 0xFF)
#define BS_SetCasterVelocityProduct(a, b, c, d) BSOP_SetCasterVelocityProduct, ((a) & 0xFF), ((b) & 0xFF), ((c) & 0xFF), ((d) & 0xFF)
#define BS_NudgeCaster(a, b) BSOP_NudgeCaster, (a), (b)
#define BS_NudgeTarget(a, b) BSOP_NudgeTarget, (a), (b)
#define BS_SetCasterPosition(a, b) BSOP_SetCasterPosition, (a), (b)
#define BS_SetTargetPosition(a, b) BSOP_SetTargetPosition, (a), (b)
#define BS_SnapTargetToSlot() BSOP_SnapTargetToSlot
#define BS_SnapCasterToSpawn() BSOP_SnapCasterToSpawn
#define BS_MoveFighterTo(a, b, c) BSOP_MoveFighterTo, (a), (b), (c)
#define BS_MoveFighterToSlotPosition(a) BSOP_MoveFighterToSlotPosition, (a)
#define BS_MoveCasterTo(a, b, c, d, e) BSOP_MoveCasterTo, ((a) & 0xFF), ((b) & 0xFF), (c), (d), (e)
#define BS_WaitForCasterField86() BSOP_WaitForCasterField86
#define BS_SetCasterAnim(a, b) BSOP_SetCasterAnim, (a), (b)
#define BS_LoadBgEffect(a, b, c) BSOP_LoadBgEffect, (a), (b), (c)
#define BS_QueueScanlineEffect(a) BSOP_QueueScanlineEffect, (a)
#define BS_SetBgEffectId(a) BSOP_SetBgEffectId, (a)
#define BS_TeleportTo(a, b) BSOP_TeleportTo, (a), (b)
#define BS_KillTarget() BSOP_KillTarget
#define BS_RampBlendUp() BSOP_RampBlendUp
#define BS_RampBlendDown() BSOP_RampBlendDown
#define BS_GotoIfLocalAGreater(a, b) BSOP_GotoIfLocalAGreater, (a), (b)
#define BS_GotoIfLocalALess(a, b) BSOP_GotoIfLocalALess, (a), (b)
#define BS_GotoIfLocalAInRange(a, b, c) BSOP_GotoIfLocalAInRange, (a), (b), (c)
#define BS_GotoIfLocalAOutOfRange(a, b, c) BSOP_GotoIfLocalAOutOfRange, (a), (b), (c)
#define BS_SetBgPaletteColors(a, b, c, d) BSOP_SetBgPaletteColors, (a), (b), (c), (d)
#define BS_SetBgPaletteColorsAdjust(a, b, c, d, e) BSOP_SetBgPaletteColorsAdjust, (a), (b), (c), (d), (e)
#define BS_SetBgPriority(a, b) BSOP_SetBgPriority, (a), (b)
#define BS_SetEffectTimers(a, b, c, d, e, f, g, h, i, j) BSOP_SetEffectTimers, (a), (b), (c), (d), (e), (f), (g), (h), (i), (j)
#define BS_StartFadeCounter(a, b) BSOP_StartFadeCounter, (a), (b)
#define BS_SetWindowLayers(a, b, c, d, e, f, g, h, i, j, k) BSOP_SetWindowLayers, (a), (b), (c), (d), (e), (f), (g), (h), (i), (j), (k)
#define BS_SetWindowRect(a, b, c, d, e) BSOP_SetWindowRect, (a), (b), (c), (d), (e)
#define BS_SetBehaviorFlag10() BSOP_SetBehaviorFlag10
#define BS_HideWindow(a) BSOP_HideWindow, (a)
#define BS_ResetBgState(a) BSOP_ResetBgState, (a)
#define BS_Unk94() BSOP_Unk94
#define BS_Unk95() BSOP_Unk95
#define BS_FlipTargetFacing() BSOP_FlipTargetFacing
#define BS_StatusEffect(a, b, c) BSOP_StatusEffect, (a), (b), (c)
#define BS_Unk98() BSOP_Unk98
#define BS_SetLocalAToPartySize() BSOP_SetLocalAToPartySize
#define BS_Unk9A(a, b) BSOP_Unk9A, (a), (b)
#define BS_SetDispcntBit15() BSOP_SetDispcntBit15
#define BS_ClearDispcntBit15() BSOP_ClearDispcntBit15
#define BS_SelectFirstAlly() BSOP_SelectFirstAlly
#define BS_SelectNextAlly() BSOP_SelectNextAlly
#define BS_SelectFirstLiveEnemy() BSOP_SelectFirstLiveEnemy
#define BS_SelectNextLiveEnemy() BSOP_SelectNextLiveEnemy
#define BS_UnkA1() BSOP_UnkA1
#define BS_SetLocalRandom(a, b) BSOP_SetLocalRandom, (a), (b)
#define BS_ReloadBattleBackgroundTiles() BSOP_ReloadBattleBackgroundTiles
#define BS_PlaySoundOrDefault(a) BSOP_PlaySoundOrDefault, (a)
#define BS_DarkenScreenPalette() BSOP_DarkenScreenPalette
#define BS_RestoreScreenPalette() BSOP_RestoreScreenPalette
#define BS_PlaySoundEffect(a) BSOP_PlaySoundEffect, (a)

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
