#include "types.h"
#include "background.h"
#include "modes.h"
#include "gen/graphics/overworld.h"
#include "map.h"

void LoadRoomAltPresentationPalette(void)
{
    switch (g_GameModeStackContext.dwCurrentGameModeArg2)
    {
    case RoomLeakyCauldronHarrysRoom:
        LoadEmbeddedPalette(gRoomAltPalette001Palette, 0, 16);
        break;
    case RoomGryffindorBoysDormitory:
        LoadEmbeddedPalette(gRoomAltPalette002Palette, 0, 16);
        break;
    case RoomHogwartsGroundsCastleDoors:
    case RoomHogwartsGroundsBoathouse:
    case RoomHogwartsGroundsGreenhouses:
    case RoomHogwartsGroundsLake:
    case RoomHogwartsGroundsWhompingWillow:
        LoadEmbeddedPalette(gRoomAltPalette003Palette, 0, 16);
        break;
    case RoomHagridsHut:
        LoadEmbeddedPalette(gRoomAltPalette004Palette, 0, 16);
        break;
    case RoomHogwartsExpressBaggageCar:
        LoadEmbeddedPalette(gRoomAltPalette005Palette, 0, 16);
        break;
    case RoomHogwartsExpressBuffetCar:
        LoadEmbeddedPalette(gRoomAltPalette006Palette, 0, 16);
        break;
    case RoomHogwartsExpressPassengerCar:
        LoadEmbeddedPalette(gTrainWindowNightPalette, 0, 16);
        break;
    case RoomGreatHall:
        LoadEmbeddedPalette(gRoomAltPalette007Palette, 0, 16);
        break;
    case RoomSeventhFloor:
        LoadEmbeddedPalette(gRoomAltPalette008Palette, 0, 16);
        break;
    case RoomLupinsOffice:
        LoadEmbeddedPalette(gRoomAltPalette009Palette, 0, 16);
        break;
    case RoomGrandStaircase:
        LoadEmbeddedPalette(gRoomAltPalette010Palette, 0, 16);
        break;
    case RoomLibrary:
    case RoomLibrary2:
        LoadEmbeddedPalette(gRoomAltPalette011Palette, 0, 16);
        break;
    case RoomFredAndGeorgesShop:
        LoadEmbeddedPalette(gRoomAltPalette012Palette, 0, 16);
        break;
    }
}
