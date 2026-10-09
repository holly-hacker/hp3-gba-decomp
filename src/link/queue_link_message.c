#include "types.h"
#include "game/game_modes.h"
#include "hw/io_regs.h"
#include "hw/mem.h"
#include "link/link.h"

// Queues a message for the next exchange unless a message of a higher type is already waiting.
void QueueLinkMessage(u32 type, u32 data)
{
    LinkMessage message;

    if (type < g_LinkSendMessage.bType)
        return;

    memset(&message, 0, sizeof(message));
    message.bType = type;
    switch (type)
    {
    case LINK_MESSAGE_IDLE:
        break;
    case LINK_MESSAGE_KEYS:
        message.wData = ~REG_KEYINPUT;
        break;
    case LINK_MESSAGE_SEED:
        message.wData = data;
        break;
    }
    message.bSeq = g_bLinkTick;
    CopyMemory(&g_LinkSendMessage, &message, sizeof(message));
    g_dwGameModeFlags |= 0x1000;
}
