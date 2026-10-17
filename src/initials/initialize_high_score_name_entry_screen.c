#include "types.h"
#include "background.h"
#include "color.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "font.h"
#include "modes.h"
#include "menu/main_menu.h"
#include "initials.h"
#include "gen/graphics/minigames/wizard_cracker.h"
#include "gen/graphics/menus.h"
#include "cursor.h"
#include "screen_transitions.h"

void InitializeHighScoreNameEntryScreen(void)
{
    volatile u16 zero;
    u32 bgControl;
    Actor *pCursor;

    zero = 0;
    bios_CPUSet((void *)&zero, VRAM_BASE, 0x01008000);
    ResetDisplayState(0);
    SetDispcntFlag(0x1000);
    SetBgControl(2, g_dwHighScoreNameEntryBg2Control);
    bgControl = g_dwHighScoreNameEntryBg0Control;
    SetBgControl(0, bgControl);
    SetBgControl(3, g_dwHighScoreNameEntryBg3Control);
    LoadBgGraphic(2, gWizardCrackerPopItBg1Graphic, 1, 0, 0, 0);
    LoadBgGraphic(3, gWizardCrackerPopItBg0Graphic, 1, 0, 0, 0);
    ClearBgTilemap(0);
    SetTextTargetFromBgControl(bgControl);
    SelectTextFont(5, 0, -1);
    StartPaletteEffectWithFrameCount(3, 1, 8, 0x10, 0x19, GRAPHIC_BLOB_PALETTE_COLORS(gMenuSelectionPalette), 6);
    SetBgScroll(2, 0, 0);
    g_GameModeStackContext.dwModeState = 0;

    pCursor = SpawnMenuCursorActor(4);
    g_HighScoreNameEntry.pCursor = pCursor;
    pCursor->pfnTick = HighScoreNameEntryCursorTick;
    g_HighScoreNameEntry.dwRow = 0;
    g_HighScoreNameEntry.dwColumn = 0;
    g_HighScoreNameEntry.abCandidate[0] = 'A';
    g_HighScoreNameEntry.abName[3] = 0;
    g_HighScoreNameEntry.abName[2] = 0;
    g_HighScoreNameEntry.abName[1] = 0;
    g_HighScoreNameEntry.abName[0] = 0;
    g_HighScoreNameEntry.dwTileCursor = 0;
    g_HighScoreNameEntry.dwNameLength = 0;
    SetActorPosition(pCursor, 0x19, 0x20);

    DrawHighScoreNameEntryKeypad();
    DrawHighScoreNameEntryPreview();
    PlayMusicModule(0x11);
    PlayScreenTransitionInByIndex(0x3F, 2);
}
