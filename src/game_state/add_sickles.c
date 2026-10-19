#include "types.h"
#include "save.h"
#include "game_state.h"

#define MAX_SICKLES 999999

// Adds a signed amount to the player's money, clamped to 0..MAX_SICKLES.
u32 AddSickles(s32 amount)
{
    s32 money;

    g_saveStateBlock.dwMoney += amount;
    money = g_saveStateBlock.dwMoney;
    if (money > MAX_SICKLES)
        g_saveStateBlock.dwMoney = MAX_SICKLES;
    else if (money < 0)
        g_saveStateBlock.dwMoney = 0;

    return g_saveStateBlock.dwMoney;
}
