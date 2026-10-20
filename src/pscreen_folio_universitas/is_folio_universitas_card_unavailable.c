#include "types.h"
#include "modes.h"
#include "pscreen_folio_universitas.h"
#include "combat.h"

// Cards whose combo cannot be played in the current battle.
u32 IsFolioUniversitasCardUnavailable(s32 cardIndex)
{
    // Cards 3-5, Tempest Jinx: it blows an opponent off-screen, which would skip a scripted
    // battle's (0xFF) opponent.
    if (g_GameModeStackContext.dwCurrentGameModeArg1 == FolioUniversitasPickCombo
        && g_pFightState->abBattleResumeArgs[2] == 0xFF && cardIndex > 2 && cardIndex <= 5)
        return 1;

    // Cards 20-22, Revive: only while an ally has fainted.
    if (g_GameModeStackContext.dwCurrentGameModeArg1 == FolioUniversitasPickCombo
        && g_pFightState->bFaintedAllyCount == 0 && cardIndex > 19 && cardIndex <= 22)
        return 1;

    return 0;
}
