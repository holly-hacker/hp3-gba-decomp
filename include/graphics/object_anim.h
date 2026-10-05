#pragma once

// Object animation command streams, attached with SetObjectAnimData and played
// two bytes at a time from Object.pAnimFrameCursor by sub_080021F4
// (AdvanceAnimationCommand in docs/formats/battle_scripts.md). A first byte up
// to 0xEE shows that animation frame for the second byte's count of ticks (0
// holds it); 0xEF-0xFF are commands that run immediately, in sequence, until
// the next frame. Move distances are whole pixels.

#define ANIM_FRAME(frame, duration) (frame), (duration)
// x += dx (signed); x -= dx while the object is horizontally flipped.
#define ANIM_MOVE_FORWARD(dx)       0xEF, (u8)(dx)
// Sets ObjectFlagActionAnimDone and stays on this command. The operand is
// ignored; a few monster animations store 0xFF there (ANIM_END_ARG).
#define ANIM_END                    0xF0, 0
#define ANIM_END_ARG(arg)           0xF0, (arg)
#define ANIM_TOGGLE_VFLIP           0xF1, 0
#define ANIM_TOGGLE_HFLIP           0xF2, 0
#define ANIM_SHOW                   0xF3, 0  // sets ObjectFlagVisible
#define ANIM_HIDE                   0xF4, 0  // clears ObjectFlagVisible
#define ANIM_MOVE_DOWN_LEFT(d)      0xF5, (d)
#define ANIM_MOVE_UP_LEFT(d)        0xF6, (d)
#define ANIM_MOVE_DOWN_RIGHT(d)     0xF7, (d)
#define ANIM_MOVE_UP_RIGHT(d)       0xF8, (d)
#define ANIM_MOVE_DOWN(d)           0xF9, (d)
#define ANIM_MOVE_UP(d)             0xFA, (d)
#define ANIM_MOVE_LEFT(d)           0xFB, (d)
#define ANIM_MOVE_RIGHT(d)          0xFC, (d)
#define ANIM_SOUND(id)              0xFD, (id)  // PlaySoundById
// Continues at the stream's command `index` (counted in 2-byte commands from
// the base SetObjectAnimData was given).
#define ANIM_JUMP(index)            0xFE, (index)
// Sets ObjectFlagSpecialMoveTrigger and stores `marker` in Object.unk_DC for
// one tick; see WaitForCounter in docs/formats/battle_scripts.md.
#define ANIM_EVENT(marker)          0xFF, (marker)
