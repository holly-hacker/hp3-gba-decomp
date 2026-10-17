#pragma once

#include "graphics/display.h"
#include "types.h"
#include "actor.h"
#include "particles.h"
#include "battle/battle.h"
#include "graphics/scanline_effects.h"

// Battle-effect script interpreter; see docs/formats/battle_scripts.md.


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


// Scanline callbacks of the effect tables.
extern void EffectScanlineRestoreBgs(u32 *pPayload0, u32 *pPayload1);
extern void EffectScanlineAdvanceScroll(u32 *pPayload0, u32 *pPayload1);
extern void EffectScanlineSetBandScroll(u32 *pPayload0, u32 *pPayload1);
extern void EffectScanlineCopyTilemap(u32 *pPayload0, u32 *pPayload1);
extern void EffectScanlineEnableBlend(u32 *pPayload0, u32 *pPayload1);
extern void EffectScanlineStopHBlankDma(u32 *pPayload0, u32 *pPayload1);

extern void WaitFramesTick(Actor *actor);
extern void WaitForCounterTick(Actor *actor);
extern void WaitForFieldClearTick(Actor *actor);
extern void WaitForCasterField86Tick_candidate(Actor *actor);
extern IntPoint ComputeEffectSpawnPosition(void);
extern void JumpToScriptLabel(Actor *actor, u8 label);  // jumps the script to the Label opcode with this id
extern ParticleEmitter *CreateScriptEmitter12(Actor *actor, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h, u32 i, u32 j, u32 k, u32 l);
extern ParticleEmitter *CreateScriptEmitter8(Actor *actor, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h);
