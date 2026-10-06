#include "types.h"
#include "game/save.h"

// Reads each monster's 3-bit level, low bit first.
void DeserializeMonsterDexLevels(void)
{
    u32 i;
    u8 bit;

    for (i = 0; i < sizeof(g_saveStateBlock.abMonsterDocLevel); i++)
    {
        UnpackBitsFromSaveStream(&bit, 1);
        g_saveStateBlock.abMonsterDocLevel[i] = bit;
        UnpackBitsFromSaveStream(&bit, 1);
        g_saveStateBlock.abMonsterDocLevel[i] |= bit << 1;
        UnpackBitsFromSaveStream(&bit, 1);
        g_saveStateBlock.abMonsterDocLevel[i] |= bit << 2;
    }
}
