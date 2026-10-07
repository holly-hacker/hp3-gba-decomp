#include "types.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "graphics/text.h"
#include "game/game_modes.h"
#include "menu/main_menu.h"
#include "minigame/high_score_name_entry.h"
#include "gen/graphics/minigames/wizard_cracker.h"
#include "gen/graphics/minigames/pumpkin.h"

void InitializeHighScoreNameEntryScreen(void)
{
    volatile u16 zero;
    u32 bgControl;
    Object *pCursor;

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
    sub_0800D57C(3, 1, 8, 0x10, 0x19, GRAPHIC_BLOB_PALETTE_COLORS(gServePumpkinJuicePanelPalette), 6);
    SetBgScroll_candidate(2, 0, 0);
    g_GameModeStackContext.dwModeState = 0;

    pCursor = sub_0801D940(4);
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
    SetObjectPosition(pCursor, 0x19, 0x20);

    DrawHighScoreNameEntryKeypad();
    DrawHighScoreNameEntryPreview();
    PlayMusicModule(0x11);
    PlayScreenTransitionInByIndex(0x3F, 2);
}
