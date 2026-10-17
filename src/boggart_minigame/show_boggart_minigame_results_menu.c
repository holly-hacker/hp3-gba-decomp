#include "types.h"
#include "background.h"
#include "actor.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "modes.h"
#include "menu/main_menu.h"
#include "font.h"
#include "text.h"
#include "boggart_minigame.h"
#include "cursor.h"

void ShowBoggartMinigameResultsMenu(void)
{
    u32 tileCursor;
    Actor *pCursor;

    PlaySoundById(1);
    ClearBgTilemapRect(3, 0, 0x10, 0x1E, 4);
    SetActorVelocity(g_BoggartMinigame.pActor, 0, 0);
    SetActorAnimData(g_BoggartMinigame.pActor, &g_aBoggartFormAssets[g_BoggartMinigame.dwBoggartDirection],
                     g_abBoggartStopAnimData, 0);

    tileCursor = DrawStringAligned(0x81, 0x78, 0x40, GetDialogText(0xA59), 1);  // "Replay"
    DrawStringAligned(tileCursor, 0x78, 0x50, GetDialogText(0xA5A), 1);  // "Exit Game"

    g_GameModeStackContext.dwModeScratchB = 0;
    pCursor = SpawnMenuCursorActor(4);
    g_BoggartMinigame.pCursorActor = pCursor;
    pCursor->pfnTick = MoveBoggartMinigameMenuCursor;
    SetActorPosition(pCursor, 0x78, g_GameModeStackContext.dwModeScratchB * 16 + 0x48);
    g_GameModeStackContext.dwModeState = BoggartMinigameStateResultsMenu;
}
