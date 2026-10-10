#pragma once

#include "types.h"
#include "graphics/object.h"

// Shop tab stock lists, defined in src/shop/shop_stock.c and consumed as a
// pointer table by src/shop/shop_stock_lists.c. See docs/formats/items.md's
// "Shop prices" section.

extern const u32 g_aShopStockMisc[];
extern const u32 g_aShopStockBelts[];
extern const u32 g_aShopStockCharms[];
extern const u32 g_aShopStockGloves[];
extern const u32 g_aShopStockBoots[];
extern const u32 g_aShopStockHats[];
extern const u32 g_aShopStockCloaks[];
extern const u32 *const g_apShopStockLists[7];  // indexed by FredAndGeorgesShopState.bCategory

// Rolls one Folio Universitas card for a bought Chocolate Frogs and adds it to
// the collection; returns the rolled reward id.
u32 GrantRandomChocolateFrogCard(void);

// Game mode 0x2E (FredAndGeorgesShop), the Weasleys' Wizard Wheezes shop,
// src/store/. dwModeState is a ShopState; screen
// changes fade BG1 out (ShopStateFadeOut), swap the screens and fade back in
// (ShopStateFadeIn).
typedef enum {
    ShopStateFadeOut    = 1,
    ShopStateFadeIn     = 2,
    ShopStateMainMenu   = 4,   // Buy / Sell / Exit
    ShopStateCategories = 6,   // the 7 buy tabs
    ShopStateSellList   = 8,
    ShopStateBuyList    = 10,
    ShopStateQuantity   = 12,
    ShopStateMessage    = 14,
} ShopState;

// StartShopScreenTransition's screen argument.
typedef enum {
    ShopScreenMainMenu,
    ShopScreenCategories,
    ShopScreenSellList,
    ShopScreenBuyList,
    ShopScreenQuantity,
    ShopScreenMessage,
} ShopScreen;

// dwBuyItem/dwSellItem of the side not being traded.
#define SHOP_NO_ITEM 0x85

// Chocolate Frogs: buying them grants collector's cards instead of the item,
// so they are not capped at MAX_ITEM_QUANTITY.
#define SHOP_ITEM_CHOCOLATE_FROGS 0x46

typedef struct FredAndGeorgesShopState {
    u32 dwPrevState;            // 0x00; ShopState faded out of
    u32 dwNextState;            // 0x04; ShopState faded into
    s8 bCursor;                 // 0x08; selected main menu or category row
    s8 bCategory;               // 0x09; chosen buy tab
    Object *pCursor;            // 0x0C; main menu/category cursor
    u32 dwHasListItems;         // 0x10; nonzero when the sell/buy list is not empty
    u32 dwMessageTextId;        // 0x14; ShopStateMessage's text
    u32 dwBuyItem;              // 0x18; SHOP_NO_ITEM while selling
    u32 dwSellItem;             // 0x1C; SHOP_NO_ITEM while buying
    Object *apRowObjects[7];    // 0x20; icons beside the main menu/category rows
    Object *pItemIcon;          // 0x3C; quantity screen
    Object *pLeftArrow;         // 0x40
    Object *pRightArrow;        // 0x44
    ObjectGfxRecord itemIconGfx;  // 0x48
    s32 nQuantity;              // 0x50
    s32 nUnitPrice;             // 0x54
    u32 dwItem;                 // 0x58; item being traded
    u8 bSoldItem;               // 0x5C; set by a sale, so an emptied sell list returns to the main menu
} FredAndGeorgesShopState;
extern FredAndGeorgesShopState g_FredAndGeorgesShop;  // 0x03005AC8

extern const ObjectAssetRecord g_aShopMainMenuIcons[3];  // 0x0806BA4C
extern const ObjectAssetRecord g_aShopCategoryIcons[7];  // 0x0806BA7C
extern const u8 g_abShopMenuIconAnim[2];                 // 0x0806BAEC
extern const u32 g_dwFredAndGeorgesShopBg1Control;      // 0x0806BAF0

// Copied whole into a local by DrawShopMainMenuRow.
typedef struct {
    u32 adwTextIds[3];  // Buy, Sell, Exit
} ShopMainMenuTextIds;
extern const ShopMainMenuTextIds g_ShopMainMenuTextIds;  // 0x0806BAF4

// In ROM order, one per file under src/store/. Bodies that the ROM also
// inlines into callers live in shop_inline.h.
void ShowShopMainMenu(void);
void UpdateShopMainMenu(void);
void MoveShopMainMenuCursor(s32 row);
void ShowShopCategoryMenu(void);
void UpdateShopCategoryMenu(void);
void MoveShopCategoryCursor(s32 row);
void ShowShopQuantitySelect(void);
void UpdateShopQuantitySelect(void);
void TickShopFadeOut(void);
void InitializeFredAndGeorgesShop(void);
void UpdateFredAndGeorgesShop(void);
void ExitFredAndGeorgesShop(void);
void StartShopScreenTransition(ShopScreen screen);
void TickShopFadeIn(void);
void DrawShopSickles(void);
void ClearShopSicklesBox(void);
void TickShopMenuCursor(Object *pCursor);
void DrawShopMainMenuRow(s32 row, u32 color);
void ExitShopMainMenu(void);
void DrawShopCategoryRow(s32 row, u32 color);
void ExitShopCategoryMenu(void);
void ShowShopSellList(void);
void UpdateShopSellList(void);
void ExitShopSellList(void);
void DrawShopSellPrice(u32 item);
void ShowShopBuyList(void);
void UpdateShopBuyList(void);
void ExitShopBuyList(void);
void DrawShopBuyPrice(u32 item);
void DrawShopQuantity(void);
void ExitShopQuantitySelect(void);
void ShowShopMessage(void);
void UpdateShopMessage(void);
void ExitShopMessage(void);
