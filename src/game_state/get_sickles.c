#include "types.h"
#include "save.h"
#include "game_state.h"

s32 GetSickles(void)
{
    return g_saveStateBlock.dwMoney;
}
