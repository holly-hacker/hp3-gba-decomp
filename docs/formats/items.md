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

`0x34` bytes (`ItemEntry` in `include/game/items.h`), read by the
inventory functions in `src/inventory/`:

| Offset | Field | Reader |
|---|---|---|
| `+0x00` | `nNameTextId` -- dialog string id for the display name | `GetRewardNameStringId_candidate` |
| `+0x04`, `+0x08`, `+0x0C` | `pPalette`/`pTileData`/`pFrameData` -- icon data, see [`graphics.md`](graphics.md)'s "Item icons" section | `GetItemImageData` |
| `+0x10` | `nBuyPrice` -- shop buy price (Sickles), see "Shop prices" below | `GetItemBuyPrice` |
| `+0x14` | `nSellPrice` -- shop sell price (Sickles) | `GetItemSellPrice`, `BuildFilteredItemList` |
| `+0x18` | `dwCategory` -- item category id, see below | `GetItemCategory`, `BuildFilteredItemList`, `OwnsItemInCategory` |
| `+0x1C` | `nCharacterMask` -- per-character equip mask, see below | `CanFighterEquipItem` |
| `+0x20` | `dwFlags` -- see "Item flags" below | `IsItemUsableInBattle_candidate`, `IsItemListedInItemsMenu_candidate`, `IsItemConsumable` |
| `+0x24` | `stats` (`ItemStats`): `equipment.nDefenseX2` (Def, pre-doubled) or `potion.nEffect` | `GetItemDefenseBoost`, `GetPotionEffect` |
| `+0x28` | `stats`: `equipment.nAgility` (Agi, signed) or `potion.nMagnitude` | `GetItemAgility`, `GetPotionMagnitude` |
| `+0x2C` | unidentified | -- |
| `+0x30` | `nMagicDefense` -- M.Def stat | `GetItemMagicDefense`, `ApplyEquipmentStatModifiers` |

## Equipment stats

`ApplyEquipmentStatModifiers` (`0x08026870`) applies each of a
party member's 6 equipped items as:

```c
bDefenseFactorPercent -= item.stats.equipment.nDefenseX2 / 2;  // displayed Def = 100 - value
bMagicDefensePercent  -= item.nMagicDefense;                   // displayed M.Def = 100 - value
bAgility                -= item.stats.equipment.nAgility;          // displayed Agi = 255 - value
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

The shop's quantity screen (`ShowShopQuantitySelect`, `0x08040B94`) reads
`nBuyPrice`/`nSellPrice` via `GetItemBuyPrice`/`GetItemSellPrice`
depending on buy/sell mode; `UpdateShopBuyList` (`0x080416CC`) compares
`nBuyPrice` against the player's Sickle count to gate a purchase.

**Buyability is gated by shop-tab membership, not `nBuyPrice`.** The
shop (Fred and George's, `src/store/`; see
[`game_modes.md`](../memory-map/game_modes.md)) has 7
tabs -- Miscellaneous, Belts, Charms, Gloves, Boots, Hats, Cloaks --
each a fixed item-id list in `src/shop/shop_stock.c`, pointed
at by `g_apShopStockLists` (`src/shop/shop_stock_lists.c`,
`0x08FB0D94`). `ShowShopBuyList` (`0x08041680`) picks a tab's
list and `OpenItemListFromIds` copies it into the display
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
| `0x1` | 8-19 | charms |
| `0x2` | 20-28 | gloves |
| `0x3` | 29-37 | boots |
| `0x4` | 38-46 | caps/hats |
| `0x5` | 47-55 | robes/cloaks |
| `0x6` | 56-61 | potions |
| `0x8` | 62-78 | key items ("Miscellaneous" in game): ingredients, pets, quest objects |

`0x7` has no items; its Items-screen label "Books" survives, as the
section labels are text `0x581 + category` ("Potions", "Books",
"Miscellaneous"). `OwnsItemInCategory(category)` reports whether the
player owns any item of a given category; `BuildFilteredItemList`
builds a list of owned items, where `ITEM_FILTER_NON_EQUIPMENT` (10)
means `dwCategory > 5` and `ITEM_FILTER_SELLABLE` (11) means
`nSellPrice != 0`.

Each run carries its own local string-ID base -- e.g. potions are
`index + 1540`, gloves/boots are `index + 1538`, belts/misc are
`index + 1576`.

## Item flags -- `dwFlags` (`+0x20`)

Potions carry `7`, category-8 items `2`, equipment `0`. Bit 2 marks the
consumables, the potions (`IsItemConsumable`): the Items screen sends them
through character and quantity select before `ItemUseScreen`.

Bits 0 and 1 are never read in either ROM: their only readers,
`IsItemUsableInBattle_candidate`, `IsItemListedInItemsMenu_candidate` and
`BuildBattleItemList_candidate`, have no callers or stored pointers.
**UNCONFIRMED** meanings, from the data: bit 0 (potions only) matches the
battle Items menu, which instead hard-codes the six potions as slots
(`IsBattleItemSlotUsable`); `BuildBattleItemList_candidate` lists the owned
non-equipment items with bit 0. Bit 1 (potions and category 8) matches the
pause Items screen, which instead selects by category
(`ITEM_FILTER_NON_EQUIPMENT`).

## Potions -- `stats.potion` (`+0x24`/`+0x28`)

For potions these fields hold the effect (`PotionEffect`: 1 Stamina,
2 Magic, 3 cure poison, 4 cure paralysis) and the Stamina/Magic restored
per potion. `UseRestorePotion` (`0x080269E0`) restores up to `quantity`
potions' worth, consumes only as many as needed, and returns the result
message.

## Real item count

Indices 0-78 (79 entries) are real items; index 79 is a dummy record
marking the end (`nNameTextId` `0`, `dwCategory` `0xC` -- matches no
real category but passes the `0xA` "all items" filter, clones index
62's icon); indices 80-131 are all-zero padding, ending exactly at
`0x08060EE4 + 132*0x34 = 0x080629B4`. `OwnsItemInCategory` walks `0`-`78`,
`BuildFilteredItemList` walks `0`-`131`; 132 is also where
`g_ItemInventory.abQuantities` hands over to `aabEquipped` (see
[`save.md`](save.md)).

## The table as committed C source

**PROVEN** (byte-exact, `just check-all` passes). `g_pItemTable` is
committed as `src/items/items.c`, all 132 `ItemEntry` initializers in
on-disk order, each with a leading `// <index>: <name>` comment for the
79 real entries, and placed in both versions. Real items' `pPalette`/`pTileData`/
`pFrameData` fields reference `extern` icon-label symbols
(`gItemNNNPalette`/`Tiles`/`Frames`) instead of literal
addresses; the dummy record 79 reuses item 63's labels, and records
80-131 are all zero.

## Item icons

Real items' `pPalette`/`pTileData`/`pFrameData` aren't stored as
literal integers in `src/items/items.c` -- see [`graphics.md`](graphics.md)'s
"Item icons" section for the format. File stems follow item-table order:
index 0 becomes `Item001`, independent of display text, and names the
editable `data/graphics/menus/Item001.png`. Index 70's icon is
`ItemChocolateFrogs` instead, since card rewards reuse it, and the extra
`ITEM_REMOVE` icon after the table's icons is `ItemRemove`. All are part of
the `ItemAndHelpIcons` `image-bank` run (see [`graphics.md`](graphics.md) "Graphics build
format"). The shared packer rebuilds each icon from its PNG and emits its
labels and declarations in `include/gen/graphics/menus.h`; it does not need
to parse `src/items/items.c` or know item-specific formats.

## What's NOT yet known

- `+0x2C` -- no readers found at all.
