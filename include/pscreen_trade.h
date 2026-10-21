#pragma once

#include "types.h"
#include "pause_menu.h"
#include "actor.h"

// Card value meaning "no card chosen"; real cards are 0-50.
#define CARD_TRADE_NO_CARD 0x33

// One past the last dialog string: ShowCardTradeMessage clears the box without text.
#define CARD_TRADE_NO_MESSAGE 0xACF

// Text tile layout: the two slot names, then the message box (28x2 tiles), then the link status.
#ifdef VERSION_JP
#define CARD_TRADE_SLOT_NAME_TILES 40
#else
#define CARD_TRADE_SLOT_NAME_TILES 30
#endif
#define CARD_TRADE_SLOT_NAME_TILE   0xF1
#define CARD_TRADE_MESSAGE_TILE     (CARD_TRADE_SLOT_NAME_TILE + 2 * CARD_TRADE_SLOT_NAME_TILES)
#define CARD_TRADE_LINK_STATUS_TILE (CARD_TRADE_MESSAGE_TILE + 28 * 2)

// One side of a card trade. aSides[CARD_TRADE_LOCAL] is this player's; the peer's arrives
// through ReceiveCardTradeOffer.
typedef struct {
    u8 bReady;      // +0: confirmed the trade; picks the side's ready icon
    u8 bOffer;      // +1: offered card, or CARD_TRADE_NO_CARD
    u8 bLocked;     // +2: bOffer latched when the trade starts
    u8 bShownCard;  // +3: card the side's slot shows, set by SetCardTradeSlotCard
} CardTradeSide;

#define CARD_TRADE_LOCAL 0
#define CARD_TRADE_PEER  1

// Link card trade session at 0x03005568.
typedef struct {
    u32 dwStatus;              // 0x00: last link result, 0/1
    CardTradeSide aSides[2];   // 0x04
} CardTradeState;

// Where each side's card actor parks, in screen pixels.
typedef struct {
    u8 bX;
    u8 bY;
    u8 abPad[2];
} CardTradeSlotPosition;

extern CardTradeState g_CardTradeState;  // 0x03005568

extern const ListMenuEntry g_aCardTradeEntries[3];                    // 0x0806B35C
extern const ListMenuDefinition g_CardTradeMenuDefinition;            // 0x0806B380
extern const CardTradeSlotPosition g_aCardTradeSlotPositions[2];      // 0x0806B3A4
extern const ActorAssetRecord g_aCardTradeReadyIconAssets[2];         // 0x0806B3AC: not ready, ready

extern const u8 gCardTradeOverlay[];

extern void ReceiveCardTradeOffer(u32 word, u32 playerId);
extern u32 GetCardTradeSendWord(void);

extern void InitializeCardTrade(void);
extern void UpdateCardTrade(void);
extern void ExitCardTrade(void);
extern void ResetCardTradeAfterLinkLoss(void);
extern void SpawnCardTradeReadyIcons(void);
extern void SelectCardTradeEntry(void);
extern void CancelCardTradeOffer(void);
extern void ShowCardTradeLinkStatus(u32 linkUp);
extern void RefreshCardTradeSlots(void);
extern void SetCardTradeSlotCard(u32 side, u32 card);
extern void RespawnCardTradeCardActor(u32 side, u32 card);
extern void DrawCardTradeSlotName(u32 side, u32 card);
extern void ShowCardTradeMessage(u32 textId);  // CARD_TRADE_NO_MESSAGE only clears the box
extern void TickCardTradeReadyIcon(Actor *pIcon);
extern void LeaveCardTradeScreen(void);
