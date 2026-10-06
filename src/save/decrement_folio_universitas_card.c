#include "types.h"
#include "game/save.h"
#include "menu/folio_universitas.h"

u32 DecrementFolioUniversitasCard(u32 cardIndex)
{
    if (g_saveStateBlock.abFolioUniversitasCounts[cardIndex] != 0)
    {
        g_saveStateBlock.abFolioUniversitasCounts[cardIndex]--;
        if (g_saveStateBlock.abFolioUniversitasCounts[cardIndex] == 0)
        {
            u32 byteIndex = cardIndex >> 3;
            u32 bit = cardIndex & 7;

            g_saveStateBlock.abFolioUniversitasSeen[byteIndex] &= ~(1 << bit);
            g_saveStateBlock.abFolioUniversitasCardIsNew[byteIndex] &= ~(1 << bit);
        }
    }
    return g_saveStateBlock.abFolioUniversitasCounts[cardIndex];
}
