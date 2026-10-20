#include "types.h"
#include "color.h"
#include "commands.h"
#include "map.h"
#include "overworld/room.h"
#include "scroll.h"

// Loads the room's BG palette (color 0 forced to black), stores the BG layers' control values
// and sets up both tilesets' tile offset and code tables.
void SetupRoomBgControlAndTilesets(u32 ctrl3, u32 ctrl1, u32 ctrl2, u32 ctrl0,
                                            RoomBgResources resourcesA, RoomBgResources resourcesB)
{
    u16 black;

    black = 0;
    LoadBgPaletteColors(resourcesA.pPalette, 0, 0x100);
    if (g_abQuestEventState[QUEST_ALT_PRESENTATION] != 0)
        LoadRoomAltPresentationPalette();
    LoadBgPaletteColors(&black, 0, 1);

    *(u32 *)&g_aBgControl[0] = ctrl3;
    *(u32 *)&g_aBgControl[1] = ctrl1;
    *(u32 *)&g_aBgControl[2] = ctrl2;
    *(u32 *)&g_aBgControl[3] = ctrl0;
    g_adwBgTilesetTileCount[0] = DecodeBgTilesetOffsetTable(
        resourcesA, &g_aBgTilesets[0], (BgTileCodeTable *)g_aBgTileCodeTableBuffers[0]);
    g_adwBgTilesetTileCount[1] = DecodeBgTilesetOffsetTable(
        resourcesB, &g_aBgTilesets[1], (BgTileCodeTable *)g_aBgTileCodeTableBuffers[1]);
    g_apRoomBgTilesets[0] = resourcesA.pTileset;
    g_apRoomBgTilesets[1] = resourcesB.pTileset;
}
