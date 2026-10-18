#include "arm_routines.h"
#include "actor.h"

// Sorts an array of Actor pointers into draw order. ARM-mode; InitActorPool
// copies it into IWRAM (SortActorsByDepthIwram), and only that copy runs.
//
// Shell sort with the gaps 21, 7, 3, 1, packed byte-wise into one constant
// and peeled off by shifting it left 8 bits each pass. The key sorts by
// draw layer (oam.priority), then bDepthSortBias, then descending screen Y;
// the 0x10000 keeps the Y subtraction from borrowing into the bias byte.
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

// Empty and never referenced. CheckActorCollisions is followed by the same
// lone return, and both IWRAM copies stop just short of it, which fits an
// end-of-routine marker whose address once sized the copy.
void SortActorsByDepthEnd_candidate(void)
{
}
