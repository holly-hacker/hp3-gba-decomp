#include "arm_routines.h"
#include "actor.h"

// Shell sort (gaps 21, 7, 3, 1) into draw order: by oam.priority, then
// bDepthSortBias, then descending screen Y.
void SortActorsByDepth(Actor **actors, u32 count)
{
    u32 gaps = 0x15070301;

    do {
        u32 gap = gaps >> 24;
        u32 i, j;

        for (i = gap; i < count; i++) {
            Actor *actor = actors[i];
            u32 key = actor->oam.priority << 24;

            key += actor->bDepthSortBias << 16;
            key += 0x10000 - (s16)(actor->posPrev.y >> 16);
            j = i;
            while (j >= gap) {
                u32 k = j - gap;
                Actor *other = actors[k];

                if (key >= (other->oam.priority << 24) + (other->bDepthSortBias << 16)
                               + (0x10000 - (s16)(other->posPrev.y >> 16)))
                    break;
                actors[j] = other;
                j = k;
            }
            actors[j] = actor;
        }
        gaps <<= 8;
    } while (gaps != 0);
}

// End marker: never referenced, but InitActorPool's IWRAM copy of
// SortActorsByDepth is exactly as long as the code up to it.
void SortActorsByDepthEnd(void)
{
}
