#include "types.h"
#include "graphics/object.h"
#include "gen/graphics/overworld.h"
#include "overworld/overworld.h"

// Indexed by party character id; see SetPartyMemberAnim.
const ObjectAssetRecord g_aPartyWalkAssets[PARTY_CHARACTER_COUNT] = {
    { (void *)gOverworldPlayer004Tiles, (void *)gOverworldPlayer004Frames, (void *)gOverworldPlayer004Palette, 0 },
    { (void *)gOverworldPlayer005Tiles, (void *)gOverworldPlayer005Frames, (void *)gOverworldPlayer005Palette, 0 },
    { (void *)gOverworldPlayer006Tiles, (void *)gOverworldPlayer006Frames, (void *)gOverworldPlayer006Palette, 0 },
    { (void *)gOverworldPlayer002Tiles, (void *)gOverworldPlayer002Frames, (void *)gOverworldPlayer004Palette, 0 },
    { (void *)gOverworldPlayer007Tiles, (void *)gOverworldPlayer007Frames, (void *)gOverworldPlayer007Palette, 0 },
    { (void *)gOverworldPlayer008Tiles, (void *)gOverworldPlayer008Frames, (void *)gOverworldPlayer004Palette, 0 },
    { (void *)gOverworldPlayer009Tiles, (void *)gOverworldPlayer009Frames, (void *)gOverworldPlayer005Palette, 0 },
    { (void *)gOverworldPlayer010Tiles, (void *)gOverworldPlayer010Frames, (void *)gOverworldPlayer006Palette, 0 },
    { (void *)gObjectSprite2_004Tiles, (void *)gObjectSprite2_004Frames, (void *)gObjectSprite2_004Palette, 0 },
};

const ObjectAssetRecord g_aPartyAnim3Assets[PARTY_CHARACTER_COUNT] = {
    { (void *)gOverworldPlayer011Tiles, (void *)gOverworldPlayer011Frames, (void *)gOverworldPlayer011Palette, 0 },
    { (void *)gOverworldPlayer012Tiles, (void *)gOverworldPlayer012Frames, (void *)gOverworldPlayer011Palette, 0 },
    { (void *)gOverworldPlayer013Tiles, (void *)gOverworldPlayer013Frames, (void *)gOverworldPlayer011Palette, 0 },
    { (void *)gOverworldPlayer011Tiles, (void *)gOverworldPlayer011Frames, (void *)gOverworldPlayer011Palette, 0 },
    { (void *)gOverworldPlayer011Tiles, (void *)gOverworldPlayer011Frames, (void *)gOverworldPlayer011Palette, 0 },
    { (void *)gOverworldPlayer011Tiles, (void *)gOverworldPlayer011Frames, (void *)gOverworldPlayer011Palette, 0 },
    { (void *)gOverworldPlayer012Tiles, (void *)gOverworldPlayer012Frames, (void *)gOverworldPlayer011Palette, 0 },
    { (void *)gOverworldPlayer013Tiles, (void *)gOverworldPlayer013Frames, (void *)gOverworldPlayer011Palette, 0 },
    { (void *)gObjectSprite2_004Tiles, (void *)gObjectSprite2_004Frames, (void *)gObjectSprite2_004Palette, 0 },
};

const ObjectAssetRecord g_aPartyCastAssets[PARTY_CHARACTER_COUNT] = {
    { (void *)gOverworldPlayer001Tiles, (void *)gOverworldPlayer001Frames, (void *)gOverworldPlayer004Palette, 0 },
    { (void *)gOverworldPlayer014Tiles, (void *)gOverworldPlayer014Frames, (void *)gOverworldPlayer005Palette, 0 },
    { (void *)gOverworldPlayer015Tiles, (void *)gOverworldPlayer015Frames, (void *)gOverworldPlayer006Palette, 0 },
    { (void *)gOverworldPlayer001Tiles, (void *)gOverworldPlayer001Frames, (void *)gOverworldPlayer004Palette, 0 },
    { (void *)gOverworldPlayer001Tiles, (void *)gOverworldPlayer001Frames, (void *)gOverworldPlayer004Palette, 0 },
    { (void *)gOverworldPlayer001Tiles, (void *)gOverworldPlayer001Frames, (void *)gOverworldPlayer004Palette, 0 },
    { (void *)gOverworldPlayer014Tiles, (void *)gOverworldPlayer014Frames, (void *)gOverworldPlayer005Palette, 0 },
    { (void *)gOverworldPlayer015Tiles, (void *)gOverworldPlayer015Frames, (void *)gOverworldPlayer006Palette, 0 },
    { (void *)gObjectSprite2_004Tiles, (void *)gObjectSprite2_004Frames, (void *)gObjectSprite2_004Palette, 0 },
};

const ObjectAssetRecord g_aPartyAnim4Assets[PARTY_CHARACTER_COUNT] = {
    { (void *)gOverworldPlayer016Tiles, (void *)gOverworldPlayer016Frames, (void *)gOverworldPlayer004Palette, 0 },
    { (void *)gOverworldPlayer017Tiles, (void *)gOverworldPlayer017Frames, (void *)gOverworldPlayer005Palette, 0 },
    { (void *)gOverworldPlayer018Tiles, (void *)gOverworldPlayer018Frames, (void *)gOverworldPlayer006Palette, 0 },
    { (void *)gOverworldPlayer016Tiles, (void *)gOverworldPlayer016Frames, (void *)gOverworldPlayer004Palette, 0 },
    { (void *)gOverworldPlayer016Tiles, (void *)gOverworldPlayer016Frames, (void *)gOverworldPlayer004Palette, 0 },
    { (void *)gOverworldPlayer016Tiles, (void *)gOverworldPlayer016Frames, (void *)gOverworldPlayer004Palette, 0 },
    { (void *)gOverworldPlayer017Tiles, (void *)gOverworldPlayer017Frames, (void *)gOverworldPlayer005Palette, 0 },
    { (void *)gOverworldPlayer018Tiles, (void *)gOverworldPlayer018Frames, (void *)gOverworldPlayer006Palette, 0 },
    { (void *)gObjectSprite2_004Tiles, (void *)gObjectSprite2_004Frames, (void *)gObjectSprite2_004Palette, 0 },
};
