#include "types.h"
#include "audio.h"
#include "bios.h"
#include "debug_menu.h"
#include "display.h"
#include "game_modes.h"
#include "io_regs.h"
#include "object.h"
#include "room.h"
#include "text.h"

void InitializeDebugSoundTestMenu(void)
{
    u16 fillValue;
    u16 *pFillValue;
    u32 bgCtrl1;
    Object *pObject;

    StopScanlineEffects();
    pFillValue = &fillValue;
    *pFillValue = 0;
    bios_CPUSet(pFillValue, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(0, g_dwDebugSoundTestBg0Control);
    bgCtrl1 = g_dwDebugSoundTestBg1Control;
    SetBgControl(1, bgCtrl1);
    LoadBgGraphic(0, g_DebugMenuGraphic, 0, 0, 0, 0);
    ClearBgTilemap(1);
    SetTextTargetFromBgControl(bgCtrl1);
    SelectTextFont(5, 0, -1);
    SetBgScroll_candidate(0, 0, 0);
    SetBgScroll_candidate(1, 0, 0);

    g_DebugSoundTestState.dwRow = 0;
    g_DebugSoundTestState.dwMusicPlaying = 0;
    g_DebugSoundTestState.nSoundHandle = DEBUG_SOUND_TEST_NO_HANDLE;
    g_DebugSoundTestState.adwSelection[0] = 0;
    g_DebugSoundTestState.adwSelection[1] = 0;
    if (g_bMusicPaused)
        StopMusic();
    g_bCurrentMusicModule = 0xFF;

    pObject = SpawnObject(10, 0x9C, g_DebugSoundTestState.dwRow * 18 + 0x3A, g_DebugMenuCursorSpawnData);
    g_DebugSoundTestState.pCursorObject = pObject;
    pObject->dwFlags |= ObjectFlagHasSpriteCells;
    SetObjectAnimData(pObject, (void *)g_DebugSoundTestAnimFrames, (void *)g_DebugSoundTestAnimData, 0);

    g_GameModeStackContext.dwModeState = 0;
    sub_0800B8F0();
    PlayScreenTransitionInByIndex(0x3F, 2);
}
