#include "graphics/object.h"
#include "graphics/object_anim.h"
#include "graphics/audio.h"

// Runs the commands at the animation cursor until it reaches a frame, which
// becomes the current frame for its duration; see graphics/object_anim.h. Move
// commands change the position directly, in whole pixels.
void RunObjectAnimCommands(Object *obj)
{
    ObjectAnimState *anim;
    u8 *cursor;
    s32 running;

    obj->dwFlags &= ~ObjectFlagActionAnimDone;
    anim = &obj->anim;
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
                obj->dwFlags |= ObjectFlagSpecialMoveTrigger;
                obj->anim.unk_DC.bEnemyAttackPhase_candidate = cursor[1];
                obj->anim.bAnimFrameCounter = 1;
                running = 0;
                break;
            case 0xFE:
                obj->anim.pAnimFrameCursor = obj->anim.pAnimFrameBase + cursor[1] * 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xFD:
                PlaySoundById(cursor[1]);
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xFC:
                obj->pos.x += cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xFB:
                obj->pos.x -= cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xFA:
                obj->pos.y -= cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF9:
                obj->pos.y += cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF8:
                obj->pos.x += cursor[1] << 16;
                obj->pos.y -= cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF7:
                obj->pos.x += cursor[1] << 16;
                obj->pos.y += cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF6:
                obj->pos.x -= cursor[1] << 16;
                obj->pos.y -= cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF5:
                obj->pos.x -= cursor[1] << 16;
                obj->pos.y += cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF4:
                obj->dwFlags &= ~ObjectFlagVisible;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF3:
                obj->dwFlags |= ObjectFlagVisible;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF2:
                obj->oam.hFlip = !obj->oam.hFlip;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF1:
                obj->oam.vFlip = !obj->oam.vFlip;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            case 0xF0:
                obj->dwFlags |= ObjectFlagActionAnimDone;
                running = 0;
                break;
            case 0xEF:
                if (!obj->oam.hFlip)
                    obj->pos.x += (s8)cursor[1] << 16;
                else
                    obj->pos.x -= (s8)cursor[1] << 16;
                anim->pAnimFrameCursor += 2;
                cursor = anim->pAnimFrameCursor;
                break;
            }
        }
    }
}
