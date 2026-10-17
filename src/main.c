#include "area.h"
#include "color.h"
#include "hw/vblank.h"
#include "interrupts.h"
#include "graphics/display.h"
#include "display.h"
#include "hw/io_regs.h"
#include "mem.h"
#include "actor.h"
#include "ram_clear.h"
#include "input.h"
#include "font.h"
#include "text.h"
#include "modes.h"
#include "battle/battle.h"
#include "random.h"
#include "save.h"
#include "game_state.h"
#include "decompress.h"
#include "particles.h"
#include "oam.h"
#include "sound.h"
#include "video.h"
#include "dialog.h"
#include "dialog_box.h"
#include "overworld/room.h"
#include "math.h"
#include "timers.h"
#include "vram.h"
#include "mode7.h"
#include "flipbook.h"
#include "huffman.h"
#include "map.h"
#include "screen_transitions.h"
#include "scroll.h"
#include "move.h"
#include "main.h"

// agbcc special-cases a C function literally named `main`, inserting an
// implicit call to `__gccmain` at entry that the real ROM code doesn't
// have -- hence AgbMain.
void AgbMain(void)
{
    REG_WAITCNT &= 0xFFE3;
    REG_WAITCNT |= 0x4014;
    SetFadeToWhite(0x3F, 0x10);
    ClearSystemMemory();
    InitInterruptSystem();
    InitHeap();
    InstallIwramDivideRoutines();
    InstallIwramFindFreeObjTileRun();
    InstallIwramDecompressCodecs();
    Mt19937AllocState();
    InitTextMacroTable();
    InitDialogTextEngine();
    InitSaveSystem();
    InitGameModeStack();
    InitActorPool();
    InitGammaPalette();
    NoopInit();
    InitOamSystem();
    InitParticlePools();
    InitScreenTransitionState_candidate();
    InitRoomBgState_candidate();
    NoopInit2();
    InitInputSystem();
    ResetAllGameTimers();
    InitDisplayControl();
    InitRoomScriptState();
    NoopInit3();
    InitDialogBox();
    InitRoomTileAnimationTable();
    InitRoomState();
    ClearObjPaletteSlots();
    InstallBgTileCodec();

    g_dwGameModeFlags = 0;
    g_pVBlankState->wOamFrameReady = 0;

    SetVBlankCallback(VBlankCallback);
    kramInstall();
    EnableInterrupts();
    InitScanlineEffects();
    g_dwFrameSyncTarget = 2;

    while (1)
    {
        TickGameModeStack();
        ProcessPlaytimeTick();
        WaitForVBlank();
    }
}

// Frame limiter: blocks until at least g_dwFrameSyncTarget vblanks have
// elapsed since the last frame, then records the current vblank count.
void WaitForVBlank(void)
{
    u32 vblankCount;
    u32 elapsed;
    s32 delta;

    do {
        WaitForVBlankIntr();
        vblankCount = g_pVBlankState->dwVBlankCount;
        delta = vblankCount - g_pVBlankState->dwVBlankConsumed;
        elapsed = g_pVBlankState->dwVBlankConsumed - vblankCount;
        if (delta >= 0)
            elapsed = delta;
    } while (elapsed < g_dwFrameSyncTarget);

    g_pVBlankState->dwVBlankConsumed = vblankCount;
}
