#include "modes.h"
#include "actor.h"
#include "area.h"
#include "main.h"

// Action state 0x14: while GameModeFlagSwitchingMode is set, runs bRespawnRow and
// bChainRow every tick.
void TickActorRespawnRow(Actor *actor)
{
    if (g_dwGameModeFlags & GameModeFlagSwitchingMode)
        RespawnGroupAndRunChain(actor->bRespawnRow, actor->bChainRow);
}
