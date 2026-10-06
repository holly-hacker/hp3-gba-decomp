#include "types.h"
#include "battle/battle.h"
#include "mt19937.h"

// Plays animation `state` on a monster's Object (wObjectType is the monster id + 4), and
// on its companion shadow Object for monsters 45-47. State 0 (idle) starts
// from one of 2 random frames.
void SetMonsterObjectAnim(Object *obj, u8 state)
{
    if (obj->dwFlags & ObjectFlagVisible) {
        obj->dwFlags &= ~(ObjectFlagVisible | ObjectFlagActionAnimDone);
        SetObjectAnimData(obj, &g_pMonsterGraphicsTable[obj->wObjectType - 4].battle,
                          g_pMonsterAnimFrameTable[obj->wObjectType - 4], state);

        if ((u16)(obj->wObjectType - 0x31) <= 2) {
            SetObjectAnimData(obj->pShadowObject, &g_MonsterShadowGfxRow, g_MonsterShadowAnimData, state);
        } else if (state == 0) {
            obj->pAnimFrameCursor += Mt19937RandMax(2) * 4;
            SetObjectAnimFrame(obj, *obj->pAnimFrameCursor);
        }

        obj->dwFlags |= ObjectFlagVisible;
    } else {
        obj->dwFlags &= ~ObjectFlagActionAnimDone;
        SetObjectAnimData(obj, &g_pMonsterGraphicsTable[obj->wObjectType - 4].battle,
                          g_pMonsterAnimFrameTable[obj->wObjectType - 4], state);

        if ((u16)(obj->wObjectType - 0x31) <= 2)
            SetObjectAnimData(obj->pShadowObject, &g_MonsterShadowGfxRow, g_MonsterShadowAnimData, state);
    }
}
