#include "types.h"
#include "dialog.h"
#include "font.h"
#include "text.h"
#include "text_actor.h"
#include "items.h"
#include "items_list.h"

void DrawItemListRowText(s32 row, u32 highlighted)
{
    s32 item;
    s32 slot;
    u32 color;
    u32 textId;
    u8 *pText;
    u32 hasLine2;
    s32 i;

    item = row + g_bItemListScroll;
    slot = ITEM_LIST_INCOMING_SLOT;
    if (row >= 0 && row < g_ItemList.bRowCount)
        slot = row;

    if (g_ItemList.nCharacter == ITEM_LIST_NO_CHARACTER || g_ItemList.adwItems[item] == ITEM_REMOVE
        || CanFighterEquipItem(g_ItemList.nCharacter, g_ItemList.adwItems[item]))
        color = highlighted ? 4 : 1;
    else
        color = 2;

    SelectTextFont(1, color, 0);
    SetTextMacro1String(GetDialogText(GetRewardNameTextId(g_ItemList.adwItems[item])));
    if (g_ItemList.adwItems[item] == ITEM_REMOVE)
        textId = 0x3FD;  // "Remove"
    else
    {
        switch (g_ItemList.dwTextMode)
        {
        case 1:
            SetTextMacro2Number(GetItemQuantity(g_ItemList.adwItems[item]));
            textId = 0x663;  // "@1 (x@2)"
            break;
        case 0:
            textId = 0x8F7;  // "@1"
            break;
        default:
            textId = 0;
            break;
        }
    }

    pText = GetDialogText(textId);
    pText = ExpandTextMacros(g_pDialogMacroExpandBuffer, pText, 0x400);
    InsertTextLineBreaks(pText, 0xD5 - g_ItemList.nX);
    SetTextActorString(g_ItemList.apTextLine1[slot], pText);

    hasLine2 = 0;
    for (i = 0; pText[i] != '\0'; i++)
    {
        if (pText[i] == '\n')
        {
            hasLine2 = 1;
            pText = &pText[i] + 1;
            break;
        }
    }

    if (hasLine2)
        SetTextActorString(g_ItemList.apTextLine2[slot], pText);
    else
        g_ItemList.apTextLine2[slot]->dwFlags &= ~ActorFlagVisible;
}
