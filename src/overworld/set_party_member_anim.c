#include "types.h"
#include "actor.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

// Sets a party member's sprite set and animation for its facing. Facings 5-7 use the
// frames of 3-1, horizontally flipped.
void SetPartyMemberAnim(Actor *obj, u8 anim)
{
    if (obj->bActionState == 0xD)
        return;

    obj->dwFlags |= ActorFlagHasAnimation;

    switch (anim)
    {
    case PartyAnimStand:
        if (g_dwPendingCameraFocusFlag != 0 && obj->bFighterIndex == 1)
        {
            SetActorAssetRecord(obj, &g_PartyFocusGfx_candidate);
            SetActorAnimFrame(obj, g_abPartyStandFrames[obj->bFacing]);
        }
        else
        {
            SetActorAssetRecord(obj, &g_aPartyWalkAssets[obj->wCharacterId_candidate]);
            if (obj->wCharacterId_candidate == 8)
                SetActorAnimFrame(obj, g_abPartyStandFramesChar8[obj->bFacing]);
            else
                SetActorAnimFrame(obj, g_abPartyStandFrames[obj->bFacing]);
        }
        obj->dwFlags &= ~ActorFlagHasAnimation;
        break;
    case PartyAnimWalk:
        if (g_dwPendingCameraFocusFlag != 0 && obj->bFighterIndex == 1)
        {
            SetActorAnimData(obj, &g_PartyFocusGfx_candidate, g_aPartyWalkAnims[obj->bFacing], 0);
        }
        else if (obj->wCharacterId_candidate == 4)
        {
            SetActorAnimData(obj, &g_aPartyWalkAssets[obj->wCharacterId_candidate],
                              g_aPartyWalkAnimsChar4[obj->bFacing], 0);
            obj->oam.hFlip = obj->bFacing > 4;
        }
        else if (obj->wCharacterId_candidate == 8)
        {
            SetActorAnimData(obj, &g_aPartyWalkAssets[obj->wCharacterId_candidate],
                              g_aPartyWalkAnimsChar8[obj->bFacing], 0);
        }
        else
        {
            SetActorAnimData(obj, &g_aPartyWalkAssets[obj->wCharacterId_candidate],
                              g_aPartyWalkAnims[obj->bFacing], 0);
        }
        break;
    case PartyAnim4:
        SetActorAnimData(obj, &g_aPartyAnim4Assets[obj->wCharacterId_candidate],
                          g_aPartyAnim4Anims[obj->bFacing], 0);
        break;
    case PartyAnimCast:
        SetActorAnimData(obj, &g_aPartyCastAssets[obj->wCharacterId_candidate],
                          g_aPartyCastAnims[obj->bFacing], 0);
        break;
    case PartyAnim3:
        SetActorAnimData(obj, &g_aPartyAnim3Assets[obj->wCharacterId_candidate], g_abPartyAnim3Anim, 0);
        break;
    }

    obj->oam.hFlip = obj->bFacing > 4;
}
