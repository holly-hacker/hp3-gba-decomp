#pragma once

#include "actor.h"
#include "background.h"
#include "char_block.h"
#include "color.h"
#include "hw/io_regs.h"
#include "interrupts.h"
#include "map.h"
#include "modes.h"
#include "oam.h"
#include "particles.h"
#include "screen_transitions.h"
#include "serial.h"
#include "windows.h"

// Screen transition logic that the ROM compiles inline into the transitions.

// One step of a transition that keeps the scene animating: the frame systems' tick (without the
// overworld pause-menu check), then two frames.
static inline void TickTransitionFrame(void)
{
    TickSerialCommIfActive_candidate();
    if (g_GameModeStackContext.dwCurrentGameMode == Overworld)
        TickOverworldBeforeActors_candidate();

    TickActiveActors();
    TickParticleEmitters();
    TickBgLayers();
    TickScreenWindows_candidate();
    TickPaletteAnimations_candidate();
    TickBgTileAnimations();
    HideUnusedOamEntries();
    WaitForVBlankIntr();
    WaitForVBlankIntr();
}

// The body of SetAlphaBlendCoefficients.
static inline void SetAlphaBlendCoefficientsInline(u16 eva, u16 evb)
{
    g_AlphaBlendEvaRamp.wValue = eva << 8;
    g_AlphaBlendEvbRamp.wValue = evb << 8;
    REG_BLDALPHA = (evb << 8) | eva;
}
