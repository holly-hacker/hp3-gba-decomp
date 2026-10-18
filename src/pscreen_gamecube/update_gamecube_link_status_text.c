#include "types.h"
#include "modes.h"
#include "gamecube.h"
#include "pscreen_gamecube_inline.h"

// Draws the text for the link's progress and, while there is none, the text for linkEvent
// (a JOYBUS_STATE_* value).
void UpdateGameCubeLinkStatusText(u32 linkEvent)
{
    u32 textId = g_aGameCubeLinkStatusTexts[g_JoybusLinkState.bLinkProgress].wTextId;

    if (g_JoybusLinkState.wStatusTextId != textId)
    {
        g_JoybusLinkState.wStatusTextId = textId;
        g_JoybusLinkState.wStatusTextFrames = g_aGameCubeLinkStatusTexts[g_JoybusLinkState.bLinkProgress].wFrames;
        FillBgTilemapRect(2, 2, 0xB, 0x1A, 4, 0);
        if (textId <= 0xACE)
        {
            SelectTextFont(3, 6, 0);
            PrintTextBox(0xE1, 0x78, 0x58, 0xC8, GetDialogText(textId), 1);
        }

        switch (g_JoybusLinkState.bLinkProgress)
        {
        case 1:
            ShowGameCubeLinkMessage(0x591);  // "Press any button to continue"
            g_GameModeStackContext.dwModeState = 2;
            break;

        case 2:
            ShowGameCubeLinkMessage(0x591);
            g_GameModeStackContext.dwModeState = 2;
            break;
        }
    }

    if (textId <= 0xACE)
    {
        if (g_JoybusLinkState.wStatusTextFrames != 0 && --g_JoybusLinkState.wStatusTextFrames == 0)
        {
            FillBgTilemapRect(2, 5, 0xB, 0x14, 4, 0);
            g_JoybusLinkState.bLinkProgress = 0;
        }
    }
    else
    {
        textId = g_aGameCubeLinkResultTexts[linkEvent].wTextId;
        if (g_JoybusLinkState.wResultTextId != textId)
        {
            if (g_JoybusLinkState.wResultTextHoldFrames == 0 || linkEvent == JOYBUS_STATE_RECEIVING
                || linkEvent == JOYBUS_STATE_SENDING)
            {
                g_JoybusLinkState.wResultTextId = textId;
                FillBgTilemapRect(2, 5, 0xB, 0x14, 2, 0);
                SelectTextFont(2, 0, 0);
                DrawStringAligned(0x61, 0x78, 0x5C, GetDialogText(textId), 1);
                g_JoybusLinkState.wResultTextHoldFrames = g_aGameCubeLinkResultTexts[linkEvent].wFrames;
            }
            else
                g_JoybusLinkState.wResultTextHoldFrames--;
        }
    }
}
