#include "types.h"
#include "background.h"
#include "graphics/audio.h"
#include "hw/bios.h"
#include "cheat_sound_test.h"
#include "graphics/display.h"
#include "modes.h"
#include "hw/io_regs.h"
#include "actor.h"
#include "overworld/room.h"
#include "font.h"
#include "gen/graphics/menus.h"

void InitializeCheatSoundTest(void)
{
    u16 fillValue;
    u16 *pFillValue;
    u32 bgCtrl1;
    Actor *pActor;

    StopScanlineEffects();
    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwCheatSoundTestBg0Control);
    bgCtrl1 = g_dwCheatSoundTestBg1Control;
    SetBgControl(1, bgCtrl1);
    LoadBgGraphic(0, gDebugMenuGraphic, 0, 0, 0, 0);
    ClearBgTilemap(1);
    SetTextTargetFromBgControl(bgCtrl1);
    SelectTextFont(5, 0, -1);
    SetBgScroll(0, 0, 0);
    SetBgScroll(1, 0, 0);

    g_CheatSoundTestState.dwRow = 0;
    g_CheatSoundTestState.dwMusicPlaying = 0;
    g_CheatSoundTestState.nSoundHandle = CHEAT_SOUND_TEST_NO_HANDLE;
    g_CheatSoundTestState.adwSelection[0] = 0;
    g_CheatSoundTestState.adwSelection[1] = 0;
    if (g_bMusicPaused)
        StopMusic();
    g_bCurrentMusicModule = 0xFF;

    pActor = SpawnActor(10, 0x9C, g_CheatSoundTestState.dwRow * 18 + 0x3A, (const ObjPalette *)gDebugMenuCursorPalette);
    g_CheatSoundTestState.pCursorActor = pActor;
    pActor->dwFlags |= ActorFlagHasSpriteCells;
    SetActorAnimData(pActor, &g_CheatSoundTestAnimFrames, (void *)g_CheatSoundTestAnimData, 0);

    g_GameModeStackContext.dwModeState = 0;
    DrawCheatSoundTestRows();
    PlayScreenTransitionInByIndex(0x3F, 2);
}
