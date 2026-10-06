#include "types.h"
#include "game/save.h"

// Sets the player's money to an exact amount.
void SetSickles(u32 amount)
{
    g_saveStateBlock.dwMoney = amount;
}
