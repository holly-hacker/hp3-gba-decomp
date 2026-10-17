#include "types.h"
#include "background.h"
#include "color.h"
#include "hw/bios.h"
#include "gen/graphics/cutscenes.h"
#include "modes.h"
#include "hw/io_regs.h"
#include "screen_transitions.h"
#include "time_skip_cutscene.h"

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
    SetBgScrollFixed(0, 0, 0x480000);
    SetBgScrollFixed(1, 0, 0xFFD00000);
    PlayScreenTransitionInByIndex(0x3F, 2);
    sub_0800D5DC(0, 0x100, 0x10, 10, 0x31, GRAPHIC_BLOB_PALETTE_COLORS(gHogwartsUpNightFadeGraphic));
}
