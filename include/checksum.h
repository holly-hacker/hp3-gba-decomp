#pragma once

#include "types.h"

// CRC-8 over len bytes (reflected polynomial 0x8C, initial value 0, no final XOR).
u8 ComputeCrc8(const u8 *data, u32 len);

// 8-bit checksum of a halfword, used by the GameCube link's JOYBUS data words.
u8 ComputeJoybusChecksum(u16 value);
