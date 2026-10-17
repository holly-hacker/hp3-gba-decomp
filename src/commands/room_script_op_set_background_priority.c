#include "types.h"
#include "background.h"
#include "commands.h"

typedef struct SetBackgroundPriorityRecord {
    u32 dwOpcode;
    u8 bBg;
    u8 bPriority;
} SetBackgroundPriorityRecord;

void RoomScriptOpSetBackgroundPriority(SetBackgroundPriorityRecord *pRecord)
{
    SetBgPriority(pRecord->bBg, pRecord->bPriority);
}
