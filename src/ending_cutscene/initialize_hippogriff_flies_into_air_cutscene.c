#include "background.h"
#include "sound.h"
#include "gen/graphics/minigames/hippogriff.h"
#include "ending_cutscene.h"
#include "actor.h"
#include "gen/graphics/minigames/boggart.h"
#include "screen_transitions.h"

void InitializeHippogriffFliesIntoAirCutscene(void)
{
    ResetDisplayState(0);
    SetBgControl(0, g_dwHippogriffFliesIntoAirBg0Control);
    SetDispcntFlag(0x1000);
    LoadBgGraphic(0, gHippogriffFliesIntoAirGraphic, 0, 0, 0, 0);

    g_pHippogriffFliesIntoAirActor2 = SpawnActor(0, 0x30, 0xA8, (const ObjPalette *)gHippogriffFliesIntoAir2Palette);
    g_pHippogriffFliesIntoAirActor2->oam.priority = 2;
    SetActorSprite(g_pHippogriffFliesIntoAirActor2, &g_HippogriffFliesIntoAirAsset2);

    g_pHippogriffFliesIntoAirActor = SpawnActor(0, 0x78, 0x3C, (const ObjPalette *)gHippogriffFliesIntoAirPalette);
    g_pHippogriffFliesIntoAirActor->oam.priority = 2;
    SetActorSprite(g_pHippogriffFliesIntoAirActor, &g_HippogriffFliesIntoAirAsset);
    SetActorAffineTransform(g_pHippogriffFliesIntoAirActor, 0x18000, 0x18000, 0, 3);
    StartActorAffineScaleTween(g_pHippogriffFliesIntoAirActor, 0x10000, 0x10000, 0x64);
    StartActorMove(g_pHippogriffFliesIntoAirActor, 0xA00000, 0x280000, 0x15E);
    g_pHippogriffFliesIntoAirActor->dwStateTimer = 0x12C;

    PlayMusicModule(0x32);
    PlayScreenTransitionInByIndex(0x3F, 2);
}
