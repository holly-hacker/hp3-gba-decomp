#include "types.h"
#include "actor.h"
#include "sound.h"
#include "torch_actor.h"

// Relights a flame pillar for a full burn; RestoreRoomActorState uses it for
// pillars saved while lit.
void IgniteFlamePillar(Actor *pActor)
{
    pActor->dwStateTimer = pActor->modeState.flamePillar.wLitTicks;
    SetActorAnimData(pActor, g_apRoomFlamePillarAnimFrames[pActor->wSubtype],
                     g_abRoomFlamePillarAnimData, 0);
    SetActorActionSubState(pActor, 8);
    g_nFlamePillarSoundHandle = PlaySoundByIdUnlessActive(18, g_nFlamePillarSoundHandle);
}
