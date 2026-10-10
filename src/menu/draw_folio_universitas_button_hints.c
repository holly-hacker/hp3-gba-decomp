#include "types.h"
#include "math.h"
#include "game/game_modes.h"
#include "font.h"
#include "graphics/text.h"
#include "menu/folio_universitas_inline.h"

// Draws the two button hints at the bottom of the screen, and shows or dims the L/R prompts that go with them:
// what the A button does for the selection and what Select does.
void DrawFolioUniversitasButtonHints(void)
{
    u32 purpose = g_GameModeStackContext.dwCurrentGameModeArg1;
    u32 cardIndex;
    u32 hasCombo;

    if (purpose == FolioUniversitasBrowse)
    {
        cardIndex = GetFolioUniversitasSelectedCard();
        if (IsFolioUniversitasCardSeen(cardIndex))
        {
            SelectTextFont(1, 0, -1);
            g_FolioUniversitasState.pPrevArrow->dwFlags |= ObjectFlagVisible;
        }
        else
        {
            SelectTextFont(1, 2, -1);
            g_FolioUniversitasState.pPrevArrow->dwFlags &= ~ObjectFlagVisible;
        }
        DrawString(0x8B, 0x18, 0x94, GetDialogText(0x40E));  // "Card Details"

        if (cardIndex % 10 <= 8)
        {
            SelectTextFont(1, 0, -1);
            g_FolioUniversitasState.pNextArrow->dwFlags |= ObjectFlagVisible;
        }
        else
        {
            SelectTextFont(1, 2, -1);
            g_FolioUniversitasState.pNextArrow->dwFlags &= ~ObjectFlagVisible;
        }
        DrawString(0xB3, 0x8C, 0x94, GetDialogText(0x40C));  // "Card Combo"
    }
    else if (purpose == FolioUniversitasPickCombo)
    {
        iwramDivideSignedQuotient(g_FolioUniversitasState.dwSlot, 3);
        cardIndex = g_FolioUniversitasState.dwCategory * 10 + g_FolioUniversitasState.dwSlot
                    - g_FolioUniversitasState.dwSlot % 3;
        if (cardIndex == 0x32)
            hasCombo = IsFolioUniversitasCardSeen(0x32) ? 1 : 0;
        else
            hasCombo = IsFolioUniversitasCardSeen(cardIndex) && IsFolioUniversitasCardSeen(cardIndex + 1) && IsFolioUniversitasCardSeen(cardIndex + 2);

        if (hasCombo)
        {
            SelectTextFont(1, 0, -1);
            g_FolioUniversitasState.pPrevArrow->dwFlags |= ObjectFlagVisible;
        }
        else
        {
            SelectTextFont(1, 2, -1);
            g_FolioUniversitasState.pPrevArrow->dwFlags &= ~ObjectFlagVisible;
        }
        DrawString(0x8B, 0x18, 0x94, GetDialogText(0x40F));  // "Use Combo"

        SelectTextFont(1, 0, -1);
        DrawString(0xB3, 0x8C, 0x94, GetDialogText(0x410));  // "View Combo"
    }
    else if (purpose == FolioUniversitasPickCard)
    {
        cardIndex = GetFolioUniversitasSelectedCard();
        if (g_saveStateBlock.abFolioUniversitasCounts[cardIndex] != 0)
        {
            SelectTextFont(1, 0, -1);
            g_FolioUniversitasState.pPrevArrow->dwFlags |= ObjectFlagVisible;
        }
        else
        {
            SelectTextFont(1, 2, -1);
            g_FolioUniversitasState.pPrevArrow->dwFlags &= ~ObjectFlagVisible;
        }
        DrawString(0x8B, 0x18, 0x94, GetDialogText(0x411));  // "Select"

        if (cardIndex % 10 <= 8)
        {
            SelectTextFont(1, 0, -1);
            g_FolioUniversitasState.pNextArrow->dwFlags |= ObjectFlagVisible;
        }
        else
        {
            SelectTextFont(1, 2, -1);
            g_FolioUniversitasState.pNextArrow->dwFlags &= ~ObjectFlagVisible;
        }
        DrawString(0xB3, 0x8C, 0x94, GetDialogText(0x40C));  // "Card Combo"
    }
}
