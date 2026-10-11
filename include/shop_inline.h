#pragma once

#include "types.h"
#include "graphics/display.h"
#include "graphics/graphics.h"
#include "font.h"
#include "text.h"
#include "menu/dialog.h"
#include "menu/items_menu.h"
#include "menu/main_menu.h"
#include "shop.h"

// The ROM compiles these into TickShopFadeOut, MoveShopMainMenuCursor,
// MoveShopCategoryCursor and UpdateShopQuantitySelect and also keeps an
// out-of-line copy of each, as one translation unit with inline definitions
// would. The files that emit the out-of-line copies define the linkage macro
// as empty. ShowShopSellList comes before ShowShopMessage so that its call is
// not inlined, as in the ROM.
#ifndef SHOW_SHOP_SELL_LIST_LINKAGE
#define SHOW_SHOP_SELL_LIST_LINKAGE extern inline
#endif
#ifndef SHOW_SHOP_MESSAGE_LINKAGE
#define SHOW_SHOP_MESSAGE_LINKAGE extern inline
#endif
#ifndef SHOW_SHOP_BUY_LIST_LINKAGE
#define SHOW_SHOP_BUY_LIST_LINKAGE extern inline
#endif
#ifndef DRAW_SHOP_MAIN_MENU_ROW_LINKAGE
#define DRAW_SHOP_MAIN_MENU_ROW_LINKAGE extern inline
#endif
#ifndef DRAW_SHOP_CATEGORY_ROW_LINKAGE
#define DRAW_SHOP_CATEGORY_ROW_LINKAGE extern inline
#endif
#ifndef DRAW_SHOP_QUANTITY_LINKAGE
#define DRAW_SHOP_QUANTITY_LINKAGE extern inline
#endif
#ifndef EXIT_SHOP_MAIN_MENU_LINKAGE
#define EXIT_SHOP_MAIN_MENU_LINKAGE extern inline
#endif
#ifndef EXIT_SHOP_CATEGORY_MENU_LINKAGE
#define EXIT_SHOP_CATEGORY_MENU_LINKAGE extern inline
#endif
#ifndef EXIT_SHOP_SELL_LIST_LINKAGE
#define EXIT_SHOP_SELL_LIST_LINKAGE extern inline
#endif
#ifndef EXIT_SHOP_BUY_LIST_LINKAGE
#define EXIT_SHOP_BUY_LIST_LINKAGE extern inline
#endif
#ifndef EXIT_SHOP_QUANTITY_SELECT_LINKAGE
#define EXIT_SHOP_QUANTITY_SELECT_LINKAGE extern inline
#endif
#ifndef EXIT_SHOP_MESSAGE_LINKAGE
#define EXIT_SHOP_MESSAGE_LINKAGE extern inline
#endif

SHOW_SHOP_MESSAGE_LINKAGE void ShowShopMessage(void);

SHOW_SHOP_SELL_LIST_LINKAGE void ShowShopSellList(void)
{
    g_FredAndGeorgesShop.dwHasListItems = OpenFilteredItemList(0xB, 0x26, 0x36, 1, 0, 3, -1);
    if (g_FredAndGeorgesShop.dwHasListItems == 0)
    {
        if (!g_FredAndGeorgesShop.bSoldItem)
        {
            g_FredAndGeorgesShop.dwMessageTextId = 0x544;  // "You have nothing worth selling..."
            ShowShopMessage();
            g_FredAndGeorgesShop.dwNextState = ShopStateMessage;
        }
        else
        {
            ShowShopMainMenu();
            g_FredAndGeorgesShop.dwNextState = ShopStateMainMenu;
        }
    }
    else
    {
        SetItemListCallbacks(DrawShopSellPrice, NULL);
        DrawShopSellPrice(GetItemListSelection());
    }
}

SHOW_SHOP_MESSAGE_LINKAGE void ShowShopMessage(void)
{
    u8 *text;

    SetTextTargetFromBgControl(g_dwFredAndGeorgesShopBg1Control);
    SelectTextFont(2, 0, -1);
    text = GetDialogText(g_FredAndGeorgesShop.dwMessageTextId);
    DrawTextLines(1, 0x78, 0x48, 0xB0, 0x20, &text, 1);
}

