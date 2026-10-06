#include "types.h"
#include "game/save.h"
#include "game/clear_save_slot_buffer.h"

// Serializes the game state into the cleared slot buffer and stores the
// negated checksum in the slot's last halfword.
void PackAndChecksumSaveSlot(void)
{
    u8 *pBuffer;
    u16 *pChecksum;

    ClearSaveSlotBuffer();
    pBuffer = g_saveManager.pSlotBuffer;
    g_saveManager.pStreamCursor = pBuffer;
    g_saveManager.dwStreamBitPos = 0;
    g_saveManager.dwStreamMode = SaveStreamPacking;
    SerializeGameStateToSaveBuffer();
    g_saveManager.dwStreamBytesUsed = g_saveManager.pStreamCursor - pBuffer;
    g_saveManager.dwStreamPercentUsed = g_saveManager.dwStreamBytesUsed * 100 / SAVE_SLOT_SIZE;
    g_saveManager.dwStreamMode = SaveStreamIdle;

    pChecksum = (u16 *)(pBuffer + SAVE_SLOT_SIZE - 2);
    *pChecksum = 0;
    *pChecksum = -Sum16(pBuffer, SAVE_SLOT_SIZE);
}
