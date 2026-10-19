#include "types.h"
#include "combat_fighter.h"

// Puts every party member at the start of the first level.
void ResetAllPartyLevelsTo1(void)
{
    u32 i;

    for (i = 0; i < 3; i++)
        ResetCharacterToLevel(i, 0);
}
