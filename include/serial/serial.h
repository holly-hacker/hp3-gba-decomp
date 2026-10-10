#pragma once

#include "types.h"

// Number of multiplayer slots the link code's per-player setup loops cover. The per-player arrays
// (g_abSerialLastRecvSeq, g_awSerialKeysReceived and the SerialPlayerState buffers) hold only 2
// entries, so those loops also write the memory that follows them; see the BUG comments in
// InitSerial and BeginSerialSession.
#define SERIAL_MAX_PLAYERS 4

// Serial-link session block at 0x03005A24, written by the link init/teardown
// code and SerialTimer3Intr. See docs/memory-map/serial.md.
typedef struct SerialPlayerState {
    s32 dwUnk_0x00;         // 0x00, only ever written -1 and compared with -1
    u8 bPlayerCount;        // 0x04, g_dwSerialPlayerCount latched by SerialTimer3Intr before the handshake
    s8 bPlayerId;           // 0x05, this GBA's multiplayer terminal ID: SIOCNT bits 4-5
                             // (0 = parent, 1-3 = child) sampled by SerialTimer3Intr
                             // while linked; -1 when no session
    u8 pad_06[0x02];        // -> 0x08
    s32 (*pfnWaitCallback)(void); // 0x08, polled by SerialConnect while SIOCNT is not ready; 0 aborts
    u16 *pSendCurrent;      // 0x0C
    u16 *pSendNext;         // 0x10, receives each message SubmitSerialMessage checksums
    u16 awSendBuffers[2][6];  // 0x14
    volatile u16 *apRecvA[2];  // 0x2C, -> awRecvA
    volatile u16 *apRecvB[2];  // 0x34, -> awRecvB; copied out by SubmitSerialMessage
    volatile u16 awRecvA[2][6];  // 0x3C
    volatile u16 awRecvB[2][6];  // 0x54
} SerialPlayerState;        // 0x6C

extern SerialPlayerState g_SerialPlayerState;

// Returns g_SerialPlayerState.bPlayerId; -1 when there is no link session.
extern s32 GetSerialPlayerId(void);

// A message exchanged once per round, 12 bytes. The parent's send word starts each round and the
// children answer; see docs/memory-map/serial.md.
typedef struct SerialMessage {
    u8 bType;         // 0 none, 1 idle, 2 keys, 3 RNG seed
    u8 bSeq;          // g_bSerialTick when queued
    s16 wChecksum;    // set by SubmitSerialMessage, checked by VerifySerialMessageChecksum
    u16 wData;        // keys held (type 2) or seed (type 3)
    u8 pad_06[6];
} SerialMessage;

#define SERIAL_MESSAGE_NONE 0
#define SERIAL_MESSAGE_IDLE 1
#define SERIAL_MESSAGE_KEYS 2
#define SERIAL_MESSAGE_SEED 3

// Bits of g_SerialLink.dwFlags. Roles are inferred from the exchange loop.
#define SERIAL_FLAG_CLEARED_ON_RESET  0x0004  // also set when the 0xB0CA handshake completes
#define SERIAL_FLAG_TRANSFER_KICKED   0x0008  // set with SERIAL_FLAG_TRANSFER_STARTED
#define SERIAL_FLAG_TRANSFER_DONE     0x0010
#define SERIAL_FLAG_TRANSFER_STARTED  0x0020
#define SERIAL_FLAG_FRAME_READY       0x0040
#define SERIAL_FLAG_OWN_MESSAGE_SEEN  0x0080  // the local player's message was just received
#define SERIAL_FLAG_ROUND_COMPLETE    0x0200
#define SERIAL_FLAG_TIMED_OUT         0x8000
#define SERIAL_FLAG_PLAYER_ID_ERROR   0x10000  // terminal ID reached g_dwSerialMaxPlayers
#define SERIAL_FLAG_HANDSHAKE         0x20000  // 0xB0CA handshake in progress
#define SERIAL_FLAG_CLOSED            0x80000

// Frames of waiting after which an exchange round gives up.
#define SERIAL_TIMEOUT_VBLANKS 600

