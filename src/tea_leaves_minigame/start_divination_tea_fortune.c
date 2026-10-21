#include "types.h"
#include "actor.h"
#include "modes.h"
#include "tea_leaves_minigame.h"
#include "screen_transitions.h"
#include "gen/graphics/overworld.h"

void StartDivinationTeaFortune(void)
{
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_DivinationTea.apCupActors); i++)
        g_DivinationTea.apCupActors[i]->dwFlags |= ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;

    SetAlphaBlendTargets(0, 0x12);
    SetAlphaBlendCoefficients(0, 0x10);
    g_GameModeStackContext.dwModeState = DivinationTeaStateFadeIn;
    g_DivinationTea.dwFadeStep = 0;

    for (i = 0; i < ARRAY_COUNT(g_DivinationTea.apFadeActors); i++)
    {
        g_DivinationTea.apFadeActors[i] = SpawnActor(i, i * 32, 4, (const ObjPalette *)gDivinationTeaTextFramePalette);
        SetActorSprite(g_DivinationTea.apFadeActors[i], &g_DivinationTeaTextFrameAsset);
        SetActorAnimFrame(g_DivinationTea.apFadeActors[i], 1);
        g_DivinationTea.apFadeActors[i]->oam.priority = 1;
        g_DivinationTea.apFadeActors[i]->oam.objMode = 1;
    }
}
