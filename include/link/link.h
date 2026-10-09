#pragma once

#include "types.h"

// Serial-link session block at 0x03005A24, written by the link init/teardown
// code and LinkSerialTimer3Intr. See docs/memory-map/link.md. Only the fields
// with a confirmed role are named.
typedef struct LinkPlayerState {
    s32 dwUnk_0x00;         // 0x00, set to -1 by link init and teardown
    u8 bUnk_0x04;           // 0x04, zeroed by link init and teardown
    s8 bPlayerId;           // 0x05, this GBA's multiplayer terminal ID: SIOCNT bits 4-5
                             // (0 = parent, 1-3 = child) sampled by LinkSerialTimer3Intr
                             // while linked; -1 when no session
    u8 pad_06[0x02];        // -> 0x08
    u32 dwUnk_0x08;         // 0x08, zeroed by link init; set by sub_0803FA7C
} LinkPlayerState;

extern LinkPlayerState g_LinkPlayerState;

// Returns g_LinkPlayerState.bPlayerId; -1 when there is no link session.
extern s32 GetLinkPlayerId(void);

// A message exchanged once per round, 12 bytes. The parent's send word starts each round and the
// children answer; see docs/memory-map/link.md.
typedef struct LinkMessage {
    u8 bType;         // 0 none, 1 idle, 2 keys, 3 RNG seed
    u8 bSeq;          // g_bLinkTick when queued
    u8 pad_02[2];
    u16 wData;        // keys held (type 2) or seed (type 3)
    u8 pad_06[6];
} LinkMessage;

#define LINK_MESSAGE_NONE 0
#define LINK_MESSAGE_IDLE 1
#define LINK_MESSAGE_KEYS 2
#define LINK_MESSAGE_SEED 3

// Bits of g_dwLinkFlags. Roles are inferred from the exchange loop.
#define LINK_FLAG_CLEARED_ON_RESET  0x0004
#define LINK_FLAG_TRANSFER_KICKED   0x0008  // set with LINK_FLAG_TRANSFER_STARTED
#define LINK_FLAG_TRANSFER_DONE     0x0010
#define LINK_FLAG_TRANSFER_STARTED  0x0020
#define LINK_FLAG_FRAME_READY       0x0040
#define LINK_FLAG_OWN_MESSAGE_SEEN  0x0080  // the local player's message was just received
#define LINK_FLAG_ROUND_COMPLETE    0x0200
#define LINK_FLAG_TIMED_OUT         0x8000
#define LINK_FLAG_CLOSED            0x80000

// Frames of waiting after which an exchange round gives up.
#define LINK_TIMEOUT_VBLANKS 600

extern volatile u32 g_dwLinkFlags;
extern LinkMessage g_aLinkRecvMessages[2];
extern LinkMessage g_LinkSendMessage;
extern u8 g_bLinkTick;
extern u8 g_abLinkLastRecvSeq[2];
extern u16 g_awLinkKeysReceived[2];
extern u8 g_bLinkSeedReceived;
extern u32 g_dwLinkMode;
extern u8 g_bLinkPeerCount;
extern u32 g_dwLinkExchangeCount;
extern u32 g_dwLinkLastExchangeTime;
extern u32 g_dwLinkPollFlags_candidate;

extern void DisableLinkSerial(void);
extern void ResetLinkSession(void);
extern void QueueLinkMessage(u32 type, u32 data);
extern void ProcessLinkMessages(void);
extern s32 RunLinkExchange(void);
extern s32 ExchangeLinkFrame_candidate(void);
