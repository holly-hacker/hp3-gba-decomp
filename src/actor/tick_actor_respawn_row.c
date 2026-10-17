#include "actor.h"
#include "area.h"
#include "main.h"

// Action state 0x14: while g_dwGameModeFlags bit 0x10 is set, runs bRespawnRow and
// bChainRow every tick.
void TickActorRespawnRow(Actor *actor)
{
    if (g_dwGameModeFlags & 0x10)
        RespawnGroupAndRunChain(actor->bRespawnRow, actor->bChainRow);
}
