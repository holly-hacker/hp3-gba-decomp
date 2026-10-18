#include "pscreen_character.h"
#include "actor.h"
#include "background.h"
#include "default_menu.h"

void CloseStatusEquipCharacterSelectScreen(void)
{
    ClearBgTilemap(1);
    ClearBgTilemap(2);
    ClearBgTilemap(3);
    DisableBg(3);
    ExitMenuScreen();
    FreeAllActors(&g_ActiveActorListState.pHead);
}