// Words a terminal sends during connection and the handshake that starts a game session.
#define SERIAL_WORD_CONNECT   0xFEED
#define SERIAL_WORD_HANDSHAKE 0xB0CA
// The parent's round words (see RunSerialExchange); a child sending one is an error.
#define SERIAL_WORD_ROUND_START 0xC0DE
#define SERIAL_WORD_ROUND_END   0xBEEF
#define SERIAL_WORD_BABE        0xBABE
#define SERIAL_WORD_DEAD        0xDEAD
// Words 0xA000-0xAFFF carry game data to the receive callback.
#define SERIAL_WORD_DATA_MASK 0xF000
#define SERIAL_WORD_DATA      0xA000

// Reload value of the Timer 3 serial pump.
#define SERIAL_TIMER_RELOAD 0xC352

// g_dwSerialPlayerCount after a terminal sent one of the parent's round words outside a round.
#define SERIAL_PLAYER_COUNT_ERROR 5

typedef struct SerialLink {
    volatile u32 dwFlags;                          // SERIAL_FLAG_*
    void (*pfnReceive)(u32 word, u32 playerId);    // called for each SERIAL_WORD_DATA word
    u32 (*pfnGetSendWord)(void);                   // supplies the send word before the handshake
} SerialLink;

extern SerialLink g_SerialLink;
extern SerialMessage g_aSerialRecvMessages[2];
extern SerialMessage g_SerialSendMessage;
extern u8 g_bSerialTick;
extern u8 g_abSerialLastRecvSeq[2];
extern u8 g_bSerialUnk03005A10;
extern u8 g_bSerialChecksumRollByte;
extern u16 g_awSerialKeysReceived[2];
extern u8 g_bSerialSeedReceived;
extern u32 g_dwSerialMode;
extern u32 g_dwSerialPlayerCount;
extern u8 g_bSerialPeerCount;
extern u8 g_bSerialLocalPlayerId;
extern u8 g_bSerialPlayerMask;
extern u32 g_dwSerialExchangeCount;
extern u32 g_dwSerialChecksumExchangeCount;
extern u32 g_dwSerialLastExchangeTime;
extern u32 g_dwSerialPollFlags_candidate;
extern u32 g_dwSerialMaxPlayers;
extern u32 g_dwSerialUnk03005AA4;
extern u32 g_dwSerialUnk03005AA8;
extern u32 g_dwSerialUnk03005AAC;
extern u32 g_dwSerialUnk03005AB0;
extern u32 g_dwSerialConnectRetries;
extern u32 g_dwSerialUnk03005AB8;
extern u32 g_dwSerialUnk03005ABC;

extern void DisableSerial(void);
extern void ResetSerialSession(void);
extern void QueueSerialMessage(u32 type, u32 data);
extern void ProcessSerialMessages(void);
extern s32 RunSerialExchange(void);
extern s32 ExchangeSerialFrame_candidate(void);
extern void SetSerialCallbacks(void (*pfnReceive)(u32 word, u32 playerId), u32 (*pfnGetSendWord)(void));
extern s32 InitSerialSession(void);
extern s32 BeginSerialSession(void);
extern u32 GetSerialMode(void);
extern void SetSerialMode(u32 mode);
extern void TickSerialCommIfActive_candidate(void);
extern s16 GetMt19937LastRollByte(void);
extern s16 GetSerialChecksumRollByte(void);
extern void LatchSerialChecksumRollByte(void);
extern void ClearSerialChecksumRollBytes(void);
extern void StartSerialGameSession(void);
extern u32 StartSerialConnection(u32 unused);
extern u32 TickSerialSession(u32 unused0, u32 unused1);
extern u32 IsSerialReady(void);
extern void InitSerial(void);
extern u32 SerialConnect(u32 maxPlayers);
extern u32 UpdateSerialConnection(void);
extern void SubmitSerialMessage(SerialMessage *pMessage, SerialMessage *pRecvOut);
extern void SerialTimer3Intr(void);
extern void WaitForSerialHandshake(void);
extern void CloseSerialSession(void);
extern void SetSerialWaitCallback(s32 (*pfnWaitCallback)(void));
extern u32 GetSerialPlayerCount(void);
extern void sub_0803FB34(u32 value);
extern u32 sub_0803FB40(void);
extern void SetSerialSendKeys(u32 enable);
extern u32 IsSerialUp(void);
extern u32 IsSerialFrameReady(void);
extern s32 SerialPhase2(void);
extern void MarkSerialSessionClosed(void);
extern u32 VerifySerialMessageChecksum(SerialMessage *pMessage);
extern s32 CountSerialConnectRetries(void);
