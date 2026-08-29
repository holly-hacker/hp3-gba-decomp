#include "types.h"

extern const u32 g_aShopStockMisc[];
extern const u32 g_aShopStockBelts[];
extern const u32 g_aShopStockCharms[];
extern const u32 g_aShopStockGloves[];
extern const u32 g_aShopStockBoots[];
extern const u32 g_aShopStockHats[];
extern const u32 g_aShopStockCloaks[];

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
