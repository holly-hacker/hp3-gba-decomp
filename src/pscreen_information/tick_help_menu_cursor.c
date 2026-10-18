#include "pscreen_information.h"

void TickHelpMenuCursor(Actor *pActor)
{
    SetActorMoveTargetWithDuration(pActor, 0x12, g_HelpState.bSelectedEntry * HELP_MENU_ROW_HEIGHT + 0x22, 2);
}
