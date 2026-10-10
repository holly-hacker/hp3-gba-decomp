#include "types.h"
#include "battle/battle.h"
#include "math.h"
#include "game/game_modes.h"
#include "game/save.h"
#include "graphics/audio.h"
#include "hw/input.h"
#include "menu/folio_universitas.h"
#include "menu/minigame_menu.h"

#define MOVE_CURSOR()                                                                              \
    SetObjectMoveTargetWithDuration_candidate(                                                     \
        g_FolioUniversitasState.pCursor,                                                           \
        (g_FolioUniversitasState.dwSlot + g_FolioUniversitasState.dwSlot / 3) * 8 + 0x78,          \
        g_FolioUniversitasState.dwCategory * 8 + 0x20, 5)

void UpdateFolioUniversitas(void)
{
    u32 prevSlot = g_FolioUniversitasState.dwSlot;
    u32 prevCategory = g_FolioUniversitasState.dwCategory;
    u32 card;
    u32 combo;
    u32 comboComplete;

    if (g_GameModeStackContext.dwModeState == 0)
    {
        u32 lastCategory = 5;

        // Only the first column has a sixth row.
        if (g_FolioUniversitasState.dwSlot != 0)
            lastCategory = 4;

        if (StepWrappedSelectionVertical_candidate(&g_FolioUniversitasState.dwCategory, 0, lastCategory, 1, 0))
        {
            MOVE_CURSOR();
            UpdateFolioComboSlots();
            HighlightFolioComboSlot();
            DrawFolioUniversitasNames(1);
        }

        if (g_GameModeStackContext.dwCurrentGameModeArg1 != FolioUniversitasPickCombo)
        {
            if (g_FolioUniversitasState.dwCategory != 5
                && StepWrappedSelectionHorizontal_candidate(&g_FolioUniversitasState.dwSlot, 0, 9, 1, 0))
            {
                MOVE_CURSOR();
                if (g_FolioUniversitasState.dwSlot / 3 != prevSlot / 3)
                {
                    DrawFolioUniversitasNames(1);
                    UpdateFolioComboSlots();
                }
                else
                {
                    DrawFolioUniversitasNames(0);
                }
                HighlightFolioComboSlot();
            }
        }
        else if ((g_wKeysPressed & (KeyRight | KeyLeft)) && g_FolioUniversitasState.dwCategory != 5)
        {
            if (g_wKeysPressed & KeyRight)
            {
                g_FolioUniversitasState.dwSlot += 3;
                if (g_FolioUniversitasState.dwSlot == 9)
                    g_FolioUniversitasState.dwSlot = 0;
            }
            else if (g_wKeysPressed & KeyLeft)
            {
                if (g_FolioUniversitasState.dwSlot == 0)
                    g_FolioUniversitasState.dwSlot = 6;
                else
                    g_FolioUniversitasState.dwSlot -= 3;
            }
            MOVE_CURSOR();
            DrawFolioUniversitasNames(1);
            UpdateFolioComboSlots();
        }

        if (g_wKeysPressed & KeyA)
        {
            switch (g_GameModeStackContext.dwCurrentGameModeArg1)
            {
            case FolioUniversitasBrowse:
                card = GetFolioUniversitasSelectedCard();
                if (FOLIO_CARD_SEEN(card))
                {
                    PlaySoundById(1);
                    PushGameMode_2(FolioUniversitasCardDetails, g_GameModeStackContext.dwCurrentGameModeArg1, card);
                }
                else
                {
                    PlaySoundById(3);
                }
                break;

            case FolioUniversitasPickCombo:
                combo = iwramDivideSignedQuotient(g_FolioUniversitasState.dwSlot, 3) + g_FolioUniversitasState.dwCategory * 3;
                card = GetFolioUniversitasSelectedCombo();
                comboComplete = 0;
                if (card == 0x32 && IsFolioUniversitasCardSeen(0x32))
                {
                    comboComplete = 1;
                }
                else if (IsFolioUniversitasCardSeen(card) && IsFolioUniversitasCardSeen(card + 1)
                         && IsFolioUniversitasCardSeen(card + 2))
                {
                    comboComplete = 1;
                }

                if (!comboComplete || IsFolioUniversitasCardUnavailable(card))
                {
                    PlaySoundById(3);
                    break;
                }

                if (card != 0x32)
                    g_pFightState->bFolioComboFirstCard = card;
                else
                    g_pFightState->bFolioComboFirstCard = 0xFF;
                g_GameModeStackContext.dwCurrentGameModeArg2 = combo;
                PushGameMode_3(Battle, g_pFightState->abBattleResumeArgs_candidate[0],
                               g_pFightState->abBattleResumeArgs_candidate[1],
                               g_pFightState->abBattleResumeArgs_candidate[2]);
                break;

            case FolioUniversitasPickCard:
                card = GetFolioUniversitasSelectedCard();
                if (g_saveStateBlock.abFolioUniversitasCounts[card] != 0)
                {
                    PlaySoundById(1);
                    ClearFolioUniversitasNewCards();
                    PushGameMode_2(CardTrade, 1, card);
                }
                else
                {
                    PlaySoundById(3);
                }
                break;
            }
        }
        else if (g_wKeysPressed & KeyB)
        {
            PlaySoundById(2);
            switch (g_GameModeStackContext.dwCurrentGameModeArg1)
            {
            case FolioUniversitasBrowse:
                ClearFolioUniversitasNewCards();
                PushGameMode_2(Folios, 1, 0);
                break;

            case FolioUniversitasPickCombo:
                g_GameModeStackContext.dwCurrentGameModeArg2 = 0xFF;
                PushGameMode_3(Battle, g_pFightState->abBattleResumeArgs_candidate[0],
                               g_pFightState->abBattleResumeArgs_candidate[1],
                               g_pFightState->abBattleResumeArgs_candidate[2]);
                break;

            case FolioUniversitasPickCard:
                ClearFolioUniversitasNewCards();
                PushGameMode_2(CardTrade, 1, 0x33);
                break;
            }
        }
        else if (g_wKeysPressed & KeySelect)
        {
            // The rare tenth card has no combo.
            if (g_FolioUniversitasState.dwSlot % 9 != 0 || g_FolioUniversitasState.dwSlot == 0)
            {
                PlaySoundById(1);
                PushGameMode_3(CardComboDescription, g_GameModeStackContext.dwCurrentGameModeArg1,
                               g_FolioUniversitasState.dwCategory * 10 + g_FolioUniversitasState.dwSlot,
                               g_FolioUniversitasState.dwCategory * 3
                                   + iwramDivideSignedQuotient(g_FolioUniversitasState.dwSlot, 3));
            }
            else
            {
                PlaySoundById(3);
            }
        }
    }

    if (prevSlot != g_FolioUniversitasState.dwSlot || prevCategory != g_FolioUniversitasState.dwCategory)
    {
        PlaySoundById(0);
        DrawFolioUniversitasButtonHints();
    }
}
