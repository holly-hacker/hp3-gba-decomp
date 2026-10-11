#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "cutscene/hippogriff_flies_into_air_cutscene.h"
#include "actor.h"
#include "gen/graphics/minigames/riddikulus.h"

void InitializeHippogriffFliesIntoAirCutscene(void)
{
    ResetDisplayState(0);
    SetBgControl(0, g_dwHippogriffFliesIntoAirBg0Control);
    SetDispcntFlag(0x1000);
    LoadBgGraphic(0, gHippogriffFliesIntoAirGraphic, 0, 0, 0, 0);

    g_pHippogriffFliesIntoAirObject2 = SpawnActor(0, 0x30, 0xA8, (const ObjPalette *)gHippogriffFliesIntoAir2Palette);
    g_pHippogriffFliesIntoAirObject2->oam.priority = 2;
    sub_08001690(g_pHippogriffFliesIntoAirObject2, &g_HippogriffFliesIntoAirAsset2);

    g_pHippogriffFliesIntoAirObject = SpawnActor(0, 0x78, 0x3C, (const ObjPalette *)gHippogriffFliesIntoAirPalette);
    g_pHippogriffFliesIntoAirObject->oam.priority = 2;
    sub_08001690(g_pHippogriffFliesIntoAirObject, &g_HippogriffFliesIntoAirAsset);
    SetActorAffineTransform(g_pHippogriffFliesIntoAirObject, 0x18000, 0x18000, 0, 3);
    StartActorAffineScaleTween(g_pHippogriffFliesIntoAirObject, 0x10000, 0x10000, 0x64);
    StartActorMove(g_pHippogriffFliesIntoAirObject, 0xA00000, 0x280000, 0x15E);
    g_pHippogriffFliesIntoAirObject->dwStateTimer = 0x12C;

    PlayMusicModule(0x32);
    PlayScreenTransitionInByIndex(0x3F, 2);
}
