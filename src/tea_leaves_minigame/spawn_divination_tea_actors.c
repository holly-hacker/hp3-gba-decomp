#include "types.h"
#include "actor.h"
#include "random.h"
#include "tea_leaves_minigame.h"
#include "hw/io_regs.h"
#include "gen/graphics/minigames/divination_tea.h"

void SpawnDivinationTeaActors(void)
{
    Actor *pActor;
    s32 frame;
    s32 angle;
    s32 distance;
    s32 radius;
    s32 i;

    g_DivinationTea.apCupActors[0] = SpawnActor(0, 0, 0, (const ObjPalette *)gDivinationTeaPalette001Palette);
    g_DivinationTea.apCupActors[1] = SpawnActor(0, SCREEN_WIDTH, 0, (const ObjPalette *)gDivinationTeaPalette001Palette);
    g_DivinationTea.apCupActors[1]->oam.hFlip = 1;
    g_DivinationTea.apCupActors[2] = SpawnActor(0, 0, SCREEN_HEIGHT, (const ObjPalette *)gDivinationTeaPalette001Palette);
    g_DivinationTea.apCupActors[2]->oam.vFlip = 1;
    g_DivinationTea.apCupActors[3] = SpawnActor(0, SCREEN_WIDTH, SCREEN_HEIGHT,
                                                (const ObjPalette *)gDivinationTeaPalette001Palette);
    g_DivinationTea.apCupActors[3]->oam.hFlip = 1;
    g_DivinationTea.apCupActors[3]->oam.vFlip = 1;

    for (i = 0; i < ARRAY_COUNT(g_DivinationTea.apCupActors); i++)
    {
        g_DivinationTea.apCupActors[i]->bActorPoolAuxSlot = 0;
        g_DivinationTea.apCupActors[i]->bDrawFlags |= ActorDrawFlagShareTiles;
        g_DivinationTea.apCupActors[i]->oam.objMode = 2;
        g_DivinationTea.apCupActors[i]->oam.priority = 2;
        SetActorAnimData(g_DivinationTea.apCupActors[i], &g_DivinationTeaCupSprite, g_DivinationTeaCupAnimData, 0);
    }

    // The cups draw the OBJ window: inside it only BG0, BG1 and sprites show, outside it
    // every layer and the blend.
    REG_DISPCNT |= DISPCNT_OBJWIN_ON;
    REG_WINOUT = 0x133F;

    for (i = 0; i < DIVINATION_TEA_LEAF_COUNT; i++)
    {
        pActor = SpawnActor(0, Mt19937RandRange(-20, 20) + 120, Mt19937RandRange(-20, 20) + 80,
                            (const ObjPalette *)gDivinationTeaPalette002Palette);
        g_DivinationTea.aLeaves[i].pActor = pActor;
        frame = i % 3;
        pActor->bActorPoolAuxSlot = frame + 1;
        g_DivinationTea.aLeaves[i].pActor->bDrawFlags |= ActorDrawFlagShareTiles;
        SetActorAssetRecord(g_DivinationTea.aLeaves[i].pActor, &g_DivinationTeaLeafSprite);
        SetActorAnimFrame(g_DivinationTea.aLeaves[i].pActor, frame);
        CopyOrbitParamsFromTable(g_DivinationTea.aLeaves[i].pActor, &g_DivinationTea.aLeaves[i].orbit);
        g_DivinationTea.aLeaves[i].pActor->oam.priority = 2;
        g_DivinationTea.aLeaves[i].wScaleX = g_DivinationTea.aLeaves[i].wScaleY = 0x100;
        g_DivinationTea.aLeaves[i].wAngle = Mt19937RandRange(0, 0x100) << 8;

        // Each leaf orbits its spawn point 30-70 pixels out, in either direction.
        distance = Mt19937RandRange(30, 70);
        radius = Mt19937RandMax(100) % 2 != 0 ? -distance : distance;
        g_DivinationTea.aLeaves[i].wOrbitSpeed = (Mt19937RandRange(0, 3) + 1) << 7;
        angle = Mt19937RandRange(0, 0x80);
        SetActorOrbitX(g_DivinationTea.aLeaves[i].pActor, angle, g_DivinationTea.aLeaves[i].wOrbitSpeed, radius);
        SetActorOrbitY(g_DivinationTea.aLeaves[i].pActor, angle, g_DivinationTea.aLeaves[i].wOrbitSpeed, radius);
    }
}
