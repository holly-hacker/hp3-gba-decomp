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
        && IS_HOGWARTS_GROUNDS_ROOM(g_bCurrentRoomId))
        return gBattleAltWall;

    return g_aBattleBackgroundPairs[g_bCurrentRoomId].pWall;
}
