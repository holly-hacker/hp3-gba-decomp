#include "types.h"
#include "actor.h"
#include "hero.h"
#include "move.h"

// pfnTick of g_pFieldSpellCompanionActor: until bFighterIndex is set, keeps Lumos's glow on the
// caster's wand (anchor 0) and in its draw layer.
void TickFieldSpellCompanionActor(Actor *companion)
{
    IntPoint anchor;

    if (companion->wSubtype == FieldSpellLumos && companion->bFighterIndex == 0)
    {
        GetActorFlippedAnchor(companion->pLinkedActor, 0, &anchor);
        SnapActorPosition(companion, companion->pLinkedActor->pos.x + (anchor.x << 16),
                          companion->pLinkedActor->pos.y + (anchor.y << 16));
        companion->oam.priority = companion->pLinkedActor->oam.priority;
    }
}
