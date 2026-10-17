#include "types.h"
#include "graphics/display.h"
#include "pause_menu.h"
#include "actor.h"
#include "menu/status_equip.h"
#include "default_menu.h"

void InitializeStatusEquipCharacterSelectLastCursor(void)
{
    StartMenuFadeIn();
    SetAlphaBlendTargets(0x1E, 1);
    sub_08035A34();

    g_bStatusEquipCharacterSlot = StatusEquipCharacterToSlot(g_dwStatusEquipCharacter);
    SetActorPosition(g_pMenuCursorActor, g_bStatusEquipCharacterSlot * 72 + 24, 68);
}
