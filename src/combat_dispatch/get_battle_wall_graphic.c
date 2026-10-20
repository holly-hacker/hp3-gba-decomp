#include "types.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "commands.h"
#include "gen/graphics/battle.h"
#include "map.h"
#include "overworld/room.h"

const u8 *GetBattleWallGraphic(void)
{
    if (g_abQuestEventState[QUEST_ALT_PRESENTATION]
        && g_bCurrentRoomId >= 8 && g_bCurrentRoomId <= 15)
        return gBattleAltWall;

    return g_aBattleBackgroundPairs[g_bCurrentRoomId].pWall;
}
