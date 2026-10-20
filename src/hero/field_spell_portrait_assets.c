#include "actor.h"
#include "gen/graphics/overworld.h"
#include "hero.h"

const ActorAssetRecord g_aFieldSpellPortraitAssets[4] = {
    { (void *)gFieldSpellPortraitHarryTiles, (void *)gFieldSpellPortraitHarryFrames, (void *)gFieldSpellPortraitHarryPalette, 0 },
    { (void *)gFieldSpellPortraitHermioneTiles, (void *)gFieldSpellPortraitHermioneFrames, (void *)gFieldSpellPortraitHermionePalette, 0 },
    { (void *)gFieldSpellPortraitRonTiles, (void *)gFieldSpellPortraitRonFrames, (void *)gFieldSpellPortraitRonPalette, 0 },
    { (void *)gFieldSpellPortraitRonTiles, (void *)gFieldSpellPortraitRonFrames, (void *)gFieldSpellPortraitRonPalette, 0 },
};

const ActorAssetRecord g_MapNamePopupAsset = {
    (void *)gMapNamePopupBarTiles, (void *)gMapNamePopupBarFrames, NULL, 0,
};
