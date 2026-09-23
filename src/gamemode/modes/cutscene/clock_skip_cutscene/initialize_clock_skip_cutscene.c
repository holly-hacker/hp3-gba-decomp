#include "types.h"
#include "audio.h"
#include "bios.h"
#include "clock_skip_cutscene.h"
#include "hogwarts_up_night_cutscene.h"
#include "debug_menu.h"
#include "display.h"
#include "game_modes.h"
#include "io_regs.h"

void InitializeClockSkipCutscene(void)
{
    volatile u16 zero;
    Object *pObject;

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwUpNightBg0Control);
    LoadBgGraphic(0, g_ClockSkipGraphic, 1, 0, 0, 0);

    pObject = SpawnObject(0x17, 0x78, 0x50, g_ClockSkipObject1SpawnData);
    sub_08001690(pObject, g_ClockSkipObject1Asset);
    SetObjectAnimData(pObject, (void *)g_ClockSkipObject1Asset, (void *)g_ClockSkipAnimData, 0);

    pObject = SpawnObject(0x17, 0x78, 0x50, g_ClockSkipObject2SpawnData);
    sub_08001690(pObject, g_ClockSkipObject2Asset);
    SetObjectAnimData(pObject, (void *)g_ClockSkipObject2Asset, (void *)(g_ClockSkipAnimData + 0x36), 0);

    PlayMusicModule(0x19);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
    PlayScreenTransitionInByIndex(0x3F, 2);
}
