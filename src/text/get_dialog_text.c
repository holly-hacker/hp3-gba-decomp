#include "types.h"
#include "text.h"

extern u8 *gDialogTextScratchBuf;

s32 DecompressDialogText(s32 stringId, u8 *outBuf, s32 maxSize);

u8 *GetDialogText(s32 stringId)
{
    if (DecompressDialogText(stringId, gDialogTextScratchBuf, 0x400) == DialogTextOk)
        return gDialogTextScratchBuf;
    return 0;
}
