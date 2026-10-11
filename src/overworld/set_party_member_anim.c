#include "types.h"
#include "actor.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

// Sets a party member's sprite set and animation for its facing. Facings 5-7 use the
// frames of 3-1, horizontally flipped.
void SetPartyMemberAnim(Actor *actor, u8 anim)
{
    if (actor->bActionState == 0xD)
        return;

    actor->dwFlags |= ActorFlagHasAnimation;

    switch (anim)
    {
    case PartyAnimStand:
        if (g_dwPendingCameraFocusFlag != 0 && actor->bFighterIndex == 1)
        {
            SetActorAssetRecord(actor, &g_PartyFocusGfx_candidate);
            SetActorAnimFrame(actor, g_abPartyStandFrames[actor->bFacing]);
        }
        else
        {
            SetActorAssetRecord(actor, &g_aPartyWalkAssets[actor->wCharacterId_candidate]);
            if (actor->wCharacterId_candidate == 8)
                SetActorAnimFrame(actor, g_abPartyStandFramesChar8[actor->bFacing]);
            else
                SetActorAnimFrame(actor, g_abPartyStandFrames[actor->bFacing]);
        }
        actor->dwFlags &= ~ActorFlagHasAnimation;
        break;
    case PartyAnimWalk:
        if (g_dwPendingCameraFocusFlag != 0 && actor->bFighterIndex == 1)
        {
            SetActorAnimData(actor, &g_PartyFocusGfx_candidate, g_aPartyWalkAnims[actor->bFacing], 0);
        }
        else if (actor->wCharacterId_candidate == 4)
        {
            SetActorAnimData(actor, &g_aPartyWalkAssets[actor->wCharacterId_candidate],
                              g_aPartyWalkAnimsChar4[actor->bFacing], 0);
            actor->oam.hFlip = actor->bFacing > 4;
        }
        else if (actor->wCharacterId_candidate == 8)
        {
            SetActorAnimData(actor, &g_aPartyWalkAssets[actor->wCharacterId_candidate],
                              g_aPartyWalkAnimsChar8[actor->bFacing], 0);
        }
        else
        {
            SetActorAnimData(actor, &g_aPartyWalkAssets[actor->wCharacterId_candidate],
                              g_aPartyWalkAnims[actor->bFacing], 0);
        }
        break;
    case PartyAnim4:
        SetActorAnimData(actor, &g_aPartyAnim4Assets[actor->wCharacterId_candidate],
                          g_aPartyAnim4Anims[actor->bFacing], 0);
        break;
    case PartyAnimCast:
        SetActorAnimData(actor, &g_aPartyCastAssets[actor->wCharacterId_candidate],
                          g_aPartyCastAnims[actor->bFacing], 0);
        break;
    case PartyAnim3:
        SetActorAnimData(actor, &g_aPartyAnim3Assets[actor->wCharacterId_candidate], g_abPartyAnim3Anim, 0);
        break;
    }

    actor->oam.hFlip = actor->bFacing > 4;
}
