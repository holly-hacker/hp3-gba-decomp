#include "eeprom.h"

// Nintendo EEPROM library object EEPROM_NOWAIT: block writes that return
// as soon as the chip reports ready. The ID string is not read by any
// game code.
const u8 sEepromNoWaitVersionString[14] = "EEPROM_NOWAIT";

// Refuses to write through the small (512-byte) interface -- only the
// 8 KB interface's raw single-shot write (no retry) is exposed here.
u16 EepromWriteBlockGuarded(u16 block, const u16 *src)
{
    if (g_pEepromInterface->size == 0x200)
        return 0x8080;

    return EepromWriteBlockRaw(block, src, 0);
}

// Up to 3 attempts of guarded-write-then-verify, stopping at the first
// attempt where both succeed.
u16 EepromWriteBlockVerified(u16 block, const u16 *src)
{
    u16 result;
    u8 attempt;

    for (attempt = 0; attempt <= 2; attempt++)
    {
        result = EepromWriteBlockGuarded(block, src);
        if (result != 0)
            continue;

        result = EepromVerifyBlock(block, src);
        if (result != 0)
            continue;

        break;
    }

    return result;
}
