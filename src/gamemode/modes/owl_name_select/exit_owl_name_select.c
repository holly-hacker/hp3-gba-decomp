#include "types.h"
#include "background.h"
#include "modes.h"
#include "graphics/display.h"
#include "mem.h"
#include "actor.h"
#include "menu/owl_name_select.h"

void ExitOwlNameSelect(void)
{
    if (g_GameModeStackContext.dwCurrentGameModeArg1 == 1)
        PlayScreenTransitionOutByIndex(0x3F, 2);

    FreeAllActors(&g_ActiveActorListState.pHead);
    DisableBg(3);
}
