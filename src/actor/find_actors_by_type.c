#include "types.h"
#include "actor.h"

// Collects up to maxCount active actors with the given wActorType and
// wCharacterId_candidate into out; returns how many it found.
u8 FindActorsByType(u8 type, u8 characterId, Actor **out, u8 maxCount)
{
    Actor *actor;
    Actor *next;
    u8 count;

    count = 0;
    actor = (Actor *)g_ActiveActorListState.pHead;
    while (actor != 0 && count < maxCount) {
        next = (Actor *)actor->node.pNext;
        if (actor->wActorType == type && actor->wCharacterId_candidate == characterId) {
            out[count] = actor;
            count++;
        }
        actor = next;
    }

    return count;
}
