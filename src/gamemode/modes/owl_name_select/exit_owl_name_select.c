#include "types.h"
#include "game/game_modes.h"
#include "graphics/display.h"
#include "hw/mem.h"
#include "menu/owl_name_select.h"

void ExitOwlNameSelect(void)
{
    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 1)
        PlayScreenTransitionOutByIndex(0x3F, 2);

    FreeAllObjects(&g_ActiveObjectListState.pHead);
    DisableBg(3);
}
