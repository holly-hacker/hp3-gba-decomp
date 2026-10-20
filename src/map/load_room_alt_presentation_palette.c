#include "types.h"
#include "background.h"
#include "modes.h"
#include "gen/graphics/overworld.h"
#include "map.h"

void LoadRoomAltPresentationPalette(void)
{
    switch (g_GameModeStackContext.dwCurrentGameModeArg2)
    {
    case 41:
        LoadEmbeddedPalette(gRoomAltPalette001Palette, 0, 16);
        break;
    case 28:
        LoadEmbeddedPalette(gRoomAltPalette002Palette, 0, 16);
        break;
    case 8:
    case 9:
    case 10:
    case 13:
    case 15:
        LoadEmbeddedPalette(gRoomAltPalette003Palette, 0, 16);
        break;
    case 11:
        LoadEmbeddedPalette(gRoomAltPalette004Palette, 0, 16);
        break;
    case 5:
        LoadEmbeddedPalette(gRoomAltPalette005Palette, 0, 16);
        break;
    case 7:
        LoadEmbeddedPalette(gRoomAltPalette006Palette, 0, 16);
        break;
    case 6:
        LoadEmbeddedPalette(gTrainWindowNightPalette, 0, 16);
        break;
    case 17:
        LoadEmbeddedPalette(gRoomAltPalette007Palette, 0, 16);
        break;
    case 24:
        LoadEmbeddedPalette(gRoomAltPalette008Palette, 0, 16);
        break;
    case 26:
        LoadEmbeddedPalette(gRoomAltPalette009Palette, 0, 16);
        break;
    case 30:
        LoadEmbeddedPalette(gRoomAltPalette010Palette, 0, 16);
        break;
    case 34:
    case 35:
        LoadEmbeddedPalette(gRoomAltPalette011Palette, 0, 16);
        break;
    case 36:
        LoadEmbeddedPalette(gRoomAltPalette012Palette, 0, 16);
        break;
    }
}
