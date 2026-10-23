#include "arm_routines.h"
#include "actor.h"
#include "modes.h"

// Tests each active box of every queued actor against box 0 of each later
// actor and, on overlap in the overworld, calls both actors' callbacks for
// that box slot. Pairs that both set ActorFlagCollisionGroup are
// skipped.
void CheckActorCollisions(s32 count, Actor **actors)
{
    s32 i;
    s32 j;
    s32 slot;
    Actor *actor;
    Actor *other;
    s32 offsets;
    s32 origin;
    s32 top;
    s32 bottom;
    s32 left;
    s32 right;
    s32 otherTop;
    s32 otherBottom;
    s32 otherLeft;
    s32 otherRight;

    for (i = 0; i < count; i++) {
        actor = actors[i];
        for (slot = 1; slot >= 0; slot--) {
            if ((actor->aCollisionBoxes + slot)->state.bState != 1)
                continue;

            offsets = (actor->aCollisionBoxes + slot)->offsets.dwPackedOffsets;
            origin = (s16)(actor->posPrev.y >> 16);
            if (actor->oam.vFlip) {
                top = origin - (offsets >> 24);
                offsets <<= 8;
                bottom = origin - (offsets >> 24);
            }
            else {
                bottom = origin + (offsets >> 24);
                offsets <<= 8;
                top = origin + (offsets >> 24);
            }
            offsets <<= 8;
            origin = (s16)(actor->posPrev.x >> 16);
            if (actor->oam.hFlip) {
                left = origin - (offsets >> 24);
                offsets <<= 8;
                right = origin - (offsets >> 24);
            }
            else {
                right = origin + (offsets >> 24);
                offsets <<= 8;
                left = origin + (offsets >> 24);
            }

            for (j = i + 1; j < count; j++) {
                other = actors[j];
                if (actor->dwFlags & other->dwFlags & ActorFlagCollisionGroup)
                    continue;
                if (other->aCollisionBoxes[0].state.bState != 1)
                    continue;

                offsets = other->aCollisionBoxes[0].offsets.dwPackedOffsets;
                origin = (s16)(other->posPrev.y >> 16);
                if (other->oam.vFlip) {
                    otherTop = origin - (offsets >> 24);
                    offsets <<= 8;
                    otherBottom = origin - (offsets >> 24);
                }
                else {
                    otherBottom = origin + (offsets >> 24);
                    offsets <<= 8;
                    otherTop = origin + (offsets >> 24);
                }
                offsets <<= 8;
                origin = (s16)(other->posPrev.x >> 16);
                if (other->oam.hFlip) {
                    otherLeft = origin - (offsets >> 24);
                    offsets <<= 8;
                    otherRight = origin - (offsets >> 24);
                }
                else {
                    otherRight = origin + (offsets >> 24);
                    offsets <<= 8;
                    otherLeft = origin + (offsets >> 24);
                }

                if (right >= otherLeft && otherRight >= left && bottom >= otherTop
                    && otherBottom >= top && g_GameModeStackContext.dwCurrentGameMode == Overworld) {
                    if (other->apfnCollisionCallback[slot])
                        other->apfnCollisionCallback[slot](other, actor);
                    if (actor->apfnCollisionCallback[slot])
                        actor->apfnCollisionCallback[slot](actor, other);
                }
            }
        }
    }
}

// End marker; see SortActorsByDepthEnd.
void CheckActorCollisionsEnd(void)
{
}
