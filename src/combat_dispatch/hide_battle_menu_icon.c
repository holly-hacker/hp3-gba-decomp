#include "types.h"
#include "actor.h"
#include "combat_dispatch.h"

void HideBattleMenuIcon(u8 row)
{
    Actor *actor;

    actor = g_apBattleMenuIconActors[row];
    actor->dwFlags &= ~ActorFlagVisible;
    if (actor->oam.affineMode)
        ReleaseActorAffineSlot(actor);
}
