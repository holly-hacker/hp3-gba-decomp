#include "types.h"
#include "shop.h"
#include "graphics/object_anim.h"
#include "gen/graphics/overworld.h"

const ObjectAssetRecord g_aShopMainMenuIcons[3] = {
    { (void *)gShopIconBuyTiles, (void *)gShopIconBuyFrames, (const ObjPalette *)gShopIconBuyPalette },
    { (void *)gShopIconSellTiles, (void *)gShopIconSellFrames, (const ObjPalette *)gShopIconSellPalette },
    { (void *)gShopIconExitTiles, (void *)gShopIconExitFrames, (const ObjPalette *)gShopIconExitPalette },
};

const ObjectAssetRecord g_aShopCategoryIcons[7] = {
    { (void *)gShopIconBuyTiles, (void *)gShopIconBuyFrames, (const ObjPalette *)gShopIconBuyPalette },
    { (void *)gShopIconBuyTiles, (void *)gShopIconBuyFrames, (const ObjPalette *)gShopIconBuyPalette },
    { (void *)gShopIconBuyTiles, (void *)gShopIconBuyFrames, (const ObjPalette *)gShopIconBuyPalette },
    { (void *)gShopIconBuyTiles, (void *)gShopIconBuyFrames, (const ObjPalette *)gShopIconBuyPalette },
    { (void *)gShopIconBuyTiles, (void *)gShopIconBuyFrames, (const ObjPalette *)gShopIconBuyPalette },
    { (void *)gShopIconBuyTiles, (void *)gShopIconBuyFrames, (const ObjPalette *)gShopIconBuyPalette },
    { (void *)gShopIconBuyTiles, (void *)gShopIconBuyFrames, (const ObjPalette *)gShopIconBuyPalette },
};

const u8 g_abShopMenuIconAnim[2] = { ANIM_FRAME(0, 0) };

const u32 g_dwFredAndGeorgesShopBg1Control = 0x1E05;

const ShopMainMenuTextIds g_ShopMainMenuTextIds = { {
    0x53B,  // "Buy"
    0x53C,  // "Sell"
    0x53D,  // "Exit"
} };
