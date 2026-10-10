# GameCube link (JOYBUS slave)

The owl-care screen's Upload action leads to the Connectivity screen's
"Nintendo GameCube™ Link" entry (string `0x650`), game mode `0x41`
(`InitializeGameCubeLink`/`UpdateGameCubeLink`/`ExitGameCubeLink`,
`0x08038290`/`0x08038320`/`0x0803860C`). It runs owl races against the
GameCube version of the game over a GCN-GBA cable (string `0x91E`). All
addresses are US-ROM unless noted. See [`../README.md`](../README.md) for
the confidence key.

This covers the GBA-side slave only. The GBA-GBA multiplayer side lives in
[`serial.md`](serial.md).

## Transport (PROVEN)

The transport is matched C in `src/gamecube/` (block `0x080216D4`-`0x08021C08`);
`include/gamecube.h` declares the state, constants and functions.

- `SetupJoybusHardware` (`0x08021938`) masks `IME`, steps `RCNT` through
  `0x8000` (skipped while `bInitialSetup` is set) to `0xC000`, clears
  `JOYSTAT`/`JOY_TRANS`, writes `0x47` to `JOYCNT` and acknowledges the serial
  interrupt in `IF`, then clears the session flags.
  `TeardownJoybusHardware` (`0x08021B28`, called from `ExitGameCubeLink`)
  returns `RCNT` to `0x8000`, disables the serial interrupt, restores
  interrupt slot 0 (`ResetIntrFunc`), frees both buffers and clears the state.
- `InitJoybusSession` installs `HandleJoybusInterrupt` (`0x080216D4`) in
  interrupt slot 0. It reads `JOYCNT` and dispatches on its flags: bit 1
  (receive) passes `JOY_RECV` to `HandleJoybusCommandWord` (`0x08021748`),
  bit 2 (send) calls `HandleJoybusTransmit` (`0x080218C0`), bit 0 (JOY reset)
  calls `HandleJoybusReset` (`0x08021BD8`). A rejected word clears `JOYSTAT`
  and drops the connection with state 6. It then acknowledges the `JOYCNT`
  flags and zeroes `bTimeoutCounter`.
- `HandleJoybusReset` loads this cartridge's header game code (`0x080000AC`)
  into `JOY_TRANS`, sets `JOYSTAT` to `0x20` and restarts the handshake.
- `JoybusNoOp` is an empty function between `TransmitJoybusWord` and
  `InitJoybusSession`; no caller was found.

## Session (PROVEN)

`InitJoybusSession` (`0x08021A58`, called with `DispatchGameCubeLinkCommand`
and the bounds `0x43`/`0x83`) clears the state, allocates the two `0x202`-byte
buffers, runs `SetupJoybusHardware`, and stores the expected peer game code
"GAZE" (string at `0x08060620`).
`TickJoybusSession` (`0x08021AF4`) is the per-frame driver: it runs
`TickJoybusTimeout` (`0x08021B98`), which resets the hardware with
error 3 once more than 10 frames pass without a JOY interrupt, and returns the
state, reporting each completed transfer (state 4 or 5) once before going back
to state 1. State 6 stays until the next JOY reset.

`g_JoybusLinkState` at `0x03003238` (`JoybusLinkState`, 0x38 bytes; the
session code clears all of it):

| Offset | Field | Role |
|---|---|---|
| +0x0 | `bState` | 0 idle, 1 connected, 2 receiving, 3 sending, 4 received, 5 sent, 6 error |
| +0x1 | `bError` | code of the last rejected word (below) |
| +0x2 | `bLinkProgress` | set to 1/2 by link commands `0x41`/`0x82` |
| +0x3 | `bConnected` | set when the peer's game code matched |
| +0x4 | `bHandshake` | 1 after a JOY reset, 2 once the GameCube read the game code |
| +0x5 | `bTimeoutCounter` | frames since the last JOY interrupt |
| +0x6 | `bTimedOut` | set by a timeout reset, cleared on connect |
| +0x7 | `bCommand` | command byte of the transfer in progress |
| +0x9 | `bInitialSetup` | set while `InitJoybusSession` runs the hardware setup |
| +0xC | `dwGameCode` | this cartridge's game code, sent after each JOY reset |
| +0x10 | `dwPeerGameCode` | the game code the GameCube sent |
| +0x14 | `dwExpectedPeerGameCode` | "GAZE" |
| +0x18/+0x1A | `wRecvCommandMax`/`wSendCommandMax` | highest accepted receive/send command |
| +0x1C/+0x1E | `wRecvRemaining`/`wSendRemaining` | halfwords left in the transfer |
| +0x20/+0x22 | `wRecvIndex`/`wSendIndex` | buffer cursors (halfword units) |
| +0x24/+0x28 | `pRecvBuffer`/`pSendBuffer` | the two `0x202`-byte heap buffers |
| +0x2C | `pfnCommand` | `DispatchGameCubeLinkCommand` |
| +0x30/+0x34 | `wResultTextId`/`wStatusTextId` | the link mode's last drawn text ids |
| +0x32 | `wResultTextHoldFrames` | frames before a new result text may replace the current one (ignored for events 2/3); from the `0x08069A8C` table |
| +0x36 | `wStatusTextFrames` | countdown that clears the status box and `bLinkProgress`; from the `0x08069AA8` table, whose durations are all 0 |

