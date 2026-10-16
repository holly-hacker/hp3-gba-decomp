#include "types.h"
#include "area.h"
#include "commands.h"
#include "overworld/room_script.h"

typedef struct PlayTileActorAnimationRecord {
    u32 dwOpcode;
    u8 bTileX;
    u8 bTileY;
    u16 wAnimId;
} PlayTileActorAnimationRecord;

void RoomScriptOpPlayTileActorAnimation(PlayTileActorAnimationRecord *pRecord)
{
    Actor *pActor;

    if (g_dwRoomScriptRunState == 1)
        g_dwRoomScriptRunState = 2;
    pActor = GetRoomActorPtr(pRecord->bTileX, pRecord->bTileY);
    if (g_dwRoomScriptRunState == 2)
        pActor->dwFlags |= ActorFlagRoomScriptYield;
    SetActorAnimData_candidate(pActor, pRecord->wAnimId);
    pActor->dwFlags |= ActorFlagHasAnimation;
}
