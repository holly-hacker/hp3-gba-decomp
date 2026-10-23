#pragma once

#include "actor.h"
#include "text_actor.h"

// The text actor setup SpawnTextActorLines, SpawnTextActor and
// SpawnUnslottedTextActor share: a visible 4bpp horizontal sprite strip
// drawing *ppText.
static inline Actor *AllocTextActor(const u8 **ppText)
{
    Actor *pActor;

    pActor = AllocActorOfType(ActorType_Text);
    pActor->dwFlags = ActorFlagVisible | ActorFlagHasTickLogic;
    pActor->bOamStrip = 1;
    pActor->oam.tileNum = pActor->wVramTileAllocId;
    pActor->oam.shape = 1;
    DrawTextActorText(pActor, ppText);
    return pActor;
}
