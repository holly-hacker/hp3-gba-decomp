#pragma once

#include "types.h"

// Shop tab stock lists, defined in src/data/shop_stock.c and consumed as a
// pointer table by src/data/shop_stock_lists.c. See docs/formats/items.md's
// "Shop prices" section.

extern const u32 g_aShopStockMisc[];
extern const u32 g_aShopStockBelts[];
extern const u32 g_aShopStockCharms[];
extern const u32 g_aShopStockGloves[];
extern const u32 g_aShopStockBoots[];
extern const u32 g_aShopStockHats[];
extern const u32 g_aShopStockCloaks[];
