#include "types.h"
#include "actor.h"
#include "hero.h"
#include "move.h"
#include "sound.h"

void PlayFieldSpellHitSound(Actor *effect)
{
    switch (effect->wCharacterId_candidate)
    {
    case 7:
        PlaySoundById(0x51);
        break;
    case FieldSpellReparo:
        PlaySoundById(0x20);
        break;
    case FieldSpellAlohomora:
        PlaySoundById(0x52);
        break;
    case FieldSpellFlipendo:
    case FieldSpellGlacius:
        PlaySoundById(0x50);
        break;
    case FieldSpellSpongify:
        PlaySoundById(0x56);
        break;
    case FieldSpellDiffindo:
        PlaySoundById(0x54);
        break;
    }
}
