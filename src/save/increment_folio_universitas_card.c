#include "types.h"
#include "game/save.h"
#include "menu/folio_universitas.h"

u32 IncrementFolioUniversitasCard(u32 cardIndex)
{
    if (g_saveStateBlock.abFolioUniversitasCounts[cardIndex] <= 8)
    {
        u32 byteIndex = cardIndex >> 3;
        u32 bit = cardIndex & 7;

        if (((g_saveStateBlock.abFolioUniversitasSeen[byteIndex] >> bit) & 1) == 0)
        {
            g_saveStateBlock.abFolioUniversitasCardIsNew[byteIndex] |= 1 << bit;
            g_saveStateBlock.abFolioUniversitasSeen[byteIndex] |= 1 << bit;
        }
        g_saveStateBlock.abFolioUniversitasCounts[cardIndex]++;
    }
    return g_saveStateBlock.abFolioUniversitasCounts[cardIndex];
}
