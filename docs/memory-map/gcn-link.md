# GameCube link (JOYBUS slave)

The owl-care screen's Upload action leads to the Connectivity screen's
"Nintendo GameCube™ Link" entry (string `0x650`), game mode `0x41`
(`InitializeGameCubeLink`/`UpdateGameCubeLink`/`ExitGameCubeLink`,
`0x08038290`/`0x08038320`/`0x0803860C`). It runs owl races against the
GameCube version of the game over a GCN-GBA cable (string `0x91E`). All
addresses are US-ROM unless noted. See [`../README.md`](../README.md) for
the confidence key.

This covers the GBA-side slave only. The GBA-GBA multiplayer side lives in
[`link.md`](link.md).

## Transport (PROVEN)

- `SetupJoybusHardware` (`0x08021938`) fences `IE`, zeroes the SIO control
  halfword, raises `RCNT` (`0x04000134`) `0x8000` then `0xC000`, zeroes the
  JOY registers, writes `0x47` to `0x04000140` and `0x80` to `0x04000202`,
  clears the session state bytes, and restores `IE`.
  `TeardownJoybusHardware` (`0x08021B28`, called from `ExitGameCubeLink`)
  is the mirror (restores the saved `IE`, memsets the state).
- Live JOY registers: `0x04000140` status polled by the vblank handler,
  `0x04000150` receive word, `0x04000154` transmit word, `0x04000158`
  error/clear. Ghidra pools confirm each address against raw bytes.
- The vblank handler dispatches three bit-keyed handlers off the status
  halfword (the poller itself is inline in `vblankHandler`, not separately
  named): bit 1 reads the receive word and calls `HandleJoybusCommandWord`
  (`0x08021748`, returns consumed/not); bit 2 calls `HandleJoybusTransmit`
  (`0x080218C0`); bit 0 calls `LatchJoybusTransferLength` (`0x08021BD8`).
  `HandleJoybusCommandWord`'s body runs to `0x080218BD` -- Ghidra splits
  the tail at `0x08021878` into a second function with no external xrefs,
  which is the same function, not a separate one.

## Session (PROVEN)

`InitJoybusSession` (`0x08021A58`, called once with a ROM callback plus two
bound bytes, `0x43`/`0x83` for this menu) allocates two `0x202`-byte heap
buffers (receive → state `+0x24`, send → `+0x28`), memsets the state,
stores the callback at `+0x2C`, and runs `SetupJoybusHardware`.
`TickJoybusSession` (`0x08021AF4`) is the per-frame driver; past a timeout
counter it re-runs the hardware setup via `MaybeResetJoybusHardware`
(`0x08021B98`).

`JoybusLinkState` at `0x03003238` (Ghidra type + global, 0xA3 bytes):

| Offset | Field | Role |
|---|---|---|
| +0x0 | `bState` | handler state machine |
| +0x1 | `bError` | sticky error code |
| +0x5 | `bTimeoutCounter` | reset watchdog, trips past `0xA` |
| +0x7 | `bLastCmd` | last received low byte |
| +0x9 | `bActive` | session live flag |
| +0xC | `dwStagedLen` | latched transfer length |
| +0x18/+0x1A | `wBound1`/`wBound2` | command-byte range bounds (`0x43`/`0x83`) |
| +0x1C | `wRxRemaining` | receive halfwords still expected |
| +0x1E | `wTxRemaining` | transmit halfwords still to send |
| +0x20/+0x22 | `wRxIndex`/`wTxIndex` | buffer cursors (halfword units) |
| +0x24/+0x28 | `pRxBuf`/`pTxBuf` | the two `0x202` heap buffers |
| +0x2C | `pCmdCallback` | ROM command callback (`0x080386F1`) |
| +0x9C-0xA2 | `bStatus0`-`bStatus6` | status bytes the `0x82` command serves |

## Wire protocol (PROVEN shapes, UNCONFIRMED intent)

Each GameCube word is dispatched on its low byte:

- `<= 0x3F` (and within `wBound1`): session/length word. Byte 2 becomes
  `wRxRemaining`; at most 255 halfwords (510 bytes) against the 514-byte
  buffer, so the length can never overflow it. Excess words past a zero
  count take the error path without writing.
- `0x60`: data word. Bits 8-15 are the payload byte, bits 24-31 its
  checksum; `HandleJoybusDataWord` (`0x080219A8`) verifies the byte through
  `ComputeJoybusChecksum` and appends it at `pRxBuf + wRxIndex*2`.
- `0x80` and up (within `wBound2`): send requests, served by
  `HandleJoybusTransmit`/`TransmitJoybusWord` (`0x08021A00`), which emit
  `0xA0`-class words built from the send buffer halfwords plus checksum.

`ComputeJoybusChecksum` (`0x0801D4A8`) folds a halfword to a checksum byte,
CRC-flavored (constants `0xCC`/`0xCD`, 8+7 shift-xor rounds). Its only
callers are the five JOYBUS functions above.

## Link commands (PROVEN behavior)

`DispatchGameCubeLinkCommand` (`0x080386F0`, returns consumed/not) switches
on the received low byte with `(spBuf, recvBuf)` arguments:

| Byte | Handler | Behavior |
|---|---|---|
| `0x40` | `VerifyGameCubeHandshakeBytes` (`0x08038760`) | scans the scratch buffer for the `0x61`-based handshake sequence, bounded `0x18` |
| `0x41` | `FlagGameCubeHeaderReceived` (`0x08038784`) | sets a header bit and a status byte |
| `0x42` | `AcknowledgeGameCubeCommand` (`0x080387AC`) | no-op acknowledge (`bx lr`) |
| `0x80` | `PadGameCubeReceiveBuffer` (`0x080387B0`) | fills 26 receive bytes with `0x5A`, reports length `0x1A` |
| `0x81` | `StageGameCubeStatusByte` (`0x080387CC`) | serves one status byte, length 1 |
| `0x82` | `StageGameCubeStateBytes` (`0x080385B8`) | serves 7 state bytes (`+0x9C`-`+0xA2`), length 8 |

Every length is a small constant or the count-gated `wRxRemaining`; the
indirect call in the receive path targets the ROM-fixed `pCmdCallback`,
never GameCube-influenced data. The slave was assessed for
peer-driven code execution alongside the save format and the GBA link
layer: all three are bounded end to end, with no attacker-reachable
pointer, length-into-code, or unclamped callback dispatch.

## Open questions

- Exact protocol meaning of the `0x40`/`0x41` handshake bytes and the
  `wBound1`/`wBound2` contract with the GameCube title.
- Readers/writers of state `+0x30`/`+0x34` and the `+0x10`/`+0x14` words.
- The exact checksum polynomial behind `ComputeJoybusChecksum`.
