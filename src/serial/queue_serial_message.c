#include "types.h"
#include "game/game_modes.h"
#include "hw/io_regs.h"
#include "hw/mem.h"
#include "serial/serial.h"

// Queues a message for the next exchange unless a message of a higher type is already waiting.
void QueueSerialMessage(u32 type, u32 data)
{
    SerialMessage message;

    if (type < g_SerialSendMessage.bType)
        return;

    memset(&message, 0, sizeof(message));
    message.bType = type;
    switch (type)
    {
    case SERIAL_MESSAGE_IDLE:
        break;
    case SERIAL_MESSAGE_KEYS:
        message.wData = ~REG_KEYINPUT;
        break;
    case SERIAL_MESSAGE_SEED:
        message.wData = data;
        break;
    }
    message.bSeq = g_bSerialTick;
    CopyMemory(&g_SerialSendMessage, &message, sizeof(message));
    g_dwGameModeFlags |= 0x1000;
}
