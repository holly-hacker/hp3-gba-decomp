#include "types.h"
#include "pause_menu.h"
#include "actor.h"
#include "default_menu.h"
#include "pscreen_character.h"
#include "screen_transitions.h"

void InitializeStatusEquipCharacterSelectLastCursor(void)
{
    StartMenuFadeIn();
    SetAlphaBlendTargets(0x1E, 1);
    sub_08035A34();

    g_bStatusEquipCharacterSlot = StatusEquipCharacterToSlot(g_dwStatusEquipCharacter);
    SetActorPosition(g_pMenuCursorActor, g_bStatusEquipCharacterSlot * 72 + 24, 68);
}
