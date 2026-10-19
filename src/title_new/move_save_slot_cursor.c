#include "types.h"
#include "sound.h"
#include "modes.h"
#include "input.h"
#include "actor.h"
#include "save.h"
#include "title_load.h"
#include "title_new.h"

void MoveSaveSlotCursor(void)
{
    u32 previous;

    previous = g_GameModeStackContext.dwModeScratchB;
    if (StepCursorUpDown(&g_GameModeStackContext.dwModeScratchB, 0, SAVE_SLOT_COUNT - 1, 1, 0))
    {
        DrawSaveSlot(previous, g_GameModeStackContext.dwModeScratchB);
        DrawSaveSlot(g_GameModeStackContext.dwModeScratchB, g_GameModeStackContext.dwModeScratchB);
        SetActorPosition(g_pSaveSlotCursorActor, 0x1C, g_GameModeStackContext.dwModeScratchB * 28 + 47);
        PlaySoundById(0);
    }
}
