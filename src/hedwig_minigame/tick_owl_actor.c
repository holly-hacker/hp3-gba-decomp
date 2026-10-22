#include "types.h"
#include "actor.h"
#include "math.h"
#include "random.h"
#include "save.h"
#include "sound.h"
#include "game_state.h"
#include "hedwig_minigame_inline.h"

// The owl's per-tick behavior, by OwlState. Most animations return it to
// OwlStateIdle when they end.
void TickOwlActor(Actor *pOwl)
{
    s32 care;
    u32 prevFlip;
    s32 distance;
    s32 targetX;
    s32 targetY;

    switch (pOwl->bActionState)
    {
    case OwlStateIdle:
        // wTimedMoveTicks counts the idle ticks here.
        if (++pOwl->wTimedMoveTicks < 120)
            break;

        care = FindOwlNeediestCare();
        if (g_saveStateBlock.owlCareKit.abCareCounters[care] > OWL_CARE_NEED_THRESHOLD)
        {
            PlaySoundById(49);
            SetOwlState(g_aOwlCareActionStates[care].bNeedState);
        }
        else
            SetOwlState(Mt19937RandRange(OwlStateIdleAnim1, OwlStateIdleAnim5));

        switch (pOwl->bActionState)
        {
        default:
            prevFlip = pOwl->oam.hFlip;
            pOwl->oam.hFlip = Mt19937RandRange(0, 1);
            if (pOwl->oam.hFlip != prevFlip)
                SetActorPosition(pOwl, (s16)(pOwl->pos.x >> 16) + (pOwl->oam.hFlip - prevFlip),
                                 (s16)(pOwl->pos.y >> 16));
            break;
        case OwlStateIdleAnim4:
            if ((s16)(pOwl->pos.x >> 16) <= 131)
                pOwl->oam.hFlip = 1;
            else
                pOwl->oam.hFlip = 0;
            break;
        case OwlStateIdleAnim5:
            // Hops 26-50 pixels.
            if ((s16)(pOwl->pos.x >> 16) <= 131)
            {
                pOwl->oam.hFlip = 1;
                targetX = (s16)(pOwl->pos.x >> 16) + (distance = Mt19937RandRange(1, 25) + 25);
                targetY = (s16)(pOwl->pos.y >> 16);
            }
            else
            {
                pOwl->oam.hFlip = 0;
                targetX = (s16)(pOwl->pos.x >> 16) - (distance = Mt19937RandRange(1, 25) + 25);
                targetY = (s16)(pOwl->pos.y >> 16);
            }
            SetActorMoveTargetWithDuration(pOwl, targetX, targetY, 36);
            break;
        }
        pOwl->wTimedMoveTicks = 0;
        break;
    case OwlStateRefusePet:
    case OwlStateRefuseGroom:
        if (pOwl->dwFlags & ActorFlagActionAnimDone)
            SetOwlState(OwlStateIdleAnim3);
        break;
    case OwlStateFlap:
        if (!(pOwl->dwFlags & ActorFlagActionAnimDone))
            break;

        if (pOwl->dwStateTimer == 0)
        {
            SetOwlState(OwlStateGlide);
            SetActorLocalVelocityX(pOwl, -0x8000);
            SetActorLocalVelocityY(pOwl, 0x10000);
        }
        else
        {
            pOwl->dwStateTimer--;
            if (ABS(132 - (s16)(pOwl->pos.x >> 16)) > 42)
            {
                if ((s16)(pOwl->pos.x >> 16) <= 131)
                    pOwl->oam.hFlip = 1;
                else
                    pOwl->oam.hFlip = 0;
                SetActorLocalVelocityX(pOwl, -0x10000);
            }
            SetOwlState(OwlStateFlap);
            SetActorLocalVelocityY(pOwl, pOwl->vel.y * 3 / 4);
        }
        break;
    case OwlStateLand:
        if (pOwl->dwFlags & ActorFlagActionAnimDone)
            SetOwlState(OwlStateIdle);
        break;
    case OwlStateGlide:
        if (pOwl->dwFlags & ActorFlagActionAnimDone)
        {
            SetOwlState(OwlStateGlide);
            if (ABS(132 - (s16)(pOwl->pos.x >> 16)) > 42)
            {
                if ((s16)(pOwl->pos.x >> 16) <= 131)
                    pOwl->oam.hFlip = 1;
                else
                    pOwl->oam.hFlip = 0;
                SetActorLocalVelocityX(pOwl, -0x10000);
            }
        }
        if (pOwl->pos.y > 112 << 16)
        {
            pOwl->pos.y = 112 << 16;
            SetOwlState(OwlStateLand);
            CancelActorMove_candidate(pOwl);
        }
        break;
    case OwlStateTakeOff:
        if (pOwl->dwFlags & ActorFlagActionAnimDone)
        {
            pOwl->dwStateTimer = 15;
            SetOwlState(OwlStateFlap);
            SetActorLocalVelocityX(pOwl, -0x10000);
            SetActorLocalVelocityY(pOwl, -0x18000);
        }
        break;
    case OwlStateAway:
        if (g_saveStateBlock.owlCareKit.wMailTimer == 0)
        {
            SetOwlState(OwlStateMailReturn);
            pOwl->dwFlags |= ActorFlagVisible;
            SnapActorPosition(pOwl, 120 << 16, pOwl->pos.y);
        }
        else
            pOwl->dwFlags &= ~ActorFlagVisible;
        break;
    case OwlStateMailDepart:
        if (pOwl->dwFlags & ActorFlagActionAnimDone)
        {
            g_saveStateBlock.owlCareKit.bFlags |= OwlCareKitFlagMailOut;
            g_saveStateBlock.owlCareKit.wMailTimer = 600;
            SetOwlState(OwlStateAway);
            pOwl->dwFlags &= ~ActorFlagVisible;
            SetActorLocalVelocityX(pOwl, 0);
        }
        break;
    case OwlStateMailReturn:
        if (pOwl->dwFlags & ActorFlagActionAnimDone)
        {
            SetOwlCageDoorAnim(3);
            SetOwlState(OwlStateMailDelivered);
            g_saveStateBlock.owlCareKit.bFlags &= ~OwlCareKitFlagMailOut;
        }
        break;
    case OwlStateMailDelivered:
        break;
    case OwlStateIdleAnim1:
    case OwlStateIdleAnim2:
    case OwlStateIdleAnim3:
    case OwlStateIdleAnim4:
    case OwlStateIdleAnim5:
    case OwlStateFed:
    case OwlStateCleaned:
    case OwlStatePetted:
    case OwlStateGroomed:
    case OwlStateTaught:
    case OwlStateRefuse:
    case OwlStateNeedFeed:
    case OwlStateNeedClean:
    case OwlStateNeedPet:
    case OwlStateNeedGroom:
    case OwlStateNeedExercise:
    case OwlStateNeedTeach:
    case OwlStateUnusedA:
    case OwlStateUnusedB:
    case OwlStateUnusedC:
        if (pOwl->dwFlags & ActorFlagActionAnimDone)
            SetOwlState(OwlStateIdle);
        break;
    }
}
