#include "pscreen_information.h"

void SpawnHelpPageSprite(u32 x, u32 y, u32 assetIndex)
{
    u32 slot = g_HelpState.dwSpriteCount;

    g_HelpState.dwSpriteCount = slot + 1;
    g_HelpState.apSprites[slot] = SpawnActor(assetIndex, x, y, g_apHelpSpritePalettes[assetIndex]);
    g_HelpState.apSprites[slot]->oam.objMode = 1;
    SetActorSprite(g_HelpState.apSprites[slot], &g_aHelpSpriteAssets[assetIndex]);
    if (x == 0xB4)
        g_HelpState.apSprites[slot]->oam.hFlip = 1;
}
