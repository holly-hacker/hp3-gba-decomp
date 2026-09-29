#pragma once

#include "types.h"

// Describes one of the two EEPROM sizes the cartridge backup can be built
// with. `size` is the whole device size in bytes; `blockCount` is `size`
// divided by the fixed 8-byte block, and `addressBits` is the serial
// address width (6 for the 4 Kbit/512-byte part, 14 for the 64 Kbit/8 KB
// part) sent before each read/write command. `waitcntBits` is the GBA
// WAITCNT wait-2 field EepromDma3Transfer ORs in while the EEPROM's
// SRAM-area mirror is being accessed.
typedef struct
{
    u32 size;
    u16 blockCount;
    u16 waitcntBits;
    u8 addressBits;
} EepromInterface;

// Selected by EepromSelectInterface; NULL until then. See docs/formats/save.md.
extern const EepromInterface *g_pEepromInterface;

extern const EepromInterface sEepromInterface4K;
extern const EepromInterface sEepromInterface64K;

u16 EepromSelectInterface(u16 saveType);
void EepromDma3Transfer(const void *src, void *dest, u16 count);
u16 EepromReadBlock(u16 block, u16 *dest);
u16 EepromWriteBlockUnguarded(u16 block, const u16 *src);
u16 EepromWriteBlockRaw(u16 block, const u16 *src, u8 waitForTimeout);
u16 EepromVerifyBlock(u16 block, const u16 *src);
u16 EepromWriteBlockRetryLoop(u16 block, const u16 *src);
u16 EepromWriteBlockGuarded(u16 block, const u16 *src);
u16 EepromWriteBlockVerified(u16 block, const u16 *src);
