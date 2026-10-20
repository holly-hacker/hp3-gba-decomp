#include "types.h"
#include "char_block.h"
#include "commands.h"
#include "overworld/room.h"
#include "map.h"

// Registers a room's BG tile animation, with the BG control word its bFlags
// selects. Rooms 5-7 (the Hogwarts Express) instead register the window
// scenery animation for QUEST_ROOM_BG_VARIANT and start an endless camera shake.
void RegisterRoomBgTileAnimation(const BgTileAnimHeader *pAnimation)
{
    if (pAnimation != NULL)
    {
        if (g_bCurrentRoomId - 5 <= 2)
        {
            if (g_abQuestEventState[QUEST_ROOM_BG_VARIANT] == 1)
                RegisterBgTileAnimation(&g_aSpecialSceneBg0, &g_dwBg3Control, 0);
            else
            {
                RegisterBgTileAnimation(&g_aSpecialSceneBg2, &g_dwBg3Control, 0);
                StartEndlessCameraShake();
            }
        }
        else
        {
            switch (pAnimation->bFlags)
            {
            case 0:
                RegisterBgTileAnimation(pAnimation, &g_dwBg3Control, 0);
                break;
            case 1:
                RegisterBgTileAnimation(pAnimation, &g_dwBg1Control, 0);
                break;
            case 2:
                RegisterBgTileAnimation(pAnimation, &g_dwBg2Control, 0);
                break;
            case 3:
                RegisterBgTileAnimation(pAnimation, &g_dwBg0Control, 0);
                break;
            }
        }
    }
}
