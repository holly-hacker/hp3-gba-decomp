#include "types.h"
#include "actor.h"
#include "gen/graphics/overworld.h"
#include "landmarks.h"
#include "modes.h"

void SpawnUnusedHogwartsMapEntryActors(void)
{
    s32 i;

    for (i = 0; i < UNUSED_HOGWARTS_MAP_ENTRY_COUNT; i++)
    {
        g_apUnusedHogwartsMapActors[i] = SpawnActor(i + 10, 0xDA, i * 16 + 8,
                                                    (const ObjPalette *)gActorSprite015Palette);
        SetActorAssetRecord(g_apUnusedHogwartsMapActors[i], &g_UnusedHogwartsMapEntryGfx);
        SetActorAnimFrame(g_apUnusedHogwartsMapActors[i], i + 1);
    }

    SetActorMoveTargetWithDuration(
        g_apUnusedHogwartsMapActors[g_GameModeStackContext.dwCurrentGameModeArg2], 0xD2,
        (s16)(g_apUnusedHogwartsMapActors[g_GameModeStackContext.dwCurrentGameModeArg2]->pos.y >> 16), 3);
}
