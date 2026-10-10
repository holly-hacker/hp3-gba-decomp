# Link cable and card trade

Two GBAs trading Famous Wizard Cards (game mode `0x15`, reached from the
pause menu's Connectivity submenu). All addresses are US-ROM unless noted.
See [`../README.md`](../README.md) for the confidence key. The GameCube
(JOYBUS slave) side is documented separately in
[`gcn-link.md`](gcn-link.md).

## Link layer (PROVEN)

- Transport is GBA multiplayer mode (`SIOCNT = 0x2000`, set by
  `InitSerial`, `0x0803F0A8`), `SIOMLT_SEND` at `0x0400012A`, slave
  words at `0x04000130+`.
- Everything is interrupt-pumped by `SerialTimer3Intr`: the parent from
  Timer 3 (`TM3CNT_L = 0xC352`), a child from the serial IRQ. No BIOS swap
  calls.
- `SerialConnect` (`0x0803F298`) busy-waits the `SIOCNT` start/error bits,
  buddy-checks `0xFFFF`, then exchanges magic words (`0xFEED` out, expects
  `0xFEED`/`0xB0CA` back). Timeout dies via a vblank-counter delta in the
  per-tick pump.
- Session state, ISR-owned: `SerialTimer3Intr` clears
  `g_dwSerialPlayerCount` (`0x03005A1C`) and `g_bSerialPlayerMask`
  (`0x03005A22`) each interrupt, then counts slots 1 and 0 whose `SIOMULTI`
  word is `0xFEED`, `0xB0CA` or `0xAxxx` (data, passed to the receive
  callback) and sets one mask bit per slot. A round word (`0xBEEF`,
  `0xC0DE`, `0xBABE`, `0xDEAD`) outside a round sets the count to 5.
  `IsSerialUp` (`0x0803FB78`) is exactly "count == 2 and mask == 3" — a
  two-player session ready.
- Handshake (`SERIAL_FLAG_HANDSHAKE`): a received `0xB0CA` sets the flag. The
  parent finishes once every child echoes `0xB0CA`; a child echoes the
  parent's word. Finishing installs `SerialPhase2` as the wait callback,
  sets `SERIAL_FLAG_CLEARED_ON_RESET` and runs `StartSerialGameSession`,
  which sets `SerialSessionActive`, latches the peer count and local ID, and
  has the parent queue a random RNG-seed message (a child queues idle).
- `g_SerialPlayerState` (`0x03005A24`, `include/serial/serial.h`) holds the session's
  local terminal ID at `+5` (`bPlayerId`, `s8`): `SerialTimer3Intr` stores
  `(SIOCNT >> 4) & 3` there while `g_dwSerialPlayerCount != 0` (0 = parent, 1-3 =
  child), and init/teardown reset it to `0xFF` (-1, no session).
  `GetSerialPlayerId` (`0x0803FA94`) returns it; `UpdateKeyInput` uses it to
  pick the local player's key slot. A value above 1 tears the session down.
- Per-frame exchange (STRUCTURAL MATCH, `TickSerialCommIfActive_candidate`): while
  `g_dwSerialMode == 1`, `ExchangeSerialFrame_candidate` queues an idle (type 1) or key (type 2)
  `SerialMessage` with `QueueSerialMessage`, then `RunSerialExchange` busy-waits on
  `g_SerialLink.dwFlags` bits set by the serial interrupt (600 vblanks maximum), kicks the parent's
  send words (`0xC0DE` to start, `0xBEEF` to finish a round) and runs `ProcessSerialMessages`
  to fill `g_awSerialKeysReceived` (and apply a type 3 RNG seed). A timeout clears
  `SerialSessionActive` and runs `ResetSerialSession`. Message types and `SERIAL_FLAG_*` roles are in
  `include/serial/serial.h`.
- A 9-entry error vocabulary (`Error: Send Overrun`, `Recv CRC`, `Timeout`,
  `Game Code Recv/Send`, …) sits at `0x08060554` but is currently
  unreferenced — dead debug strings, reached by computed index if at all.
  The game-code check means both ends must run the same title.

## Trade session (PROVEN)

`CardTradeState` at `0x03005568` (12 bytes, Ghidra type only so far):

| Offset | Field | Role |
|---|---|---|
| +0 | `dwStatus` (u32) | last link result, 0/1 (edge-detected) |
| +4 | `bConfirmed` | set on confirm, cleared on reset |
| +5/+6 | `bLocalOffer`/`bLocalLocked` | local card, then latched copy |
| +7/+11 | `bUnk07`/`bUnk0B` | always `0x33`, never read (UNCONFIRMED) |
| +8/+9/+10 | `bPeerReady`/`bPeerOffer`/`bPeerLocked` | peer side, same shape |

Card values are 0–50 (51 Famous Wizard Cards); `0x33` (51) means "no
card". The mode's state machine (states 0–8) lives in the shared
`g_dwGameModeState` word (`0x03003F04`, reused by every mode), with
`g_dwGameModeTimer` (`0x03003F0C`) as its countdown:

- 0–1: wait for link (`IsSerialUp`), error box otherwise.
- 2: pick a card (`ConfirmCardTradeOffer` locks offer→locked on link-up;
  `CancelCardTradeOffer` clears back to state 4).
- 3–4: peer sync. 5: compare — peer offer differing from the latched copy
  re-announces; matching sets up the swap.
- 6: validate (both latched cards `≤0x32`), render both slots, grant and
  remove via the folio count routines.
- 7–8: commit countdown, copy the locked cards out, re-save.
- `ExitCardTrade` (`0x0803ABBC`) is teardown only (the old
  `DrawCardTrade` seed name for this address was wrong and is fixed).

`ShowCardTradeLinkStatus` redraws only on transitions (up∧was-down →
plain box, down∧was-up → "Waiting for connection.", text `0x653`).

Persistence: the received card increments the Folio Universitas counts
(51 nibbles) and the game re-saves with a recomputed checksum
(`SyncSaveHeaderIfDirty` + `SaveGameToSlot`) — no checksum bypass exists
on this path.

## Hostile peer (PROVEN where stated)

- The peer's 16-bit word splits with no validation: low byte →
  `bPeerOffer` (any 0–255), bit 8 → `bPeerReady`
  (`ReceiveCardTradeOffer`, `0x0803ABF8`, registered as the link receive
  callback at init). STRUCTURAL MATCH on the callback invocation itself
  (taken by address, single static pointer).
- Out-of-range offers (52+) grant nothing — the folio increment is gated
  at `≤0x32` — but the victim's own valid card is still decremented, and
  the trade completes and saves. Display of such values reads past the
  string table (garbage text, possible hang).
- No arbitrary code execution avenue: every peer byte lands in a fixed
  single-byte slot and only reaches comparisons and gated calls. The
  handshake is compare-only, and no attacker-controlled address, length,
  or count reaches any copy.
- Practical upshot: a hacked partner grants any of the 51 cards on demand
  (a category-rules question, not a tech exploit), and can grief by
  offering invalid cards that cost the victim theirs.

## Open questions

- What, if anything, reads `bUnk07`/`bUnk0B`.
- The `+0x14` word between `g_dwGameModeState` and `g_dwGameModeTimer`
  (blocks extending `GameModeStackContext_candidate` over these words).
- The role of `g_SerialPlayerState.dwUnk_0x00`. Every access is a store of
  -1 (init, reset, handshake completion) or a compare with -1 (the parent's
  transfer kick and the send-buffer swap), so both gates always pass.
  `pSendCurrent` is likewise never read outside the swap, and nothing fills
  `awRecvB` after init; the transfer itself runs through the `g_SerialLink`
  callbacks.
- `SubmitSerialMessage` (checksummed send staging),
  `VerifySerialMessageChecksum` and the `g_dwSerialUnk03005AB8` accessors
  `sub_0803FB34`/`sub_0803FB40` have no callers found.
