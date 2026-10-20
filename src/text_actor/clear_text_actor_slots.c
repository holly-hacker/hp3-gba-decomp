#include "types.h"
#include "text_actor.h"

// Unreferenced.
void ClearTextActorSlots(void)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_apTextActors); i++)
        g_apTextActors[i] = NULL;
}
