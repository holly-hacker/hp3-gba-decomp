#include "types.h"
#include "overworld/room_object.h"
#include "gen/graphics/overworld.h"

// Room object constructor for tile objType 9, the chest/one-time pickup.
// See docs/formats/rooms.md.
Object *SpawnScriptedOneTimeObject(u8 bColumn, u8 bRow)
{
    RoomObjectRecordUnk9 *pRecord = sub_08005C38(bColumn, bRow);
    Object *pObj = AllocObjectOfType(RoomObjectType_ScriptedOneTime);
    u32 kind;
    u32 mask;
    u8 index;
    u32 pc;

    SnapObjectPosition(pObj, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pObj->dwFlags = 0x04002015;
    SetObjectActionState(pObj, 0);
    SetObjectActionSubState(pObj, 1);
    pObj->bUnk_0x7C = 1;
    pObj->bAnimFrameDelay = 1;
    pObj->scriptState.wScriptPc = pRecord->wScriptPc;
    kind = pRecord->bKind;
    pObj->modeState.actor.bRoomScriptArg64_candidate = kind;
    pObj->modeState.actor.wStagedDamage = pRecord->bArgB;
    pObj->modeState.actor.bFollowStopDistance = pRecord->bArgD;
    pObj->modeState.actor.bRoomObjectArg69_candidate = pRecord->bArgC;

    pc = pObj->scriptState.wScriptPc;
    index = pc >> 3;
    mask = 1 << (pc & 7);

    if (g_abTriggeredScriptFlags[index] & mask)
        pObj->modeState.actor.bFollowResumeDistance = 1;

    pObj->pfnTick = sub_0800BDCC;
    pObj->apfnCollisionCallback[0] = sub_0800BF20;
    sub_08030844(pObj, gChestPalette);
    pObj->modeState.actor.bRoomObjectArg67_candidate = 0;
    pObj->modeState.actor.bRoomScriptArg66_candidate = 0;

    if (kind == 2)
        pObj->dwFlags &= ~5;

    if (pObj->modeState.actor.bFollowResumeDistance != 0)
    {
        if (kind == 2)
            pObj->dwFlags |= 0x82;
        else
            SetObjectAnimData(pObj, g_apRoomChestAnimFrames[kind], (void *)g_abRoomChestAnimData[kind], 8);
    }
    else
    {
        SetObjectAnimData(pObj, g_apRoomChestAnimFrames[kind], (void *)g_abRoomChestAnimData[kind], 0);
    }

    pObj->oam.priority = 1;
    pObj->bDepthSortBias = 0x80;
    return pObj;
}
