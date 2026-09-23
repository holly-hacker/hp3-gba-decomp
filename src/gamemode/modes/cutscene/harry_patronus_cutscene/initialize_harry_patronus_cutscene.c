#include "types.h"
#include "bios.h"
#include "display.h"
#include "game_modes.h"
#include "harry_patronus_cutscene.h"
#include "io_regs.h"
#include "vblank.h"

void InitializeHarryPatronusCutscene(void)
{
    volatile u16 zero;

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ResetDisplayState(2);
    SetDispcntFlag(0x1000);
    SetBgControl(2, g_dwPatronusBg2Control);
    SetBgControl(3, g_dwPatronusBg3Control);

    g_swPatronusBgParam = 0x180;
    g_nPatronusBgOffset = 0xFFB00000;
    sub_08007AF0(2, 0, 0);
    sub_08007C94(2, g_nPatronusBgOffset >> 16, 0);
    sub_08007CF4(2, g_swPatronusBgParam);
    sub_08007C2C(2, 0, 0);
    sub_08007C2C(2, 0, 0);
    sub_08007AF0(3, 0, 0);
    sub_08007C94(3, g_nPatronusBgOffset >> 16, 0);
    sub_08007CF4(3, g_swPatronusBgParam);
    sub_08007C2C(3, 0, 0);

    LoadBgGraphic(2, g_apPatronusGraphics[0], 0, 0, 0, 0);
    LoadBgGraphic(3, g_apPatronusGraphics[1], 0, 0, 0, 0);
    g_dwPatronusBgFront = 2;
    g_dwPatronusBgBack = 3;
    g_bPatronusGraphicIndex = 0;
    g_dwPatronusSwapPending = 0;
    g_swPatronusBgParam = 0x200;
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
    DisableBg(3);
    SetVBlankCallback(HandleHarryPatronusCutsceneVBlank);
    SetFadeToBlack(0x3F, 0x10);
    PlayScreenTransitionInByIndex(0x3F, 2);
    g_GameModeStackContext.dwModeState = 0;
}
