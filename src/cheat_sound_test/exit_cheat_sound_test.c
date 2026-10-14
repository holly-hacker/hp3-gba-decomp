#include "types.h"
#include "graphics/display.h"
#include "hw/mem.h"
#include "menu/minigame_menu.h"

void ExitCheatSoundTest(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    sub_0803FF04();
    FreeAllActors(&g_ActiveActorListState.pHead);
}
