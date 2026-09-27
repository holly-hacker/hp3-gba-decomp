#include "types.h"
#include "display.h"
#include "room_script.h"

typedef struct SetBackgroundBlendLayersRecord {
    u32 dwOpcode;
    u8 bBg0;
    u8 bBg1;
    u8 bBg2;
    u8 bBg3;
} SetBackgroundBlendLayersRecord;

void RoomScriptOpSetBackgroundBlendLayers(SetBackgroundBlendLayersRecord *pRecord)
{
    SetAlphaBlendTargets((pRecord->bBg1 << 1) | pRecord->bBg0 | (pRecord->bBg2 << 2) | (pRecord->bBg3 << 3), 0x1f);
}
