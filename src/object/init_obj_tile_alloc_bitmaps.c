#include "types.h"
#include "hw/mem.h"
#include "overworld/room.h"

// Resets the OBJ tile allocator for a display using BG mode bgMode. In the
// bitmap modes (3-5) the first 512 OBJ tiles share VRAM with the BG
// framebuffer, so they start out marked in use and only the upper half is
// allocatable; those modes leave the pending-free mask untouched.
void InitObjTileAllocBitmaps(u8 bgMode)
{
    if (bgMode >= 3 && bgMode <= 5) {
        memset(g_abObjTileAllocBitmap, 0xFF, 0x40);
        memset(&g_abObjTileAllocBitmap[64], 0, 0x40);
    } else {
        memset(g_abObjTileAllocBitmap, 0, 0x80);
        memset(g_abObjTileFreeMask, 0xFF, 0x80);
    }
}
