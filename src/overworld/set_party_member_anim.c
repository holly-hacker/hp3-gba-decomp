#include "types.h"
#include "graphics/object.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

// Sets a party member's sprite set and animation for its facing. Facings 5-7 use the
// frames of 3-1, horizontally flipped.
void SetPartyMemberAnim(Object *obj, u8 anim)
{
    if (obj->bActionState == 0xD)
        return;

    obj->dwFlags |= ObjectFlagHasAnimation;

    switch (anim)
    {
    case PartyAnimStand:
        if (g_dwPendingCameraFocusFlag != 0 && obj->bFighterIndex == 1)
        {
            SetObjectAssetRecord(obj, &g_PartyFocusGfx_candidate);
            SetObjectAnimFrame(obj, g_abPartyStandFrames[obj->bFacing]);
        }
        else
        {
            SetObjectAssetRecord(obj, &g_aPartyWalkAssets[obj->wCharacterId_candidate]);
            if (obj->wCharacterId_candidate == 8)
                SetObjectAnimFrame(obj, g_abPartyStandFramesChar8[obj->bFacing]);
            else
                SetObjectAnimFrame(obj, g_abPartyStandFrames[obj->bFacing]);
        }
        obj->dwFlags &= ~ObjectFlagHasAnimation;
        break;
    case PartyAnimWalk:
        if (g_dwPendingCameraFocusFlag != 0 && obj->bFighterIndex == 1)
        {
            SetObjectAnimData(obj, &g_PartyFocusGfx_candidate, g_aPartyWalkAnims[obj->bFacing], 0);
        }
        else if (obj->wCharacterId_candidate == 4)
        {
            SetObjectAnimData(obj, &g_aPartyWalkAssets[obj->wCharacterId_candidate],
                              g_aPartyWalkAnimsChar4[obj->bFacing], 0);
            obj->oam.hFlip = obj->bFacing > 4;
        }
        else if (obj->wCharacterId_candidate == 8)
        {
            SetObjectAnimData(obj, &g_aPartyWalkAssets[obj->wCharacterId_candidate],
                              g_aPartyWalkAnimsChar8[obj->bFacing], 0);
        }
        else
        {
            SetObjectAnimData(obj, &g_aPartyWalkAssets[obj->wCharacterId_candidate],
                              g_aPartyWalkAnims[obj->bFacing], 0);
        }
        break;
    case PartyAnim4:
        SetObjectAnimData(obj, &g_aPartyAnim4Assets[obj->wCharacterId_candidate],
                          g_aPartyAnim4Anims[obj->bFacing], 0);
        break;
    case PartyAnimCast:
        SetObjectAnimData(obj, &g_aPartyCastAssets[obj->wCharacterId_candidate],
                          g_aPartyCastAnims[obj->bFacing], 0);
        break;
    case PartyAnim3:
        SetObjectAnimData(obj, &g_aPartyAnim3Assets[obj->wCharacterId_candidate], g_abPartyAnim3Anim, 0);
        break;
    }

    obj->oam.hFlip = obj->bFacing > 4;
}
