#pragma once

#include "combat.h"
#include "video.h"

// Battle effect scripts and emitters.

// Battle-effect staging area at 0x03002750. TriggerBattleEffect fills the
// fields below before spawning the effect actor; the low bytes belong to
// other battle state.
typedef struct EffectStaging {
    ParticleEmitter *pEmitter_candidate;  // 0x00, emitter spawned by the last emitter opcode
    u8 pad_04[0x02];
    u16 awSavedOrbit[6];    // 0x06, orbit parameters saved by script opcode 0x43
    u16 awBandScroll[4];    // 0x12, BG1 X scroll per band of the scrolling scanline effect
    u16 wBlendFirstTargets;   // 0x1A, alpha-blend targets EffectScanlineEnableBlend applies
    u16 wBlendSecondTargets;
    u16 wContextValue;
    u8 bScriptParam;
    u8 bSlotParam;
    u8 bTargetIndex;
    u8 bCasterIndex;
    u8 bBgEffectId_candidate;
    u8 bBg0Priority;  // last priorities BSOP_SetBgPriority gave BG0 and BG1
    u8 bBg1Priority;
    u8 bIdStaged_candidate;
    u32 dwBgPrioritiesPending;  // set by EffectScanlineEnableBlend; HandleBattleVBlank then
                                // restores the two priorities above instead of BG1 priority 1
} EffectStaging;

// A BG graphic load queued by QueueBattleBgLoad: FlushQueuedBattleDma copies
// the tiles and tilemap to VRAM during vblank and clears dwPending.
typedef struct QueuedBgLoad {
    BgTileLoadInfo tiles;   // 0x00, tiles.pTilemapBuffer is the tilemap to copy
    const u16 *pTilemap;    // 0x10, the blob's tilemap
    u16 *pScreenBase;       // 0x14, destination screen block
    u32 dwPending;          // 0x18
} QueuedBgLoad;

