#include "hw/vblank.h"
#include "graphics/display.h"
#include "hw/interrupts.h"
#include "hw/io_regs.h"
#include "hw/mem.h"
#include "input.h"
#include "font.h"
#include "graphics/text.h"
#include "game/game_modes.h"
#include "battle/battle.h"
#include "mt19937.h"
#include "game/save.h"
#include "graphics/graphics.h"
#include "graphics/oam.h"
#include "graphics/palette.h"
#include "graphics/audio.h"
#include "graphics/scanline_effects.h"
#include "menu/main_menu.h"
#include "menu/dialog.h"
#include "overworld/room.h"
#include "math.h"
#include "game/game_timer.h"

extern void InstallIwramFindFreeObjTileRun(void);
extern void InstallIwramDecompressCodecs(void);
extern void InitSaveSystem(void);
extern void NoopInit(void);
extern void NoopInit2(void);
extern void NoopInit3(void);

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
    InitObjectPool();
    InitGammaPalette();
    NoopInit();
    InitOamSystem();
    InitResourceCachePools();
    InitScreenTransitionState_candidate();
    InitRoomBgState_candidate();
    NoopInit2();
    InitInputSystem();
    ResetAllGameTimers();
    InitDisplayControl();
    InitRoomScriptState_candidate();
    NoopInit3();
    InitDialogBox();
    InitRoomTileAnimationTable();
    InitRoomState();
    ClearResourceCacheSlots();
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
