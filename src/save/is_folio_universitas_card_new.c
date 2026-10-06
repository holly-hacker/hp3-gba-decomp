#include "types.h"
#include "game/save.h"
#include "menu/folio_universitas.h"

u32 IsFolioUniversitasCardNew(u32 cardIndex)
{
    u32 byteIndex = cardIndex >> 3;
    u32 bit = cardIndex & 7;

    if ((g_saveStateBlock.abFolioUniversitasCardIsNew[byteIndex] >> bit) & 1)
        return 1;
    return 0;
}
