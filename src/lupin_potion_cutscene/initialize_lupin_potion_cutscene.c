#include "types.h"
#include "background.h"
#include "color.h"
#include "sound.h"
#include "hw/bios.h"
#include "dialog_box.h"
#include "gen/graphics/cutscenes.h"
#include "modes.h"
#include "hw/io_regs.h"
#include "lupin_potion_cutscene.h"
#include "video.h"
#include "font.h"
#include "gen/graphics/menus.h"
#include "screen_transitions.h"
#include "scroll.h"

void InitializeLupinPotionCutscene(void)
{
    volatile u16 zero;
    FixedPoint position;

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ClearObjPaletteSlots();
    ReserveObjPaletteSlot(0);
    ReserveObjPaletteSlot(1);
    ReserveObjPaletteSlot(2);
    QueueObjPaletteLoad((const u16 *)gMainMenuPalette, 0, 0x10);
    LoadLupinPotionCutsceneBgs();
    SpawnLupinPotionCast();
    ResetLupinPotionScripts();

    g_GameModeStackContext.dwModeState = 0;
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
    g_GameModeStackContext.dwCurrentGameModeArg3 = 0xFFFE8000;
    g_LupinPotionCutscene.bParallaxScroll = 1;
    ResetCameraFocusSlot(0);

    position.x = 0x960000;
    position.y = 0;
    SetCameraFocusPosition(position, 0);
    position.x >>= 16;
    position.y >>= 16;
    SetCameraPosition(&position.x);

    SetTextTargetFromBgControl(g_dwLupinPotionTextBgControl);
    SelectTextFont(7, 0, 0);
    SetDialogTextAlign(0);
    LoadEmbeddedPalette((u8 *)gDialogBoxGraphic, 0, 1);
    PlayMusicModule(0x10);
    QueueScanlineEffectTable(g_aLupinPotionScanlineTable, 2);
    while (!IsScanlineEffectQueueIdle())
        ;
    StartScanlineEffects();
    PlayScreenTransitionInByIndex(0x3F, 2);
}
