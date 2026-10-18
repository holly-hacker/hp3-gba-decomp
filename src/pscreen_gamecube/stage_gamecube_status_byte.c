#include "types.h"
#include "modes.h"
#include "pscreen_gamecube.h"

// Command 0x81: sends the mode's Arg1 (0 from the owl name select, 1 from the Owl Care Kit).
void StageGameCubeStatusByte(u16 *pLength, u16 *pBuffer)
{
    *(u8 *)pBuffer = g_GameModeStackContext.dwCurrentGameModeArg1;
    *pLength = 1;
}
