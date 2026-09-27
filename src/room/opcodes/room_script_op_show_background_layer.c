#include "types.h"
#include "display.h"
#include "room_script.h"

typedef struct ShowBackgroundLayerRecord {
    u32 dwOpcode;
    u8 bBg;
} ShowBackgroundLayerRecord;

void RoomScriptOpShowBackgroundLayer(ShowBackgroundLayerRecord *pRecord)
{
    EnableBg(pRecord->bBg);
}
