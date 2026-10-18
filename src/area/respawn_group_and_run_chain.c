#include "types.h"
#include "area.h"

// Spawns group respawnRow's missing actors, then runs chain chainRow; each step only
// if ShouldRunRoomIndex allows its index.
void RespawnGroupAndRunChain(u8 respawnRow, u8 chainRow)
{
    if (ShouldRunRoomIndex(respawnRow))
    {
        g_dwRoomChainRanThisFrame_candidate = 1;
        SpawnMissingRoomGroupActors(respawnRow);
    }
    if (ShouldRunRoomIndex(chainRow))
    {
        g_dwRoomChainRanThisFrame_candidate = 1;
        RunRoomScriptChain(chainRow, 0);
    }
}
