#include "types.h"
#include "shop.h"

// Per-tab pointer table into src/data/shop_stock.c
const u32 *const g_apShopStockLists[7] = {
    g_aShopStockMisc,
    g_aShopStockBelts,
    g_aShopStockCharms,
    g_aShopStockGloves,
    g_aShopStockBoots,
    g_aShopStockHats,
    g_aShopStockCloaks,
};
