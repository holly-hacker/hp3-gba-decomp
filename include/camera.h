#pragma once

#include "types.h"
#include "math.h"
#include "actor.h"

// Per-slot scripted camera effect, started by room script opcodes 0x10
// (QueueTileActorMove: pan the camera focus to an actor) and 0x12
// (SetAllQueuedMoveParams: shake). One 0x2C-byte record per control slot,
// ticked by TickCameraFocus_candidate.
typedef struct CameraEffect {
    Actor *pTarget;           // 0x00, pan target
    FixedPoint savedVel;       // 0x04, the controlled actor's velocity, restored when the pan ends
    u8 pad_0C[0x08];           // -> 0x14
    s32 nStep;                 // 0x14, pan speed; shake amplitude (posX << 16) in state 3
    u32 dwFramesLeft;          // 0x18, shake duration in frames
    u32 dwRunForever;          // 0x1C, shake: nonzero when the duration operand was 0
    u16 wCounter;              // 0x20, pan: frames to wait; shake: 0/1 toggle
    u8 pad_22;                 // -> 0x23
    u8 bRespawnRow;            // 0x23, first argument to RespawnGroupAndRunChain
    u8 bChainRow;              // 0x24, second argument to RespawnGroupAndRunChain
    u8 bState;                 // 0x25, 0 = idle, 1 = pan, 3 = shake
    u8 bSavedActionSubState;   // 0x26, controlled actor's bActionSubState when the pan began
    u8 bChainRan;              // 0x27, set once the pan's chain has run
    u32 dwResumeScript;        // 0x28, nonzero: resume the yielded room script when the pan ends
} CameraEffect;
extern CameraEffect g_aCameraEffects_candidate[];

// Per-slot camera focus point: what UpdateOverworldCamera centres the
// screen on (16.16 world coordinates). Follows pTarget unless wPinned is nonzero.
typedef struct CameraFocusSlot {
    FixedPoint focus;          // 0x00
    FixedPoint aUnused[2];     // 0x08, zeroed by ResetCameraFocusSlot; no other access found
    FixedPoint latched;        // 0x18, copy of the focus point
    IntPoint scrollMin;        // 0x20, room scroll bounds; only slot 0's are used
    IntPoint scrollMax;        // 0x28
    Actor *pTarget;            // 0x30, actor the focus follows
    u16 wPinned;               // 0x34, 0 = follow pTarget every frame, 1 = hold
} CameraFocusSlot;
extern CameraFocusSlot g_aCameraFocusSlots[];

// Camera offset applied to the player's follow target.
typedef struct CameraFocusOffset {
    s32 nX;
    s32 nY;
} CameraFocusOffset;
extern CameraFocusOffset g_aCameraFollowOffsets[];

// Result of MoveCameraFocusToward once the focus is on the target.
#define CAMERA_FOCUS_ARRIVED 8

// Resets a camera focus slot and its effect state; the focus then holds (wPinned = 1).
extern void ResetCameraFocusSlot(u8 slot);
// Ticks slot's camera focus: follows the target actor, or runs the active pan/shake
// effect and its completion chain.
extern void TickCameraFocus_candidate(u8 slot);
// Steps the focus up to step units toward target, snapping onto it when
// within step on both axes. Returns CAMERA_FOCUS_ARRIVED on arrival, 0 otherwise.
extern u8 MoveCameraFocusToward(FixedPoint target, s32 step, u8 slot);
// Sets the focus and its latched copy to position.
extern void SnapCameraFocus(FixedPoint position, u8 slot);
// wPinned = pinned; cancels any scripted effect, and pinning with 1 also drops the target.
extern void SetCameraFocusPinned(u32 pinned, u8 slot);
// Stores a position into a slot's focus point.
extern void SetCameraFocusPosition(FixedPoint position, u8 slot);
extern void SetCameraFollowTarget_candidate(Actor *pTarget, CameraFocusOffset offset, u8 slot);
// Writes the slot's focus as two 16.16 words.
extern void GetCameraFocusPosition(FixedPoint *pPosition, u8 slot);
extern void GetCameraFollowOffset(CameraFocusOffset *pOffset, u8 slot);
// Moves the focus by delta and updates the latched copy.
extern void OffsetCameraFocus(FixedPoint delta, u8 slot);
extern void SetCameraFollowOffset(CameraFocusOffset offset, u8 slot);
// Writes the focus's on-screen pixel position: its integer part minus the camera position.
extern void GetCameraFocusScreenPosition(s32 *pPosition, u8 slot);
// Writes the room's scroll bounds, or (0, 0)-(defaultMaxX, defaultMaxY) when all four are zero.
extern void GetRoomScrollBounds(IntPoint *pMin, IntPoint *pMax, s32 defaultMaxX, s32 defaultMaxY);
extern void SetRoomScrollBounds(u16 minX, u16 minY, u16 maxX, u16 maxY);
