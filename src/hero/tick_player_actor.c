#include "types.h"
#include "actor.h"
#include "hero.h"
#include "hero_inline.h"
#include "main.h"
#include "map.h"
#include "math.h"
#include "modes.h"
#include "overworld/overworld.h"

// pfnTick of the party leader. Shows the field spell HUD while the player is walking
// around the overworld and restarts the walk animation when the actor's sub state or
// facing changes.
void TickPlayerActor(Actor *actor)
{
    if (actor->bActionSubState == 5)
    {
        DestroyPartyMemberActor(actor);
        return;
    }

    TickActorActionState(actor);

    if ((actor->bActionState == 0x21 || actor->bActionState == 0x13)
        && !(g_dwGameModeFlags & GameModeFlagScreenTransitionOut)
        && g_GameModeStackContext.dwCurrentGameMode == Overworld
        && !(actor->dwFlags & ActorFlagAnimPaused)
        && g_bCurrentRoomId != RoomPortraitRoomPassage)
    {
        if (g_pFieldSpellIconActor == NULL)
            SpawnFieldSpellIconActor();
    }
    else if (g_pFieldSpellIconActor != NULL)
        FreeFieldHudActors();

    if (actor->bActionFlags & 2)
    {
        if (actor->bActionSubState == 3)
        {
            actor->bActionFlags &= ~2;
            actor->vel.x = FixedMultiply(g_aDirection8Vectors[actor->bFacing][0], actor->nMoveSpeed);
            actor->vel.y = FixedMultiply(g_aDirection8Vectors[actor->bFacing][1], actor->nMoveSpeed);
            SetPartyMemberAnim(actor, PartyAnimWalk);
        }
        else if (actor->bActionSubState == 2)
        {
            actor->bActionFlags &= ~2;
            StopActorMotion(actor);
            SetPartyMemberAnim(actor, PartyAnimStand);
        }
        else if (actor->bActionSubState == 0xF)
        {
            actor->bActionFlags &= ~2;
            SetPartyMemberAnim(actor, PartyAnim4);
            actor->dwFlags &= ~ActorFlagHasAnimation;
        }
    }

    if (actor->bActionFlags & 0x10)
    {
        actor->bActionFlags &= ~0x10;
        actor->vel.x = FixedMultiply(g_aDirection8Vectors[actor->bFacing][0], actor->nMoveSpeed);
        actor->vel.y = FixedMultiply(g_aDirection8Vectors[actor->bFacing][1], actor->nMoveSpeed);
        SetPartyMemberAnim(actor, PartyAnimWalk);
    }
}
