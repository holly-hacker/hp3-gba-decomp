#include "types.h"
#include "battle.h"

// Monster-side counterpart to InitPlayerBattleActor: allocates the fighter's
// Object, hardwires pObject->pfnTick = TickFighterAttackAnimState_candidate,
// then populates the BattleFighter from MonsterTable. See docs/memory-map/battle.md.

#define BATTLE_SLOT_ORIGIN_X 204
#define BATTLE_SLOT_ORIGIN_Y 78

Object *InitMonsterBattleActor(BattleFighter *fighter, s32 monsterIndex, s32 battleSlotIndex)
{
    Object *pObject;
    u8 type = monsterIndex;
    u8 slot = battleSlotIndex;
    s32 clearMask;
    s32 flagsBeforeClear;
    s32 xBase;
    s32 objType;
    s32 slotX2;
    Object *pShadowObject;
    u8 **ppAnimCursor;
    u8 **ppBase;

    pObject = AllocDefaultObject();
    objType = type + 4;
    pObject->wObjectType = objType;
    pObject->bUnk_0x7C = 0;

    // Slot anchor in pixels, stored 16.16; the move target reuses X + 24.
    xBase = slot * 36;
    SnapObjectPosition(pObject, (xBase + BATTLE_SLOT_ORIGIN_X) << 16, (BATTLE_SLOT_ORIGIN_Y - slot * 4) << 16);
    StartObjectMove(pObject, (xBase + 24) << 16, (BATTLE_SLOT_ORIGIN_Y - slot * 4) << 16, 0x1E);

    sub_08003A44(pObject, 0, 0x400, -0xC);

    flagsBeforeClear = pObject->bGfxSlotAndFlags;
    clearMask = ~0xC;
    clearMask &= flagsBeforeClear;
    pObject->bGfxSlotAndFlags = clearMask | 4;
    pObject->bUnk16 = -0x40;
    pObject->dwUnk_0x28 = 1;
    pObject->dwFlags = 0x20006019;

    SetObjectActionState(pObject, 0xF);

    pObject->bAnimFrameDelay = 1;
    pObject->pfnTick = TickFighterAttackAnimState_candidate; // contains `Mt19937RandMax` call every enemy turn to determine target

    AttachObjectEffectSlot_candidate(pObject, g_pMonsterGraphicsTable[type].nEffectSlot_candidate);
    SetObjectAnimData(pObject, &g_pMonsterGraphicsTable[type], &g_pMonsterAnimFrameTable[type * 0x60], 0);

    ppAnimCursor = &pObject->pAnimFrameCursor;
    ppBase = &pObject->pAnimFrameBase;

    // Doubling as slot + slot: slot * 2 splits the copy and shift across
    // r3/r0, this keeps both in r0.
    slotX2 = slot + slot;

    *ppAnimCursor = *ppBase + slotX2 + 2;
    if (slot > 4)
        *ppAnimCursor = *ppBase + 2;

    sub_08001958(pObject, **ppAnimCursor);

    // certain flying monsters? Cornish Pixie, Bat, Dragonfly
    if (type == 3 || type == 0x1D || type == 0x1A)
    {
        s32 slot64 = slot * 64;
        sub_08003A30(pObject, slot64, 0x800, 2);
        sub_08003A44(pObject, slot64, 0x800, 2);
    }
    // fire effect monsters? Salamander, Amazonian Salamander, Peruvian Salamander
    else if ((u8)(type - 0x2D) <= 2)
    {
        pShadowObject = AllocDefaultObject();
        pShadowObject->wObjectType = objType;
        pShadowObject->bUnk_0x7C = 0;

        sub_08003A44(pShadowObject, 0, 0x400, -0xC);

        flagsBeforeClear = pShadowObject->bGfxSlotAndFlags;
        clearMask = ~0xC;
        clearMask &= flagsBeforeClear;

        pShadowObject->bGfxSlotAndFlags = clearMask | 4;
        pShadowObject->bUnk16 = -0x40;
        pShadowObject->dwUnk_0x28 = 1;
        pShadowObject->dwFlags = 0x6019;
        pShadowObject->bAnimFrameDelay = 1;

        AttachEffectOwner_candidate(pShadowObject, g_MonsterShadowGfxRow.pEffectData);
        SetObjectAnimData(pShadowObject, &g_MonsterShadowGfxRow, g_MonsterShadowAnimData, 0);

        pShadowObject->pAnimFrameCursor = pShadowObject->pAnimFrameBase + slotX2 + 2;

        if (slot > 4)
            pShadowObject->pAnimFrameCursor = pShadowObject->pAnimFrameBase + 2;

        sub_08001958(pShadowObject, pShadowObject->pAnimFrameCursor[0]);

        pShadowObject->pOwnerObject = pObject;
        pObject->pShadowObject = pShadowObject;
    }
    fighter->bFighterType = Enemy;
    fighter->pObject = pObject;
    fighter->wHp = MonsterTable[type].wHp;
    fighter->wHp_max = MonsterTable[type].wHp;
    fighter->bSpeed = MonsterTable[type].bSpeed;
    fighter->bAccuracy = MonsterTable[type].bAccuracy;
    fighter->bCritChance = MonsterTable[type].bCritChance;
    fighter->wDamageRollMin = MonsterTable[type].wDamageMin;
    fighter->wDamageRollMax = MonsterTable[type].wDamageMax;

    fighter->bEffectivenessFlipendo = MonsterTable[type].abEffectiveness[0];
    fighter->bEffectivenessIncendio = MonsterTable[type].abEffectiveness[1];
    fighter->bEffectivenessVerdimillious = MonsterTable[type].abEffectiveness[2];
    fighter->bEffectivenessWingardiumLeviosa = MonsterTable[type].abEffectiveness[3];
    fighter->bEffectivenessGlacius = MonsterTable[type].abEffectiveness[4];
    fighter->bEffectivenessDiffindo = MonsterTable[type].abEffectiveness[5];

    fighter->wRewardXp = MonsterTable[type].wRewardXp;
    fighter->bLevel = MonsterTable[type].bLevel;
    fighter->wRewardGold = MonsterTable[type].wRewardGold;
    fighter->bStatusFlags = StatusNone;
    fighter->nFaintedFlag = 0;
    fighter->bRosterIndex = type;
    fighter->unk3E = -1;
    fighter->bSlotParam = slot;

    return pObject;
}
