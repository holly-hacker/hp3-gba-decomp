#pragma once

#include "types.h"

// The snapshot of the current room's non-default objects saved with each slot
// (g_pRoomObjectStateBuffer, ROOM_OBJECT_STATE_BUFFER_SIZE bytes); see
// docs/formats/save.md. Records are opaque here: the capture and restore code
// that fills them is not decompiled.
typedef struct { u8 ab[0x6C]; } RoomObjectDefaultRecord;
typedef struct { u8 ab[0x0C]; } RoomObjectKind4Or7Record;
typedef struct { u8 ab[0x34]; } RoomObjectKind5Record;
typedef struct { u8 ab[0x0C]; } RoomObjectFloorItemRecord;
typedef struct { u8 ab[0x04]; } RoomObjectTileRecord;

#define ROOM_OBJECT_STATE_MAX_RECORDS 32
#define ROOM_OBJECT_STATE_MAX_PRESENCE_MARKERS 570

typedef struct {
    u8 bPlayerFacing;          // 0x00
    u8 bDefaultCount;          // 0x01: entries of aDefault
    u8 bKind4Or7Count;         // 0x02
    u8 bKind5Count;            // 0x03
    u8 bFloorItemCount;        // 0x04
    u8 bPresenceMarkerCount;   // 0x05
    u8 bKind5SwitchCount;      // 0x06
    u8 bPickupMarkerCount;     // 0x07
    u8 bUnsaved08;             // 0x08: not serialized
    u8 bSwitchState;           // 0x09
    u8 pad_0A[2];
    s32 fxPlayerPosX;          // 0x0C
    s32 fxPlayerPosY;          // 0x10
    RoomObjectDefaultRecord aDefault[ROOM_OBJECT_STATE_MAX_RECORDS];        // 0x14
    RoomObjectKind4Or7Record aKind4Or7[ROOM_OBJECT_STATE_MAX_RECORDS];      // 0xD94
    RoomObjectKind5Record aKind5[ROOM_OBJECT_STATE_MAX_RECORDS];            // 0xF14
    RoomObjectFloorItemRecord aFloorItem[ROOM_OBJECT_STATE_MAX_RECORDS];    // 0x1594
    RoomObjectTileRecord aKind5Switch[ROOM_OBJECT_STATE_MAX_RECORDS];       // 0x1714
    RoomObjectTileRecord aPickupMarker[16];                                 // 0x1794
    RoomObjectTileRecord aPresenceMarker[ROOM_OBJECT_STATE_MAX_PRESENCE_MARKERS];  // 0x17D4
} RoomObjectStateBuffer;

extern RoomObjectStateBuffer *g_pRoomObjectStateBuffer;
