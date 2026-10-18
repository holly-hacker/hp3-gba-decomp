#include "types.h"
#include "background.h"
#include "sound.h"
#include "font.h"
#include "text.h"
#include "modes.h"
#include "input.h"
#include "actor.h"
#include "combat_end.h"
#include "screen_transitions.h"
#include "map.h"

void UpdateCombatResult(void)
{
    u8 *pText;

    switch (g_GameModeStackContext.dwModeState)
    {
    case CombatResultStateIntroDelay:
        g_GameModeStackContext.dwModeTimer--;
        if (g_GameModeStackContext.dwModeTimer == -1)
            g_GameModeStackContext.dwModeState = CombatResultStateXp;
        break;

    case CombatResultStateXp:
        if (g_dwCombatResultXpRemaining != 0)
        {
            if (g_dwCombatResultXpRemaining & 1)
                PlaySoundById(0x1A);

            TickCombatResultXpCounter();
            if (g_wKeysPressed & KeyA)
            {
                while (g_dwCombatResultXpRemaining != 0)
                    TickCombatResultXpCounter();
            }

            if (g_dwCombatResultXpRemaining != 0)
                break;

            g_GameModeStackContext.dwModeTimer = 0x3C;
            g_GameModeStackContext.dwModeState = CombatResultStateIntroDelay;
            g_GameModeStackContext.dwCurrentGameModeArg2 = 0;
            break;
        }

        if (g_GameModeStackContext.dwCurrentGameModeArg2 == 0)
        {
            g_GameModeStackContext.dwCurrentGameModeArg2 = 1;
            ClearBgTilemapRect(0, 0, 0x12, 0x1E, 2);
            SelectTextFont(1, 0, -1);
            pText = GetDialogText(0x647);  // "Press the A Button to continue."
            g_wCombatResultTextTileCursor = DrawStringAligned(g_wCombatResultTextTileCursor, 0x78, 0x94, pText, 1);
        }

        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            SetAlphaBlendTargets(0x17, 0xC);
            SetAlphaBlendCoefficients(0xF, 0);
            g_GameModeStackContext.dwModeState = CombatResultStateFadeOutXp;
            g_GameModeStackContext.dwModeTimer = 0x10;
        }
        break;

    case CombatResultStateFadeOutXp:
        if (g_GameModeStackContext.dwModeTimer-- > 0)
        {
            SetAlphaBlendCoefficients(g_GameModeStackContext.dwModeTimer, 0x10 - g_GameModeStackContext.dwModeTimer);
            if (g_GameModeStackContext.dwModeTimer == 2)
                ClearBgTilemap(0);
        }
        else
        {
            ClearBgTilemap(1);
            ClearBgTilemap(2);
            FreeAllActors(&g_ActiveActorListState.pHead);
            InitializeCombatResultDrops();
            SetAlphaBlendTargets(0x11, 8);
            SetAlphaBlendCoefficients(0, 0x10);
            g_GameModeStackContext.dwModeState = CombatResultStateFadeInDrops;
            g_GameModeStackContext.dwModeTimer = 0x10;
        }
        break;

    case CombatResultStateFadeInDrops:
        if (g_GameModeStackContext.dwModeTimer != 0)
        {
            g_GameModeStackContext.dwModeTimer--;
            SetAlphaBlendCoefficients(0x10 - g_GameModeStackContext.dwModeTimer, g_GameModeStackContext.dwModeTimer);
        }
        else
            g_GameModeStackContext.dwModeState = CombatResultStateDrops;
        break;

    case CombatResultStateDrops:
        if (g_wKeysPressed & KeyA)
        {
            PlaySoundById(1);
            PushGameMode_2(Overworld, 2, g_bCurrentRoomId);
        }
        break;
    }
}
