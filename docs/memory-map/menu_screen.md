# Menu screens — memory map

See [`../README.md`](../README.md) for the confidence-key legend. Addresses are US;
JP is 4 bytes lower for these functions. The matched C is authoritative:
`include/menu/main_menu.h` and the callers under `src/gamemode/modes/`.

## Setup functions — STRUCTURAL MATCH (read from the assembly; the callers are matched C)

The shared frame of the options, save, minigame-select and card-combo screens
(and others) is built by a small family of functions.

| Function | Address | Behavior |
|---|---|---|
| `InitializeMenuScreen` | `0x0801DF6C` | `(titleStringId, cursorKind, hasPanel, pOverlayGraphic, overlayX, overlayY)`: `LoadMenuScreenFrame`, then `BeginMenuScreen`. |
| `LoadMenuScreenFrame` | `0x0801DF90` | Resets the display, loads the palette embedded in `gMenuBg3Graphic` (rows 0-15) and the palette-less frame blob `0x08DC1EFC` onto BG0, then `LoadMenuScreenOverlay`. |
| `LoadMenuScreenOverlay` | `0x0801E004` | If a graphic is given, loads it onto BG1 at tile offset `0x70` (palette bank 0). |
| `BeginMenuScreen` | `0x0801E05C` | Clears BG2, `DrawMenuScreenTitle`, spawns the cursor object into `g_pMenuCursorObject` (`cursorKind` 9 spawns none), and optionally creates the panel from the data at `0x08DA08BE`. |
| `ExitMenuScreen` | `0x0801E0DC` | Releases the cursor object, the panel and cached resources. |
| `DrawMenuScreenTitle` | `0x0801E118` | Clears a text rectangle on BG2 and draws the string, except for string id `0xACF`. |

`BuildListMenu` and `InitializeItemsItemSelect` call `BeginMenuScreen` without
`InitializeMenuScreen`; `sub_08031FB8` calls `LoadMenuScreenFrame` directly.

## Palette-less graphic blobs

Blobs without an embedded palette (flags `0x78`, `0xF8`) draw with a palette
that is already loaded; see [`../formats/graphic_blob.md`](../formats/graphic_blob.md).

- `0x08DC1EFC` (frame, **PROVEN**): `LoadMenuScreenFrame` loads
  `gMenuBg3Graphic`'s palette immediately before it.
- `gMenuScreenGraphic` and the blob at `0x08DA0AC0` are overlays passed to
  `InitializeMenuScreen` (Options; card combo description), loaded after that
  frame (**UNCONFIRMED**: that they use the same palette).
- The Patronus frames 1-5 (`g_apPatronusGraphics`, `0x08FAAEF8`) are cycled by
  the cutscene update; only entry 0 carries a palette (**UNCONFIRMED**: that
  they use it).
- The four 8x10 blobs of the minigame select menu (table at `0x08066064`, x
  positions at `0x08066074`) are loaded onto BG3 at tile offset `0x60` by
  `HandleMinigameMenuSelection`; the palette source is not traced.
