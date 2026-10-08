#include "types.h"
#include "battle/battle.h"
#include "mt19937.h"

// state 0 (idle) re-rolls one of 2 random idle starting frames.
void SetPlayerObjectAnim(Object *obj, s32 state)
{
    if (obj->dwFlags & ObjectFlagVisible)
    {
        obj->dwFlags &= ~(ObjectFlagVisible | ObjectFlagActionAnimDone);
        if (state == 0)
        {
            SetObjectAnimData(obj, (u8 *)&g_aFighterAnimTable[obj->wObjectType] + state * 0x10,
                               g_aFighterAnimDataTable[obj->wObjectType][state], 0);
            obj->anim.pAnimFrameCursor = obj->anim.pAnimFrameBase + Mt19937RandMax(2) * 4;
            SetObjectAnimFrame(obj, *obj->anim.pAnimFrameCursor);
        }
        else
        {
            SetObjectAnimData(obj, (u8 *)&g_aFighterAnimTable[obj->wObjectType] + state * 0x10,
                               g_aFighterAnimDataTable[obj->wObjectType][state], 0);
        }
        obj->dwFlags |= ObjectFlagVisible;
    }
    else
    {
        obj->dwFlags &= ~ObjectFlagActionAnimDone;
        SetObjectAnimData(obj, (u8 *)&g_aFighterAnimTable[obj->wObjectType] + state * 0x10,
                           g_aFighterAnimDataTable[obj->wObjectType][state], 0);
    }
}
