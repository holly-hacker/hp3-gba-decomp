#include "input.h"

// ORs the low byte (A through Down, without L/R) of every player's pressed keys.
u8 GetAnyPlayerKeysPressed(void)
{
    u8 keys = 0;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(g_awPlayerKeysPressed); i++)
        keys |= g_awPlayerKeysPressed[i];
    return keys;
}
