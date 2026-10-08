#include "types.h"
#include "overworld/room.h"

// Room tile animation sets; see docs/memory-map/frame_systems.md.

#define FRAME(frame) ((const RoomTileAnimFrame *)&(frame))

const ROOM_TILE_ANIM_FRAME(0) g_RoomTileAnimHaltFrame = { 0, ROOM_TILE_ANIM_HALT, 0x00 };
const ROOM_TILE_ANIM_FRAME(0) g_RoomTileAnimLoopFrame = { 0, ROOM_TILE_ANIM_LOOP, 0x00 };
const ROOM_TILE_ANIM_FRAME(3) g_RoomTileAnim0Frame0 = {
    3, 3, 0x1F,
    {
        { 18, 1 }, { 18, 2 }, { 18, 3 },
    },
};
const ROOM_TILE_ANIM_FRAME(3) g_RoomTileAnim0Frame1 = {
    3, 0, 0x1F,
    {
        { 19, 1 }, { 19, 2 }, { 19, 3 },
    },
};

const ROOM_TILE_ANIM_SET(3) g_RoomTileAnim0 = {
    3,
    {
        FRAME(g_RoomTileAnim0Frame0),
        FRAME(g_RoomTileAnim0Frame1),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim1Frame0 = {
    4, 3, 0x1F,
    {
        { 35, 27 }, { 35, 28 }, { 36, 27 }, { 36, 28 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim1Frame1 = {
    4, 0, 0x1F,
    {
        { 37, 27 }, { 37, 28 }, { 38, 27 }, { 38, 28 },
    },
};

const ROOM_TILE_ANIM_SET(3) g_RoomTileAnim1 = {
    3,
    {
        FRAME(g_RoomTileAnim1Frame0),
        FRAME(g_RoomTileAnim1Frame1),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim2Frame0 = {
    4, 3, 0x1F,
    {
        { 0, 27 }, { 1, 27 }, { 0, 28 }, { 1, 28 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim2Frame1 = {
    4, 3, 0x1F,
    {
        { 2, 27 }, { 3, 27 }, { 2, 28 }, { 3, 28 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim2Frame2 = {
    4, 3, 0x1F,
    {
        { 4, 27 }, { 5, 27 }, { 4, 28 }, { 5, 28 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim2Frame3 = {
    4, 3, 0x1F,
    {
        { 6, 27 }, { 7, 27 }, { 6, 28 }, { 7, 28 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim2Frame4 = {
    4, 0, 0x1F,
    {
        { 8, 27 }, { 9, 27 }, { 8, 28 }, { 9, 28 },
    },
};

const ROOM_TILE_ANIM_SET(6) g_RoomTileAnim2 = {
    6,
    {
        FRAME(g_RoomTileAnim2Frame0),
        FRAME(g_RoomTileAnim2Frame1),
        FRAME(g_RoomTileAnim2Frame2),
        FRAME(g_RoomTileAnim2Frame3),
        FRAME(g_RoomTileAnim2Frame4),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim3Frame0 = {
    4, 3, 0x1F,
    {
        { 19, 1 }, { 20, 1 }, { 19, 2 }, { 20, 2 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim3Frame1 = {
    4, 3, 0x1F,
    {
        { 21, 1 }, { 22, 1 }, { 21, 2 }, { 22, 2 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim3Frame2 = {
    4, 0, 0x1F,
    {
        { 23, 1 }, { 24, 1 }, { 23, 2 }, { 24, 2 },
    },
};

const ROOM_TILE_ANIM_SET(4) g_RoomTileAnim3 = {
    4,
    {
        FRAME(g_RoomTileAnim3Frame0),
        FRAME(g_RoomTileAnim3Frame1),
        FRAME(g_RoomTileAnim3Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim4Frame0 = {
    4, 2, 0x1F,
    {
        { 26, 6 }, { 27, 6 }, { 26, 7 }, { 27, 7 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim4Frame1 = {
    4, 2, 0x1F,
    {
        { 28, 6 }, { 29, 6 }, { 28, 7 }, { 29, 7 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim4Frame2 = {
    4, 0, 0x1F,
    {
        { 30, 6 }, { 31, 6 }, { 30, 7 }, { 31, 7 },
    },
};

const ROOM_TILE_ANIM_SET(4) g_RoomTileAnim4 = {
    4,
    {
        FRAME(g_RoomTileAnim4Frame0),
        FRAME(g_RoomTileAnim4Frame1),
        FRAME(g_RoomTileAnim4Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(2) g_RoomTileAnim5Frame0 = {
    2, 0, 0x1F,
    {
        { 2, 31 }, { 3, 31 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim5 = {
    2,
    {
        FRAME(g_RoomTileAnim5Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(2) g_RoomTileAnim6Frame0 = {
    2, 3, 0x1F,
    {
        { 3, 8 }, { 3, 9 },
    },
};
const ROOM_TILE_ANIM_FRAME(2) g_RoomTileAnim6Frame1 = {
    2, 3, 0x1F,
    {
        { 3, 10 }, { 3, 11 },
    },
};
const ROOM_TILE_ANIM_FRAME(2) g_RoomTileAnim6Frame2 = {
    2, 3, 0x1F,
    {
        { 3, 12 }, { 3, 13 },
    },
};

const ROOM_TILE_ANIM_SET(7) g_RoomTileAnim6 = {
    7,
    {
        FRAME(g_RoomTileAnim6Frame1),
        FRAME(g_RoomTileAnim6Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim6Frame1),
        FRAME(g_RoomTileAnim6Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim7Frame0 = {
    4, 3, 0x1F,
    {
        { 6, 8 }, { 7, 8 }, { 6, 9 }, { 7, 9 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim7Frame1 = {
    4, 3, 0x1F,
    {
        { 6, 10 }, { 7, 10 }, { 6, 11 }, { 7, 11 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim7Frame2 = {
    4, 3, 0x1F,
    {
        { 6, 12 }, { 7, 12 }, { 6, 13 }, { 7, 13 },
    },
};

const ROOM_TILE_ANIM_SET(8) g_RoomTileAnim7 = {
    8,
    {
        FRAME(g_RoomTileAnim7Frame0),
        FRAME(g_RoomTileAnim7Frame1),
        FRAME(g_RoomTileAnim7Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim7Frame1),
        FRAME(g_RoomTileAnim7Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim8Frame0 = {
    4, 3, 0x1F,
    {
        { 10, 8 }, { 11, 8 }, { 10, 9 }, { 11, 9 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim8Frame1 = {
    4, 3, 0x1F,
    {
        { 10, 10 }, { 11, 10 }, { 10, 11 }, { 11, 11 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim8Frame2 = {
    4, 3, 0x1F,
    {
        { 10, 12 }, { 11, 12 }, { 10, 13 }, { 11, 13 },
    },
};

const ROOM_TILE_ANIM_SET(7) g_RoomTileAnim8 = {
    7,
    {
        FRAME(g_RoomTileAnim8Frame1),
        FRAME(g_RoomTileAnim8Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim8Frame1),
        FRAME(g_RoomTileAnim8Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim9Frame0 = {
    4, 3, 0x1F,
    {
        { 16, 8 }, { 17, 8 }, { 16, 9 }, { 17, 9 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim9Frame1 = {
    4, 3, 0x1F,
    {
        { 16, 10 }, { 17, 10 }, { 16, 11 }, { 17, 11 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim9Frame2 = {
    4, 3, 0x1F,
    {
        { 16, 12 }, { 17, 12 }, { 16, 13 }, { 17, 13 },
    },
};

const ROOM_TILE_ANIM_SET(7) g_RoomTileAnim9 = {
    7,
    {
        FRAME(g_RoomTileAnim9Frame1),
        FRAME(g_RoomTileAnim9Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim9Frame1),
        FRAME(g_RoomTileAnim9Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim10Frame0 = {
    4, 3, 0x1F,
    {
        { 20, 8 }, { 21, 8 }, { 20, 9 }, { 21, 9 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim10Frame1 = {
    4, 3, 0x1F,
    {
        { 20, 10 }, { 21, 10 }, { 20, 11 }, { 21, 11 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim10Frame2 = {
    4, 3, 0x1F,
    {
        { 20, 12 }, { 21, 12 }, { 20, 13 }, { 21, 13 },
    },
};

const ROOM_TILE_ANIM_SET(7) g_RoomTileAnim10 = {
    7,
    {
        FRAME(g_RoomTileAnim10Frame1),
        FRAME(g_RoomTileAnim10Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim10Frame1),
        FRAME(g_RoomTileAnim10Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(2) g_RoomTileAnim11Frame0 = {
    2, 3, 0x1F,
    {
        { 24, 8 }, { 24, 9 },
    },
};
const ROOM_TILE_ANIM_FRAME(2) g_RoomTileAnim11Frame1 = {
    2, 3, 0x1F,
    {
        { 24, 10 }, { 24, 11 },
    },
};
const ROOM_TILE_ANIM_FRAME(2) g_RoomTileAnim11Frame2 = {
    2, 3, 0x1F,
    {
        { 24, 12 }, { 24, 13 },
    },
};

const ROOM_TILE_ANIM_SET(7) g_RoomTileAnim11 = {
    7,
    {
        FRAME(g_RoomTileAnim11Frame1),
        FRAME(g_RoomTileAnim11Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim11Frame1),
        FRAME(g_RoomTileAnim11Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim19Frame0 = {
    4, 3, 0x1F,
    {
        { 4, 11 }, { 5, 11 }, { 4, 12 }, { 5, 12 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim19Frame1 = {
    4, 3, 0x1F,
    {
        { 4, 13 }, { 5, 13 }, { 4, 14 }, { 5, 14 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim19Frame2 = {
    4, 3, 0x1F,
    {
        { 4, 15 }, { 5, 15 }, { 4, 16 }, { 5, 16 },
    },
};

const ROOM_TILE_ANIM_SET(7) g_RoomTileAnim19 = {
    7,
    {
        FRAME(g_RoomTileAnim19Frame1),
        FRAME(g_RoomTileAnim19Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim19Frame1),
        FRAME(g_RoomTileAnim19Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim20Frame0 = {
    4, 3, 0x1F,
    {
        { 9, 11 }, { 10, 11 }, { 9, 12 }, { 10, 12 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim20Frame1 = {
    4, 3, 0x1F,
    {
        { 9, 13 }, { 10, 13 }, { 9, 14 }, { 10, 14 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim20Frame2 = {
    4, 3, 0x1F,
    {
        { 9, 15 }, { 10, 15 }, { 9, 16 }, { 10, 16 },
    },
};

const ROOM_TILE_ANIM_SET(7) g_RoomTileAnim20 = {
    7,
    {
        FRAME(g_RoomTileAnim20Frame1),
        FRAME(g_RoomTileAnim20Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim20Frame1),
        FRAME(g_RoomTileAnim20Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim21Frame0 = {
    4, 3, 0x1F,
    {
        { 14, 11 }, { 15, 11 }, { 14, 12 }, { 15, 12 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim21Frame1 = {
    4, 3, 0x1F,
    {
        { 14, 13 }, { 15, 13 }, { 14, 14 }, { 15, 14 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim21Frame2 = {
    4, 3, 0x1F,
    {
        { 14, 15 }, { 15, 15 }, { 14, 16 }, { 15, 16 },
    },
};

const ROOM_TILE_ANIM_SET(7) g_RoomTileAnim21 = {
    7,
    {
        FRAME(g_RoomTileAnim21Frame1),
        FRAME(g_RoomTileAnim21Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim21Frame1),
        FRAME(g_RoomTileAnim21Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim12Frame0 = {
    4, 0, 0x04,
    {
        { 9, 0 }, { 9, 1 }, { 9, 2 }, { 9, 3 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim12Frame1 = {
    4, 0, 0x1F,
    {
        { 9, 5 }, { 9, 6 }, { 9, 7 }, { 9, 8 },
    },
};

const ROOM_TILE_ANIM_SET(3) g_RoomTileAnim12 = {
    3,
    {
        FRAME(g_RoomTileAnim12Frame0),
        FRAME(g_RoomTileAnim12Frame1),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(24) g_RoomTileAnimUnusedFrame0 = {
    24, 3, 0x1F,
    {
        { 10, 7 }, { 11, 7 }, { 12, 7 }, { 10, 8 },
        { 11, 8 }, { 12, 8 }, { 13, 8 }, { 11, 9 },
        { 12, 9 }, { 13, 9 }, { 12, 10 }, { 13, 10 },
        { 14, 10 }, { 13, 11 }, { 14, 11 }, { 15, 11 },
        { 16, 11 }, { 17, 11 }, { 13, 12 }, { 14, 12 },
        { 15, 12 }, { 16, 12 }, { 17, 12 }, { 18, 12 },
    },
};
const ROOM_TILE_ANIM_FRAME(24) g_RoomTileAnimUnusedFrame1 = {
    24, 3, 0x1F,
    {
        { 10, 0 }, { 11, 0 }, { 12, 0 }, { 10, 1 },
        { 11, 1 }, { 12, 1 }, { 13, 1 }, { 11, 2 },
        { 12, 2 }, { 13, 2 }, { 12, 3 }, { 13, 3 },
        { 14, 3 }, { 13, 4 }, { 14, 4 }, { 15, 4 },
        { 16, 4 }, { 17, 4 }, { 13, 5 }, { 14, 5 },
        { 15, 5 }, { 16, 5 }, { 17, 5 }, { 18, 5 },
    },
};
const ROOM_TILE_ANIM_FRAME(2) g_RoomTileAnim13Frame2 = {
    2, 0, 0x1F,
    {
        { 8, 17 }, { 9, 17 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim13 = {
    2,
    {
        FRAME(g_RoomTileAnim13Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim14Frame0 = {
    4, 0, 0x1F,
    {
        { 11, 18 }, { 12, 18 }, { 11, 19 }, { 12, 19 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim14 = {
    2,
    {
        FRAME(g_RoomTileAnim14Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim15Frame0 = {
    4, 0, 0x1F,
    {
        { 17, 18 }, { 18, 18 }, { 17, 19 }, { 18, 19 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim15 = {
    2,
    {
        FRAME(g_RoomTileAnim15Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(1) g_RoomTileAnim16Frame0 = {
    1, 3, 0x1F,
    {
        { 1, 15 },
    },
};
const ROOM_TILE_ANIM_FRAME(1) g_RoomTileAnim16Frame1 = {
    1, 3, 0x1F,
    {
        { 1, 16 },
    },
};
const ROOM_TILE_ANIM_FRAME(1) g_RoomTileAnim16Frame2 = {
    1, 3, 0x1F,
    {
        { 1, 17 },
    },
};

const ROOM_TILE_ANIM_SET(7) g_RoomTileAnim16 = {
    7,
    {
        FRAME(g_RoomTileAnim16Frame0),
        FRAME(g_RoomTileAnim16Frame1),
        FRAME(g_RoomTileAnim16Frame2),
        FRAME(g_RoomTileAnim16Frame1),
        FRAME(g_RoomTileAnim16Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(11) g_RoomTileAnim17Frame0 = {
    11, 2, 0x1F,
    {
        { 11, 15 }, { 12, 15 }, { 13, 15 }, { 14, 15 },
        { 15, 15 }, { 16, 15 }, { 17, 15 }, { 18, 15 },
        { 19, 15 }, { 20, 15 }, { 21, 15 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame1 = {
    12, 2, 0x1F,
    {
        { 11, 15 }, { 11, 16 }, { 12, 16 }, { 13, 16 },
        { 14, 16 }, { 15, 16 }, { 16, 16 }, { 17, 16 },
        { 18, 16 }, { 19, 16 }, { 20, 16 }, { 21, 16 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame2 = {
    12, 2, 0x1F,
    {
        { 11, 15 }, { 11, 17 }, { 12, 17 }, { 13, 17 },
        { 14, 17 }, { 15, 17 }, { 16, 17 }, { 17, 17 },
        { 18, 17 }, { 19, 17 }, { 20, 17 }, { 21, 17 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame3 = {
    12, 2, 0x1F,
    {
        { 11, 15 }, { 11, 18 }, { 12, 18 }, { 13, 18 },
        { 14, 18 }, { 15, 18 }, { 16, 18 }, { 17, 18 },
        { 18, 18 }, { 19, 18 }, { 20, 18 }, { 21, 18 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame4 = {
    12, 2, 0x1F,
    {
        { 11, 15 }, { 11, 19 }, { 12, 19 }, { 13, 19 },
        { 14, 19 }, { 15, 19 }, { 16, 19 }, { 17, 19 },
        { 18, 19 }, { 19, 19 }, { 20, 19 }, { 21, 19 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame5 = {
    12, 2, 0x1F,
    {
        { 11, 15 }, { 11, 20 }, { 12, 20 }, { 13, 20 },
        { 14, 20 }, { 15, 20 }, { 16, 20 }, { 17, 20 },
        { 18, 20 }, { 19, 20 }, { 20, 20 }, { 21, 20 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame6 = {
    12, 2, 0x1F,
    {
        { 11, 15 }, { 11, 21 }, { 12, 21 }, { 13, 21 },
        { 14, 21 }, { 15, 21 }, { 16, 21 }, { 17, 21 },
        { 18, 21 }, { 19, 21 }, { 20, 21 }, { 21, 21 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame7 = {
    12, 2, 0x1F,
    {
        { 11, 15 }, { 11, 22 }, { 12, 22 }, { 13, 22 },
        { 14, 22 }, { 15, 22 }, { 16, 22 }, { 17, 22 },
        { 18, 22 }, { 19, 22 }, { 20, 22 }, { 21, 22 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame8 = {
    12, 2, 0x1F,
    {
        { 11, 15 }, { 11, 23 }, { 12, 23 }, { 13, 23 },
        { 14, 23 }, { 15, 23 }, { 16, 23 }, { 17, 23 },
        { 18, 23 }, { 19, 23 }, { 20, 23 }, { 21, 23 },
    },
};
const ROOM_TILE_ANIM_FRAME(11) g_RoomTileAnim17Frame9 = {
    11, 2, 0x1F,
    {
        { 11, 24 }, { 12, 24 }, { 13, 24 }, { 14, 24 },
        { 15, 24 }, { 16, 24 }, { 17, 24 }, { 18, 24 },
        { 19, 24 }, { 20, 24 }, { 21, 24 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame10 = {
    12, 2, 0x1F,
    {
        { 11, 24 }, { 11, 25 }, { 12, 25 }, { 13, 25 },
        { 14, 25 }, { 15, 25 }, { 16, 25 }, { 17, 25 },
        { 18, 25 }, { 19, 25 }, { 20, 25 }, { 21, 25 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame11 = {
    12, 2, 0x1F,
    {
        { 11, 24 }, { 11, 26 }, { 12, 26 }, { 13, 26 },
        { 14, 26 }, { 15, 26 }, { 16, 26 }, { 17, 26 },
        { 18, 26 }, { 19, 26 }, { 20, 26 }, { 21, 26 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame12 = {
    12, 2, 0x1F,
    {
        { 11, 24 }, { 11, 27 }, { 12, 27 }, { 13, 27 },
        { 14, 27 }, { 15, 27 }, { 16, 27 }, { 17, 27 },
        { 18, 27 }, { 19, 27 }, { 20, 27 }, { 21, 27 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame13 = {
    12, 2, 0x1F,
    {
        { 11, 24 }, { 11, 28 }, { 12, 28 }, { 13, 28 },
        { 14, 28 }, { 15, 28 }, { 16, 28 }, { 17, 28 },
        { 18, 28 }, { 19, 28 }, { 20, 28 }, { 21, 28 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame14 = {
    12, 2, 0x1F,
    {
        { 11, 24 }, { 11, 29 }, { 12, 29 }, { 13, 29 },
        { 14, 29 }, { 15, 29 }, { 16, 29 }, { 17, 29 },
        { 18, 29 }, { 19, 29 }, { 20, 29 }, { 21, 29 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame15 = {
    12, 2, 0x1F,
    {
        { 11, 24 }, { 11, 30 }, { 12, 30 }, { 13, 30 },
        { 14, 30 }, { 15, 30 }, { 16, 30 }, { 17, 30 },
        { 18, 30 }, { 19, 30 }, { 20, 30 }, { 21, 30 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame16 = {
    12, 2, 0x1F,
    {
        { 11, 24 }, { 11, 31 }, { 12, 31 }, { 13, 31 },
        { 14, 31 }, { 15, 31 }, { 16, 31 }, { 17, 31 },
        { 18, 31 }, { 19, 31 }, { 20, 31 }, { 21, 31 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim17Frame17 = {
    12, 2, 0x1F,
    {
        { 11, 24 }, { 11, 32 }, { 12, 32 }, { 13, 32 },
        { 14, 32 }, { 15, 32 }, { 16, 32 }, { 17, 32 },
        { 18, 32 }, { 19, 32 }, { 20, 32 }, { 21, 32 },
    },
};

const ROOM_TILE_ANIM_SET(21) g_RoomTileAnim17 = {
    21,
    {
        FRAME(g_RoomTileAnim17Frame8),
        FRAME(g_RoomTileAnim17Frame7),
        FRAME(g_RoomTileAnim17Frame6),
        FRAME(g_RoomTileAnim17Frame5),
        FRAME(g_RoomTileAnim17Frame4),
        FRAME(g_RoomTileAnim17Frame3),
        FRAME(g_RoomTileAnim17Frame2),
        FRAME(g_RoomTileAnim17Frame1),
        FRAME(g_RoomTileAnim17Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim17Frame9),
        FRAME(g_RoomTileAnim17Frame10),
        FRAME(g_RoomTileAnim17Frame11),
        FRAME(g_RoomTileAnim17Frame12),
        FRAME(g_RoomTileAnim17Frame13),
        FRAME(g_RoomTileAnim17Frame14),
        FRAME(g_RoomTileAnim17Frame15),
        FRAME(g_RoomTileAnim17Frame16),
        FRAME(g_RoomTileAnim17Frame17),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(11) g_RoomTileAnim18Frame0 = {
    11, 2, 0x1F,
    {
        { 0, 15 }, { 1, 15 }, { 2, 15 }, { 3, 15 },
        { 4, 15 }, { 5, 15 }, { 6, 15 }, { 7, 15 },
        { 8, 15 }, { 9, 15 }, { 10, 15 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame1 = {
    12, 2, 0x1F,
    {
        { 0, 15 }, { 0, 16 }, { 1, 16 }, { 2, 16 },
        { 3, 16 }, { 4, 16 }, { 5, 16 }, { 6, 16 },
        { 7, 16 }, { 8, 16 }, { 9, 16 }, { 10, 16 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame2 = {
    12, 2, 0x1F,
    {
        { 0, 15 }, { 0, 17 }, { 1, 17 }, { 2, 17 },
        { 3, 17 }, { 4, 17 }, { 5, 17 }, { 6, 17 },
        { 7, 17 }, { 8, 17 }, { 9, 17 }, { 10, 17 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame3 = {
    12, 2, 0x1F,
    {
        { 0, 15 }, { 0, 18 }, { 1, 18 }, { 2, 18 },
        { 3, 18 }, { 4, 18 }, { 5, 18 }, { 6, 18 },
        { 7, 18 }, { 8, 18 }, { 9, 18 }, { 10, 18 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame4 = {
    12, 2, 0x1F,
    {
        { 0, 15 }, { 0, 19 }, { 1, 19 }, { 2, 19 },
        { 3, 19 }, { 4, 19 }, { 5, 19 }, { 6, 19 },
        { 7, 19 }, { 8, 19 }, { 9, 19 }, { 10, 19 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame5 = {
    12, 2, 0x1F,
    {
        { 0, 15 }, { 0, 20 }, { 1, 20 }, { 2, 20 },
        { 3, 20 }, { 4, 20 }, { 5, 20 }, { 6, 20 },
        { 7, 20 }, { 8, 20 }, { 9, 20 }, { 10, 20 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame6 = {
    12, 2, 0x1F,
    {
        { 0, 15 }, { 0, 21 }, { 1, 21 }, { 2, 21 },
        { 3, 21 }, { 4, 21 }, { 5, 21 }, { 6, 21 },
        { 7, 21 }, { 8, 21 }, { 9, 21 }, { 10, 21 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame7 = {
    12, 2, 0x1F,
    {
        { 0, 15 }, { 0, 22 }, { 1, 22 }, { 2, 22 },
        { 3, 22 }, { 4, 22 }, { 5, 22 }, { 6, 22 },
        { 7, 22 }, { 8, 22 }, { 9, 22 }, { 10, 22 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame8 = {
    12, 2, 0x1F,
    {
        { 0, 15 }, { 0, 23 }, { 1, 23 }, { 2, 23 },
        { 3, 23 }, { 4, 23 }, { 5, 23 }, { 6, 23 },
        { 7, 23 }, { 8, 23 }, { 9, 23 }, { 10, 23 },
    },
};
const ROOM_TILE_ANIM_FRAME(11) g_RoomTileAnim18Frame9 = {
    11, 2, 0x1F,
    {
        { 0, 24 }, { 1, 24 }, { 2, 24 }, { 3, 24 },
        { 4, 24 }, { 5, 24 }, { 6, 24 }, { 7, 24 },
        { 8, 24 }, { 9, 24 }, { 10, 24 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame10 = {
    12, 2, 0x1F,
    {
        { 0, 24 }, { 0, 25 }, { 1, 25 }, { 2, 25 },
        { 3, 25 }, { 4, 25 }, { 5, 25 }, { 6, 25 },
        { 7, 25 }, { 8, 25 }, { 9, 25 }, { 10, 25 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame11 = {
    12, 2, 0x1F,
    {
        { 0, 24 }, { 0, 26 }, { 1, 26 }, { 2, 26 },
        { 3, 26 }, { 4, 26 }, { 5, 26 }, { 6, 26 },
        { 7, 26 }, { 8, 26 }, { 9, 26 }, { 10, 26 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame12 = {
    12, 2, 0x1F,
    {
        { 0, 24 }, { 0, 27 }, { 1, 27 }, { 2, 27 },
        { 3, 27 }, { 4, 27 }, { 5, 27 }, { 6, 27 },
        { 7, 27 }, { 8, 27 }, { 9, 27 }, { 10, 27 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame13 = {
    12, 2, 0x1F,
    {
        { 0, 24 }, { 0, 28 }, { 1, 28 }, { 2, 28 },
        { 3, 28 }, { 4, 28 }, { 5, 28 }, { 6, 28 },
        { 7, 28 }, { 8, 28 }, { 9, 28 }, { 10, 28 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame14 = {
    12, 2, 0x1F,
    {
        { 0, 24 }, { 0, 29 }, { 1, 29 }, { 2, 29 },
        { 3, 29 }, { 4, 29 }, { 5, 29 }, { 6, 29 },
        { 7, 29 }, { 8, 29 }, { 9, 29 }, { 10, 29 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame15 = {
    12, 2, 0x1F,
    {
        { 0, 24 }, { 0, 30 }, { 1, 30 }, { 2, 30 },
        { 3, 30 }, { 4, 30 }, { 5, 30 }, { 6, 30 },
        { 7, 30 }, { 8, 30 }, { 9, 30 }, { 10, 30 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame16 = {
    12, 2, 0x1F,
    {
        { 0, 24 }, { 0, 31 }, { 1, 31 }, { 2, 31 },
        { 3, 31 }, { 4, 31 }, { 5, 31 }, { 6, 31 },
        { 7, 31 }, { 8, 31 }, { 9, 31 }, { 10, 31 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim18Frame17 = {
    12, 2, 0x1F,
    {
        { 0, 24 }, { 0, 32 }, { 1, 32 }, { 2, 32 },
        { 3, 32 }, { 4, 32 }, { 5, 32 }, { 6, 32 },
        { 7, 32 }, { 8, 32 }, { 9, 32 }, { 10, 32 },
    },
};

const ROOM_TILE_ANIM_SET(21) g_RoomTileAnim18 = {
    21,
    {
        FRAME(g_RoomTileAnim18Frame8),
        FRAME(g_RoomTileAnim18Frame7),
        FRAME(g_RoomTileAnim18Frame6),
        FRAME(g_RoomTileAnim18Frame5),
        FRAME(g_RoomTileAnim18Frame4),
        FRAME(g_RoomTileAnim18Frame3),
        FRAME(g_RoomTileAnim18Frame2),
        FRAME(g_RoomTileAnim18Frame1),
        FRAME(g_RoomTileAnim18Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim18Frame9),
        FRAME(g_RoomTileAnim18Frame10),
        FRAME(g_RoomTileAnim18Frame11),
        FRAME(g_RoomTileAnim18Frame12),
        FRAME(g_RoomTileAnim18Frame13),
        FRAME(g_RoomTileAnim18Frame14),
        FRAME(g_RoomTileAnim18Frame15),
        FRAME(g_RoomTileAnim18Frame16),
        FRAME(g_RoomTileAnim18Frame17),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(15) g_RoomTileAnim22Frame0 = {
    15, 1, 0x1F,
    {
        { 42, 21 }, { 43, 21 }, { 44, 21 }, { 45, 21 },
        { 46, 21 }, { 42, 22 }, { 43, 22 }, { 44, 22 },
        { 45, 22 }, { 46, 22 }, { 42, 23 }, { 43, 23 },
        { 44, 23 }, { 45, 23 }, { 46, 23 },
    },
};
const ROOM_TILE_ANIM_FRAME(15) g_RoomTileAnim22Frame1 = {
    15, 1, 0x1F,
    {
        { 42, 25 }, { 43, 25 }, { 44, 25 }, { 45, 25 },
        { 46, 25 }, { 42, 26 }, { 43, 26 }, { 44, 26 },
        { 45, 26 }, { 46, 26 }, { 42, 27 }, { 43, 27 },
        { 44, 27 }, { 45, 27 }, { 46, 27 },
    },
};
const ROOM_TILE_ANIM_FRAME(15) g_RoomTileAnim22Frame2 = {
    15, 1, 0x1F,
    {
        { 42, 29 }, { 43, 29 }, { 44, 29 }, { 45, 29 },
        { 46, 29 }, { 42, 30 }, { 43, 30 }, { 44, 30 },
        { 45, 30 }, { 46, 30 }, { 42, 31 }, { 43, 31 },
        { 44, 31 }, { 45, 31 }, { 46, 31 },
    },
};

const ROOM_TILE_ANIM_SET(8) g_RoomTileAnim22 = {
    8,
    {
        FRAME(g_RoomTileAnim22Frame2),
        FRAME(g_RoomTileAnim22Frame1),
        FRAME(g_RoomTileAnim22Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim22Frame1),
        FRAME(g_RoomTileAnim22Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim23Frame0 = {
    12, 1, 0x1F,
    {
        { 37, 21 }, { 38, 21 }, { 39, 21 }, { 40, 21 },
        { 37, 22 }, { 38, 22 }, { 39, 22 }, { 40, 22 },
        { 37, 23 }, { 38, 23 }, { 39, 23 }, { 40, 23 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim23Frame1 = {
    12, 1, 0x1F,
    {
        { 37, 25 }, { 38, 25 }, { 39, 25 }, { 40, 25 },
        { 37, 26 }, { 38, 26 }, { 39, 26 }, { 40, 26 },
        { 37, 27 }, { 38, 27 }, { 39, 27 }, { 40, 27 },
    },
};
const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim23Frame2 = {
    12, 1, 0x1F,
    {
        { 37, 29 }, { 38, 29 }, { 39, 29 }, { 40, 29 },
        { 37, 30 }, { 38, 30 }, { 39, 30 }, { 40, 30 },
        { 37, 31 }, { 38, 31 }, { 39, 31 }, { 40, 31 },
    },
};

const ROOM_TILE_ANIM_SET(8) g_RoomTileAnim23 = {
    8,
    {
        FRAME(g_RoomTileAnim23Frame2),
        FRAME(g_RoomTileAnim23Frame1),
        FRAME(g_RoomTileAnim23Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim23Frame1),
        FRAME(g_RoomTileAnim23Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(21) g_RoomTileAnim24Frame0 = {
    21, 0, 0x10,
    {
        { 22, 17 }, { 23, 17 }, { 24, 17 }, { 25, 17 },
        { 26, 17 }, { 27, 17 }, { 28, 17 }, { 22, 18 },
        { 23, 18 }, { 24, 18 }, { 25, 18 }, { 26, 18 },
        { 27, 18 }, { 28, 18 }, { 22, 19 }, { 23, 19 },
        { 24, 19 }, { 25, 19 }, { 26, 19 }, { 27, 19 },
        { 28, 19 },
    },
};

const ROOM_TILE_ANIM_SET(1) g_RoomTileAnim24 = {
    1,
    {
        FRAME(g_RoomTileAnim24Frame0),
    },
};

const ROOM_TILE_ANIM_FRAME(21) g_RoomTileAnim25Frame0 = {
    21, 0, 0x10,
    {
        { 22, 5 }, { 23, 5 }, { 24, 5 }, { 25, 5 },
        { 26, 5 }, { 27, 5 }, { 28, 5 }, { 22, 6 },
        { 23, 6 }, { 24, 6 }, { 25, 6 }, { 26, 6 },
        { 27, 6 }, { 28, 6 }, { 22, 7 }, { 23, 7 },
        { 24, 7 }, { 25, 7 }, { 26, 7 }, { 27, 7 },
        { 28, 7 },
    },
};

const ROOM_TILE_ANIM_SET(1) g_RoomTileAnim25 = {
    1,
    {
        FRAME(g_RoomTileAnim25Frame0),
    },
};

const ROOM_TILE_ANIM_FRAME(8) g_RoomTileAnim26Frame0 = {
    8, 1, 0x1F,
    {
        { 5, 38 }, { 6, 38 }, { 7, 38 }, { 8, 38 },
        { 5, 39 }, { 6, 39 }, { 7, 39 }, { 8, 39 },
    },
};
const ROOM_TILE_ANIM_FRAME(8) g_RoomTileAnim26Frame1 = {
    8, 1, 0x1F,
    {
        { 10, 38 }, { 11, 38 }, { 12, 38 }, { 13, 38 },
        { 10, 39 }, { 11, 39 }, { 12, 39 }, { 13, 39 },
    },
};

const ROOM_TILE_ANIM_SET(5) g_RoomTileAnim26 = {
    5,
    {
        FRAME(g_RoomTileAnim26Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim26Frame1),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(12) g_RoomTileAnim28Frame0 = {
    12, 0, 0x1F,
    {
        { 2, 37 }, { 3, 37 }, { 2, 38 }, { 3, 38 },
        { 2, 39 }, { 3, 39 }, { 2, 40 }, { 3, 40 },
        { 2, 41 }, { 3, 41 }, { 2, 42 }, { 3, 42 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim28 = {
    2,
    {
        FRAME(g_RoomTileAnim28Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(16) g_RoomTileAnim27Frame0 = {
    16, 1, 0x1F,
    {
        { 5, 39 }, { 6, 39 }, { 7, 39 }, { 8, 39 },
        { 5, 40 }, { 6, 40 }, { 7, 40 }, { 8, 40 },
        { 5, 41 }, { 6, 41 }, { 7, 41 }, { 8, 41 },
        { 5, 42 }, { 6, 42 }, { 7, 42 }, { 8, 42 },
    },
};
const ROOM_TILE_ANIM_FRAME(16) g_RoomTileAnim27Frame1 = {
    16, 1, 0x1F,
    {
        { 9, 39 }, { 10, 39 }, { 11, 39 }, { 12, 39 },
        { 9, 40 }, { 10, 40 }, { 11, 40 }, { 12, 40 },
        { 9, 41 }, { 10, 41 }, { 11, 41 }, { 12, 41 },
        { 9, 42 }, { 10, 42 }, { 11, 42 }, { 12, 42 },
    },
};

const ROOM_TILE_ANIM_SET(5) g_RoomTileAnim27 = {
    5,
    {
        FRAME(g_RoomTileAnim27Frame1),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim27Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(9) g_RoomTileAnim29Frame0 = {
    9, 0, 0x1F,
    {
        { 0, 0 }, { 1, 0 }, { 2, 0 }, { 0, 1 },
        { 1, 1 }, { 2, 1 }, { 0, 2 }, { 1, 2 },
        { 2, 2 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim29 = {
    2,
    {
        FRAME(g_RoomTileAnim29Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim30Frame0 = {
    6, 3, 0x03,
    {
        { 30, 0 }, { 30, 1 }, { 30, 2 }, { 31, 0 },
        { 31, 1 }, { 31, 2 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim30Frame1 = {
    6, 3, 0x03,
    {
        { 33, 0 }, { 33, 1 }, { 33, 2 }, { 34, 0 },
        { 34, 1 }, { 34, 2 },
    },
};

const ROOM_TILE_ANIM_SET(3) g_RoomTileAnim30 = {
    3,
    {
        FRAME(g_RoomTileAnim30Frame0),
        FRAME(g_RoomTileAnim30Frame1),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim31Frame0 = {
    4, 0, 0x11,
    {
        { 28, 35 }, { 28, 36 }, { 29, 35 }, { 29, 36 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim31 = {
    2,
    {
        FRAME(g_RoomTileAnim31Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(8) g_RoomTileAnim32Frame0 = {
    8, 0, 0x10,
    {
        { 27, 35 }, { 28, 35 }, { 29, 35 }, { 30, 35 },
        { 27, 36 }, { 28, 36 }, { 29, 36 }, { 30, 36 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim32 = {
    2,
    {
        FRAME(g_RoomTileAnim32Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(9) g_RoomTileAnim33Frame0 = {
    9, 0, 0x11,
    {
        { 28, 0 }, { 28, 1 }, { 28, 2 }, { 29, 0 },
        { 29, 1 }, { 29, 2 }, { 30, 0 }, { 30, 1 },
        { 30, 2 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim33 = {
    2,
    {
        FRAME(g_RoomTileAnim33Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(9) g_RoomTileAnim34Frame0 = {
    9, 0, 0x1F,
    {
        { 0, 0 }, { 0, 1 }, { 0, 2 }, { 1, 0 },
        { 1, 1 }, { 1, 2 }, { 2, 0 }, { 2, 1 },
        { 2, 2 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim34 = {
    2,
    {
        FRAME(g_RoomTileAnim34Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(8) g_RoomTileAnim35Frame0 = {
    8, 0, 0x04,
    {
        { 0, 12 }, { 1, 12 }, { 0, 13 }, { 1, 13 },
        { 0, 14 }, { 1, 14 }, { 0, 15 }, { 1, 15 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim35 = {
    2,
    {
        FRAME(g_RoomTileAnim35Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim36Frame0 = {
    6, 3, 0x03,
    {
        { 41, 5 }, { 41, 6 }, { 41, 7 }, { 42, 5 },
        { 42, 6 }, { 42, 7 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim36Frame1 = {
    6, 3, 0x03,
    {
        { 43, 5 }, { 43, 6 }, { 43, 7 }, { 44, 5 },
        { 44, 6 }, { 44, 7 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim36Frame2 = {
    6, 3, 0x13,
    {
        { 45, 5 }, { 45, 6 }, { 45, 7 }, { 46, 5 },
        { 46, 6 }, { 46, 7 },
    },
};

const ROOM_TILE_ANIM_SET(4) g_RoomTileAnim36 = {
    4,
    {
        FRAME(g_RoomTileAnim36Frame0),
        FRAME(g_RoomTileAnim36Frame1),
        FRAME(g_RoomTileAnim36Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim37Frame0 = {
    6, 3, 0x03,
    {
        { 41, 9 }, { 41, 10 }, { 41, 11 }, { 42, 9 },
        { 42, 10 }, { 42, 11 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim37Frame1 = {
    6, 3, 0x03,
    {
        { 43, 9 }, { 43, 10 }, { 43, 11 }, { 44, 9 },
        { 44, 10 }, { 44, 11 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim37Frame2 = {
    6, 3, 0x03,
    {
        { 45, 9 }, { 45, 10 }, { 45, 11 }, { 46, 9 },
        { 46, 10 }, { 46, 11 },
    },
};

const ROOM_TILE_ANIM_SET(4) g_RoomTileAnim37 = {
    4,
    {
        FRAME(g_RoomTileAnim37Frame0),
        FRAME(g_RoomTileAnim37Frame1),
        FRAME(g_RoomTileAnim37Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim38Frame0 = {
    6, 3, 0x03,
    {
        { 41, 14 }, { 41, 15 }, { 41, 16 }, { 42, 14 },
        { 42, 15 }, { 42, 16 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim38Frame1 = {
    6, 3, 0x03,
    {
        { 43, 14 }, { 43, 15 }, { 43, 16 }, { 44, 14 },
        { 44, 15 }, { 44, 16 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim38Frame2 = {
    6, 3, 0x03,
    {
        { 45, 14 }, { 45, 15 }, { 45, 16 }, { 46, 14 },
        { 46, 15 }, { 46, 16 },
    },
};

const ROOM_TILE_ANIM_SET(4) g_RoomTileAnim38 = {
    4,
    {
        FRAME(g_RoomTileAnim38Frame0),
        FRAME(g_RoomTileAnim38Frame1),
        FRAME(g_RoomTileAnim38Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim39Frame0 = {
    4, 3, 0x11,
    {
        { 37, 18 }, { 38, 18 }, { 37, 19 }, { 38, 19 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim39Frame1 = {
    4, 3, 0x11,
    {
        { 37, 20 }, { 38, 20 }, { 37, 21 }, { 38, 22 },
    },
};
const ROOM_TILE_ANIM_FRAME(4) g_RoomTileAnim39Frame2 = {
    4, 3, 0x11,
    {
        { 37, 22 }, { 38, 22 }, { 37, 23 }, { 38, 23 },
    },
};

const ROOM_TILE_ANIM_SET(4) g_RoomTileAnim39 = {
    4,
    {
        FRAME(g_RoomTileAnim39Frame0),
        FRAME(g_RoomTileAnim39Frame1),
        FRAME(g_RoomTileAnim39Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(3) g_RoomTileAnim40Frame0 = {
    3, 3, 0x03,
    {
        { 39, 18 }, { 39, 19 }, { 39, 20 },
    },
};
const ROOM_TILE_ANIM_FRAME(3) g_RoomTileAnim40Frame1 = {
    3, 3, 0x03,
    {
        { 39, 21 }, { 39, 22 }, { 39, 23 },
    },
};
const ROOM_TILE_ANIM_FRAME(3) g_RoomTileAnim40Frame2 = {
    3, 3, 0x03,
    {
        { 39, 24 }, { 39, 25 }, { 39, 26 },
    },
};

const ROOM_TILE_ANIM_SET(4) g_RoomTileAnim40 = {
    4,
    {
        FRAME(g_RoomTileAnim40Frame0),
        FRAME(g_RoomTileAnim40Frame1),
        FRAME(g_RoomTileAnim40Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim41Frame0 = {
    6, 3, 0x03,
    {
        { 40, 18 }, { 41, 18 }, { 40, 19 }, { 41, 19 },
        { 40, 20 }, { 41, 20 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim41Frame1 = {
    6, 3, 0x03,
    {
        { 40, 21 }, { 41, 21 }, { 40, 22 }, { 41, 22 },
        { 40, 23 }, { 41, 23 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim41Frame2 = {
    6, 3, 0x03,
    {
        { 40, 24 }, { 41, 24 }, { 40, 25 }, { 41, 25 },
        { 40, 26 }, { 41, 26 },
    },
};

const ROOM_TILE_ANIM_SET(4) g_RoomTileAnim41 = {
    4,
    {
        FRAME(g_RoomTileAnim41Frame0),
        FRAME(g_RoomTileAnim41Frame1),
        FRAME(g_RoomTileAnim41Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim42Frame0 = {
    6, 3, 0x03,
    {
        { 44, 18 }, { 44, 19 }, { 44, 20 }, { 45, 18 },
        { 45, 19 }, { 45, 20 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim42Frame1 = {
    6, 3, 0x03,
    {
        { 44, 21 }, { 44, 22 }, { 44, 23 }, { 45, 21 },
        { 45, 22 }, { 45, 23 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim42Frame2 = {
    6, 3, 0x03,
    {
        { 44, 24 }, { 44, 25 }, { 44, 26 }, { 45, 24 },
        { 45, 25 }, { 45, 26 },
    },
};

const ROOM_TILE_ANIM_SET(4) g_RoomTileAnim42 = {
    4,
    {
        FRAME(g_RoomTileAnim42Frame0),
        FRAME(g_RoomTileAnim42Frame1),
        FRAME(g_RoomTileAnim42Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(3) g_RoomTileAnim43Frame0 = {
    3, 3, 0x03,
    {
        { 46, 18 }, { 46, 19 }, { 46, 20 },
    },
};
const ROOM_TILE_ANIM_FRAME(3) g_RoomTileAnim43Frame1 = {
    3, 3, 0x03,
    {
        { 46, 21 }, { 46, 22 }, { 46, 23 },
    },
};
const ROOM_TILE_ANIM_FRAME(3) g_RoomTileAnim43Frame2 = {
    3, 3, 0x03,
    {
        { 46, 24 }, { 46, 25 }, { 46, 26 },
    },
};

const ROOM_TILE_ANIM_SET(4) g_RoomTileAnim43 = {
    4,
    {
        FRAME(g_RoomTileAnim43Frame0),
        FRAME(g_RoomTileAnim43Frame1),
        FRAME(g_RoomTileAnim43Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(1) g_RoomTileAnim44Frame0 = {
    1, 0, 0x10,
    {
        { 41, 1 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim44 = {
    2,
    {
        FRAME(g_RoomTileAnim44Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(1) g_RoomTileAnim45Frame0 = {
    1, 0, 0x10,
    {
        { 45, 1 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim45 = {
    2,
    {
        FRAME(g_RoomTileAnim45Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(1) g_RoomTileAnim46Frame0 = {
    1, 0, 0x10,
    {
        { 41, 32 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim46 = {
    2,
    {
        FRAME(g_RoomTileAnim46Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(2) g_RoomTileAnim47Frame0 = {
    2, 0, 0x10,
    {
        { 42, 32 }, { 43, 32 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim47 = {
    2,
    {
        FRAME(g_RoomTileAnim47Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(1) g_RoomTileAnim48Frame0 = {
    1, 0, 0x10,
    {
        { 44, 32 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim48 = {
    2,
    {
        FRAME(g_RoomTileAnim48Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(2) g_RoomTileAnim49Frame0 = {
    2, 0, 0x10,
    {
        { 45, 32 }, { 46, 32 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim49 = {
    2,
    {
        FRAME(g_RoomTileAnim49Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(2) g_RoomTileAnim50Frame0 = {
    2, 0, 0x1F,
    {
        { 0, 1 }, { 1, 1 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim50 = {
    2,
    {
        FRAME(g_RoomTileAnim50Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(10) g_RoomTileAnim51Frame0 = {
    10, 0, 0x1F,
    {
        { 0, 3 }, { 1, 3 }, { 2, 3 }, { 3, 3 },
        { 4, 3 }, { 0, 4 }, { 1, 4 }, { 2, 4 },
        { 3, 4 }, { 4, 4 },
    },
};

const ROOM_TILE_ANIM_SET(2) g_RoomTileAnim51 = {
    2,
    {
        FRAME(g_RoomTileAnim51Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim52Frame0 = {
    6, 0, 0x1F,
    {
        { 12, 32 }, { 13, 32 }, { 12, 33 }, { 13, 33 },
        { 12, 34 }, { 13, 34 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim52Frame1 = {
    6, 0, 0x1F,
    {
        { 14, 32 }, { 15, 32 }, { 14, 33 }, { 15, 33 },
        { 14, 34 }, { 15, 34 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim52Frame2 = {
    6, 0, 0x1F,
    {
        { 16, 32 }, { 17, 32 }, { 16, 33 }, { 17, 33 },
        { 16, 34 }, { 17, 34 },
    },
};

const ROOM_TILE_ANIM_SET(7) g_RoomTileAnim52 = {
    7,
    {
        FRAME(g_RoomTileAnim52Frame1),
        FRAME(g_RoomTileAnim52Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim52Frame1),
        FRAME(g_RoomTileAnim52Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(8) g_RoomTileAnim53Frame0 = {
    8, 0, 0x1F,
    {
        { 12, 35 }, { 13, 35 }, { 12, 36 }, { 13, 36 },
        { 12, 37 }, { 13, 37 }, { 12, 38 }, { 13, 38 },
    },
};
const ROOM_TILE_ANIM_FRAME(8) g_RoomTileAnim53Frame1 = {
    8, 0, 0x1F,
    {
        { 14, 35 }, { 15, 35 }, { 14, 36 }, { 15, 36 },
        { 14, 37 }, { 15, 37 }, { 14, 38 }, { 15, 38 },
    },
};
const ROOM_TILE_ANIM_FRAME(8) g_RoomTileAnim53Frame2 = {
    8, 0, 0x1F,
    {
        { 16, 35 }, { 17, 35 }, { 16, 36 }, { 17, 36 },
        { 16, 37 }, { 17, 37 }, { 16, 38 }, { 17, 38 },
    },
};

const ROOM_TILE_ANIM_SET(7) g_RoomTileAnim53 = {
    7,
    {
        FRAME(g_RoomTileAnim53Frame1),
        FRAME(g_RoomTileAnim53Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim53Frame1),
        FRAME(g_RoomTileAnim53Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim54Frame0 = {
    6, 0, 0x1F,
    {
        { 12, 39 }, { 13, 39 }, { 12, 40 }, { 13, 40 },
        { 12, 41 }, { 13, 41 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim54Frame1 = {
    6, 0, 0x1F,
    {
        { 14, 39 }, { 15, 39 }, { 14, 40 }, { 15, 40 },
        { 14, 41 }, { 15, 41 },
    },
};
const ROOM_TILE_ANIM_FRAME(6) g_RoomTileAnim54Frame2 = {
    6, 0, 0x1F,
    {
        { 16, 39 }, { 17, 39 }, { 16, 40 }, { 17, 40 },
        { 16, 41 }, { 17, 41 },
    },
};

const ROOM_TILE_ANIM_SET(7) g_RoomTileAnim54 = {
    7,
    {
        FRAME(g_RoomTileAnim54Frame1),
        FRAME(g_RoomTileAnim54Frame2),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnim54Frame1),
        FRAME(g_RoomTileAnim54Frame0),
        FRAME(g_RoomTileAnimHaltFrame),
        FRAME(g_RoomTileAnimLoopFrame),
    },
};

const RoomTileAnimSet *const g_apRoomTileAnimSets[55] = {
    (const RoomTileAnimSet *)&g_RoomTileAnim0,
    (const RoomTileAnimSet *)&g_RoomTileAnim1,
    (const RoomTileAnimSet *)&g_RoomTileAnim2,
    (const RoomTileAnimSet *)&g_RoomTileAnim3,
    (const RoomTileAnimSet *)&g_RoomTileAnim4,
    (const RoomTileAnimSet *)&g_RoomTileAnim5,
    (const RoomTileAnimSet *)&g_RoomTileAnim6,
    (const RoomTileAnimSet *)&g_RoomTileAnim7,
    (const RoomTileAnimSet *)&g_RoomTileAnim8,
    (const RoomTileAnimSet *)&g_RoomTileAnim9,
    (const RoomTileAnimSet *)&g_RoomTileAnim10,
    (const RoomTileAnimSet *)&g_RoomTileAnim11,
    (const RoomTileAnimSet *)&g_RoomTileAnim12,
    (const RoomTileAnimSet *)&g_RoomTileAnim13,
    (const RoomTileAnimSet *)&g_RoomTileAnim14,
    (const RoomTileAnimSet *)&g_RoomTileAnim15,
    (const RoomTileAnimSet *)&g_RoomTileAnim16,
    (const RoomTileAnimSet *)&g_RoomTileAnim17,
    (const RoomTileAnimSet *)&g_RoomTileAnim18,
    (const RoomTileAnimSet *)&g_RoomTileAnim19,
    (const RoomTileAnimSet *)&g_RoomTileAnim20,
    (const RoomTileAnimSet *)&g_RoomTileAnim21,
    (const RoomTileAnimSet *)&g_RoomTileAnim22,
    (const RoomTileAnimSet *)&g_RoomTileAnim23,
    (const RoomTileAnimSet *)&g_RoomTileAnim24,
    (const RoomTileAnimSet *)&g_RoomTileAnim25,
    (const RoomTileAnimSet *)&g_RoomTileAnim26,
    (const RoomTileAnimSet *)&g_RoomTileAnim27,
    (const RoomTileAnimSet *)&g_RoomTileAnim28,
    (const RoomTileAnimSet *)&g_RoomTileAnim29,
    (const RoomTileAnimSet *)&g_RoomTileAnim30,
    (const RoomTileAnimSet *)&g_RoomTileAnim31,
    (const RoomTileAnimSet *)&g_RoomTileAnim32,
    (const RoomTileAnimSet *)&g_RoomTileAnim33,
    (const RoomTileAnimSet *)&g_RoomTileAnim34,
    (const RoomTileAnimSet *)&g_RoomTileAnim35,
    (const RoomTileAnimSet *)&g_RoomTileAnim36,
    (const RoomTileAnimSet *)&g_RoomTileAnim37,
    (const RoomTileAnimSet *)&g_RoomTileAnim38,
    (const RoomTileAnimSet *)&g_RoomTileAnim39,
    (const RoomTileAnimSet *)&g_RoomTileAnim40,
    (const RoomTileAnimSet *)&g_RoomTileAnim41,
    (const RoomTileAnimSet *)&g_RoomTileAnim42,
    (const RoomTileAnimSet *)&g_RoomTileAnim43,
    (const RoomTileAnimSet *)&g_RoomTileAnim44,
    (const RoomTileAnimSet *)&g_RoomTileAnim45,
    (const RoomTileAnimSet *)&g_RoomTileAnim46,
    (const RoomTileAnimSet *)&g_RoomTileAnim47,
    (const RoomTileAnimSet *)&g_RoomTileAnim48,
    (const RoomTileAnimSet *)&g_RoomTileAnim49,
    (const RoomTileAnimSet *)&g_RoomTileAnim50,
    (const RoomTileAnimSet *)&g_RoomTileAnim51,
    (const RoomTileAnimSet *)&g_RoomTileAnim52,
    (const RoomTileAnimSet *)&g_RoomTileAnim53,
    (const RoomTileAnimSet *)&g_RoomTileAnim54,
};
