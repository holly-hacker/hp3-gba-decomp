#include "title_load.h"
#include "title_new.h"

void InitializeLoadGame(void)
{
    InitializeSaveSlotScreen_candidate(0x8CE);  // "Load Game"
}
