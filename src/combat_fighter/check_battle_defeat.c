#include "types.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_fighter.h"
#include "sound.h"
#include "overworld/room.h"
#include "combat.h"
#include "commands.h"
#include "hero.h"
#include "map.h"
#include "modes.h"

// Ends the battle in defeat once every non-Enemy fighter (only Buckbeak in a
// Buckbeak-only encounter) is at 0 HP: fully heals the party, picks the
// overworld warp room from the defeat-warp selector, sets the story stage to
// 0x1F (saving the old one as a pending override) and pushes BattleStateDefeat.
void CheckBattleDefeat(void)
{
    u8 i;

    // Buckbeak-only encounter
    if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0xFF && g_GameModeStackContext.dwCurrentGameModeArg1 == 3) {
        for (i = 0; i < g_pFightState->bFighterCount; i++) {
            if (g_pFightState->pFighters[i].bFighterType == Buckbeak && g_pFightState->pFighters[i].stats.wHp != 0)
                return;
        }
    } else {
        for (i = 0; i < g_pFightState->bFighterCount; i++) {
            if (g_pFightState->pFighters[i].bFighterType != Enemy && g_pFightState->pFighters[i].stats.wHp != 0)
                return;
        }
    }

    if (g_bPartyCharId2 == 8)
        g_bPartyCharId2 = 0xFF;

    g_pFightState->bHitResultCount = 0;
    ShowBattleMessage(Defeat, 0, 0);
    PlayMusicModule(0x1C);

    for (i = 0; i < 4; i++) {
        g_aPartyMasterStats[i].stats.wHp = g_aPartyMasterStats[i].wHp_max;
        g_aPartyMasterStats[i].stats.wMp = g_aPartyMasterStats[i].wMp_max;
    }

    g_GameModeStackContext.dwCurrentGameModeArg3 = 0xFE;
    g_pFightState->bMenuScreen = BattleMenuNone;
    g_pFightState->dwBattleResultPending = 1;
    g_pFightState->bDefeatWarpTarget = g_aDefeatWarpRoomId[g_abQuestEventState[QUEST_DEFEAT_WARP_SELECTOR]];

    if (g_abQuestEventState[QUEST_DEFEAT_WARP_SELECTOR] == 0x13)
        g_abRoomEntryIds[0] = 1;
    else
        g_abRoomEntryIds[0] = 0;

    g_bStoryStageToRestore = g_abQuestEventState[QUEST_STORY_STAGE];
    g_abQuestEventState[QUEST_STORY_STAGE] = 0x1F;
    PushBattleState(BattleStateDefeat);
}