The fields at +0x0-+0x9 and +0x1C-+0x22 are volatile (every store is preceded
by a load in the ROM).

`bError` codes follow the string table at `0x08FAA830`, whose entries name
them in order: 0 None, 1 Game Code Send, 2 Game Code Recv, 3 Timeout,
4 Invalid Command, 5 Invalid Mode, 6 Recv Missing Packet, 7 Recv CRC,
8 Recv Overrun, 9 Send Overrun. No reader of the table was found.

## Wire protocol (PROVEN shapes, UNCONFIRMED intent)

Each GameCube word is dispatched on its low byte:

- Before `bConnected` is set, the only accepted word is the GameCube's game
  code, after the GameCube read this cartridge's code (`bHandshake` 2).
- `0x40` up to `wRecvCommandMax`: receive command. Byte 1 becomes
  `wRecvRemaining`; at most 255 halfwords (510 bytes) against the 514-byte
  buffer, so the length can never overflow it. Excess words past a zero
  count take the error path without writing. The GBA answers with the count
  and its checksum; a zero count calls the callback at once.
- `0x60`: data word of a receive command. Bits 8-23 are the payload
  halfword, bits 24-31 its checksum; `HandleJoybusDataWord` (`0x080219A8`)
  verifies it through `ComputeJoybusChecksum` and appends it at
  `pRecvBuffer[wRecvIndex]`. The last one calls the callback with the byte
  count.
- `0x80` up to `wSendCommandMax`: send command. The callback fills the send
  buffer and its byte count; `HandleJoybusTransmit`/`TransmitJoybusWord`
  (`0x08021A00`) then emit one `0xA0` word per halfword plus checksum.

`ComputeJoybusChecksum` (`0x0801D4A8`) folds a halfword to a checksum byte,
CRC-flavored (constants `0xCC`/`0xCD`, 8+7 shift-xor rounds). Its only
callers are the five JOYBUS functions above.

## Link commands (PROVEN behavior)

`DispatchGameCubeLinkCommand` (`0x080386F0`, returns consumed/not) is the
session's `(command, pLength, pBuffer)` callback; it switches on the command
byte and passes `(pLength, pBuffer)` to the handler. For receive commands
`pBuffer` holds the received data; for send commands the handler fills it and
`*pLength`:

| Byte | Handler | Behavior |
|---|---|---|
| `0x40` | `VerifyGameCubeHandshakeBytes` (`0x08038760`) | scans the scratch buffer for the `0x61`-based handshake sequence, bounded `0x18` |
| `0x41` | `FlagGameCubeHeaderReceived` (`0x08038784`) | if bit 0 of `g_saveManager` +0xD is clear, sets it and `bLinkProgress` = 1 |
| `0x42` | `AcknowledgeGameCubeCommand` (`0x080387AC`) | no-op acknowledge (`bx lr`) |
| `0x80` | `PadGameCubeReceiveBuffer` (`0x080387B0`) | fills 26 bytes with `0x5A`, length `0x1A` |
| `0x81` | `StageGameCubeStatusByte` (`0x080387CC`) | serves one status byte, length 1 |
| `0x82` | `StageGameCubeStateBytes` (`0x080385B8`) | serves 7 bytes of `g_saveStateBlock` (`+0x9C`-`+0xA2`) and a zero, length 8; sets `bLinkProgress` = 2 |

Every length is a small constant or the count-gated `wRecvRemaining`; the
indirect call targets the ROM-fixed `pfnCommand`,
never GameCube-influenced data. The slave was assessed for
peer-driven code execution alongside the save format and the GBA link
layer: all three are bounded end to end, with no attacker-reachable
pointer, length-into-code, or unclamped callback dispatch.

## Open questions

- Exact protocol meaning of the `0x40`/`0x41` handshake bytes and the
  `wRecvCommandMax`/`wSendCommandMax` contract with the GameCube title.
- Readers of `dwPeerGameCode` and the `0x08FAA830` error-string table.
- The exact checksum polynomial behind `ComputeJoybusChecksum`.
