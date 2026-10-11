#include "types.h"
#include "graphics/audio.h"
#include "hw/bios.h"
#include "cutscene/clock_skip_cutscene.h"
#include "cutscene/hogwarts_up_night_cutscene.h"
#include "actor.h"
#include "graphics/display.h"
#include "game/game_modes.h"
#include "hw/io_regs.h"
#include "gen/graphics/overworld.h"

void InitializeClockSkipCutscene(void)
{
    volatile u16 zero;
    Actor *pActor;

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwUpNightBg0Control);
    LoadBgGraphic(0, gClockSkipGraphic, 1, 0, 0, 0);

    pActor = SpawnActor(0x17, 0x78, 0x50, (const ObjPalette *)gClockSkipActor1Palette);
    SetActorSprite(pActor, &g_ClockSkipActor1Asset);
    SetActorAnimData(pActor, &g_ClockSkipActor1Asset, (void *)g_ClockSkipAnimData[0], 0);

    pActor = SpawnActor(0x17, 0x78, 0x50, (const ObjPalette *)gClockSkipActor2Palette);
    SetActorSprite(pActor, &g_ClockSkipActor2Asset);
    SetActorAnimData(pActor, &g_ClockSkipActor2Asset, (void *)g_ClockSkipAnimData[1], 0);

    PlayMusicModule(0x19);
    g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
    PlayScreenTransitionInByIndex(0x3F, 2);
}
