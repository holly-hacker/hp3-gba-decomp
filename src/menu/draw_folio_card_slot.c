#include "types.h"
#include "math.h"
#include "graphics/display.h"
#include "menu/folio_universitas_inline.h"
#include "overworld/room_script.h"

// Draws one card's tile in the card grid. Each category is a row; each group of three cards (one
// combo) is followed by a gap column. The last card of an unlocked row also gets a 2-wide tile.
void DrawFolioCardSlot(u32 cardIndex)
{
    s32 slot;
    s32 category = iwramDivideSignedRemainder(cardIndex, 10, &slot);
    s32 combo = iwramDivideSignedQuotient(slot, 3);
    u32 tile;
    s32 column;
    s32 x;
    s32 y;

    if (IsFolioUniversitasCardNew(cardIndex))
    {
        tile = 1;
    }
    else
    {
        if (!IsFolioUniversitasCardSeen(cardIndex))
        {
            if (IsFolioUniversitasCardUnavailable(cardIndex))
            {
                sub_08006C00(0, g_FolioUniversitasState.pGridTilemap, 1, 0, 8, 0x14,
                             slot + (column = combo + 0xF), category + 4, 1, 1);
            }
            return;
        }
        tile = 0;
    }

    // The column and row are assigned inside the argument lists: the original computes them
    // after the first stack arguments are stored.
    if (IsFolioUniversitasCardUnavailable(cardIndex))
    {
        sub_08006C00(0, g_FolioUniversitasState.pGridTilemap, 1, 0, tile + 6, 0x14, slot + (x = combo + 0xF),
                     y = category + 4, 1, 1);
    }
    else
    {
        sub_08006C00(0, g_FolioUniversitasState.pGridTilemap, 1, 0, tile, 0x14, slot + (x = combo + 0xF),
                     y = category + 4, 1, 1);
    }

    if (slot == 9 && IsFolioPageGroupUnlocked_candidate(category))
        sub_08006C00(0, g_FolioUniversitasState.pGridTilemap, 1, 0, tile * 2 + 2, 0x14, slot + x + 1, y, 2, 1);
}
