#include "pscreen_character.h"
#include "actor.h"

void TickStatusEquipCharacterCursor(Actor *pCursor)
{
    SetActorMoveTargetWithDuration(pCursor, StatusEquipSlotToColumn(g_bStatusEquipCharacterSlot) * 72 + 24, 68, 2);
}
