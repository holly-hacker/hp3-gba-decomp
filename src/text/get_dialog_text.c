#include "types.h"
#include "text.h"

u8 *GetDialogText(s32 stringId)
{
    if (DecompressDialogText(stringId, gDialogTextScratchBuf, 0x400) == DialogTextOk)
        return gDialogTextScratchBuf;
    return 0;
}
