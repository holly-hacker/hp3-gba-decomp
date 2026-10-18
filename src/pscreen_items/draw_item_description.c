#include "types.h"
#include "font.h"
#include "text.h"
#include "default_menu.h"
#include "pscreen_items.h"
#include "items.h"

void DrawItemDescription(u32 item)
{
    const u8 *text;

    ClearItemDescription();
    SetTextTargetFromBgControl(g_dwCommonBg2Control);
    SelectTextFont(2, 0, -1);

    // NOTE: an effect above PotionEffectParalysis (4) would leave text uninitialized.
    switch (GetPotionEffect(item))
    {
    case PotionEffectStamina:
        SetTextMacro1Number(GetPotionMagnitude(item));
        text = GetDialogText(0x665);  // "Restores @1 Stamina Points."
        break;

    case PotionEffectMagic:
        SetTextMacro1Number(GetPotionMagnitude(item));
        text = GetDialogText(0x668);  // "Restores @1 Magic Points."
        break;

    case 0:
    case PotionEffectPoison:
    case PotionEffectParalysis:
        text = GetDialogText(0x662);  // "You can't use this item now..."
        break;
    }

    DrawTextLines(0x50, 0x18, 0x84, 0xC0, 0x10, &text, 0);
}
