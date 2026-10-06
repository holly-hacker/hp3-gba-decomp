#include "types.h"
#include "game/save.h"
#include "graphics/display.h"
#include "menu/folio_bruti.h"

// Marks every monster's cell of the grid with the tile for its level (see ClearMonsterDexNewFlags).
void DrawFolioBrutiGrid(void)
{
    u32 monster = 0;
    u32 row;
    u32 column;

    for (row = 0; row <= 5; row++)
    {
        for (column = 0; column <= 8; column++)
        {
            if (column == 8 && row == 5)
                continue;

            if (monster <= 0x44)
            {
                u32 level = g_saveStateBlock.abMonsterDocLevel[monster];

                sub_08006C00(3, g_FolioBrutiState.pGridTilemap, 1, 0, level, 0x14, column + 3, row + 3, 1, 1);
            }
            monster++;
        }
    }
}
