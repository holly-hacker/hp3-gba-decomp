#include "types.h"
#include "hw/interrupts.h"
#include "mt19937.h"
#include "serial/serial.h"

// Resets the link hardware when the exchange loop is enabled, reseeds the RNG and forgets every
// peer's last message sequence number.
s32 BeginSerialSession(void)
{
    if (g_dwSerialMode == 1)
    {
        InstallInterruptHandler(IntrMain);
        InitSerial();
    }
    Mt19937AutoSeed();
    g_bSerialTick = 0;
    g_abSerialLastRecvSeq[0] = 0xFF;
    g_abSerialLastRecvSeq[1] = 0xFF;
    // BUG: g_abSerialLastRecvSeq has 2 entries. [3] sets the low byte of g_awSerialKeysReceived[0].
    g_abSerialLastRecvSeq[2] = 0xFF;
    g_abSerialLastRecvSeq[3] = 0xFF;
    return 1;
}
