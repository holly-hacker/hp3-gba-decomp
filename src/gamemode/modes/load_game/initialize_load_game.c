#include "types.h"
#include "menu/main_menu.h"

void InitializeLoadGame(void)
{
    InitializeSaveSlotScreen_candidate(0x8CE);  // "Load Game"
}
