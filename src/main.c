#include "vblank.h"
#include "interrupts.h"
#include "io_regs.h"
#include "mem.h"
#include "text.h"
#include "game_modes.h"
#include "battle.h"

extern void ClearSystemMemory(void);
extern void InstallIwramDivideRoutines(void);
extern void sub_080453B4(void);
extern void sub_0801DD40(void);
extern void sub_0803B314(void);
extern void sub_08020D30(void);
extern void InitSaveSystem(void);
extern void sub_0800D1A4(void);
extern void sub_08021560(void);
extern void InitOamSystem(void);
extern void sub_080315A4(void);
extern void sub_0803D2C8(void);
extern void sub_0803E4FC(void);
extern void sub_0802DD54(void);
extern void sub_080258E8(void);
extern void sub_08042E2C(void);
extern void InitDisplayControl(void);
extern void sub_08005A44(void);
extern void sub_0802D544(void);
extern void sub_0801FB78(void);
extern void sub_080203A8(void);
extern void InitRoomState(void);
extern void InstallBgTileCodec_candidate(void);
extern void SetFadeToWhite(u16 layerMask, u16 amount);
extern void kramInstall(void);
extern void sub_08045094(void);
extern void ProcessPlaytimeTick(void);

// Thumb function entry point in still-raw territory, taken by address as
// the VBlank callback -- see `thumb-func 0x08026244` in regions.us.txt.
extern void sub_08026244(void);

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
    sub_080453B4();
    sub_0801DD40();
    sub_0803B314();
    sub_08020D30();
    InitDialogTextEngine();
    InitSaveSystem();
    InitGameModeStack();
    InitObjectPool();
    sub_0800D1A4();
    sub_08021560();
    InitOamSystem();
    sub_080315A4();
    sub_0803D2C8();
    sub_0803E4FC();
    sub_0802DD54();
    sub_080258E8();
    sub_08042E2C();
    InitDisplayControl();
    sub_08005A44();
    sub_0802D544();
    sub_0801FB78();
    sub_080203A8();
    InitRoomState();
    sub_08030824();
    InstallBgTileCodec_candidate();

    g_dwGameModeFlags = 0;
    g_pVBlankState->wSuppressOamSwap = 0;

    SetVBlankCallback(sub_08026244);
    kramInstall();
    EnableInterrupts();
    sub_08045094();
    g_dwFrameSyncTarget = 2;

    while (1)
    {
        TickGameModeStack_candidate();
        ProcessPlaytimeTick();
        WaitForVBlank();
    }
}
