#include "types.h"
#include "save.h"
#include "pscreen_folio_bruti.h"
#include "game_state.h"

// Writes each monster's 3-bit level, low bit first.
void SerializeMonsterDexLevels(void)
{
    u32 i;
    u8 bits;

    for (i = 0; i < sizeof(g_saveStateBlock.abMonsterDocLevel); i++)
    {
        bits = g_saveStateBlock.abMonsterDocLevel[i];
        PackBitsToSaveStream(&bits, 1);
        bits >>= 1;
        PackBitsToSaveStream(&bits, 1);
        bits >>= 1;
        PackBitsToSaveStream(&bits, 1);
    }
}
