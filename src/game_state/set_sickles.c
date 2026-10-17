#include "types.h"
#include "save.h"
#include "game_state.h"

// Sets the player's money to an exact amount.
void SetSickles(u32 amount)
{
    g_saveStateBlock.dwMoney = amount;
}
