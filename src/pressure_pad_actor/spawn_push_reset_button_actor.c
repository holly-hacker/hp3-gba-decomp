#include "types.h"
#include "area.h"
#include "pressure_pad_actor.h"

// Room actor constructor for tile actorType 8, a button that a Flipendo spell
// presses to respawn a push puzzle's actors.
Actor *SpawnPushResetButtonActor(u8 bColumn, u8 bRow)
{
    RoomActorRecordPushResetButton *pRecord = GetRoomActorStaticRecord(bColumn, bRow);
    Actor *pActor = AllocActorOfType(RoomActorType_PushResetButton);

    SnapActorPosition(pActor, pRecord->nPixelX << 16, pRecord->nPixelY << 16);
    pActor->oam.objMode = 0;
    pActor->oam.bpp8 = 0;
    pActor->oam.priority = 1;
    pActor->bDepthSortBias = 0xFF;
    pActor->wSubtype = pRecord->bVariant;
    pActor->anim.bAnimFrameDelay = 0;
    pActor->pfnTick = TickPushResetButtonActor;
    pActor->apfnCollisionCallback[0] = HandlePushResetButtonTouch;
    PUSH_RESET_BUTTON_TARGETS(pActor)->abGroups[0] = pRecord->abTargets[0];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abMembers[0] = pRecord->abTargets[1];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abGroups[1] = pRecord->abTargets[2];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abMembers[1] = pRecord->abTargets[3];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abGroups[2] = pRecord->abTargets[4];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abMembers[2] = pRecord->abTargets[5];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abGroups[3] = pRecord->abTargets[6];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abMembers[3] = pRecord->abTargets[7];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abGroups[4] = pRecord->abTargets[8];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abMembers[4] = pRecord->abTargets[9];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abGroups[5] = pRecord->abTargets[10];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abMembers[5] = pRecord->abTargets[11];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abGroups[6] = pRecord->abTargets[12];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abMembers[6] = pRecord->abTargets[13];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abGroups[7] = pRecord->abTargets[14];
    PUSH_RESET_BUTTON_TARGETS(pActor)->abMembers[7] = pRecord->abTargets[15];
    pActor->dwFlags = ActorFlagVisible | ActorFlagWantsCollisionCheck | ActorFlagHasTickLogic
                      | ActorFlagHasAnimation | ActorFlagTerrainCollision | ActorFlagUnk2000
                      | ActorFlagTerrainDrawLayer;
    SetActorPendingPalette(pActor, g_apPushResetButtonPalettes[pActor->wSubtype]);
    SetActorAssetRecord(pActor, g_apPushResetButtonSprites[pActor->wSubtype]);
    SetActorAnimFrame(pActor, 0);
    SetActorActionState(pActor, 0);
    return pActor;
}
