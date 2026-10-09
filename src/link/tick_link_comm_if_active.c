#include "types.h"
#include "game/game_modes.h"
#include "link/link.h"

void TickLinkCommIfActive_candidate(void)
{
    if ((g_dwGameModeFlags & LinkSessionActive) && g_dwLinkMode == 1)
        ExchangeLinkFrame_candidate();
}
