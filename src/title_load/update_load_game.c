#include "title_load.h"
#include "title_new.h"

void UpdateLoadGame(void)
{
    if (HandleSaveSlotInput())
        ConfirmLoadGameSlot();
}
