#include "types.h"
#include "game/save.h"

// Deserializes the game state from the slot buffer (already loaded by the
// caller; slot is unused) and records how much of the slot the stream used.
void UnpackSaveSlot(u32 slot)
{
    g_saveManager.pStreamCursor = g_saveManager.pSlotBuffer;
    g_saveManager.dwStreamBitPos = 0;
    g_saveManager.dwStreamMode = SaveStreamUnpacking;
    DeserializeGameStateFromSaveBuffer();
    g_saveManager.dwStreamBytesUsed = g_saveManager.pStreamCursor - g_saveManager.pSlotBuffer;
    g_saveManager.dwStreamPercentUsed = g_saveManager.dwStreamBytesUsed * 100 / SAVE_SLOT_SIZE;
    g_saveManager.dwStreamMode = SaveStreamIdle;
}
