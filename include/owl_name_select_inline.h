#pragma once

#include "types.h"
#include "background.h"
#include "font.h"
#include "text.h"
#include "modes.h"
#include "save.h"
#include "game_state.h"

// StepOwlNameSelectChoice inlines this; draw_owl_name_select_choice.c defines
// the linkage macro as empty.
#ifndef DRAW_OWL_NAME_SELECT_CHOICE_LINKAGE
#define DRAW_OWL_NAME_SELECT_CHOICE_LINKAGE extern inline
#endif

DRAW_OWL_NAME_SELECT_CHOICE_LINKAGE void DrawOwlNameSelectChoice(void)
{
    s32 textId;

    FillBgTilemapRect(2, 5, 18, 20, 2, 0);
    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 0)
        textId = g_saveStateBlock.owlCareKit.bNameIndex + 0x676;  // "Fiddletick", ...
    else
        textId = g_saveStateBlock.owlCareKit.bTypeIndex + 0x673;  // "White Owl", ...
    SelectTextFont(3, 0, 0);
    DrawStringAligned(0x71, 120, 144, GetDialogText(textId), 1);
}
