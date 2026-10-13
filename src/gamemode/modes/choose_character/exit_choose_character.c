#include "types.h"
#include "background.h"
#include "graphics/display.h"
#include "actor.h"
#include "hw/bios.h"
#include "hw/io_regs.h"
#include "menu/dialog.h"
#include "menu/choose_character.h"
#include "overworld/overworld.h"
#include "overworld/room.h"

void ExitChooseCharacter(void)
{
    s32 i;

    ClearScanlineEffects();
    StopScanlineEffects();
    bios_CPUFastSet(g_awSavedBgPalette0, BG_PLTT, 8);
    SetBgPriority(2, g_ChooseCharacterState.bSavedBg2Priority);
    g_abQuestEventState[0x12] = g_abQuestEventState[0];
    SetActorActionState(g_pPlayerActor, 0x21);
    sub_0801FA9C();
    HideScreenWindow_candidate(0);

    FreeActor(g_ChooseCharacterState.pCursorActor);
    for (i = 0; i < CHOOSE_CHARACTER_OPTION_COUNT; i++)
        FreeActor(g_ChooseCharacterState.apOptionActors[i]);

    ReserveObjPaletteSlot(1);
    ReserveObjPaletteSlot(2);
    if (g_bCurrentRoomId == 1)
        SetAlphaBlendTargets(4, 0x1F);
}
