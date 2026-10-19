#include "types.h"
#include "hw/io_regs.h"
#include "background.h"
#include "actor.h"
#include "font.h"
#include "text.h"
#include "title_options.h"

void DrawOptionValue(u32 row, s32 value)
{
    const u8 *pText;
    s32 x;

    while (!(REG_DISPSTAT & 2))
        ;

    switch (row)
    {
    case OptionsRowSound:
    case OptionsRowMusic:
        // Volume 0-10 slides the knob 35 pixels along its bar.
        x = value * 35 / 10 + 170;
        SnapActorPosition(g_OptionsState.apActors[row + OptionsItemSoundKnob],
                          (x << 16) - g_BgState.aLayers[1].scroll.x, (row * 20 + 47) << 16);
        break;

    case OptionsRowGamma:
        ClearBgTilemapRect(2, 0x10, 0xA, 0xB, 2);
        SelectTextFont(4, 1, 0);
        pText = GetDialogText(value + 0x8E1);  // "Normal", "Bright"
        DrawTextLines(0xC0, 0xD0, g_aOptionsMenuItems[OptionsRowGamma].nY, 0x30, 0x10, &pText, 2);
        break;

#ifndef VERSION_JP
    case OptionsRowLanguage:
        break;
#endif
    }
}
