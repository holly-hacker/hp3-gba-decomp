#include "types.h"
#include "font.h"
#include "save.h"
#include "text.h"
#include "game_state.h"
#include "hedwig_minigame.h"

void DrawOwlName(void)
{
    SelectTextFont(2, 0, -1);
    // 0x676: "Fiddletick", the first of the 14 owl names
#ifdef VERSION_JP
    DrawStringAligned(0x2A0, 0x22, 3, GetDialogText(0x676 + g_saveStateBlock.owlCareKit.bNameIndex), 1);
#else
    DrawStringAligned(0x2A0, 0x28, 4, GetDialogText(0x676 + g_saveStateBlock.owlCareKit.bNameIndex), 1);
#endif
}
