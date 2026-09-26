# Item/equipment table format

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout, and for the
document index.

`g_pItemTable` (ROM `0x08060EE4`, `ItemEntry[132]`, stride `0x34`, 79 of
them populated) is the game's item/equipment database -- one record per
item id, covering display name, icon, equip stats, and category. The
save format only stores item ids/quantities and equipped item ids,
indexing into this table -- see [`save.md`](save.md)'s "Item quantities
and equipment" section.

## Record layout

`0x34` bytes, from the accessors in the `0x08026754` (`EquipItemInSlot`)-
`0x08026F7E` cluster, each addressing the table as
`0x08060EE4 + index*0x34 + fieldOffset`:

| Offset | Field | Reader |
|---|---|---|
| `+0x00` | `nNameTextId` -- dialog string id for the display name | `FUN_08026B8C` |
| `+0x04`, `+0x08`, `+0x0C` | `pPalette`/`pTileData`/`pFrameData` -- icon data, see [`graphics.md`](graphics.md)'s "Item icons" section | `FUN_08026bcc` |
| `+0x10` | `nBuyPrice` -- shop buy price (Sickles), see "Shop prices" below | `GetItemBuyPrice` |
| `+0x14` | `nSellPrice` -- shop sell price (Sickles) | `GetItemSellPrice`, `FUN_08026E58` |
| `+0x18` | `dwCategory` -- item category id, see below | `FUN_08026E58`, `FUN_08026F48` |
| `+0x1C` | `nCharacterMask` -- per-character equip mask, see below | `CanFighterEquipItem` |
| `+0x20` | flag byte (bit 2 tested) | `FUN_08026D34` (no callers found) |
| `+0x24` | `nDefenseX2` -- Def stat, pre-doubled | `FUN_08026CDC` |
| `+0x28` | `nAgility` -- Agi stat, signed | `FUN_08026CF0` |
| `+0x2C` | unidentified | -- |
| `+0x30` | `dwMagicDefense` -- M.Def stat | `ApplyEquipmentStatModifiers_candidate` |

## Equipment stats

`ApplyEquipmentStatModifiers_candidate` (`0x08026870`) applies each of a
party member's 6 equipped items as:

```c
bDefenseFactorPercent -= item.nDefenseX2 / 2;   // displayed Def = 100 - value
bMagicDefensePercent  -= item.dwMagicDefense;   // displayed M.Def = 100 - value
bSpeed                -= item.nAgility;         // displayed Agi = 255 - value
```

## Equip eligibility -- `nCharacterMask` (`+0x1C`)

`CanFighterEquipItem(fighterType, itemId)` (`0x080267D0`):

```c
mask = item.dwCategory < 6 ? item.nCharacterMask : 7;  // non-equip categories always pass
return (mask & bitFor[fighterType]) != 0;               // Harry=0x1, Ron=0x2, Hermione=0x4
```

Checked by `EquipItemInSlot` (`0x08026754`) at equip-confirm time, not
by the item-select list builder -- the equip screen lists every owned
item of the right category regardless of character, and only refuses
(error sound) once an ineligible one is confirmed. Only the `Charm`
category uses restricted masks in practice; every belt/gloves/boots/
cap/robe item carries `0x7` (all three).

## Shop prices -- `nBuyPrice`/`nSellPrice` (`+0x10`/`+0x14`)

The shop's item-detail screen (`DrawShopItemDetail`, `0x08040B94`) reads
`nBuyPrice`/`nSellPrice` via `GetItemBuyPrice`/`GetItemSellPrice`
depending on buy/sell mode; `ConfirmShopBuyItem` (`0x080416CC`) compares
`nBuyPrice` against the player's Sickle count to gate a purchase.

