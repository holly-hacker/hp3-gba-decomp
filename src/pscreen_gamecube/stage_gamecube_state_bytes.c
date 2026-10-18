#include "types.h"
#include "save.h"
#include "game_state.h"
#include "gamecube.h"
#include "pscreen_gamecube.h"

// Command 0x82: sends the Owl Care Kit's owl and stat meters.
void StageGameCubeStateBytes(u16 *pLength, u16 *pBuffer)
{
    GameCubeOwlPacket *pPacket = (GameCubeOwlPacket *)pBuffer;

    pPacket->bFlags = g_saveStateBlock.owlCareKit.bFlags;
    pPacket->bNameIndex = g_saveStateBlock.owlCareKit.bNameIndex;
    pPacket->bTypeIndex = g_saveStateBlock.owlCareKit.bTypeIndex;
    pPacket->bUnknown3 = g_saveStateBlock.owlCareKit.bUnknown3;
    pPacket->bZero = 0;
    pPacket->abStatMeters[0] = g_saveStateBlock.owlCareKit.abStatMeters[0];
    pPacket->abStatMeters[1] = g_saveStateBlock.owlCareKit.abStatMeters[1];
    pPacket->abStatMeters[2] = g_saveStateBlock.owlCareKit.abStatMeters[2];
    *pLength = sizeof(GameCubeOwlPacket);
    g_JoybusLinkState.bLinkProgress = 2;
}
