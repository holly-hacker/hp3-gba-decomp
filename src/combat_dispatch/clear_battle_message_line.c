#include "types.h"
#include "background.h"
#include "combat_dispatch.h"

// Clears one text row of the battle message box.
void ClearBattleMessageLine(u8 line)
{
    ClearBgTilemapRect(0, 10, line + 24, 20, 1);
}