SHOW_SHOP_BUY_LIST_LINKAGE void ShowShopBuyList(void)
{
    DrawShopSickles();
    g_FredAndGeorgesShop.dwHasListItems = OpenItemListFromIds(g_apShopStockLists[g_FredAndGeorgesShop.bCategory], 0x26, 0x36, 0, 3);
    SetItemListCallbacks(DrawShopBuyPrice, NULL);
    DrawShopBuyPrice(GetItemListSelection());
}

DRAW_SHOP_MAIN_MENU_ROW_LINKAGE void DrawShopMainMenuRow(s32 row, u32 color)
{
    ShopMainMenuTextIds textIds = g_ShopMainMenuTextIds;
    u8 *text;

    SetTextTargetFromBgControl(g_dwFredAndGeorgesShopBg1Control);
    SelectTextFont(4, color, -1);
    text = GetDialogText(textIds.adwTextIds[row]);
    DrawTextLines(row * 32 + 1, 0x40, row * 16 + 0x20, 0xC0, 0x18, &text, 0);
}

DRAW_SHOP_CATEGORY_ROW_LINKAGE void DrawShopCategoryRow(s32 row, u32 color)
{
    u8 *text;

    SetTextTargetFromBgControl(g_dwFredAndGeorgesShopBg1Control);
    SelectTextFont(4, color, -1);
    text = GetDialogText(row + 0xA51);
    DrawTextLines(row * 32 + 1, 0x40, row * 16 + 0x20, 0xC0, 0x18, &text, 0);
}

DRAW_SHOP_QUANTITY_LINKAGE void DrawShopQuantity(void)
{
    u8 *text;

    ClearBgTilemapRect(1, 0, 0xC, 0x1E, 2);
    SetTextTargetFromBgControl(g_dwFredAndGeorgesShopBg1Control);
    SelectTextFont(2, 0, -1);
    SetTextMacro1Number(g_FredAndGeorgesShop.nQuantity);
    SetTextMacro2Number(g_FredAndGeorgesShop.nUnitPrice);
    SetTextMacro3Number(g_FredAndGeorgesShop.nQuantity * g_FredAndGeorgesShop.nUnitPrice);
    text = GetDialogText(0x545);  // "@1 (at @2 Sickles each) for a total of @3 Sickles."
    DrawTextLines(0x80, 0x78, 0x60, 0xC0, 0x10, &text, 1);
}

EXIT_SHOP_MAIN_MENU_LINKAGE void ExitShopMainMenu(void)
{
    s32 i;

    ClearBgTilemap(1);
    for (i = 0; i < 3; i++)
    {
        FreeObject(g_FredAndGeorgesShop.apRowObjects[i]);
        g_FredAndGeorgesShop.apRowObjects[i] = NULL;
    }
    ReleaseMenuCursor(g_FredAndGeorgesShop.pCursor);
    FreeAllParticleEmitters();
    FreeAllParticles();
    FreeObject(g_FredAndGeorgesShop.pCursor);
}

EXIT_SHOP_CATEGORY_MENU_LINKAGE void ExitShopCategoryMenu(void)
{
    s32 i;

    ClearBgTilemap(1);
    for (i = 0; i < 7; i++)
        FreeObject(g_FredAndGeorgesShop.apRowObjects[i]);
    ReleaseMenuCursor(g_FredAndGeorgesShop.pCursor);
    FreeAllParticleEmitters();
    FreeAllParticles();
    FreeObject(g_FredAndGeorgesShop.pCursor);
}

EXIT_SHOP_SELL_LIST_LINKAGE void ExitShopSellList(void)
{
    ClearBgTilemap(1);
    if (g_FredAndGeorgesShop.dwHasListItems)
        CloseItemList();
    ClearResourceCacheSlots();
}

EXIT_SHOP_BUY_LIST_LINKAGE void ExitShopBuyList(void)
{
    ClearBgTilemap(1);
    if (g_FredAndGeorgesShop.dwHasListItems)
        CloseItemList();
    ClearResourceCacheSlots();
}

EXIT_SHOP_QUANTITY_SELECT_LINKAGE void ExitShopQuantitySelect(void)
{
    ClearBgTilemap(1);
    FreeObject(g_FredAndGeorgesShop.pItemIcon);
    FreeObject(g_FredAndGeorgesShop.pLeftArrow);
    FreeObject(g_FredAndGeorgesShop.pRightArrow);
}

EXIT_SHOP_MESSAGE_LINKAGE void ExitShopMessage(void)
{
    ClearBgTilemap(1);
}
