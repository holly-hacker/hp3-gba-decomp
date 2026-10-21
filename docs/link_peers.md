# Untrusted link peers

What a modified game on the other end of a link cable can do.

## Card trade (GBA to GBA)

`ReceiveCardTradeOffer` takes the peer's offer from the low byte of its link
word and its ready flag from bit 8, with no validation, so any card value
0-255 can arrive.

- A hacked partner can grant any of the 51 Famous Wizard Cards on demand.
- An offer above `0x32` grants nothing, because `UpdateCardTrade` only
  increments valid cards, but the local player's own card is still
  decremented and the game saves. Showing such an offer draws dialog string
  `0x412 + card`, an unrelated string, and indexes past
  `g_aFolioCardThumbnails`, which can show garbage or hang.
- Every peer byte lands in a fixed one-byte field and only reaches
  comparisons and range-gated calls; no peer value becomes an address, a
  length or a count. There is no code-execution path.

## GameCube link (JOYBUS)

The GameCube's receive commands carry at most 255 halfwords (510 bytes)
into a 514-byte buffer, send lengths come from the game's own handlers, and
commands dispatch through the fixed `DispatchGameCubeLinkCommand`, whose
handlers only compare or ignore the received bytes. Nothing the GameCube
sends reaches a pointer, a length used for a copy, or a call target.
