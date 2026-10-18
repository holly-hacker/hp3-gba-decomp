#include "background.h"
#include "commands.h"
#include "default_menu.h"
#include "font.h"
#include "gen/graphics/minigames/hippogriff.h"
#include "overworld/room.h"
#include "pause_menu.h"
#include "text.h"

// Draws the objective panel on BG1 with the current objective's text.
void DrawPauseMenuObjective(void)
{
    const u8 *pText;

    LoadBgGraphic(1, gPauseMenuObjectiveGraphic, MENU_SCREEN_OVERLAY_TILE_OFFSET, 0, 0, 0);
    SetBgScrollFixed(1, 0, 0);
    SetTextTargetFromBgControl(g_dwCommonBg1Control);
    SelectTextFont(2, 5, -1);
    pText = GetDialogText(g_abQuestEventState[QUEST_OBJECTIVE_INDEX] + 0x924);
    DrawTextLines(0xF0, 0x78, 0x84, 0xD0, 0x10, &pText, 1);
}
