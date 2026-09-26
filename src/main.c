#include "vblank.h"
#include "interrupts.h"
#include "io_regs.h"
#include "mem.h"
#include "text.h"
#include "game_modes.h"
#include "battle.h"
#include "mt19937.h"
#include "save.h"
#include "graphics.h"
#include "main_menu.h"

extern void ClearSystemMemory(void);
extern void InstallIwramDivideRoutines(void);
extern void InstallIwramFindFreeObjTileRun(void);
extern void InstallIwramDecompressCodecs(void);
extern void InitTextMacroTable(void);
extern void InitSaveSystem(void);
extern void InitGammaPalette(void);
extern void NoopInit(void);
extern void InitOamSystem(void);
extern void InitResourceCachePools(void);
extern void InitScreenTransitionState_candidate(void);
extern void sub_0803E4FC(void);
extern void NoopInit2(void);
extern void InitInputSystem_candidate(void);
extern void sub_08042E2C(void);
extern void InitDisplayControl(void);
extern void InitRoomScriptState_candidate(void);
extern void NoopInit3(void);
extern void sub_0801FB78(void);
extern void InitRoomTileAnimationTable_candidate(void);
extern void InstallBgTileCodec(void);
extern void SetFadeToWhite(u16 layerMask, u16 amount);
extern void kramInstall(void);
extern void InitScanlineEffects(void);

// Thumb function entry point in still-raw territory, taken by address as
// the VBlank callback -- see `thumb-func 0x08026244` in regions.us.txt.
extern void VBlankCallback_candidate(void);

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
    sub_0803E4FC();
    NoopInit2();
    InitInputSystem_candidate();
    sub_08042E2C();
    InitDisplayControl();
    InitRoomScriptState_candidate();
    NoopInit3();
    sub_0801FB78();
    InitRoomTileAnimationTable_candidate();
    InitRoomState();
    ClearResourceCacheSlots();
    InstallBgTileCodec();

    g_dwGameModeFlags = 0;
    g_pVBlankState->wOamFrameReady = 0;

    SetVBlankCallback(VBlankCallback_candidate);
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
