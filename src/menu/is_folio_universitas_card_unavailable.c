#include "types.h"
#include "battle/battle.h"
#include "game/game_modes.h"
#include "menu/folio_universitas.h"

// Cards that cannot be picked from battle right now: the first combos until the battle's resume
// arguments allow them, and the reinforcement cards while no fighter is waiting.
u32 IsFolioUniversitasCardUnavailable(s32 cardIndex)
{
    if (g_GameModeStackContext.dwCurrentGameModeArg1 == FolioUniversitasPickCombo
        && g_pFightState->abBattleResumeArgs_candidate[2] == 0xFF && cardIndex > 2 && cardIndex <= 5)
        return 1;

    if (g_GameModeStackContext.dwCurrentGameModeArg1 == FolioUniversitasPickCombo
        && g_pFightState->bPendingFighterCount_candidate == 0 && cardIndex > 0x13 && cardIndex <= 0x16)
        return 1;

    return 0;
}
