#include "types.h"
#include "text.h"

// Points the three decompressor globals DecompressDialogText reads at one
// language's string-table blob (see DialogTextBlob). Called by SetLanguage
// with one of sDialogTextTable's 8 entries.
s32 InitDialogTextTable(DialogTextBlob *blob)
{
    u32 offsetTableOffset;

    gDialogTextBlobBase = (u8 *)blob;
    offsetTableOffset = blob->offsetTableOffset;
    gDialogTextTreeNodes = blob->nodes;
    gDialogTextOffsetTable = (u32 *)((u8 *)blob + offsetTableOffset);
    return 0;
}