// One 0x10-byte background record read by script opcodes 0x7F, 0x8A and 0x8B.
typedef struct EffectBgRecord {
    void *pGfx;         // 0x00
    u16 wUnk04;         // 0x04
    u16 wUnk06;         // 0x06
    void *pControls;    // 0x08
    u16 wUnk0C;         // 0x0C
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
    BSOP_SpawnEffectNoPalette = 0x0E,
    BSOP_SpawnEffect = 0x0F,
    BSOP_SpawnEffectAtSelfNoPalette = 0x10,
    BSOP_SpawnEffectAtSelf = 0x11,
    BSOP_SpawnEffectOffsetNoPalette = 0x12,
    BSOP_SpawnEffectOffset = 0x13,
    BSOP_Nop14 = 0x14,
    BSOP_Nop15 = 0x15,
    BSOP_SpawnEffectSharedTiles = 0x16,
    BSOP_ToggleActorFlipX = 0x17,
    BSOP_ToggleActorFlipY = 0x18,
    BSOP_MoveBy = 0x19,
    BSOP_MoveBy_2 = 0x1A,
    BSOP_SnapToCaster = 0x1B,
    BSOP_TeleportToSlotPosition = 0x1C,
    BSOP_SetVelocity = 0x1D,
    BSOP_SetVelocity16 = 0x1E,
    BSOP_SetBgScrollStepXY = 0x1F,
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
    BSOP_LoadParticleGfx = 0x35,
    BSOP_ReleaseParticleGfx = 0x36,
    BSOP_FreeAllParticles = 0x37,
    BSOP_ReleaseWindupEmitter = 0x38,
    BSOP_ReleaseKind2Emitters = 0x39,
    BSOP_Nop3A = 0x3A,
    BSOP_SetBehaviorFlags = 0x3B,
    BSOP_ClearBehaviorFlags = 0x3C,
    BSOP_BlendEffectPalette = 0x3D,
    BSOP_SetOamPalette = 0x3E,
    BSOP_Nop3F = 0x3F,
    BSOP_Nop40 = 0x40,
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
    BSOP_StartAlphaFadeOut = 0x5E,
    BSOP_SetAlphaBlend = 0x5F,
    BSOP_Label = 0x60,
    BSOP_Goto = 0x61,
    BSOP_Goto_2 = 0x62,
    BSOP_GotoLocalIndexedLabel = 0x63,
    BSOP_FreeTileAllocation = 0x64,
    BSOP_StartShrinkOrbit = 0x65,
    BSOP_Nop66 = 0x66,
    BSOP_SetLocalRandomRange = 0x67,
    BSOP_SetDepthBiasZero = 0x68,
    BSOP_SetDepthBiasMax = 0x69,
    BSOP_SetDepthBias = 0x6A,
    BSOP_SetDepthBiasInverseLocalA = 0x6B,
    BSOP_SetDepthBiasLocalA = 0x6C,
    BSOP_Nop6D = 0x6D,
    BSOP_Nop6E = 0x6E,
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
    BSOP_WaitForCasterTimedMove = 0x7D,
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
    BSOP_StartAlphaFadeIn = 0x8E,
    BSOP_SetWindowLayers = 0x8F,
    BSOP_SetWindowRect = 0x90,
    BSOP_StartGrowWindow = 0x91,
    BSOP_HideWindow = 0x92,
    BSOP_ResetBgState = 0x93,
    BSOP_EnableActorDepthSort = 0x94,
    BSOP_DisableActorDepthSort = 0x95,
    BSOP_FlipTargetFacing = 0x96,
    BSOP_StatusEffect = 0x97,
    BSOP_RestoreBattleScanlineEffects = 0x98,
    BSOP_SetLocalAToPartySize = 0x99,
    BSOP_SetBgScrollStepX = 0x9A,
    BSOP_SetDispcntBit15 = 0x9B,
    BSOP_ClearDispcntBit15 = 0x9C,
    BSOP_SelectFirstAlly = 0x9D,
    BSOP_SelectNextAlly = 0x9E,
    BSOP_SelectFirstLiveEnemy = 0x9F,
    BSOP_SelectNextLiveEnemy = 0xA0,
    BSOP_NopA1 = 0xA1,
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

// Ends the script and destroys the actor.
#define BS_End() BSOP_End
// (anim, frame): plays effect animation `anim` from frame offset `frame`.
#define BS_SetActorAnim(a, b) BSOP_SetActorAnim, (a), (b)
// (anim, frame): SetActorAnim, then attaches that animation's palette.
#define BS_SetActorAnimAndPalette(a, b) BSOP_SetActorAnimAndPalette, (a), (b)
// (anim, frame): SetActorAnim from the second effect animation table.
#define BS_SetActorAnimFromTable2(a, b) BSOP_SetActorAnimFromTable2, (a), (b)
// (anim, frame): SetActorAnimFromTable2, then attaches that animation's palette.
#define BS_SetActorAnimFromTable2AndPalette(a, b) BSOP_SetActorAnimFromTable2AndPalette, (a), (b)
// (palette): attaches effect palette `palette`.
#define BS_SetEffectPalette(a) BSOP_SetEffectPalette, (a)
// (sound): plays sound `sound`.
#define BS_PlaySound(a) BSOP_PlaySound, (a)
// Calls StopSoundEffectChannels.
#define BS_UnmuteMusic() BSOP_UnmuteMusic
// (frames): waits `frames` ticks, then resumes.
#define BS_WaitFrames(a) BSOP_WaitFrames, (a)
// Waits until anim.unk_DC.bEnemyAttackPhase_candidate reaches its current value + 1, or
// ActorFlagActionAnimDone is set.
#define BS_WaitForCounter() BSOP_WaitForCounter
// Waits at least one tick, until the actor's wMoveDuration is 0.
#define BS_WaitForFieldClear() BSOP_WaitForFieldClear
// (x, y, frames): moves to (x, y) over `frames` ticks.
#define BS_MoveToAbsolute(a, b, c) BSOP_MoveToAbsolute, (a), (b), (c)
// (dx, dy, frames, fromSpawn, anchor): moves over `frames` ticks to the battle slot position of the
// script parameter (ComputeEffectSpawnPosition if `fromSpawn`) plus signed (dx, dy) and, if `anchor`
// is nonzero, the target's anchor `anchor - 1`.
#define BS_MoveTo(a, b, c, d, e) BSOP_MoveTo, ((a) & 0xFF), ((b) & 0xFF), (c), (d), (e)
// Stops movement and zeroes the velocity.
#define BS_StopMove() BSOP_StopMove
// (effect): spawns child effect `effect` without its palette. Children inherit both locals plus 1.
#define BS_SpawnEffectNoPalette(a) BSOP_SpawnEffectNoPalette, (a)
// (effect): spawns child effect `effect`.
#define BS_SpawnEffect(a) BSOP_SpawnEffect, (a)
// (effect): SpawnEffectNoPalette at this actor's position.
#define BS_SpawnEffectAtSelfNoPalette(a) BSOP_SpawnEffectAtSelfNoPalette, (a)
// (effect): SpawnEffect at this actor's position.
#define BS_SpawnEffectAtSelf(a) BSOP_SpawnEffectAtSelf, (a)
// (effect, dx, xScale, dy, yScale): SpawnEffectNoPalette at this actor's position plus
// (dx * xScale, dy * yScale) pixels.
#define BS_SpawnEffectOffsetNoPalette(a, b, c, d, e) BSOP_SpawnEffectOffsetNoPalette, (a), ((b) & 0xFF), (c), ((d) & 0xFF), (e)
// (effect, dx, xScale, dy, yScale): SpawnEffect at this actor's position plus
// (dx * xScale, dy * yScale) pixels.
#define BS_SpawnEffectOffset(a, b, c, d, e) BSOP_SpawnEffectOffset, (a), ((b) & 0xFF), (c), ((d) & 0xFF), (e)
// No-op.
#define BS_Nop14(a) BSOP_Nop14, (a)
// No-op.
#define BS_Nop15(a, b, c, d, e) BSOP_Nop15, (a), (b), (c), (d), (e)
// (effect): SpawnEffect with the child sharing OBJ tiles.
#define BS_SpawnEffectSharedTiles(a) BSOP_SpawnEffectSharedTiles, (a)
// Toggles the horizontal flip.
#define BS_ToggleActorFlipX() BSOP_ToggleActorFlipX
// Toggles the vertical flip.
#define BS_ToggleActorFlipY() BSOP_ToggleActorFlipY
// (dx, dy): moves by signed (dx, dy) pixels.
#define BS_MoveBy(a, b) BSOP_MoveBy, ((a) & 0xFF), ((b) & 0xFF)
// (dx, dy): same as MoveBy.
#define BS_MoveBy_2(a, b) BSOP_MoveBy_2, ((a) & 0xFF), ((b) & 0xFF)
// (anchor): snaps to the caster's position, plus its anchor `anchor - 1` if nonzero.
#define BS_SnapToCaster(a) BSOP_SnapToCaster, (a)
// (anchor): snaps to the battle slot position of the script parameter, plus the target's anchor
// `anchor - 1` if nonzero.
#define BS_TeleportToSlotPosition(a) BSOP_TeleportToSlotPosition, (a)
// (vx, vy): sets the velocity to signed (vx, vy) pixels.
#define BS_SetVelocity(a, b) BSOP_SetVelocity, ((a) & 0xFF), ((b) & 0xFF)
// (xSign, vx, ySign, vy): sets the velocity to 8.8 (vx, vy) pixels; a sign of 0xFF negates.
#define BS_SetVelocity16(a, b, c, d) BSOP_SetVelocity16, (a), (((b) >> 8) & 0xFF), ((b) & 0xFF), (c), (((d) >> 8) & 0xFF), ((d) & 0xFF)
// (bg, x, y): SetBgScrollStep(bg, (s8)bg, (s8)x); `y` is ignored.
#define BS_SetBgScrollStepXY(a, b, c) BSOP_SetBgScrollStepXY, (a), (b), (c)
// (index, value): sets local `index` (0 = A, 1 = B).
#define BS_SetLocal(a, b) BSOP_SetLocal, (a), (b)
// (index): increments local `index`.
#define BS_IncrementLocal(a) BSOP_IncrementLocal, (a)
// (count): skips `count` script bytes.
#define BS_SkipBytes(a) BSOP_SkipBytes, (a)
// (label): jumps when the context value is at most 2 or is 0x3E9.
#define BS_GotoIfContextLow(a) BSOP_GotoIfContextLow, (a)
// (value, label): jumps when local A == `value`.
#define BS_GotoIfLocalAEqual(a, b) BSOP_GotoIfLocalAEqual, (a), (b)
// (value, label): jumps when the script parameter == `value`.
#define BS_GotoIfScriptParamEqual(a, b) BSOP_GotoIfScriptParamEqual, (a), (b)
// (value, label): jumps when local A != `value`.
#define BS_GotoIfLocalANotEqual(a, b) BSOP_GotoIfLocalANotEqual, (a), (b)
// (label): jumps when the target's roster index is in g_abEffectRosterIdPair_candidate.
#define BS_GotoIfFighterRosterMatches(a) BSOP_GotoIfFighterRosterMatches, (a)
// (value, label): same as GotoIfLocalAEqual.
#define BS_GotoIfLocalAEqual_2(a, b) BSOP_GotoIfLocalAEqual_2, (a), (b)
// (value, label): same as GotoIfScriptParamEqual.
#define BS_GotoIfScriptParamEqual_2(a, b) BSOP_GotoIfScriptParamEqual_2, (a), (b)
// (value, label): same as GotoIfLocalANotEqual.
#define BS_GotoIfLocalANotEqual_2(a, b) BSOP_GotoIfLocalANotEqual_2, (a), (b)
// (label): same as GotoIfFighterRosterMatches.
#define BS_GotoIfFighterRosterMatches_2(a) BSOP_GotoIfFighterRosterMatches_2, (a)
// (value, label): jumps when local B == `value`.
#define BS_GotoIfLocalBEqual(a, b) BSOP_GotoIfLocalBEqual, (a), (b)
// (value, label): jumps when local B != `value`.
#define BS_GotoIfLocalBNotEqual(a, b) BSOP_GotoIfLocalBNotEqual, (a), (b)
// (value, label): same as GotoIfLocalBEqual.
#define BS_GotoIfLocalBEqual_2(a, b) BSOP_GotoIfLocalBEqual_2, (a), (b)
// (value, label): same as GotoIfLocalBNotEqual.
#define BS_GotoIfLocalBNotEqual_2(a, b) BSOP_GotoIfLocalBNotEqual_2, (a), (b)
// Increments the caster's attack-outcome counter and copies it to FightState.
#define BS_AdvanceAttackOutcome() BSOP_AdvanceAttackOutcome
// Creates an emitter with CreateScriptEmitter12, operands in its parameter order.
#define BS_CreateEmitter12(a, b, c, d, e, f, g, h, i, j, k, l) BSOP_CreateEmitter12, (a), (b), (c), (d), (e), (f), (g), (h), (i), (j), (k), (l)
// Creates an emitter with CreateScriptEmitter8, operands in its parameter order.
#define BS_CreateEmitter8(a, b, c, d, e, f, g, h) BSOP_CreateEmitter8, (a), (b), (c), (d), (e), (f), (g), (h)
// Creates an emitter on this actor with CreateBattleEffectEmitter, operands in its parameter order.
#define BS_CreateEmitterOnSelf(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) BSOP_CreateEmitterOnSelf, (a), (b), (c), (d), (e), (f), (g), (h), (i), (j), (k), (l), (m), (n), (o), (p)
// Creates an emitter on the target with CreateBattleEffectEmitter, operands in its parameter order.
#define BS_CreateEmitterOnTarget(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) BSOP_CreateEmitterOnTarget, (a), (b), (c), (d), (e), (f), (g), (h), (i), (j), (k), (l), (m), (n), (o), (p)
// (pool, entry, asset): LoadParticleGfx(pool, entry, &g_aEffectActorAssets[asset]).
#define BS_LoadParticleGfx(a, b, c) BSOP_LoadParticleGfx, (a), (b), (c)
// (pool, entry): frees every particle, then ReleaseParticleGfx(pool, entry).
#define BS_ReleaseParticleGfx(a, b) BSOP_ReleaseParticleGfx, (a), (b)
// Frees every particle.
#define BS_FreeAllParticles() BSOP_FreeAllParticles
// Releases this actor's windup emitter.
#define BS_ReleaseWindupEmitter() BSOP_ReleaseWindupEmitter
// Releases every emitter whose bParalysisEffectFlag_candidate is 2, as the emitter opcodes set it.
#define BS_ReleaseKind2Emitters() BSOP_ReleaseKind2Emitters
// No-op.
#define BS_Nop3A() BSOP_Nop3A
// (flags): sets EffectBehavior* flags.
#define BS_SetBehaviorFlags(a) BSOP_SetBehaviorFlags, (a)
// (flags): clears EffectBehavior* flags.
#define BS_ClearBehaviorFlags(a) BSOP_ClearBehaviorFlags, (a)
// (bank, palette, banks): loads `banks` banks of effect palette `palette` into OBJ palette bank `bank`.
#define BS_BlendEffectPalette(a, b, c) BSOP_BlendEffectPalette, (a), (b), (c)
// (bank): sets the OBJ palette bank.
#define BS_SetOamPalette(a) BSOP_SetOamPalette, (a)
// No-op.
#define BS_Nop3F() BSOP_Nop3F
// No-op.
#define BS_Nop40() BSOP_Nop40
// (params, step): starts orbit row `params`, its X angle advanced by local A * `step`.
#define BS_StartOrbitMotion(a, b) BSOP_StartOrbitMotion, (a), (b)
// (params): starts orbit row `params` at a random angle.
#define BS_StartOrbitMotionRandom(a) BSOP_StartOrbitMotionRandom, (a)
// Saves the orbit state.
#define BS_SaveOrbit() BSOP_SaveOrbit
// Restores the saved orbit state.
#define BS_RestoreOrbit() BSOP_RestoreOrbit
// (params, step): StartOrbitMotion on the caster.
#define BS_StartCasterOrbitMotion(a, b) BSOP_StartCasterOrbitMotion, (a), (b)
// (sx, sy): sets an 8.8 affine scale, affine mode 1.
#define BS_SetAffineScale1(a, b) BSOP_SetAffineScale1, (((a) >> 8) & 0xFF), ((a) & 0xFF), (((b) >> 8) & 0xFF), ((b) & 0xFF)
// (sx, sy): sets an 8.8 affine scale, affine mode 3.
#define BS_SetAffineScale3(a, b) BSOP_SetAffineScale3, (((a) >> 8) & 0xFF), ((a) & 0xFF), (((b) >> 8) & 0xFF), ((b) & 0xFF)
// (sx, sy, angle, p0, p1, p2): sets scale and rotation `angle` (mode 3) and starts the wobble.
#define BS_StartAffineWobble(a, b, c, d, e, f) BSOP_StartAffineWobble, (((a) >> 8) & 0xFF), ((a) & 0xFF), (((b) >> 8) & 0xFF), ((b) & 0xFF), (c), (d), (e), (f)
// Stops the wobble.
#define BS_StopAffineWobble() BSOP_StopAffineWobble
// (xSign, sx, ySign, sy, toXSign, toSx, toYSign, toSy, frames): sets an 8.8 scale, each
// multiplied by its signed factor, and tweens to the second scale over `frames` ticks.
#define BS_SetAffineScaleTween(a, b, c, d, e, f, g, h, i) BSOP_SetAffineScaleTween, ((a) & 0xFF), (((b) >> 8) & 0xFF), ((b) & 0xFF), ((c) & 0xFF), (((d) >> 8) & 0xFF), ((d) & 0xFF), ((e) & 0xFF), (((f) >> 8) & 0xFF), ((f) & 0xFF), ((g) & 0xFF), (((h) >> 8) & 0xFF), ((h) & 0xFF), (i)
// (angle): sets rotation `angle` at scale 1, affine mode 1.
#define BS_SetAffineRotation1(a) BSOP_SetAffineRotation1, (a)
// (angle): sets rotation `angle` at scale 1, affine mode 3.
#define BS_SetAffineRotation3(a) BSOP_SetAffineRotation3, (a)
// (angle, sx, sy): sets rotation `angle` and an 8.8 scale, affine mode 1.
#define BS_SetAffineScaleRotation1(a, b, c) BSOP_SetAffineScaleRotation1, (a), (((b) >> 8) & 0xFF), ((b) & 0xFF), (((c) >> 8) & 0xFF), ((c) & 0xFF)
// (angle, sx, sy): sets rotation `angle` and an 8.8 scale, affine mode 3.
#define BS_SetAffineScaleRotation3(a, b, c) BSOP_SetAffineScaleRotation3, (a), (((b) >> 8) & 0xFF), ((b) & 0xFF), (((c) >> 8) & 0xFF), ((c) & 0xFF)
// Releases the affine slot, if any.
#define BS_ReleaseAffineSlot() BSOP_ReleaseAffineSlot
// Clears ActorFlagHasAnimation.
#define BS_ClearAnimFlag() BSOP_ClearAnimFlag
// Sets ActorFlagHasAnimation.
#define BS_SetAnimFlag() BSOP_SetAnimFlag
// Hides the actor.
#define BS_HideActor() BSOP_HideActor
// Shows the actor.
#define BS_ShowActor() BSOP_ShowActor
// (priority): sets this actor's OAM priority.
#define BS_SetOamPriority(a) BSOP_SetOamPriority, (a)
// (priority): sets the target's OAM priority.
#define BS_SetTargetOamPriority(a) BSOP_SetTargetOamPriority, (a)
// (priority): sets every enemy's OAM priority.
#define BS_SetEnemiesOamPriority(a) BSOP_SetEnemiesOamPriority, (a)
// (priority): sets every ally's OAM priority.
#define BS_SetAlliesOamPriority(a) BSOP_SetAlliesOamPriority, (a)
// Increments wActionVariant.
#define BS_IncrementActionVariant() BSOP_IncrementActionVariant
// (rangeX, rangeY, slotY): snaps within +-rangeX of the target slot's x and +-rangeY of slot
// `slotY`'s y.
#define BS_SnapToRandomAroundSlot(a, b, c) BSOP_SnapToRandomAroundSlot, (a), (b), (c)
// (rangeX, rangeY, unused): snaps within (+-rangeX, +-rangeY) of the spawn position.
#define BS_SnapToRandomAroundSpawn(a, b, c) BSOP_SnapToRandomAroundSpawn, (a), (b), (c)
// (rangeX, rangeY): moves by a random offset within (+-rangeX, +-rangeY).
#define BS_JitterPosition(a, b) BSOP_JitterPosition, (a), (b)
// Sets OAM mode 1 (semi-transparent), blend targets 0 / 0x1F and coefficients 16 / 0.
#define BS_EnableSemiTransparency() BSOP_EnableSemiTransparency
// Sets OAM mode 0.
#define BS_DisableBlendMode() BSOP_DisableBlendMode
// (value): sets EffectBehaviorAlphaFadeOut and local B = `value`.
#define BS_StartAlphaFadeOut(a) BSOP_StartAlphaFadeOut, (a)
// (eva, evb): sets the alpha-blend coefficients.
#define BS_SetAlphaBlend(a, b) BSOP_SetAlphaBlend, (a), (b)
// (id): a jump target.
#define BS_Label(a) BSOP_Label, (a)
// (label): jumps to `label`.
#define BS_Goto(a) BSOP_Goto, (a)
// (label): same as Goto.
#define BS_Goto_2(a) BSOP_Goto_2, (a)
// (index, label0, ...): jumps to the label operand selected by local `index`.
#define BS_GotoLocalIndexedLabel(a, b, c, d, e, f, g, h) BSOP_GotoLocalIndexedLabel, (a), (b), (c), (d), (e), (f), (g), (h)
// Frees the actor's OBJ tile allocation now.
#define BS_FreeTileAllocation() BSOP_FreeTileAllocation
// (a, b, c): sets EffectBehaviorShrinkOrbit with bParam6C = a, abParams[0..1] = (b, c), bParam6D = 0.
#define BS_StartShrinkOrbit(a, b, c) BSOP_StartShrinkOrbit, (a), (b), (c)
// No-op.
#define BS_Nop66() BSOP_Nop66
// (index, min, max): sets local `index` to a random value in [min, max).
#define BS_SetLocalRandomRange(a, b, c) BSOP_SetLocalRandomRange, (a), (b), (c)
// Sets the depth-sort bias to 0.
#define BS_SetDepthBiasZero() BSOP_SetDepthBiasZero
// Sets the depth-sort bias to 0xFF.
#define BS_SetDepthBiasMax() BSOP_SetDepthBiasMax
// (bias): sets the depth-sort bias.
#define BS_SetDepthBias(a) BSOP_SetDepthBias, (a)
// Sets the depth-sort bias to 25 - local A.
#define BS_SetDepthBiasInverseLocalA() BSOP_SetDepthBiasInverseLocalA
// Sets the depth-sort bias to local A.
#define BS_SetDepthBiasLocalA() BSOP_SetDepthBiasLocalA
// No-op.
#define BS_Nop6D() BSOP_Nop6D
// No-op.
#define BS_Nop6E() BSOP_Nop6E
// (bg): subtracts 2 pixels from BG `bg`'s x scroll and 3 from the floor heading.
#define BS_ScrollBgUp(a) BSOP_ScrollBgUp, (a)
// (bg): adds 2 pixels to BG `bg`'s x scroll and 3 to the floor heading.
#define BS_ScrollBgDown(a) BSOP_ScrollBgDown, (a)
// (vx, vy): sets the target's velocity to signed (vx, vy) / 16 pixels.
#define BS_SetTargetVelocityScaled(a, b) BSOP_SetTargetVelocityScaled, ((a) & 0xFF), ((b) & 0xFF)
// (vx, vy): sets the target's velocity to signed (vx, vy) pixels.
#define BS_SetTargetVelocity(a, b) BSOP_SetTargetVelocity, ((a) & 0xFF), ((b) & 0xFF)
// (a, b, c, d): sets the caster's velocity to signed (a * b, c * d) / 16 pixels.
#define BS_SetCasterVelocityProduct(a, b, c, d) BSOP_SetCasterVelocityProduct, ((a) & 0xFF), ((b) & 0xFF), ((c) & 0xFF), ((d) & 0xFF)
// (dx, dy): moves the caster by unsigned (dx, dy) pixels.
#define BS_NudgeCaster(a, b) BSOP_NudgeCaster, (a), (b)
// (dx, dy): moves the target by unsigned (dx, dy) pixels.
#define BS_NudgeTarget(a, b) BSOP_NudgeTarget, (a), (b)
// (x, y): snaps the caster to (x, y).
#define BS_SetCasterPosition(a, b) BSOP_SetCasterPosition, (a), (b)
// (x, y): snaps the target to (x, y).
#define BS_SetTargetPosition(a, b) BSOP_SetTargetPosition, (a), (b)
// Snaps the target to the battle slot position of the script parameter.
#define BS_SnapTargetToSlot() BSOP_SnapTargetToSlot
// Snaps the caster to ComputeEffectSpawnPosition.
#define BS_SnapCasterToSpawn() BSOP_SnapCasterToSpawn
// (x, y, frames): moves the target to (x, y) over `frames` ticks.
#define BS_MoveFighterTo(a, b, c) BSOP_MoveFighterTo, (a), (b), (c)
// (frames): moves the target to the battle slot position of the script parameter over `frames` ticks.
#define BS_MoveFighterToSlotPosition(a) BSOP_MoveFighterToSlotPosition, (a)
// (dx, dy, frames, fromSpawn, anchor): MoveTo, moving the caster instead.
#define BS_MoveCasterTo(a, b, c, d, e) BSOP_MoveCasterTo, ((a) & 0xFF), ((b) & 0xFF), (c), (d), (e)
// Waits until the caster's timed move finishes.
#define BS_WaitForCasterTimedMove() BSOP_WaitForCasterTimedMove
// (anim, frame): plays effect animation data `anim` on the caster monster's graphics.
#define BS_SetCasterAnim(a, b) BSOP_SetCasterAnim, (a), (b)
// (bg, record, palBank): queues BG effect record `record` onto BG `bg`, sets its scroll and registers
// its tile animation, if any.
#define BS_LoadBgEffect(a, b, c) BSOP_LoadBgEffect, (a), (b), (c)
// (table): queues effect scanline table `table`.
#define BS_QueueScanlineEffect(a) BSOP_QueueScanlineEffect, (a)
// (record): stores `record` in g_effectStaging.bBgEffectId_candidate.
#define BS_SetBgEffectId(a) BSOP_SetBgEffectId, (a)
// (x, y): snaps to (x, y).
#define BS_TeleportTo(a, b) BSOP_TeleportTo, (a), (b)
// Faints the target and adds its XP and gold rewards.
#define BS_KillTarget() BSOP_KillTarget
// Blocks while BLDY fades from 0 to 16.
#define BS_RampBlendUp() BSOP_RampBlendUp
// Blocks while BLDY fades from 16 to 0.
#define BS_RampBlendDown() BSOP_RampBlendDown
// (value, label): jumps when local A > `value`.
#define BS_GotoIfLocalAGreater(a, b) BSOP_GotoIfLocalAGreater, (a), (b)
// (value, label): jumps when local A < `value`.
#define BS_GotoIfLocalALess(a, b) BSOP_GotoIfLocalALess, (a), (b)
// (low, high, label): jumps when low < local A < high.
#define BS_GotoIfLocalAInRange(a, b, c) BSOP_GotoIfLocalAInRange, (a), (b), (c)
// (low, high, label): jumps when local A <= low or >= high.
#define BS_GotoIfLocalAOutOfRange(a, b, c) BSOP_GotoIfLocalAOutOfRange, (a), (b), (c)
// (record, src, bank, banks): loads `banks` banks of colors from byte 16 * `src` + 2 of BG effect
// record `record`'s graphic into BG palette bank `bank`.
#define BS_SetBgPaletteColors(a, b, c, d) BSOP_SetBgPaletteColors, (a), (b), (c), (d)
// (record, src, bank, banks, colors): SetBgPaletteColors, then cycles `colors` colors from
// color 1 of bank `bank`.
#define BS_SetBgPaletteColorsAdjust(a, b, c, d, e) BSOP_SetBgPaletteColorsAdjust, (a), (b), (c), (d), (e)
// (bg, priority): sets BG `bg`'s priority.
#define BS_SetBgPriority(a, b) BSOP_SetBgPriority, (a), (b)
// (first0, ..., first4, second0, ..., second4): sets the blend first targets to the OR of the
// first five operands and the second targets to the OR of the last five.
#define BS_SetEffectTimers(a, b, c, d, e, f, g, h, i, j) BSOP_SetEffectTimers, (a), (b), (c), (d), (e), (f), (g), (h), (i), (j)
// (a, b): sets EffectBehaviorAlphaFadeIn with local B = 16, bParam6C = bParam6D = a, abParams[4] = b.
#define BS_StartAlphaFadeIn(a, b) BSOP_StartAlphaFadeIn, (a), (b)
// (window, in0, ..., in4, out0, ..., out4): sets window `window`'s inside and outside layer
// masks, each the OR of five operands.
#define BS_SetWindowLayers(a, b, c, d, e, f, g, h, i, j, k) BSOP_SetWindowLayers, (a), (b), (c), (d), (e), (f), (g), (h), (i), (j), (k)
// (window, x0, y0, x1, y1): sets window `window`'s rectangle and stops StartGrowWindow.
#define BS_SetWindowRect(a, b, c, d, e) BSOP_SetWindowRect, (a), (b), (c), (d), (e)
// Starts growing window 0.
#define BS_StartGrowWindow() BSOP_StartGrowWindow
// (window): hides window `window`.
#define BS_HideWindow(a) BSOP_HideWindow, (a)
// (bg): clears BG `bg`'s tilemap and scroll; BG 1 also reloads the battle background tiles.
#define BS_ResetBgState(a) BSOP_ResetBgState, (a)
// Enables depth-sorting of the actor OAM queue.
#define BS_EnableActorDepthSort() BSOP_EnableActorDepthSort
// Disables depth-sorting of the actor OAM queue.
#define BS_DisableActorDepthSort() BSOP_DisableActorDepthSort
// Toggles the target's horizontal flip, unless its actor type is 0x3A or the context value is 0.
#define BS_FlipTargetFacing() BSOP_FlipTargetFacing
// (effect, a, b): applies BSSTATUS_* `effect` with two operands.
#define BS_StatusEffect(a, b, c) BSOP_StatusEffect, (a), (b), (c)
// Restores the battle screen's scanline effects.
#define BS_RestoreBattleScanlineEffects() BSOP_RestoreBattleScanlineEffects
// Sets local A to the party size (3 when game mode args 1 and 3 are 3 and 0xFF).
#define BS_SetLocalAToPartySize() BSOP_SetLocalAToPartySize
// (bg, x): SetBgScrollStep(bg, x, 0).
#define BS_SetBgScrollStepX(a, b) BSOP_SetBgScrollStepX, (a), (b)
// Sets DISPCNT bit 15 (OBJ window) and OAM mode 2.
#define BS_SetDispcntBit15() BSOP_SetDispcntBit15
// Clears DISPCNT bit 15 (OBJ window) and sets OAM mode 0.
#define BS_ClearDispcntBit15() BSOP_ClearDispcntBit15
// Targets the first ally.
#define BS_SelectFirstAlly() BSOP_SelectFirstAlly
// Targets the next ally; sets local B to 1 when there is none.
#define BS_SelectNextAlly() BSOP_SelectNextAlly
// Targets the first live enemy.
#define BS_SelectFirstLiveEnemy() BSOP_SelectFirstLiveEnemy
// Targets the next live enemy; sets local B to 1 when there is none.
#define BS_SelectNextLiveEnemy() BSOP_SelectNextLiveEnemy
// No-op.
#define BS_NopA1() BSOP_NopA1
// (index, max): sets local `index` to a random value in [0, max].
#define BS_SetLocalRandom(a, b) BSOP_SetLocalRandom, (a), (b)
// Reloads the room's battle background tiles on BG 1.
#define BS_ReloadBattleBackgroundTiles() BSOP_ReloadBattleBackgroundTiles
// (sound): plays sound `sound`, or 0x4B when the context value is 0.
#define BS_PlaySoundOrDefault(a) BSOP_PlaySoundOrDefault, (a)
// Calls DarkenScreenPalette.
#define BS_DarkenScreenPalette() BSOP_DarkenScreenPalette
// Calls RestoreScreenPalette.
#define BS_RestoreScreenPalette() BSOP_RestoreScreenPalette
// (jingle): PlayJingle(jingle).
#define BS_PlaySoundEffect(a) BSOP_PlaySoundEffect, (a)

extern Actor *TriggerBattleEffect(u8 effectId, s32 slotParam, s32 selectedActionIndex, s32 activeFighterIndex, s32 targetIdx, u16 damage);
extern Actor *CreateEffectScriptActor(s32 effectId, s32 kind);  // 0x08018BE0
extern void InterpretActorScript(Actor *actor);
extern ParticleEmitter *CreateBattleEffectEmitter(Actor *actor, u8 unused, u8 spawnPeriod,
                                                  u8 lifetimeBase, u8 spread, u8 spawnsPerPeriod,
                                                  u8 velMinX, u8 velMaxX, u8 velMinY, u8 velMaxY,
                                                  u8 param38, u8 poolIndex, u8 entryIndex,
                                                  s32 assetIndex, u8 duration, s32 fixedAnimTicks,
                                                  u8 anchor);
extern void ProcessActorFlagBehaviors(Actor *actor);
// Scanline callback of the effect tables at line 112.
extern void BeginEffectHudScanline(u32 *pPayload0, u32 *pPayload1);
extern ParticleEmitter *CreateBurstToTargetEmitter(Actor *actor, u8 poolIndex, u8 entryIndex);
extern ParticleEmitter *CreateRandomBurstEmitter(Actor *actor, u8 poolIndex, u8 entryIndex);
extern ParticleEmitter *CreateSmallBurstToTargetEmitter(Actor *actor, u8 poolIndex, u8 entryIndex);
extern s32 TryApplyParalysis(BattleFighter *fighter, s32 isEnemyMonster, s32 escapeChance);
extern BgTilemapBuffer *QueueBattleBgLoad(u32 bg, const u8 *pBlob, u16 tileOffset, u16 palBank,
                                          BgTilemapBuffer *pTilemapBuffer);
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
extern QueuedBgLoad g_queuedBattleBgLoad;
