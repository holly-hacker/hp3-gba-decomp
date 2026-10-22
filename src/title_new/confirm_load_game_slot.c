#include "types.h"
#include "sound.h"
#include "modes.h"
#include "save.h"
#include "map.h"
#include "title_new.h"

// Only a slot holding a started game loads; the others buzz.
void ConfirmLoadGameSlot(void)
{
    u32 slot;

    slot = g_GameModeStackContext.dwModeScratchB;
    if (slot < SAVE_SLOT_COUNT)
    {
        if (g_saveManager.adwSlotValid[slot]
            && (g_saveManager.aSlotPreview[slot].bSaveFlags & PlaytimeCounterActive))
        {
            PushGameMode_2(Overworld, OverworldEntryRestore, g_bCurrentRoomId);
            PlaySoundById(1);
        }
        else
        {
            PlaySoundById(3);
        }
    }
}
