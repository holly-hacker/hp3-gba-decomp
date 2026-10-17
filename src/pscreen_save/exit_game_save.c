#include "types.h"
#include "battle/battle.h"
#include "color.h"
#include "pscreen_save.h"
#include "mem.h"
#include "actor.h"
#include "default_menu.h"
#include "screen_transitions.h"

void ExitGameSave(void)
{
    SetScreenDarkenParams_candidate(0, 8);
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetScreenDarkenParams_candidate(0, 8);
    ExitMenuScreen();
    FreeAllActors(&g_ActiveActorListState.pHead);
    ResetPaletteAnimations();
}
