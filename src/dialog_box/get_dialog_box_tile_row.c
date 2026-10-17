#include "types.h"
#include "dialog_box.h"
#include "scroll.h"

u32 GetDialogBoxTileRow(void)
{
    s32 cameraPosition[2];

    GetCameraPosition(cameraPosition);
    cameraPosition[1] &= 0xFF;
    return (cameraPosition[1] >= 0x30 ? cameraPosition[1] - 0x30 : cameraPosition[1] + 0xB0) >> 3;
}
