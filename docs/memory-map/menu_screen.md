# Menu screens — memory map

See [`../README.md`](../README.md) for the confidence-key legend. Addresses are US;
JP is 4 bytes lower for these functions. The matched C in `src/default_menu/` and
`include/default_menu.h` is authoritative.

## Default menu block

The shared frame of the options, save, minigame-select and card-combo screens
(and others) is built by the functions of the "Default menu" code block
(**UNCONFIRMED**: the module name, chosen to sort between "Decompress" and
"Dementor Minigame").

| Function | Address | Behavior |
|---|---|---|
| `InitializeMenuScreen` | `0x0801DF6C` | `LoadMenuScreenFrame`, then `BeginMenuScreen`. |
| `LoadMenuScreenFrame` | `0x0801DF90` | Resets the display, loads the palette embedded in `gMenuBg3Graphic` (rows 0-15) and the palette-less frame blob `gMenuScreenFrameGraphic` onto BG0, then `LoadMenuScreenOverlay`. |
| `LoadMenuScreenOverlay` | `0x0801E004` | If a graphic is given, fills BG1 with tile `0x6F` and loads the graphic there at tile offset `0x70` (palette bank 0). |
| `ClearMenuScreenOverlay` | `0x0801E04C` | Fills BG1 with tile `0x6F`. |
| `BeginMenuScreen` | `0x0801E05C` | Clears BG2, `DrawMenuScreenTitle`, spawns the cursor actor into `g_pMenuCursorActor` (`cursorKind` 9 spawns none), and, if `pulseSelection`, starts a palette effect pulsing colors 6-8 between the first two frames of `gMenuSelectionPalette`, keeping its slot in `g_nMenuScreenPaletteEffectSlot` (-1 when none). |
| `UpdateMenuScreen` | `0x0801E0D8` | Empty; called every frame by the menu screens' update functions. |
| `ExitMenuScreen` | `0x0801E0DC` | Releases the cursor actor, stops that palette effect and frees the particles. |
| `DrawMenuScreenTitle` | `0x0801E118` | Clears a text rectangle on BG2 and draws the string, except for string id `0xACF` (no text). JP draws it one pixel lower. |

The BG control words `g_dwCommonBg0Control`, `g_dwCommonBg1Control` and
`g_dwCommonBg2Control` (`0x0805E104`-`0x0805E10F`) belong to the same block.

`BuildListMenu` and `InitializeItemsItemSelect` call `BeginMenuScreen` without
`InitializeMenuScreen`; `BeginPauseMenuScreen` calls `LoadMenuScreenFrame` directly.
Menus outside this family (title, language select, owl name select, choose character,
the folios) set up their backgrounds themselves.

## Palette-less graphic blobs

Blobs without an embedded palette (flags `0x78`, `0xF8`) draw with a palette
that is already loaded; see [`../formats/graphic_blob.md`](../formats/graphic_blob.md).

- `gMenuScreenFrameGraphic` (`0x08DC1EFC`, frame, **PROVEN**): `LoadMenuScreenFrame` loads
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
