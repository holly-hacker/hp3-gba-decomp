#include "types.h"
#include "actor.h"
#include "sound.h"
#include "modes.h"
#include "menu/main_menu.h"
#include "font.h"
#include "text.h"
#include "boggart_minigame.h"
#include "cursor.h"

void ShowBoggartMinigamePauseMenu(void)
{
    u32 tileCursor;
    Actor *pCursor;

    PlaySoundById(1);
    SetActorVelocity(g_BoggartMinigame.pActor, 0, 0);
    SetActorAnimData(g_BoggartMinigame.pActor, &g_aBoggartFormAssets[g_BoggartMinigame.dwBoggartDirection],
                     g_abBoggartStopAnimData, 0);

    tileCursor = DrawStringAligned(0x81, 0x78, 0x40, GetDialogText(0xA58), 1);  // "Resume Game"
    tileCursor = DrawStringAligned(tileCursor, 0x78, 0x50, GetDialogText(0xA59), 1);  // "Replay"
    DrawStringAligned(tileCursor, 0x78, 0x60, GetDialogText(0xA5A), 1);  // "Exit Game"

    g_GameModeStackContext.dwModeScratchB = 0;
    pCursor = SpawnMenuCursorActor(4);
    g_BoggartMinigame.pCursorActor = pCursor;
    pCursor->pfnTick = MoveBoggartMinigameMenuCursor;
    SetActorPosition(pCursor, 0x78, g_GameModeStackContext.dwModeScratchB * 16 + 0x48);
    g_GameModeStackContext.dwModeState = BoggartMinigameStatePauseMenu;
}
