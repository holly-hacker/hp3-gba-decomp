#include "types.h"
#include "background.h"
#include "camera.h"
#include "color.h"
#include "main.h"
#include "map.h"
#include "modes.h"
#include "move.h"
#include "scroll.h"
#include "sound.h"
#include "timeturner_cutscene.h"

#define CURRENT_ROOM g_aTimeTurnerCutsceneRoomTable[roomIndex]

// Loads room 0 (the hospital wing, with BG0 shown) or 1 (the path to Hagrid's hut) of the
// cutscene's room table, with its music, and places the camera at the room's start.
void LoadHarryHermionePortInTimeRoom(u32 roomIndex)
{
    u32 bgCtrl3;
    u32 bgCtrl2;
    u32 bgCtrl1;
    u32 bgCtrl0;
    const RoomTableEntry *pRoom;
    FixedPoint position;

    bgCtrl3 = g_dwBg3Control;
    SetBgControl(3, bgCtrl3);
    bgCtrl2 = g_dwBg2Control;
    SetBgControl(2, bgCtrl2);
    bgCtrl1 = g_dwBg1Control;
    SetBgControl(1, bgCtrl1);
    bgCtrl0 = g_dwBg0Control;
    SetBgControl(0, bgCtrl0);
    DisableBg(0);
    DisableBg(1);
    DisableBg(2);
    DisableBg(3);

    g_dwGameModeFlags &= ~GameModeFlagUnk2000000;
    g_dwColorCycleActiveMask = 0;
    FreeRoomBgBlockData();

    LoadRoomBgTilemap0(CURRENT_ROOM.pBgTilemap0);
    LoadRoomBgTilemap1(CURRENT_ROOM.pBgTilemap1);
    LoadRoomBgTilemap2(CURRENT_ROOM.pBgTilemap2);
    LoadRoomBgTilemap3(CURRENT_ROOM.pBgTilemap3);
    pRoom = &CURRENT_ROOM;
    SetupRoomBgControlAndTilesets(bgCtrl3, bgCtrl1, bgCtrl2, bgCtrl0,
                                  pRoom->aBgResources[0], pRoom->aBgResources[1]);
    LoadRoomCollision(CURRENT_ROOM.pCollisionBehaviorTable, CURRENT_ROOM.pCollisionTilemap);
    LoadRoomBgBlockTiles0(CURRENT_ROOM.pBgLayer0Extra, CURRENT_ROOM.dwUnused0_8, CURRENT_ROOM.dwUnused0_c);
    LoadRoomBgBlockTiles1(CURRENT_ROOM.pBgLayer1Extra, CURRENT_ROOM.dwUnused1_8, CURRENT_ROOM.dwUnused1_c);
    LoadRoomBgBlockTiles2(CURRENT_ROOM.pBgLayer2Extra, CURRENT_ROOM.dwUnused2_8, CURRENT_ROOM.dwUnused2_c);
    LoadRoomBgBlockTiles3(CURRENT_ROOM.pBgLayer3Extra, CURRENT_ROOM.dwUnused3_8, CURRENT_ROOM.dwUnused3_c);

    position.x = g_aHarryHermionePortInTimeCameraStart[roomIndex].x << 16;
    position.y = g_aHarryHermionePortInTimeCameraStart[roomIndex].y << 16;
    SetCameraFocusPinned(1, 0);
    SetCameraFocusPosition(position, 0);
    PlayMusicModule(pRoom->bDefaultMusicModule);
    EnableBg(1);
    EnableBg(2);
    EnableBg(3);
    UpdateOverworldCamera(1);
    ReloadRoomBgTiles();
    TickCameraFocus(0);

    if (roomIndex == 0)
    {
        EnableBg(0);
        SetBgPriority(0, 1);
        SetBgPriority(2, 0);
    }

    g_HarryHermionePortInTime.dwPositionIndex = roomIndex;
}