**Buyability is gated by shop-tab membership, not `nBuyPrice`.** The
shop (Fred and George's, `UpdateFredAndGeorgesShop`, `0x080411E0`) has 7
tabs -- Miscellaneous, Belts, Charms, Gloves, Boots, Hats, Cloaks --
each a fixed item-id list extracted to `asm/data/shop_stock.s`, pointed
at by `g_apShopStockLists` (`asm/data/shop_stock_lists.s`,
`0x08FB0D94`). `HandleShopScreenTransition` (`0x08040F04`) picks a tab's
list and `LoadShopStockList` (`0x08027B44`) copies it into the display
buffer -- `nBuyPrice` only sets cost once an item is on one of these
lists. Belts/Gloves/Boots/Hats/Cloaks stock their entire category run;
Charms stocks 8 of 12 (Bracelet/Beads/Head Band/Remembrall are never
sold); Misc mixes all 6 potions with Chocolate Frogs.

`nBuyPrice` doubles as a reward-selection weight in
`SelectWeightedOwlRewardItem` (`0x080231FC`, called from
`ProcessOwlMailReward`, see [`save.md`](save.md)'s "Owl Care Kit"
section).

## Item categories -- `dwCategory` (`+0x18`)

The table is ordered in contiguous per-category runs:

| `dwCategory` | Indices | Category |
|---|---|---|
| `0x0` | 0-7 | belts |
| `0x1` | 8-19 | misc/quest items (equip slot: charm) |
| `0x2` | 20-28 | gloves |
| `0x3` | 29-37 | boots |
| `0x4` | 38-46 | caps/hats |
| `0x5` | 47-55 | robes/cloaks |
| `0x6` | 56-61 | potions |
| `0x8` | 62-78 | ingredients/quest items, plus `bMonsterBookOfMonsters` at 78 |

`0x7` is unused. `FUN_08026F48(category)` reports whether the player
owns any item of a given category; `FUN_08026E58(filter, out, ...)`
builds a filtered item list, where `filter == 0xA` means "all items"
(`dwCategory > 5`) and `filter == 0xB` means "sellable" (`nSellPrice
!= 0`).

Each run carries its own local string-ID base -- e.g. potions are
`index + 1540`, gloves/boots are `index + 1538`, belts/misc are
`index + 1576`.

## Real item count

Indices 0-78 (79 entries) are real items; index 79 is a dummy record
marking the end (`nNameTextId` `0`, `dwCategory` `0xC` -- matches no
real category but passes the `0xA` "all items" filter, clones index
62's icon); indices 80-131 are all-zero padding, ending exactly at
`0x08060EE4 + 132*0x34 = 0x080629B4`. `FUN_08026F48` walks `0`-`78`,
`FUN_08026E58` walks `0`-`131`; 132 is also where the save format's
`g_abItemQuantities` hands over to `g_abEquippedItemIds` (see
[`save.md`](save.md)).

## The table as committed C source

**PROVEN** (byte-exact, `just check-all` passes). `g_pItemTable` is
committed as `src/data/items.c`, all 132 `ItemEntry` initializers in
on-disk order, each with a leading `// <index>: <name>` comment for the
79 real entries. Placed for the US ROM only by a `c-file` row in
`regions.us.txt` -- table content is not yet confirmed identical to JP
(see "What's NOT yet known" below). Real items' `pPalette`/`pTileData`/
`pFrameData` fields reference `extern` icon-label symbols
(`gItemNNNPalette`/`Tiles`/`Frames`) instead of literal
addresses; non-real entries (indices 79-131) keep literal pointer
values.

## Item icons

Real items' `pPalette`/`pTileData`/`pFrameData` aren't stored as
literal integers in `src/data/items.c` -- see [`graphics.md`](graphics.md)'s
"Item icons" section for the format. File stems follow item-table order:
index 0 becomes `Item001`, independent of display text, and names the
editable `data/images/items/Item001.png`. `just extract-images` writes
the PNGs and `data/images/items/bank.json` in ROM order. The shared
`tools/images/pack_images.py` rebuilds each icon from its PNG and emits
assembly labels and a matching C header for the single `image-bank`
region; it does not need to parse `src/data/items.c` or know
item-specific formats.

## What's NOT yet known

- `+0x20`'s bit 2, read by `FUN_08026D34`, which has no callers found
  anywhere in the ROM.
- `+0x2C` -- no readers found at all.
- JP addresses for `g_pItemTable` and this section's reader functions.
