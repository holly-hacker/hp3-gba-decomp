#include "types.h"
#include "audio.h"
#include "bios.h"
#include "dialog.h"
#include "display.h"
#include "game_modes.h"
#include "io_regs.h"
#include "lupin_potion_cutscene.h"
#include "main_menu.h"
#include "overworld.h"
#include "room.h"
#include "scanline_effects.h"
#include "text.h"
#include "graphics.h"

void InitializeLupinPotionCutscene(void)
{
    volatile u16 zero;
    CameraFocusPosition position;

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ClearResourceCacheSlots();
    sub_0803094C(0);
    sub_0803094C(1);
    sub_0803094C(2);
    sub_0800D264((void *)g_MainMenuPalette, 0, 0x10);
    sub_08028AD4();
    sub_08029558();
    sub_08028F7C();

    g_GameModeStackContext.dwModeState = 0;
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
    g_GameModeStackContext.dwCurrentGameModeArg3 = 0xFFFE8000;
    g_LupinPotionCutscene.bParallaxScroll = 1;
    sub_08009FD8(0);

    position.aCoordinates[0] = 0x960000;
    position.aCoordinates[1] = 0;
    sub_0800A38C(position, 0);
    position.aCoordinates[0] >>= 16;
    position.aCoordinates[1] >>= 16;
    sub_0803E628(position.aCoordinates);

    SetTextTargetFromBgControl(g_dwLupinPotionTextBgControl);
    SelectTextFont(7, 0, 0);
    sub_0801FBA4(0);
    LoadEmbeddedPalette_candidate((u8 *)g_LupinPotionEmbeddedPalette, 0, 1);
    PlayMusicModule(0x10);
    QueueScanlineEffectTable(g_aLupinPotionScanlineTable, 2);
    while (!IsScanlineEffectQueueIdle())
        ;
    StartScanlineEffects();
    PlayScreenTransitionInByIndex(0x3F, 2);
}
