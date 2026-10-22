#include "types.h"
#include "modes.h"
#include "actor.h"
#include "font.h"
#include "text.h"
#include "default_menu.h"
#include "title_options.h"

void BuildOptionsScreen(void)
{
    u32 i;
    Actor *pActor;
    u32 row;
    const u8 *pText;

    SetTextTargetFromBgControl(g_dwCommonBg2Control);
    SelectTextFont(3, 0, 0);
    pText = GetDialogText(0x8D8);  // "OPTIONS"
    DrawTextLines(0x160, 0x78, 3, 0xC0, 0x18, &pText, 1);

    for (i = 0; i < OPTIONS_MENU_ITEM_COUNT; i++)
    {
        pActor = SpawnActor(0x17, g_aOptionsMenuItems[i].nX, g_aOptionsMenuItems[i].nY,
                            g_aOptionsMenuItems[i].pPalette);
        g_OptionsState.apActors[i] = pActor;

        switch (i)
        {
        case OptionsRowSound:
        case OptionsRowMusic:
        case OptionsRowGamma:
#ifndef VERSION_JP
        case OptionsRowLanguage:
#endif
            SetActorSprite(pActor, &g_aOptionsMenuItems[i].asset);
            break;

        case OptionsItemSoundBar:
        case OptionsItemMusicBar:
            SetActorSprite(pActor, &g_aOptionsMenuItems[i].asset);
            pActor->oam.priority = 1;
            break;

        case OptionsItemSoundKnob:
        case OptionsItemMusicKnob:
            SetActorAnimData(pActor, &g_aOptionsMenuItems[i].asset,
                             g_aabOptionsKnobAnims[i - OptionsItemSoundKnob], 0);
            break;
        }
    }

    for (row = 0; row < OPTIONS_ROW_COUNT; row++)
    {
        DrawOptionsRowLabel(row, g_GameModeStackContext.dwModeScratchB);
        DrawOptionValue(row, g_OptionsState.adwValues[row]);
    }

    SelectTextFont(0, 0, 0);
    pText = GetDialogText(0x8DF);  // "Press START to save options."
#ifdef VERSION_JP
    DrawTextLines(0x120, 0x78, 0x80, 0xB8, 0x10, &pText, 1);
#else
    DrawTextLines(0x140, 0x78, 0x80, 0xB8, 0x10, &pText, 1);
#endif
}
