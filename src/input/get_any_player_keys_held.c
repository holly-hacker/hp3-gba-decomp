#include "input.h"

// ORs the low byte (A through Down, without L/R) of every player's held keys.
u8 GetAnyPlayerKeysHeld(void)
{
    u8 keys = 0;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_awPlayerKeysHeld); i++)
        keys |= g_awPlayerKeysHeld[i];
    return keys;
}
