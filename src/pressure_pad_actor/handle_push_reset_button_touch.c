#include "types.h"
#include "actor.h"
#include "hero.h"
#include "sound.h"
#include "pressure_pad_actor.h"

// Collision callback: a Flipendo spell effect presses variant 0.
void HandlePushResetButtonTouch(Actor *pSelf, Actor *pOther)
{
    if (pSelf->wSubtype == 0 && pOther->wActorType == RoomActorType_FieldSpellEffect
        && pOther->wSubtype == FieldSpellFlipendo)
    {
        PlaySoundById(4);
        SetActorAnimData(pSelf, g_apPushResetButtonSprites[pSelf->wSubtype],
                         g_aabPushResetButtonPressAnims[pSelf->wSubtype], 0);
    }
}
