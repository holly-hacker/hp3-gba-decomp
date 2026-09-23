#include "types.h"
#include "display.h"
#include "game_modes.h"
#include "input.h"
#include "linear_cutscene.h"
#include "minigame_menu.h"
#include "text.h"

// Credits mode's pUpdateFn: each time the scroll passes a new text row, draws
// the next credits line below it. Any of A/B/Select/Start, or running past the
// last line, leaves the credits.
void UpdateCredits(void)
{
    s32 aScroll[2];
    s32 row;
    u32 y;
    u32 cutsceneIndex;
    u8 *pText;

    cutsceneIndex = g_GameModeStackContext.dwCurrentGameMode - Credits;
    sub_08007F84(1, &aScroll[0], &aScroll[1]);
    row = aScroll[1] >> 20;

    if (row != g_dwCreditsScrollRow)
    {
        g_dwCreditsScrollRow = row;
        y = ((g_dwCreditsLine << 4) + 0xB0) & 0x1FF;

        if (cutsceneIndex == 0)
            sub_080075C0(1, 0, y >> 3, 0x20, 2, 0);

        if (g_dwCreditsLine < g_aLinearCutsceneTable[cutsceneIndex].dwLineCount)
        {
            pText = GetDialogText(g_dwCreditsLine + g_aLinearCutsceneTable[cutsceneIndex].dwTextId);

            // Text starting with '*' is a blank line.
            if (*pText != 0x2A)
            {
                if (cutsceneIndex == 0)
                    g_dwCreditsTileCursor = DrawStringAligned(g_dwCreditsTileCursor, 0x78, y, pText, 1);
                else
                    PrintTextBox(g_dwCreditsTileCursor, 0x78, y, 0xE8, pText, 1);
            }
        }

        g_dwCreditsLine++;
        if (g_dwCreditsTileCursor > 0x2FF)
            g_dwCreditsTileCursor = 1;
    }

    if (g_dwCreditsLine >= g_aLinearCutsceneTable[cutsceneIndex].dwLineCount + 0x14
        || (g_wKeysPressed & (KeyA | KeyB | KeySelect | KeyStart)) != 0)
        sub_0801D6DC();
}
