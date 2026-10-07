#include "types.h"
#include "overworld/terrain.h"

const u8 g_abOppositeFacing[8] = { 4, 5, 6, 7, 0, 1, 2, 3 };

const SlopeLineSegment g_aTileEdgeSegments[4] = {
    { 0, 0, 8, 0 },  // top edge, left to right
    { 8, 0, 8, 8 },  // right edge, top to bottom
    { 8, 8, 0, 8 },  // bottom edge, right to left
    { 0, 8, 0, 0 },  // left edge, bottom to top
};

// Terrain types 2-25 in order, four to a row.
const SlopeLineSegment g_aSlopeLineSegments[24] = {
    { 0, 8, 8, 4 }, { 0, 4, 8, 0 }, { 0, 8, 8, 0 }, { 0, 8, 4, 0 },  // 2-5
    { 4, 8, 8, 0 }, { 0, 0, 4, 8 }, { 4, 0, 8, 8 }, { 0, 0, 8, 8 },  // 6-9
    { 0, 0, 8, 4 }, { 0, 4, 8, 8 }, { 8, 4, 0, 0 }, { 8, 8, 0, 4 },  // 10-13
    { 8, 8, 0, 0 }, { 4, 8, 0, 0 }, { 8, 8, 4, 0 }, { 4, 0, 0, 8 },  // 14-17
    { 8, 0, 4, 8 }, { 8, 0, 0, 8 }, { 8, 4, 0, 8 }, { 8, 0, 0, 4 },  // 18-21
    { 4, 8, 4, 0 }, { 0, 4, 8, 4 }, { 4, 0, 4, 8 }, { 8, 4, 0, 4 },  // 22-25
};
