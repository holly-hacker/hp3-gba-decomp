#include "types.h"
#include "game/game_modes.h"
#include "hw/input.h"
#include "link/link.h"

void ResetLinkSession(void)
{
    if (g_dwLinkMode == 1)
        DisableLinkSerial();

    g_dwLinkFlags &= ~LINK_FLAG_CLEARED_ON_RESET;
    g_dwGameModeFlags &= ~LinkSessionActive;
    g_LinkPlayerState.dwUnk_0x00 = -1;
    ResetKeyInput();
}
