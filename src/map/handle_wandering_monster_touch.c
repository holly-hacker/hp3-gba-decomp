#include "types.h"
#include "area.h"
#include "hero.h"
#include "mem.h"
#include "modes.h"
#include "move.h"
#include "sound.h"
#include "map.h"

// Starts the battle with a wandering monster the player touched while walking
// (action state 0x21), and records the touch. Every fifth touch spawns
// replacement monsters for the recorded ones.
void HandleWanderingMonsterTouch(void)
{
    Actor *pMonster = g_pTouchedWanderingMonster;
    u32 i;
    TouchedMonsterRecord *pRecords;

    if (pMonster != NULL)
    {
        g_pTouchedWanderingMonster = NULL;
        if (g_pPlayerActor->bActionState == 0x21 && g_dwRoomChainRanThisFrame_candidate == 0)
        {
            SetActorActionState(g_pPlayerActor, 0);
            pRecords = g_aTouchedMonsterRecords;
            pRecords[g_bTouchedMonsterRecordCount].bEncounterId = pMonster->bFighterIndex;
            pRecords[g_bTouchedMonsterRecordCount].bKind = pMonster->bReceivedRewardId;
            if (++g_bTouchedMonsterRecordCount > 4)
            {
                for (i = 0; i <= 4; i++)
                    TrySpawnWanderingMonster(pRecords[i].bEncounterId, pRecords[i].bKind);
                g_bTouchedMonsterRecordCount = 0;
                g_pTouchedWanderingMonster = NULL;
                memset(g_aTouchedMonsterRecords, 0, sizeof(g_aTouchedMonsterRecords));
            }
            PlaySoundById(6);
            PushGameMode_3(Battle, pMonster->bFighterIndex, pMonster->bEncounterVariant, pMonster->bReceivedRewardId);
            FreeActor(pMonster);
            EndFieldSpellEffect(g_pFieldSpellEffectActor);
        }
    }
}
