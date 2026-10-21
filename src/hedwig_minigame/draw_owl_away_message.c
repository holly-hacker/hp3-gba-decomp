#include "types.h"
#include "font.h"
#include "text.h"
#include "hedwig_minigame.h"

void DrawOwlAwayMessage(void)
{
    SelectTextFont(2, 0, -1);
    DrawStringAligned(0x28C, 0x78, 0x48, GetDialogText(0xAC0), 1);  // "Your owl is away..."
}
