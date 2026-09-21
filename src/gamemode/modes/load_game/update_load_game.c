#include "types.h"
#include "main_menu.h"

void UpdateLoadGame(void)
{
    if (HandleSaveSlotInput_candidate())
        ConfirmLoadGameSlot_candidate();
}
