#pragma once

#include "actor.h"

// Effect-script tick helpers and scanline callbacks; see docs/formats/battle_scripts.md.

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
extern void WaitForCasterField86Tick_candidate(Actor *actor);
extern IntPoint ComputeEffectSpawnPosition(void);
extern void JumpToScriptLabel(Actor *actor, u8 label);  // jumps the script to the Label opcode with this id
extern ParticleEmitter *CreateScriptEmitter12(Actor *actor, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h, u32 i, u32 j, u32 k, u32 l);
extern ParticleEmitter *CreateScriptEmitter8(Actor *actor, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h);
