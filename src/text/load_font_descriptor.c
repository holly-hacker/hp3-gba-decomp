#include "graphics/text.h"

// Big-endian u16 offset at blob[at], resolved against the blob base.
#define FONT_BLOB_PTR(blob, at) ((blob) + (((blob)[at] << 8) + (blob)[(at) + 1]))

void LoadFontDescriptor(u32 index, u32 slot)
{
    const u8 *blob;
    FontDescriptor *desc;

#ifdef VERSION_JP
    // Slot 1 takes the two-byte-glyph font, slot 0 the Latin font; unk6
    // always comes from the two-byte-glyph table.
    if (slot == 1)
        blob = g_aExtFontTable[index].pBlob;
    else
        blob = g_aFontTable[index].pBlob;
#else
    blob = g_aFontTable[index].pBlob;
#endif
    desc = &g_aFontDescriptors[index][slot];

    desc->firstCode = *(const u16 *)&blob[0];
    desc->lastCode = *(const u16 *)&blob[2];
    desc->height = blob[4];
#ifdef VERSION_JP
    desc->unk6 = g_aExtFontTable[index].value;
#else
    desc->unk6 = g_aFontTable[index].value;
#endif
    desc->pGlyphOffsets = (const u16 *)FONT_BLOB_PTR(blob, 6);
    desc->pWidths = FONT_BLOB_PTR(blob, 10);
    desc->pBitmaps = FONT_BLOB_PTR(blob, 14);
#ifdef VERSION_JP
    desc->pGlyphFlags = (const u32 *)FONT_BLOB_PTR(blob, 8);
#endif
}
