#include "types.h"
#include "hw/bios.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "cutscene/hogwarts_up_night_cutscene.h"
#include "hw/io_regs.h"

void InitializeHogwartsUpNightCutscene(void)
{
    volatile u16 zero;

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwUpNightBg0Control);
    SetBgControl(1, g_dwUpNightBg1Control);
    SetBgControl(2, g_dwUpNightBg2Control);
    LoadBgGraphic(0, gHogwartsUpNightBg0Graphic, 0, 0, 0, 0);
    LoadBgGraphic(1, gHogwartsUpNightBg1Graphic, 0x258, 0, 0, 0);
    LoadBgGraphic(2, gHogwartsUpNightBg2Graphic, 0x313, 0, 0, 0);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
    sub_08007AF0(0, 0, 0x480000);
    sub_08007AF0(1, 0, 0xFFD00000);
    PlayScreenTransitionInByIndex(0x3F, 2);
    sub_0800D5DC(0, 0x100, 0x10, 10, 0x31, g_HogwartsUpNightPaletteData);
}
