# Help page scripts

The Help menu (game mode `Help`, `0x17`) and the `HelpTopicScreen` mode (`0x44`, the
minigame instruction pages shown before a minigame and from battle) share one engine
(`StartHelpScreen`, `RunHelpScript`, `UpdateHelp`) and one block of page scripts in ROM
(US `0x08069C70`-`0x0806B190`, JP `0x08069BFC`-`0x0806B11C`; every pointer in the JP block is
the US value minus `0x74`). The source is `src/gamemode/modes/help/help_pages.c`, with the
opcode macros in `include/menu/help.h`. All of this is **PROVEN** against the interpreter
`RunHelpScript` and a full parse of the block (91 pages, no gaps).

## Script format

A page is a stream of little-endian words ending with `HELP_END`. The low byte of a command
word is the opcode, the upper bytes are parameters, and operands follow as whole words.

| Op | Macro | Words | Meaning |
| --- | --- | --- | --- |
| `0` | `HELP_END` | 1 | End of page. |
| `1` | `HELP_HEADER(kind)` | 1 | Page kind in byte 1: `HelpPageText` (0) or `HelpPageMenu` (1). |
| `2` | `HELP_MENU_LINK` | 3 | Menu entry: label text id, page pointer. |
| `3` | `HELP_MENU_LINK_IF` | 4 | As `2` plus a predicate (`IsHelpTopicUnlocked`) deciding whether the entry is available; unavailable entries are drawn in a different text style. |
| `5` | `HELP_TEXT` | 3 | Text box: x and y in bytes 1-2, then width and height in the next word's bytes 0-1, then the text id. |
| `6` | `HELP_TITLE` | 2 | Title text id, drawn in a fixed box. |
| `7` | `HELP_PAGE_NUMBER` | 1 | Current and total page, shown with text `0x8EF` ("@1/@2"). |
| `8` | `HELP_SPRITE` | 1 | Page-turn arrow sprite: asset index in byte 1 (into `g_aHelpSpriteAssets`), x in byte 2, y in byte 3. x `0xB4` is the right arrow. |
| `11` / `12` | `HELP_NEXT_PAGE` / `HELP_PREV_PAGE` | 2 | Page pointer reached with Right / Left. |

Opcodes `4` (set the selected entry), `9` (no-op) and `10` (set the text-line state) are
handled by the interpreter but do not occur in the data.

## Contents

Text pages come in chains (one array per topic in `help_pages.c`), and the five menus link to
the chain heads: the root menu (`g_aHelpMenuMain`) leads to the Folios, Collector's Cards,
Items and Mini-Games menus plus the Magical Encounters and Special Moves Glossary chains. The
minigame chains (Wizard Cracker Pop-it, Hippogriff Glide, Riddikulus, Tea Leaf Divination,
Dementors) are also the targets of `HelpTopicScreen`, whose argument 2 picks the topic
(`InitializeTopicScreen`); topic `6` opens the root menu from battle. The Mini-Games menu
entries are gated by the save header's unlock flags (see [`save.md`](save.md)).

## Engine state

`g_HelpState` (`HelpState`, `include/menu/help.h`) holds the page-history stack, the entries
of the menu on screen, the cursor and arrow sprites, and the `PushGameMode_3` arguments used
when the screen closes (`SetHelpExitMode`). `UpdateHelp` is a five-state machine: fade in,
input (B cancels, Left/Right turn text pages, Up/Down/A drive menus), fade out, load the
pending or previous page, then push the exit mode.
