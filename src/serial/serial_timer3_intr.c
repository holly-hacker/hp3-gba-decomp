#include "types.h"
#include "hw/io_regs.h"
#include "hw/vblank.h"
#include "serial/serial.h"

// The parent (SIOCNT bit 2 clear) starts the next transfer and restarts the Timer 3 pump.
static inline void StartSerialTransferIfParent(void)
{
    if (!(REG_SIOCNT & 4))
    {
        REG_SIOCNT |= 0x80;
        REG_TM3CNT_H = 0xC0;
    }
}

// Ends the handshake: from here on SerialConnect's wait callback times out on missed exchanges.
static inline void CompleteSerialHandshake(void)
{
    g_SerialPlayerState.pfnWaitCallback = SerialPhase2;
    g_dwSerialLastExchangeTime = g_pVBlankState->dwVBlankCount;
    g_SerialPlayerState.dwUnk_0x00 = -1;
    ClearSerialChecksumRollBytes();
    g_SerialLink.dwFlags |= SERIAL_FLAG_CLEARED_ON_RESET;
    g_SerialLink.dwFlags &= ~SERIAL_FLAG_HANDSHAKE;
}

// Timer 3 (parent) or serial (child) interrupt during connection: counts the terminals that
// answered the last transfer, passes data words to the game's receive callback, runs the 0xB0CA
// handshake and chooses this terminal's next send word.
void SerialTimer3Intr(void)
{
    s32 i;
    s32 j;
    u32 word;
    u16 parentWord;
    u16 sendWord;
    s32 handshakeDone;

    if (REG_SIOCNT & 0x80)
        return;

    g_dwSerialPlayerCount = 0;
    g_bSerialPlayerMask = 0;
    if (REG_SIOCNT & 0x40)
        return;

    g_dwSerialLastExchangeTime = g_pVBlankState->dwVBlankCount;
    if (!(REG_SIOCNT & 4))
        REG_TM3CNT_H = 0;

    for (i = 1; i >= 0; i--)
    {
        word = REG_SIOMULTI(i);
        if (word == SERIAL_WORD_ROUND_END || word == SERIAL_WORD_ROUND_START || word == SERIAL_WORD_BABE
            || word == SERIAL_WORD_DEAD)
        {
            g_dwSerialPlayerCount = SERIAL_PLAYER_COUNT_ERROR;
            if (!(REG_SIOCNT & 4))
                StartSerialTransferIfParent();
            return;
        }

        if (word == SERIAL_WORD_CONNECT || word == SERIAL_WORD_HANDSHAKE)
        {
            g_dwSerialPlayerCount++;
            g_bSerialPlayerMask |= 1 << i;
            if (word == SERIAL_WORD_HANDSHAKE)
                g_SerialLink.dwFlags |= SERIAL_FLAG_HANDSHAKE;
        }
        else if ((word & SERIAL_WORD_DATA_MASK) == SERIAL_WORD_DATA)
        {
            g_dwSerialPlayerCount++;
            g_bSerialPlayerMask |= 1 << i;
            if (g_SerialLink.pfnReceive != NULL)
                g_SerialLink.pfnReceive(word, i);
        }
    }

    if (g_dwSerialPlayerCount != 0)
        g_SerialPlayerState.bPlayerId = (REG_SIOCNT >> 4) & 3;

    if (g_SerialPlayerState.bPlayerId > 1)
    {
        g_dwSerialPlayerCount = 0;
        g_bSerialPlayerMask = 0;
        return;
    }

    if (g_SerialLink.dwFlags & SERIAL_FLAG_HANDSHAKE)
    {
        if (g_SerialPlayerState.bPlayerId == 0)
        {
            // The parent finishes once every child echoes the handshake word.
            handshakeDone = 1;
            for (j = g_SerialPlayerState.bPlayerCount - 1; j > 0; j--)
            {
                if (REG_SIOMULTI(j) != SERIAL_WORD_HANDSHAKE)
                {
                    handshakeDone = 0;
                    break;
                }
            }
            if (handshakeDone)
            {
                CompleteSerialHandshake();
                REG_TM3CNT_L = SERIAL_TIMER_RELOAD;
                StartSerialGameSession();
                return;
            }
            REG_SIOMLT_SEND = SERIAL_WORD_HANDSHAKE;
        }
        else
        {
            // A child echoes the parent's handshake word and finishes.
            parentWord = REG_SIOMULTI(0);
            if (parentWord == SERIAL_WORD_HANDSHAKE)
            {
                REG_SIOMLT_SEND = parentWord;
                CompleteSerialHandshake();
                REG_TM3CNT_L = SERIAL_TIMER_RELOAD;
                StartSerialGameSession();
                return;
            }
            REG_SIOMLT_SEND = SERIAL_WORD_CONNECT;
        }
    }
    else
    {
        g_SerialPlayerState.bPlayerCount = g_dwSerialPlayerCount;
        if (g_SerialLink.pfnGetSendWord != NULL)
            sendWord = g_SerialLink.pfnGetSendWord();
        else
            sendWord = SERIAL_WORD_CONNECT;
        REG_SIOMLT_SEND = sendWord;
    }

    for (i = 1; i >= 0; i--)
        REG_SIOMULTI(i) = 0xFFFF;
    StartSerialTransferIfParent();
}
