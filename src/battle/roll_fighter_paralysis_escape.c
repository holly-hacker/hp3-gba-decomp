#include "types.h"
#include "battle.h"
#include "mt19937.h"

// Not-paralyzed fighters act normally (0). A paralyzed fighter rolls its
// escape chance: on failure the chance ratchets up by 25 for next time (1,
// can't act this turn); on success the status clears and the fighter still
// acts this turn (3).
u8 RollFighterParalysisEscape(u8 fighterIndex)
{
    if (g_pFightState->pFighters[fighterIndex].bStatusFlags & Paralyzed)
    {
        if (Mt19937ChanceNoisy(g_pFightState->pFighters[fighterIndex].bParalysisEscapeChance))
        {
            ClearParalyzedFighter_candidate(fighterIndex);
            return 3;
        }

        g_pFightState->pFighters[fighterIndex].bParalysisEscapeChance += 25;
        return 1;
    }

    return 0;
}
