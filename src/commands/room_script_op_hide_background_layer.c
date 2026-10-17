#include "types.h"
#include "background.h"
#include "commands.h"

typedef struct HideBackgroundLayerRecord {
    u32 dwOpcode;
    u8 bBg;
} HideBackgroundLayerRecord;

void RoomScriptOpHideBackgroundLayer(HideBackgroundLayerRecord *pRecord)
{
    DisableBg(pRecord->bBg);
}
