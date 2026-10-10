#include "font.h"
#include "hw/mem.h"

void InitTextMacroTable(void)
{
    u32 i;
    s32 j;
    u8 **slot;

    for (i = 0; i < 12; i++)
    {
        LoadFontDescriptor(i, 0);
#ifdef VERSION_JP
        LoadFontDescriptor(i, 1);
#endif
    }

    slot = sTextMacroTable;
    for (j = 3; j >= 0; j--)
        *slot++ = AllocZeroed(0x40);
}
