#include "types.h"
#include "math.h"
#include "game/game_modes.h"
#include "graphics/text.h"
#include "menu/minigame_menu.h"
#include "menu/folio_universitas.h"

// Prints the selected card's name and, when asked, its combo's name. The card name is left alone
// when picking a combo for battle.
void DrawFolioUniversitasNames(u32 drawComboName)
{
    s32 nextSlot;
    u32 nameIndex;

    if (g_GameModeStackContext.dwCurrentGameModeArg1 != FolioUniversitasPickCombo)
    {
        sub_080075C0(1, 2, 0xB, 0xD, 3, 0);
        SelectTextFont(1, 0, 0);
        nameIndex = g_FolioUniversitasState.dwCategory * 10 + g_FolioUniversitasState.dwSlot;
        PrintTextBox(0x3B, 0x10, 0x58, 0x68, GetDialogText(nameIndex + 0x412), 0);
    }

    if (drawComboName)
    {
        sub_080075C0(1, 1, 0xE, 0xF, 3, 0);
        iwramDivideSignedRemainder(g_FolioUniversitasState.dwSlot + 1, 10, &nextSlot);
        if (nextSlot != 0)
        {
            SelectTextFont(1, 0, 0);
            // Three combos per category, one per group of three cards.
            nameIndex = g_FolioUniversitasState.dwCategory * 3 + g_FolioUniversitasState.dwSlot / 3;
            PrintTextBox(0x63, 0x10, 0x70, 0x78, GetDialogText(nameIndex + 0x478), 0);
        }
    }
}
