#include "types.h"
#include "mem.h"
#include "combat_fighter.h"
#include "modes.h"
#include "combat.h"

// Party-side counterpart to InitMonsterBattleActor: allocates the fighter's
// Actor, hardwires pActor->pfnTick = TickPlayerActionState, then populates
// the BattleFighter from g_aPartyMasterStats (Harry/Hermione/Ron) or from
// hardcoded values (Buckbeak).
Actor *InitPlayerBattleActor(BattleFighter *fighter, s32 fighterType, s32 battleSlotIndex)
{
    Actor *pActor;
    u8 type = fighterType;
    u8 slot = battleSlotIndex;
    u8 i;
    u16 hp;
    s32 posY;
    u8 **ppAnimCursor;

    pActor = AllocDefaultActor();
    pActor->wActorType = type;
    pActor->bUnk_0x7C = 0;

    pActor->oam.priority = 1;
    posY = slot * 0x40000 + 0x6E0000;
    SnapActorPosition(pActor, 0, posY);
    StartActorMove(pActor, (0xD4 - slot * 9 * 4) << 16, posY, 0x19);
    SetActorOrbitY(pActor, 0, 0x400, 0xC);

    pActor->bDepthSortBias = 0x40;
    pActor->nMoveSpeed = 1;
    pActor->dwFlags = ActorFlagVisible | ActorFlagHasAnimation | ActorFlagUnk2000
                      | ActorFlagCollisionGroup_candidate | ActorFlagKeepPaletteSlot;

    SetActorActionState(pActor, 0xF);

    pActor->anim.bAnimFrameDelay = 1;
    pActor->pfnTick = TickPlayerActionState;
    fighter->bFighterType = type;

    if (type < 3)
    {
        fighter->stats.bKnownSpellCount = g_aPartyMasterStats[type].stats.bKnownSpellCount;
        i = 0;
        do
        {
            fighter->stats.aSpellCastLevel[i] = g_aPartyMasterStats[type].stats.aSpellCastLevel[i];
            fighter->stats.aSpellUsageProgress[i] = g_aPartyMasterStats[type].stats.aSpellUsageProgress[i];
            i++;
        } while (i <= 9);
    }

    fighter->pActor = pActor;

    if (g_PrevGameModeStackContext.dwCurrentGameMode != FolioUniversitas)
    {
        fighter->bSlotParam = slot;
        fighter->bSelectedActionIndex = 0xFF;

        if (type < 3)
        {
            fighter->stats.bLevel = g_aPartyMasterStats[type].stats.bLevel;
            fighter->stats.wHp = g_aPartyMasterStats[type].stats.wHp;
            fighter->wHp_max = g_aPartyMasterStats[type].wHp_max;
            fighter->stats.wMp = g_aPartyMasterStats[type].stats.wMp;
            fighter->wMp_max = g_aPartyMasterStats[type].wMp_max;
            fighter->bAgility = g_aPartyMasterStats[type].bAgility;
            fighter->bAccuracy = g_aPartyMasterStats[type].bAccuracy;
            fighter->bDefenseFactorPercent = g_aPartyMasterStats[type].bDefenseFactorPercent;
            fighter->bMagicDefensePercent = g_aPartyMasterStats[type].bMagicDefensePercent;
            fighter->stats.wRewardXp = g_aPartyMasterStats[type].stats.wRewardXp;
            fighter->bStatusFlags = StatusNone;
            fighter->nFaintedFlag = 0;
            fighter->unk3E |= 0xFF;
        }
        else
        {
            u8 *partyBase;

            // Buckbeak stats
            fighter->stats.bLevel = 50;
            fighter->stats.wHp = 400;
            fighter->wHp_max = 400;
            fighter->stats.wMp = 999;
            fighter->wMp_max = 999;
            fighter->bAgility = 10;
            fighter->bAccuracy = 101;
            fighter->bDefenseFactorPercent = 100;
            fighter->bMagicDefensePercent = 100;
            fighter->stats.wRewardXp = 0;
            fighter->bStatusFlags = StatusNone;
            fighter->nFaintedFlag = 0;
            fighter->unk3E |= 0xFF;

            // Back up into slot 3, past the three party entries; via a
            // temp because &g_aPartyMasterStats[3] folds to one ldr.
            partyBase = (u8 *)g_aPartyMasterStats;
            memcpy(partyBase + 3 * sizeof(BattleFighter), fighter, sizeof(BattleFighter));
        }
    }

    hp = fighter->stats.wHp;

    if (hp == 0)
    {
        AttachActorPaletteUnshared(pActor, g_aFighterAnimTable[type].aRecords[8].pPalette);
        SetActorAssetRecord(pActor, &g_aFighterAnimTable[type].aRecords[8]);
        SetActorAnimFrame(pActor, 8);
        SetActorActionState(pActor, 0);
        pActor->bActionFlags = hp;  // hp == 0 on this path; keeps hp in sb
        pActor->dwFlags &= ~ActorFlagHasAnimation;
        SnapActorPosition(pActor, (0xD4 - slot * 9 * 4) << 16, slot * 0x40000 + 0x6E0000);
        fighter->nFaintedFlag = -1;
    }
    else
    {
        AttachActorPaletteUnshared(pActor, g_aFighterAnimTable[type].aRecords[0].pPalette);
        SetActorAnimData(pActor, &g_aFighterAnimTable[type], g_aFighterAnimDataTable[type][0], 0);
        // Via a temp: storing the field directly recolors the function.
        // The [0] reload folds back onto the base register, no extra move.
        ppAnimCursor = &pActor->anim.pAnimFrameCursor;
        *ppAnimCursor = pActor->anim.pAnimFrameBase + slot * 4 + 2;
        SetActorAnimFrame(pActor, (*ppAnimCursor)[0]);
    }
    return pActor;
}
