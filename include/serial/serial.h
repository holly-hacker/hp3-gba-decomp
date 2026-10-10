#pragma once

#include "types.h"

// Serial-link session block at 0x03005A24, written by the link init/teardown
// code and SerialTimer3Intr. See docs/memory-map/serial.md. Only the fields
// with a confirmed role are named.
typedef struct SerialPlayerState {
    s32 dwUnk_0x00;         // 0x00, set to -1 by link init and teardown
    u8 bUnk_0x04;           // 0x04, zeroed by link init and teardown
    s8 bPlayerId;           // 0x05, this GBA's multiplayer terminal ID: SIOCNT bits 4-5
                             // (0 = parent, 1-3 = child) sampled by SerialTimer3Intr
                             // while linked; -1 when no session
    u8 pad_06[0x02];        // -> 0x08
    u32 dwUnk_0x08;         // 0x08, zeroed by link init; set by sub_0803FA7C
} SerialPlayerState;

extern SerialPlayerState g_SerialPlayerState;

// Returns g_SerialPlayerState.bPlayerId; -1 when there is no link session.
extern s32 GetSerialPlayerId(void);

// A message exchanged once per round, 12 bytes. The parent's send word starts each round and the
// children answer; see docs/memory-map/serial.md.
typedef struct SerialMessage {
    u8 bType;         // 0 none, 1 idle, 2 keys, 3 RNG seed
    u8 bSeq;          // g_bSerialTick when queued
    u8 pad_02[2];
    u16 wData;        // keys held (type 2) or seed (type 3)
    u8 pad_06[6];
} SerialMessage;

#define SERIAL_MESSAGE_NONE 0
#define SERIAL_MESSAGE_IDLE 1
#define SERIAL_MESSAGE_KEYS 2
#define SERIAL_MESSAGE_SEED 3

// Bits of g_dwSerialFlags. Roles are inferred from the exchange loop.
#define SERIAL_FLAG_CLEARED_ON_RESET  0x0004
#define SERIAL_FLAG_TRANSFER_KICKED   0x0008  // set with SERIAL_FLAG_TRANSFER_STARTED
#define SERIAL_FLAG_TRANSFER_DONE     0x0010
#define SERIAL_FLAG_TRANSFER_STARTED  0x0020
#define SERIAL_FLAG_FRAME_READY       0x0040
#define SERIAL_FLAG_OWN_MESSAGE_SEEN  0x0080  // the local player's message was just received
#define SERIAL_FLAG_ROUND_COMPLETE    0x0200
#define SERIAL_FLAG_TIMED_OUT         0x8000
#define SERIAL_FLAG_CLOSED            0x80000

// Frames of waiting after which an exchange round gives up.
#define SERIAL_TIMEOUT_VBLANKS 600

extern volatile u32 g_dwSerialFlags;
extern SerialMessage g_aSerialRecvMessages[2];
extern SerialMessage g_SerialSendMessage;
extern u8 g_bSerialTick;
extern u8 g_abSerialLastRecvSeq[2];
extern u16 g_awSerialKeysReceived[2];
extern u8 g_bSerialSeedReceived;
extern u32 g_dwSerialMode;
extern u8 g_bSerialPeerCount;
extern u32 g_dwSerialExchangeCount;
extern u32 g_dwSerialLastExchangeTime;
extern u32 g_dwSerialPollFlags_candidate;

extern void DisableSerial(void);
extern void ResetSerialSession(void);
extern void QueueSerialMessage(u32 type, u32 data);
extern void ProcessSerialMessages(void);
extern s32 RunSerialExchange(void);
extern s32 ExchangeSerialFrame_candidate(void);
