#include "types.h"
#include "color.h"
#include "save.h"
#include "game_state.h"
#include "hedwig_minigame.h"

void SetOwlPaletteRow(u32 row)
{
    QueueObjPaletteLoad(g_apOwlTypePalettes[g_saveStateBlock.owlCareKit.bTypeIndex], row * 16, 16);
}
