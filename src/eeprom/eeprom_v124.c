#include "eeprom.h"
#include "io_regs.h"

// Nintendo EEPROM library object EEPROM_V124: interface selection, the
// DMA3 serial transfer, and block read, write and verify. The ID string is
// not read by any game code.

// Scanlines EepromWriteBlockRaw waits, counted from the end of the command,
// before giving up on the chip's ready bit.
#define EEPROM_WRITE_TIMEOUT_SCANLINES 0x88

const u8 sEepromVersionString[12] = "EEPROM_V124";

const EepromInterface sEepromInterface4K = { 0x200, 0x40, 0x300, 6 };
const EepromInterface sEepromInterface64K = { 0x2000, 0x400, 0x300, 14 };

// saveType is the cartridge backup-type id from the multiboot/save header
// convention (4 = 512-byte EEPROM, 0x40 = 8 KB EEPROM); anything else
// falls back to the smaller interface. Returns 1 on that fallback, 0 when
// saveType matched a known size.
u16 EepromSelectInterface(u16 saveType)
{
    u16 result;

    result = 0;
    if (saveType == 4)
    {
        g_pEepromInterface = &sEepromInterface4K;
    }
    else if (saveType == 0x40)
    {
        g_pEepromInterface = &sEepromInterface64K;
    }
    else
    {
        g_pEepromInterface = &sEepromInterface4K;
        result = 1;
    }

    return result;
}

// Bit-bangs one EEPROM serial command over DMA3: each 16-bit unit
// transferred carries a single bit in its low bit. Interrupts are masked
// for the duration.
void EepromDma3Transfer(const void *src, void *dest, u16 count)
{
    u16 waitcnt;
    u16 savedIme;

    savedIme = REG_IME;
    REG_IME = 0;

    waitcnt = REG_WAITCNT;
    waitcnt &= 0xF8FF;
    waitcnt |= g_pEepromInterface->waitcntBits;
    REG_WAITCNT = waitcnt;

    REG_DMA3SAD = (u32)src;
    REG_DMA3DAD = (u32)dest;
    REG_DMA3CNT = count | 0x80000000;

    while (REG_DMA3CNT_H & 0x8000)
        ;

    REG_IME = savedIme;
}

// Reads one 8-byte block. The read command is 2 start bits, then
// addressBits address bits (MSB first), then a trailing bit whose value
// the chip ignores; the chip replies with 4 don't-care bits followed by
// the 64 data bits, MSB first.
u16 EepromReadBlock(u16 block, u16 *dest)
{
    u16 buffer[0x44];
    u16 value;
    u16 *cmd;
    u8 i;
    u8 word;
    u32 byteOffset;
    u8 addressBits;

    if (block >= g_pEepromInterface->blockCount)
        return 0x80FF;

    addressBits = g_pEepromInterface->addressBits;
    byteOffset = addressBits << 1;
    cmd = (u16 *)(byteOffset + (u32)buffer);
    cmd++;
    value = block;
    for (i = 0; i < g_pEepromInterface->addressBits; i++)
    {
        *cmd = value;
        cmd--;
        value >>= 1;
    }
    *cmd = 1;
    cmd--;
    *cmd = 1;

    EepromDma3Transfer(buffer, EEPROM_PORT, g_pEepromInterface->addressBits + 3);
    EepromDma3Transfer(EEPROM_PORT, buffer, 0x44);

    cmd = &buffer[4];
    dest += 3;
    for (word = 0; word <= 3; word++)
    {
        u16 bits;
        u8 bit;

        bits = 0;
        for (bit = 0; bit <= 0xf; bit++)
        {
            bits <<= 1;
            bits |= *cmd & 1;
            cmd++;
        }
        *dest = bits;
        dest--;
    }

    return 0;
}

// EepromWriteBlockRaw that polls for the full write timeout
// (waitForTimeout = 1), with no data read-back check.
u16 EepromWriteBlockUnguarded(u16 block, const u16 *src)
{
    return EepromWriteBlockRaw(block, src, 1);
}

// Sends a write command (start bit, R/W=0, addressBits address bits, the
// 64 data bits, then a trailing 0 bit, all MSB first), then polls
// EEPROM_PORT's low bit while counting scanlines through REG_VCOUNT.
// Without waitForTimeout, returns 0 as soon as the chip reports ready.
// With it, a ready report is recorded but polling continues until the
// timeout elapses. Returns 0xC001 if the timeout elapses before any ready
// report, or 0x80FF for an out-of-range block.
u16 EepromWriteBlockRaw(u16 block, const u16 *src, u8 waitForTimeout)
{
    u16 buffer[0x52];
    u16 result;

    if (block >= g_pEepromInterface->blockCount)
        return 0x80FF;

    {
        u16 *cmd;
        u8 i;
        u8 bit;

        cmd = &buffer[g_pEepromInterface->addressBits + 67];
        cmd--;
        *cmd-- = 0;

        for (i = 0; i <= 3; i++)
        {
            u16 value;

            value = *src++;
            for (bit = 0; bit <= 0xf; bit++)
            {
                *cmd-- = value;
                value >>= 1;
            }
        }

        for (i = 0; i < g_pEepromInterface->addressBits; i++)
        {
            *cmd-- = block;
            block >>= 1;
        }
        *cmd-- = 0;
        *cmd = 1;
    }

    EepromDma3Transfer(buffer, EEPROM_PORT, g_pEepromInterface->addressBits + 0x43);

    {
        volatile u16 readyCount;
        volatile u16 lastVCount;
        volatile u16 vcount;
        volatile u32 elapsedScanlines;

        result = 0;
        readyCount = 0;
        lastVCount = REG_VCOUNT;
        elapsedScanlines = 0;

        for (;;)
        {
            if (readyCount == 0 && (*(volatile u16 *)EEPROM_PORT & 1) != 0)
            {
                readyCount++;
                if (!waitForTimeout)
                    break;
            }

            vcount = REG_VCOUNT;
            if (vcount != lastVCount)
            {
                if (vcount > lastVCount)
                    elapsedScanlines += vcount - lastVCount;
                else
                    elapsedScanlines += vcount + (228 - lastVCount);

                if (elapsedScanlines > EEPROM_WRITE_TIMEOUT_SCANLINES)
                {
                    if (readyCount == 0 && (*(volatile u16 *)EEPROM_PORT & 1) == 0)
                        result = 0xC001;
                    break;
                }

                lastVCount = vcount;
            }
        }
    }

    return result;
}

// Re-reads block and compares it against src, 16 bits at a time.
u16 EepromVerifyBlock(u16 block, const u16 *src)
{
    u16 localBuffer[4];
    const u16 *actual;
    u8 i;
    u16 result;

    result = 0;
    if (block >= g_pEepromInterface->blockCount)
        return 0x80FF;

    EepromReadBlock(block, localBuffer);

    actual = localBuffer;
    for (i = 0; i <= 3; i++)
    {
        if (*src++ != *actual++)
        {
            result = 0x8000;
            break;
        }
    }

    return result;
}

// Up to 3 attempts of write-then-verify, stopping at the first attempt
// where both succeed.
u16 EepromWriteBlockRetryLoop(u16 block, const u16 *src)
{
    u16 result;
    u8 attempt;

    for (attempt = 0; attempt <= 2; attempt++)
    {
        result = EepromWriteBlockUnguarded(block, src);
        if (result != 0)
            continue;

        result = EepromVerifyBlock(block, src);
        if (result != 0)
            continue;

        break;
    }

    return result;
}
