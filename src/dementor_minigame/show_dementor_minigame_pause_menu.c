#include "types.h"
#include "actor.h"
#include "sound.h"
#include "modes.h"
#include "font.h"
#include "text.h"
#include "dementor_minigame.h"
#include "cursor.h"

void ShowDementorMinigamePauseMenu(void)
{
    s32 i;
    u32 tileCursor;
    Actor *pCursor;

    PlaySoundById(1);
    for (i = 0; i < 4; i++)
        SetActorVelocity(g_DementorMinigame.apDementors[i], 0, 0);

    tileCursor = DrawStringAligned(0x101, 0x78, 0x40, GetDialogText(0xA58), 1);  // "Resume Game"
    tileCursor = DrawStringAligned(tileCursor, 0x78, 0x50, GetDialogText(0xA59), 1);  // "Replay"
    DrawStringAligned(tileCursor, 0x78, 0x60, GetDialogText(0xA5A), 1);  // "Exit Game"

    g_GameModeStackContext.dwModeScratchB = 0;
    pCursor = SpawnMenuCursorActor(4);
    g_DementorMinigame.pCursorActor = pCursor;
    pCursor->pfnTick = MoveDementorMinigameMenuCursor;
    SetActorPosition(pCursor, 0x78, g_GameModeStackContext.dwModeScratchB * 16 + 0x48);
    g_GameModeStackContext.dwModeState = DementorMinigameStatePauseMenu;
}
