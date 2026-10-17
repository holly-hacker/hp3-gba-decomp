#include "actor.h"
#include "sound.h"

// Runs the commands at the animation cursor until it reaches a frame, which
// becomes the current frame for its duration; see actor_anim.h. Move
// commands change the position directly, in whole pixels.
void RunActorAnimCommands(Actor *actor)
{
    ActorAnimState *anim;
    u8 *cursor;
    s32 running;

    actor->dwFlags &= ~ActorFlagActionAnimDone;
    anim = &actor->anim;
    cursor = anim->pAnimFrameCursor;
    running = 1;

    while (running) {
        if (cursor[0] <= 0xEE) {
            anim->bLastAnimFrameValue = cursor[0];
            anim->bAnimFrameCounter = cursor[1];
            running = 0;
        }
        else {
            switch (cursor[0]) {
            case 0xFF:
                actor->dwFlags |= ActorFlagSpecialMoveTrigger;
                actor->anim.unk_DC.bEnemyAttackPhase_candidate = cursor[1];
                actor->anim.bAnimFrameCounter = 1;
                running = 0;
                break;
            case 0xFE:
                actor->anim.pAnimFrameCursor = actor->anim.pAnimFrameBase + cursor[1] * 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xFD:
                PlaySoundById(cursor[1]);
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xFC:
                actor->pos.x += cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xFB:
                actor->pos.x -= cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xFA:
                actor->pos.y -= cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF9:
                actor->pos.y += cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF8:
                actor->pos.x += cursor[1] << 16;
                actor->pos.y -= cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF7:
                actor->pos.x += cursor[1] << 16;
                actor->pos.y += cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF6:
                actor->pos.x -= cursor[1] << 16;
                actor->pos.y -= cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF5:
                actor->pos.x -= cursor[1] << 16;
                actor->pos.y += cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF4:
                actor->dwFlags &= ~ActorFlagVisible;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF3:
                actor->dwFlags |= ActorFlagVisible;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF2:
                actor->oam.hFlip = !actor->oam.hFlip;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF1:
                actor->oam.vFlip = !actor->oam.vFlip;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF0:
                actor->dwFlags |= ActorFlagActionAnimDone;
                running = 0;
                break;
            case 0xEF:
                if (!actor->oam.hFlip)
                    actor->pos.x += (s8)cursor[1] << 16;
                else
                    actor->pos.x -= (s8)cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            }
        }
    }
}
