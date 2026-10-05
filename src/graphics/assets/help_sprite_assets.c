#include "types.h"
#include "graphics/object.h"
#include "gen/graphics/menus.h"

// Help screen sprites, drawn by sub_08039020 with the palette of the same
// index; see docs/formats/graphics.md.
const ObjectAssetRecord g_aHelpSpriteAssets[22] = {
    { (void *)gMenuSprite006Tiles, (void *)gMenuSprite006Frames, (void *)gMenuSprite006Palette, 0 },  // 0
    { (void *)gItem063Tiles, (void *)gItem063Frames, (void *)gItem063Palette, 0 },  // 1
    { (void *)gItem068Tiles, (void *)gItem068Frames, (void *)gItem068Palette, 0 },  // 2
    { (void *)gItem070Tiles, (void *)gItem070Frames, (void *)gItem070Palette, 0 },  // 3
    { (void *)gItem069Tiles, (void *)gItem069Frames, (void *)gItem069Palette, 0 },  // 4
    { (void *)gItem072Tiles, (void *)gItem072Frames, (void *)gItem072Palette, 0 },  // 5
    { (void *)gItem074Tiles, (void *)gItem074Frames, (void *)gItem074Palette, 0 },  // 6
    { (void *)gItem071Tiles, (void *)gItem071Frames, (void *)gItem071Palette, 0 },  // 7
    { (void *)gItem073Tiles, (void *)gItem073Frames, (void *)gItem073Palette, 0 },  // 8
    { (void *)gItem078Tiles, (void *)gItem078Frames, (void *)gItem078Palette, 0 },  // 9
    { (void *)gItem064Tiles, (void *)gItem064Frames, (void *)gItem064Palette, 0 },  // 10
    { (void *)gItem065Tiles, (void *)gItem065Frames, (void *)gItem065Palette, 0 },  // 11
    { (void *)gItem066Tiles, (void *)gItem066Frames, (void *)gItem066Palette, 0 },  // 12
    { (void *)gItem067Tiles, (void *)gItem067Frames, (void *)gItem067Palette, 0 },  // 13
    { (void *)gHelp001Tiles, (void *)gHelp001Frames, (void *)gHelp001Palette, 0 },  // 14
    { (void *)gItem075Tiles, (void *)gItem075Frames, (void *)gItem075Palette, 0 },  // 15
    { (void *)gItem057Tiles, (void *)gItem057Frames, (void *)gItem057Palette, 0 },  // 16
    { (void *)gItem058Tiles, (void *)gItem058Frames, (void *)gItem058Palette, 0 },  // 17
    { (void *)gItem059Tiles, (void *)gItem059Frames, (void *)gItem059Palette, 0 },  // 18
    { (void *)gItem060Tiles, (void *)gItem060Frames, (void *)gItem060Palette, 0 },  // 19
    { (void *)gItem061Tiles, (void *)gItem061Frames, (void *)gItem061Palette, 0 },  // 20
    { (void *)gItem062Tiles, (void *)gItem062Frames, (void *)gItem062Palette, 0 },  // 21
};

const void *const g_apHelpSpritePalettes[22] = {
    gMenuSprite006Palette,
    gItem063Palette,
    gItem068Palette,
    gItem070Palette,
    gItem069Palette,
    gItem072Palette,
    gItem074Palette,
    gItem071Palette,
    gItem073Palette,
    gItem078Palette,
    gItem064Palette,
    gItem065Palette,
    gItem066Palette,
    gItem067Palette,
    gHelp001Palette,
    gItem075Palette,
    gItem057Palette,
    gItem058Palette,
    gItem059Palette,
    gItem060Palette,
    gItem061Palette,
    gItem062Palette,
};
