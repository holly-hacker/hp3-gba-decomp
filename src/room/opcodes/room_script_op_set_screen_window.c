#include "types.h"
#include "graphics/display.h"
#include "overworld/room_script.h"

typedef struct SetScreenWindowRecord {
    u32 dwOpcode;
    u8 bWindowId;
    u8 pad_05[1];
    s16 nX0;  // pixels
    s16 nY0;
    s16 nX1;
    s16 nY1;
    u8 bWinIn;
    u8 bWinOut;
} SetScreenWindowRecord;

void RoomScriptOpSetScreenWindow(SetScreenWindowRecord *pRecord)
{
    SetScreenWindowLayers_candidate(pRecord->bWindowId, pRecord->bWinIn, pRecord->bWinOut);
    SetScreenWindowRect_candidate(pRecord->bWindowId, pRecord->nX0 << 16, pRecord->nY0 << 16, pRecord->nX1 << 16,
                                  pRecord->nY1 << 16);
}
