#include "types.h"
#include "actor.h"
#include "pouring_minigame.h"
#include "gen/graphics/overworld.h"

void SpawnServePumpkinJuicePuff(s32 x, s32 y)
{
    Actor *puff = SpawnActor(0, x, y, (const ObjPalette *)gOverworldSpellEffect020Palette);

    puff->oam.priority = 1;
    puff->pfnTick = TickServePumpkinJuicePuff;
    SetActorAnimData(puff, &g_ServePumpkinJuicePuffSprite, g_abServePumpkinJuicePuffAnim, 0);
    puff->bRoomActorKind_candidate = ServePumpkinJuiceActorPuff;
    puff->bActionState = 0;
}
