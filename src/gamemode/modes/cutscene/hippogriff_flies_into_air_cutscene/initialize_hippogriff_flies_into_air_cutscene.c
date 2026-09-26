#include "types.h"
#include "audio.h"
#include "display.h"
#include "hippogriff_flies_into_air_cutscene.h"
#include "object.h"

void InitializeHippogriffFliesIntoAirCutscene(void)
{
    ResetDisplayState(0);
    SetBgControl(0, g_dwHippogriffFliesIntoAirBg0Control);
    SetDispcntFlag(0x1000);
    LoadBgGraphic(0, g_HippogriffFliesIntoAirGraphic, 0, 0, 0, 0);

    g_pHippogriffFliesIntoAirObject2 = SpawnObject(0, 0x30, 0xA8, g_HippogriffFliesIntoAirSpawnData2);
    g_pHippogriffFliesIntoAirObject2->oam.priority = 2;
    sub_08001690(g_pHippogriffFliesIntoAirObject2, g_HippogriffFliesIntoAirAsset2);

    g_pHippogriffFliesIntoAirObject = SpawnObject(0, 0x78, 0x3C, g_HippogriffFliesIntoAirSpawnData);
    g_pHippogriffFliesIntoAirObject->oam.priority = 2;
    sub_08001690(g_pHippogriffFliesIntoAirObject, g_HippogriffFliesIntoAirAsset);
    SetObjectAffineTransform(g_pHippogriffFliesIntoAirObject, 0x18000, 0x18000, 0, 3);
    StartObjectAffineScaleTween(g_pHippogriffFliesIntoAirObject, 0x10000, 0x10000, 0x64);
    StartObjectMove(g_pHippogriffFliesIntoAirObject, 0xA00000, 0x280000, 0x15E);
    g_pHippogriffFliesIntoAirObject->dwStateTimer = 0x12C;

    PlayMusicModule(0x32);
    PlayScreenTransitionInByIndex(0x3F, 2);
}
