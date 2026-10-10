#include "types.h"
#include "graphics/audio.h"
#include "graphics/display.h"
#include "battle/battle.h"
#include "game/game_modes.h"
#include "game/game_save.h"
#include "game/save.h"
#include "input.h"
#include "hw/mem.h"
#include "menu/card_trade.h"
#include "menu/folio_universitas.h"
#include "menu/in_game_menu.h"
#include "menu/minigame_menu.h"

void UpdateCardTrade(void)
{
    u32 row;

    TickSerialSession(2, 0);

    if (IsSerialUp() == 0)
    {
        g_CardTradeState.bPeerOffer = CARD_TRADE_NO_CARD;
        SetCardTradeSlotCard(1, CARD_TRADE_NO_CARD);
        SerialConnect(2);
    }

    if (g_GameModeStackContext.dwModeState != 0)
        ShowCardTradeLinkStatus(IsSerialUp());

    switch (g_GameModeStackContext.dwModeState)
    {
    case 0:
    case 1:
        TickMenuFadeIn();
        if (g_GameModeStackContext.dwModeSubState == 0)
        {
            if (g_GameModeStackContext.dwModeState == 0)
            {
                StartMenuFadeIn();
                BuildListMenu(&g_CardTradeMenuDefinition);
                RefreshCardTradeSlots();
                SpawnCardTradeCardObjects();
                g_GameModeStackContext.dwModeState = 1;
            }
            else
                g_GameModeStackContext.dwModeState = 2;
        }
        break;

    case 2:
        if (g_GameModeStackContext.dwModeTimer != 0)
        {
            g_GameModeStackContext.dwModeTimer--;
            if (g_GameModeStackContext.dwModeTimer == 0)
                ShowCardTradeMessage(0xACF);  // no text: clears the message box
        }

        RefreshCardTradeSlots();

        if (g_wKeysPressed & KeyA)
            SelectCardTradeEntry();
        else if (g_wKeysPressed & KeyB)
            LeaveCardTradeScreen();
        else if (g_wKeysPressed & (KeyUp | KeyDown))
            MoveListMenuCursor();
        break;

    case 3:
    case 4:
        TickMenuFadeOut();
        if (g_GameModeStackContext.dwModeSubState == 0x10)
        {
            if (g_GameModeStackContext.dwModeState == 4)
            {
                ClearBgTilemap(2);
                FreeAllObjects(&g_ActiveObjectListState.pHead);
                StartMenuOverlayFadeOut();
                g_GameModeStackContext.dwModeState = 3;
            }
            else
                PushGameMode(Connectivity);
        }
        break;

    case 5:
        if (IsSerialUp() == 0)
        {
            ResetCardTradeAfterLinkLoss();
            break;
        }

        if ((g_wKeysPressed & KeyB) || g_CardTradeState.bPeerLocked != g_CardTradeState.bPeerOffer)
        {
            CancelCardTradeOffer();
            PlaySoundById(2);
            break;
        }

        if (g_CardTradeState.bPeerReady != 0)
        {
            g_GameModeStackContext.dwModeTimer--;
            if (g_GameModeStackContext.dwModeTimer == -1)
            {
                PlaySoundById(0x19);
                DrawCardTradeSlotName(0, CARD_TRADE_NO_CARD);
                DrawCardTradeSlotName(1, CARD_TRADE_NO_CARD);

                if (g_apMenuIconObjects[0] != NULL)
                    SetObjectMoveTargetWithDuration_candidate(g_apMenuIconObjects[0],
                        g_aCardTradeSlotPositions[1].bX, g_aCardTradeSlotPositions[1].bY, 30);

                if (g_apMenuIconObjects[1] != NULL)
                    SetObjectMoveTargetWithDuration_candidate(g_apMenuIconObjects[1],
                        g_aCardTradeSlotPositions[0].bX, g_aCardTradeSlotPositions[0].bY, 30);

                ShowCardTradeMessage(0xACF);  // no text: clears the message box
                g_GameModeStackContext.dwModeState = 6;
                g_GameModeStackContext.dwModeTimer = 30;
            }
        }
        else
            g_GameModeStackContext.dwModeTimer = 3;
        break;

    case 6:
        if (IsSerialUp() == 0)
        {
            ResetCardTradeAfterLinkLoss();
            break;
        }

        g_GameModeStackContext.dwModeTimer--;
        if (g_GameModeStackContext.dwModeTimer == -1)
        {
            g_CardTradeState.bLocalOffer = CARD_TRADE_NO_CARD;

            if (g_CardTradeState.bLocalLocked <= 0x32)
                DecrementFolioUniversitasCard(g_CardTradeState.bLocalLocked);

            if (g_CardTradeState.bPeerLocked <= 0x32)
                IncrementFolioUniversitasCard(g_CardTradeState.bPeerLocked);

            SetCardTradeSlotCard(0, g_CardTradeState.bPeerLocked);
            SetCardTradeSlotCard(1, g_CardTradeState.bLocalLocked);
            g_GameModeStackContext.dwModeState = 8;
        }
        break;

    case 7:
        if (IsSerialUp() == 0)
        {
            ResetCardTradeAfterLinkLoss();
            break;
        }

        g_GameModeStackContext.dwModeTimer--;
        if (g_GameModeStackContext.dwModeTimer != -1)
        {
            if (g_GameModeStackContext.dwModeTimer == 5)
                g_CardTradeState.bLocalOffer = CARD_TRADE_NO_CARD;
        }
        break;

    case 8:
        ShowCardTradeMessage(0x592);  // "Saving Game..."
        PauseMusic();
        SyncSaveHeaderIfDirty();
        SaveGameToSlot(g_saveManager.dwActiveSlot);
        ResumeMusic();

        row = g_GameModeStackContext.dwModeScratchB;
        g_GameModeStackContext.dwModeScratchB = 0;
        DrawListMenuRow(row);
        DrawListMenuRow(g_GameModeStackContext.dwModeScratchB);
        CancelCardTradeOffer();
        RefreshCardTradeSlots();
        ShowCardTradeMessage(0x8CB);  // "Trade Complete!"
        g_GameModeStackContext.dwModeTimer = 150;
        g_GameModeStackContext.dwModeState = 2;
        break;
    }
}
