#include "types.h"
#include "constants/items.h"
#include "dialog.h"
#include "font.h"
#include "items.h"
#include "save.h"
#include "text.h"
#include "game_state.h"
#include "hedwig_minigame.h"

// The owl is back: it brings the dearest item the stat meters can afford and
// fills each care counter three quarters of the way up to 250.
void ProcessOwlMailReward(void)
{
    u32 item;
    s32 sumSquares;
    s32 budget;
    const u8 *pText;

    sumSquares = g_saveStateBlock.owlCareKit.abStatMeters[0] * g_saveStateBlock.owlCareKit.abStatMeters[0];
    sumSquares += g_saveStateBlock.owlCareKit.abStatMeters[1] * g_saveStateBlock.owlCareKit.abStatMeters[1];
    budget = sumSquares + g_saveStateBlock.owlCareKit.abStatMeters[2] * g_saveStateBlock.owlCareKit.abStatMeters[2];
    budget = (budget >> 8) << 16;  // to 16.16; the >> 8 keeps the shift within s32
    budget = budget / 732 * 1360;  // fraction of all three meters at 250 (3 * 250 * 250 >> 8), times 1360
    budget >>= 16;
    item = SelectOwlMailRewardItem(budget);

    g_saveStateBlock.owlCareKit.abCareCounters[0] += (250 - g_saveStateBlock.owlCareKit.abCareCounters[0]) / 4 * 3;
    g_saveStateBlock.owlCareKit.abCareCounters[1] += (250 - g_saveStateBlock.owlCareKit.abCareCounters[1]) / 4 * 3;
    g_saveStateBlock.owlCareKit.abCareCounters[2] += (250 - g_saveStateBlock.owlCareKit.abCareCounters[2]) / 4 * 3;
    g_saveStateBlock.owlCareKit.abCareCounters[3] += (250 - g_saveStateBlock.owlCareKit.abCareCounters[3]) / 4 * 3;
    g_saveStateBlock.owlCareKit.abCareCounters[4] += (250 - g_saveStateBlock.owlCareKit.abCareCounters[4]) / 4 * 3;
    g_saveStateBlock.owlCareKit.abCareCounters[5] += (250 - g_saveStateBlock.owlCareKit.abCareCounters[5]) / 4 * 3;
    UpdateOwlStatMeters(1);

    if (item <= ITEM_ANTI_PARALYSIS_POTION)
    {
        SelectTextFont(2, 0, -1);
        GrantReward(item, 1);
        SetTextMacro1String(GetDialogText(GetRewardNameTextId(item)));
        pText = GetDialogText(0xAC1);  // "The owl mail has arrived! You received @1."
        pText = ExpandTextMacros(g_pDialogMacroExpandBuffer, pText, 0x400);
        DrawTextLines(0x28C, 0x78, 0x40, 0xB0, 0x40, &pText, 1);
    }
}
