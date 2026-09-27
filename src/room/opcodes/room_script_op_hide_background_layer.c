#include "types.h"
#include "display.h"
#include "room_script.h"

typedef struct HideBackgroundLayerRecord {
    u32 dwOpcode;
    u8 bBg;
} HideBackgroundLayerRecord;

void RoomScriptOpHideBackgroundLayer(HideBackgroundLayerRecord *pRecord)
{
    DisableBg(pRecord->bBg);
}
