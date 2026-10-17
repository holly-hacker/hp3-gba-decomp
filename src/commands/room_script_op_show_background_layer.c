#include "types.h"
#include "background.h"
#include "commands.h"

typedef struct ShowBackgroundLayerRecord {
    u32 dwOpcode;
    u8 bBg;
} ShowBackgroundLayerRecord;

void RoomScriptOpShowBackgroundLayer(ShowBackgroundLayerRecord *pRecord)
{
    EnableBg(pRecord->bBg);
}
