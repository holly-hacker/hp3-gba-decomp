#pragma once

#include "types.h"
#include "menu/menu.h"

// Card value meaning "no card chosen"; real cards are 0-50.
#define CARD_TRADE_NO_CARD 0x33

// Link card trade session at 0x03005568; see docs/memory-map/link.md.
typedef struct {
    u32 dwStatus;       // 0x00: last link result, 0/1
    u8 bConfirmed;      // 0x04
    u8 bLocalOffer;     // 0x05: local card, or CARD_TRADE_NO_CARD
    u8 bLocalLocked;    // 0x06: latched copy of bLocalOffer
    u8 bUnk07;          // 0x07: always CARD_TRADE_NO_CARD, never read
    u8 bPeerReady;      // 0x08
    u8 bPeerOffer;      // 0x09
    u8 bPeerLocked;     // 0x0A
    u8 bUnk0B;          // 0x0B: always CARD_TRADE_NO_CARD, never read
} CardTradeState;

// Where each side's card object parks, in screen pixels.
typedef struct {
    u8 bX;
    u8 bY;
    u8 abPad[2];
} CardTradeSlotPosition;

extern CardTradeState g_CardTradeState;  // 0x03005568
extern Object *g_apMenuIconObjects[];    // 0x03003F68: list menu row icons (SpawnMenuIconObject) and objects
                                         // registered by slot (RegisterMenuIconObject)

extern const ListMenuEntry g_aCardTradeEntries[3];                    // 0x0806B35C
extern const ListMenuDefinition g_CardTradeMenuDefinition;            // 0x0806B380
extern const CardTradeSlotPosition g_aCardTradeSlotPositions[2];      // 0x0806B3A4

extern const u8 gCardTradeOverlay[];

extern void ReceiveCardTradeOffer(u32 word, u32 playerId);
extern u32 GetCardTradeSendWord(void);

extern u32 IsLinkUp(void);
extern u32 LinkConnect(u32 mode);
extern void SetLinkCallbacks(void (*pOnReceive)(u32 word, u32 playerId), u32 (*pGetSendWord)(void));
extern void InitLinkSession(void);
extern void StartLinkConnection(u32 arg);
extern void TickLinkSession(u32 arg0, u32 arg1);
extern void CloseLinkSession(void);
extern void ClearMenuTextLayer_candidate(void);

extern void ResetCardTradeAfterLinkLoss(void);
extern void SpawnCardTradeCardObjects(void);
extern void SelectCardTradeEntry(void);
extern void CancelCardTradeOffer(void);
extern void ShowCardTradeLinkStatus(u32 linkUp);
extern void RefreshCardTradeSlots(void);
extern void SetCardTradeSlotCard(u32 side, u32 card);
extern void DrawCardTradeSlotName(u32 side, u32 card);
extern void ShowCardTradeMessage(u32 textId);
extern void LeaveCardTradeScreen(void);
