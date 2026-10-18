#include "types.h"
#include "pscreen_gamecube.h"

// The link's command callback; returns 0 for a command it does not handle.
u32 DispatchGameCubeLinkCommand(u32 command, u16 *pLength, u16 *pBuffer)
{
    switch (command)
    {
    case 0x40:
        VerifyGameCubeHandshakeBytes(pLength, pBuffer);
        break;
    case 0x41:
        FlagGameCubeHeaderReceived(pLength, pBuffer);
        break;
    case 0x42:
        AcknowledgeGameCubeCommand(pLength, pBuffer);
        break;
    case 0x80:
        StageGameCubeTestPattern(pLength, pBuffer);
        break;
    case 0x81:
        StageGameCubeStatusByte(pLength, pBuffer);
        break;
    case 0x82:
        StageGameCubeStateBytes(pLength, pBuffer);
        break;
    default:
        return 0;
    }

    return 1;
}
