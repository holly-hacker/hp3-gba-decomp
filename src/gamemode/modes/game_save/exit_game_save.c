#include "types.h"
#include "battle/battle.h"
#include "graphics/display.h"
#include "graphics/palette.h"
#include "game/game_save.h"
#include "menu/main_menu.h"
#include "hw/mem.h"

void ExitGameSave(void)
{
    SetScreenDarkenParams_candidate(0, 8);
    PlayScreenTransitionOutByIndex(0x3F, 2);
    SetScreenDarkenParams_candidate(0, 8);
    ExitMenuScreen();
    FreeAllObjects(&g_ActiveObjectListState.pHead);
    ResetPaletteAnimations();
}
