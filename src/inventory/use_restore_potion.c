#include "types.h"
#include "battle/battle.h"
#include "font.h"
#include "inventory.h"
#include "inventory_inline.h"

// Restores the member's Stamina or Magic with up to `quantity` of the potion,
// using only as many as needed, and returns the result message.
u32 UseRestorePotion(u8 character, s32 item, s32 quantity)
{
    BattleFighter *pParty;
    BattleFighter *pFighter;
    s32 amount;
    s32 restored;
    s32 used;

    switch (g_pItemTable[item].stats.potion.nEffect)
    {
    case PotionEffectStamina:
        amount = g_pItemTable[item].stats.potion.nMagnitude * quantity;
        pParty = g_aPartyMasterStats;
        pFighter = &pParty[character];
        if (pFighter->wHp + amount > pFighter->wHp_max)
            restored = pFighter->wHp_max - pFighter->wHp;
        else
            restored = amount;
        SetTextMacro1String(GetPartyMemberName(character));
        if (restored == 0)
            break;

        used = restored / g_pItemTable[item].stats.potion.nMagnitude;
        if (restored % g_pItemTable[item].stats.potion.nMagnitude)
            used++;
        RemoveItemsInline(item, used);
        pFighter->wHp += restored;
        SetTextMacro2Number(restored);
        return 0x400;  // "@1 is feeling better now, and has recovered @2 Stamina Points."

    case PotionEffectMagic:
        amount = g_pItemTable[item].stats.potion.nMagnitude * quantity;
        pParty = g_aPartyMasterStats;
        pFighter = &pParty[character];
        if (pFighter->wMp + amount > pFighter->wMp_max)
            restored = pFighter->wMp_max - pFighter->wMp;
        else
            restored = amount;
        SetTextMacro1String(GetPartyMemberName(character));
        if (restored == 0)
            break;

        used = restored / g_pItemTable[item].stats.potion.nMagnitude;
        if (restored % g_pItemTable[item].stats.potion.nMagnitude)
            used++;
        RemoveItemsInline(item, used);
        pFighter->wMp += restored;
        SetTextMacro2Number(restored);
        return 0x401;  // "@1 is feeling better now, and has recovered @2 Magic Points."

    default:
        return 0;
    }

    return 0x403;  // "@1 is at full strength!"
}
