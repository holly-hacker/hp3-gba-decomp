#pragma once

#include "actor.h"

// Effect-script tick helpers and scanline callbacks.

// Scanline callbacks of the effect tables in combat_fx.h.
extern void EffectScanlineRestoreBgs(u32 *pPayload0, u32 *pPayload1);
extern void EffectScanlineAdvanceScroll(u32 *pPayload0, u32 *pPayload1);
extern void EffectScanlineSetBandScroll(u32 *pPayload0, u32 *pPayload1);
extern void EffectScanlineCopyTilemap(u32 *pPayload0, u32 *pPayload1);
extern void EffectScanlineEnableBlend(u32 *pPayload0, u32 *pPayload1);
extern void EffectScanlineStopHBlankDma(u32 *pPayload0, u32 *pPayload1);

// Copies a BG load queued by QueueBattleBgLoad to VRAM; run by the battle VBlank callback.
extern void FlushQueuedBattleDma(void);

extern void WaitFramesTick(Actor *actor);
extern void WaitForCounterTick(Actor *actor);
extern void WaitForFieldClearTick(Actor *actor);
extern void WaitForCasterTimedMoveTick(Actor *actor);
extern IntPoint ComputeEffectSpawnPosition(void);
extern void JumpToScriptLabel(Actor *actor, u8 label);  // jumps the script to the Label opcode with this id
extern ParticleEmitter *CreateScriptEmitter12(Actor *actor, u8 mode, u8 lifetimeBase, u8 spread,
                                              u8 direction, u8 spawnsPerPeriod, u8 flag18,
                                              s32 assetIndex, u8 poolIndex, u8 entryIndex, u8 speed,
                                              u8 duration, u8 spawnPeriod);
extern ParticleEmitter *CreateScriptEmitter8(Actor *actor, u8 unused, u8 spawnPeriod, u8 lifetimeBase,
                                             u8 spread, u8 spawnsPerPeriod, s32 assetIndex, u8 poolIndex,
                                             u8 entryIndex);
