#include "pscreen_character.h"
#include "gen/graphics/overworld.h"

// Harry, Hermione and Ron (FighterType order) with their own palettes, then
// one more sprite; no reference found.
const ActorAssetRecord g_aUnusedPartyAssetRecords[4] = {
    { (void *)gHarryWalkTiles, (void *)gHarryWalkFrames, (void *)gHarryWalkPalette, 0 },
    { (void *)gActorSprite2_009Tiles, (void *)gActorSprite2_009Frames, (void *)gActorSprite2_009Palette, 0 },
    { (void *)gActorSprite2_008Tiles, (void *)gActorSprite2_008Frames, (void *)gActorSprite2_008Palette, 0 },
    { (void *)gActorSprite024Tiles, (void *)gActorSprite024Frames, (void *)gActorSprite024Palette, 0 },
};
