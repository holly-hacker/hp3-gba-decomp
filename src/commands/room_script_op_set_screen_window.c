#include "types.h"
#include "commands.h"
#include "windows.h"

typedef struct SetScreenWindowRecord {
    u32 dwOpcode;
    u8 bWindowId;
    s16 nX0;  // pixels
    s16 nY0;
    s16 nX1;
    s16 nY1;
    u8 bWinIn;
    u8 bWinOut;
} SetScreenWindowRecord;

void RoomScriptOpSetScreenWindow(SetScreenWindowRecord *pRecord)
{
    SetScreenWindowLayers(pRecord->bWindowId, pRecord->bWinIn, pRecord->bWinOut);
    SetScreenWindowRect(pRecord->bWindowId, pRecord->nX0 << 16, pRecord->nY0 << 16, pRecord->nX1 << 16,
                        pRecord->nY1 << 16);
}
