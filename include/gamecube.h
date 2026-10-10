#pragma once

#include "types.h"

// JOYBUS transport for the GameCube link; see docs/memory-map/gcn-link.md.

// Handles one command byte (0x40-0x7F received from the GameCube, 0x80 and up sent to it).
// pLength is the byte count received into pBuffer, or receives the byte count to send from it.
typedef u32 (*JoybusCommandCallback)(u32 command, u16 *pLength, u16 *pBuffer);

// Values of JoybusLinkState.bState, returned by TickJoybusSession.
#define JOYBUS_STATE_IDLE       0  // after a JOY reset
#define JOYBUS_STATE_CONNECTED  1  // game codes exchanged, no transfer in progress
#define JOYBUS_STATE_RECEIVING  2
#define JOYBUS_STATE_SENDING    3
#define JOYBUS_STATE_RECEIVED   4  // a receive command completed; reported once
#define JOYBUS_STATE_SENT       5  // a send command completed; reported once
#define JOYBUS_STATE_ERROR      6  // a word was rejected; kept until the next JOY reset

// Values of JoybusLinkState.bError, named after the string table at 0x08FAA830.
#define JOYBUS_ERROR_NONE                0
#define JOYBUS_ERROR_GAME_CODE_SEND      1
#define JOYBUS_ERROR_GAME_CODE_RECV      2
#define JOYBUS_ERROR_TIMEOUT             3
#define JOYBUS_ERROR_INVALID_COMMAND     4
#define JOYBUS_ERROR_INVALID_MODE        5
#define JOYBUS_ERROR_RECV_MISSING_PACKET 6
#define JOYBUS_ERROR_RECV_CRC            7
#define JOYBUS_ERROR_RECV_OVERRUN        8
#define JOYBUS_ERROR_SEND_OVERRUN        9

// Low byte of every word that carries one received data halfword.
#define JOYBUS_WORD_DATA 0x60
// Low byte of every word that carries one sent data halfword.
#define JOYBUS_WORD_SEND_DATA 0xA0

// Command bytes up to 0x3F are not commands; 0x40-0x7F receive, 0x80 and up send.
#define JOYBUS_RECV_COMMAND_MIN 0x40
#define JOYBUS_SEND_COMMAND_MIN 0x80

// Halfword capacity (plus one) of each transfer buffer.
#define JOYBUS_BUFFER_SIZE 0x202

// Values of JoybusLinkState.bHandshake.
#define JOYBUS_HANDSHAKE_NONE       0
#define JOYBUS_HANDSHAKE_RESET      1  // JOY reset seen; own game code loaded for sending
#define JOYBUS_HANDSHAKE_CODE_SENT  2  // the GameCube read the game code

// Link state at 0x03003238. The GameCube link mode keeps its text ids in the last 8 bytes,
// which the session setup and teardown clear with the rest.
typedef struct JoybusLinkState {
    volatile u8 bState;           // 0x00: JOYBUS_STATE_*
    volatile u8 bError;           // 0x01: JOYBUS_ERROR_* of the last rejected word
    volatile u8 bLinkProgress;    // 0x02: set by the link commands (1 header, 2 state bytes sent)
    volatile u8 bConnected;       // 0x03: set once the GameCube's game code matched
    volatile u8 bHandshake;       // 0x04: JOYBUS_HANDSHAKE_*
    volatile u8 bTimeoutCounter;  // 0x05: frames since the last JOY interrupt
    volatile u8 bTimedOut;        // 0x06
    volatile u8 bCommand;         // 0x07: command byte of the transfer in progress, 0 for none
    u8 pad_08;
    volatile u8 bInitialSetup;    // 0x09: set while InitJoybusSession runs SetupJoybusHardware
    u8 pad_0A[2];
    u32 dwGameCode;               // 0x0C: this cartridge's header game code, sent on every JOY reset
    u32 dwPeerGameCode;           // 0x10: the game code the GameCube sent
    u32 dwExpectedPeerGameCode;   // 0x14: "GAZE"
    u16 wRecvCommandMax;          // 0x18: highest receive command byte accepted
    u16 wSendCommandMax;          // 0x1A: highest send command byte accepted
    volatile u16 wRecvRemaining;  // 0x1C: halfwords still expected
    volatile u16 wSendRemaining;  // 0x1E: halfwords still to send
    volatile u16 wRecvIndex;      // 0x20
    volatile u16 wSendIndex;      // 0x22
    u16 *pRecvBuffer;             // 0x24: JOYBUS_BUFFER_SIZE bytes
    u16 *pSendBuffer;             // 0x28: JOYBUS_BUFFER_SIZE bytes
    JoybusCommandCallback pfnCommand;  // 0x2C
    u16 wResultTextId;            // 0x30: dialog text last drawn as the link result; 0xACF = none yet
    u16 wResultTextHoldFrames;    // 0x32: frames before another result text may replace it
    u16 wStatusTextId;            // 0x34: dialog text last drawn in the status box; 0xACF = none yet
    u16 wStatusTextFrames;        // 0x36: frames until the status text is cleared; 0 = kept
} JoybusLinkState;  // 0x38

extern JoybusLinkState g_JoybusLinkState;

// This cartridge's header game code (0x080000AC), read as one word.
extern const u32 g_dwRomHeaderGameCode;

extern u8 ComputeJoybusChecksum(u16 value);
extern void HandleJoybusInterrupt(void);
extern u32 HandleJoybusCommandWord(u32 word);
extern u32 HandleJoybusTransmit(void);
extern void SetupJoybusHardware(void);
extern u32 HandleJoybusDataWord(u32 word);
extern u32 TransmitJoybusWord(void);
extern void JoybusNoOp(void);
extern void InitJoybusSession(JoybusCommandCallback pfnCommand, u32 recvCommandMax, u32 sendCommandMax);
extern u32 TickJoybusSession(void);
extern void TeardownJoybusHardware(void);
extern u32 TickJoybusTimeout(void);
extern void HandleJoybusReset(void);
