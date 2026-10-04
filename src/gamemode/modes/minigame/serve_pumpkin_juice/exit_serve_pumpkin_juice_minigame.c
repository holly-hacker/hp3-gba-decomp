#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "graphics/palette.h"
#include "hw/mem.h"
#include "menu/minigame_menu.h"

void ExitUnusedServePumpkinJuiceMinigame(void)
{
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetAlphaBlendTargets(0, 0);
    ResetPaletteAnimations();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    sub_0803FF04();
    sub_0800A914();
}
