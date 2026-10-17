#include "types.h"
#include "title_load.h"
#include "title_new.h"

void UpdateLoadGame(void)
{
    if (HandleSaveSlotInput_candidate())
        ConfirmLoadGameSlot_candidate();
}
