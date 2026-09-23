#include "types.h"
#include "bios.h"
#include "display.h"
#include "game_modes.h"
#include "io_regs.h"
#include "minigame_menu.h"
#include "mt19937.h"
#include "serve_pumpkin_juice.h"
#include "text.h"

void InitializeUnusedServePumpkinJuiceMinigame(void)
{
    volatile u16 zero;
    u32 bgControl;

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwServePumpkinJuiceBg0Control);
    SetBgControl(1, g_dwServePumpkinJuiceBg1Control);
    SetBgControl(2, g_dwServePumpkinJuiceBg2Control);
    bgControl = g_dwServePumpkinJuiceBg3Control;
    SetBgControl(3, bgControl);

    LoadBgGraphic(0, g_ServePumpkinJuiceBg0Graphic, 1, 0, 0, 0);
    g_ServePumpkinJuice.pBg1Tilemap = LoadBgGraphic(1, g_ServePumpkinJuiceBg1Graphic, 1, 0, 0, 0);
    LoadBgGraphic(2, g_ServePumpkinJuiceBg2Graphic, 1, 0, 0, 0);
    sub_08007AF0(2, 0, 0x100000);
    sub_0800A598(g_ServePumpkinJuiceTable, &g_dwServePumpkinJuiceBg2Control, 8);
    SetTextTargetFromBgControl(bgControl);
    SelectTextFont(5, 0, -1);
    sub_0800D57C(3, 1, 8, 0x10, 0x19, g_ServePumpkinJuicePanelData, 6);
    Mt19937AutoSeed();

    g_ServePumpkinJuice.dwUnk2C = 0xA8;
    g_ServePumpkinJuice.dwUnk34 = 0xB8;
    g_ServePumpkinJuice.dwUnk3C = 0xC8;
    g_ServePumpkinJuice.dwUnk30 = 0x57;
    g_ServePumpkinJuice.dwUnk38 = 0x80;
    g_ServePumpkinJuice.dwUnk40 = 0xA8;
    g_ServePumpkinJuice.dwUnk14 = 0x55;
    sub_0803539C();

    SetAlphaBlendTargets(3, 4);
    SetAlphaBlendCoefficients(8, 8);
    PlayScreenTransitionInByIndex(0x3F, 2);
}
