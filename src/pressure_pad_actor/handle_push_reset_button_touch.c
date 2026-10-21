#include "types.h"
#include "actor.h"
#include "hero.h"
#include "sound.h"
#include "pressure_pad_actor.h"

// Collision callback: a Flipendo spell effect presses variant 0.
void HandlePushResetButtonTouch(Actor *pSelf, Actor *pOther)
{
    if (pSelf->wCharacterId_candidate == 0 && pOther->wActorType == RoomActorType_FieldSpellEffect
        && pOther->wCharacterId_candidate == FieldSpellFlipendo)
    {
        PlaySoundById(4);
        SetActorAnimData(pSelf, g_apPushResetButtonSprites[pSelf->wCharacterId_candidate],
                         g_aabPushResetButtonPressAnims[pSelf->wCharacterId_candidate], 0);
    }
}
