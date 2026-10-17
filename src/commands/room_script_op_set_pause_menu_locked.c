#include "types.h"
#include "commands.h"
#include "map.h"

typedef struct SetPauseMenuLockedRecord {
    u32 dwOpcode;
    u8 bLocked;
} SetPauseMenuLockedRecord;

void RoomScriptOpSetPauseMenuLocked(SetPauseMenuLockedRecord *pRecord)
{
    g_dwPauseMenuLocked = pRecord->bLocked;
}
