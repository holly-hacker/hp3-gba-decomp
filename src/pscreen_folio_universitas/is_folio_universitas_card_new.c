#include "types.h"
#include "save.h"
#include "pscreen_folio_universitas.h"
#include "game_state.h"

u32 IsFolioUniversitasCardNew(u32 cardIndex)
{
    u32 byteIndex = cardIndex >> 3;
    u32 bit = cardIndex & 7;

    if ((g_saveStateBlock.abFolioUniversitasCardIsNew[byteIndex] >> bit) & 1)
        return 1;
    return 0;
}
