#include "types.h"
#include "commands.h"
#include "windows.h"

typedef struct HideScreenWindowRecord {
    u32 dwOpcode;
    u8 bWindowId;
} HideScreenWindowRecord;

void RoomScriptOpHideScreenWindow(HideScreenWindowRecord *pRecord)
{
    HideScreenWindow_candidate(pRecord->bWindowId);
}
