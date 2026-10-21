#include "types.h"
#include "actor.h"
#include "sound.h"
#include "modes.h"
#include "font.h"
#include "text.h"
#include "cursor.h"
#include "tea_leaves_minigame.h"

void ShowDivinationTeaPauseMenu(void)
{
    u32 tileCursor;
    Actor *pCursor;

    PlaySoundById(1);
    g_DivinationTea.dwPaused = 1;

    tileCursor = DrawStringAligned(0x21, 0x78, 0x40, GetDialogText(0xA58), 1);  // "Resume Game"
    DrawStringAligned(tileCursor, 0x78, 0x50, GetDialogText(0xA5A), 1);  // "Exit Game"

    g_GameModeStackContext.dwModeScratchB = 0;
    pCursor = SpawnMenuCursorActor(4);
    g_DivinationTea.pCursorActor = pCursor;
    pCursor->pfnTick = MoveDivinationTeaMenuCursor;
    SetActorPosition(pCursor, 0x78, g_GameModeStackContext.dwModeScratchB * 16 + 0x48);
}
