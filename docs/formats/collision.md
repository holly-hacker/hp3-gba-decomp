# Room collision map

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED). This document adds a fourth,
explicitly-labeled category: **user-verified**, meaning confirmed by a
human playing the real game and matching what they saw against a
rendered visualization of the data below -- strong empirical evidence,
but not a code-level proof, and kept distinct from the other three for
that reason.

## Format

**STRUCTURAL MATCH.** `LoadRoomSharedTileset_candidate` (`0x0802DD58`,
consumer of the level table's `dwSharedTileset`/`dwSharedTilemap`
fields, see [`levels.md`](levels.md)) decompresses two resources:

- `g_pRoomCollisionBehaviorTable`: 16 tile-type bytes per metatile
  pattern (a 4x4 grid, one byte per 8x8-px cell).
- `g_pRoomCollisionTilemap`: a 4-byte header (first `u16` = pattern
  count into `DAT_03003FB8`; second `u16` unconfirmed) followed by a
  `u16` pattern-ID grid, one entry per 32x32-px block, over a room
  `g_wRoomWidthPixels` x `g_wRoomHeightPixels` in size. The 4-byte
  header size is ground-truth confirmed (`sub_0802DD58`: `adds r0, r1,
  #4`, raw byte arithmetic on the buffer pointer, not a 2-byte skip).

`GetCollisionTypeAtPixel_candidate` (`0x0802D7A0`) resolves a pixel to
its tile-type byte (out-of-bounds = solid, type 1). The **low 6 bits**
of that byte are the tile type (below); the **top 2 bits** are a
separate value, read by `0x0802E030` and written into `bDrawLayer`
(`Object+0xD5` bits 2-3, see `SetObjectDrawLayer`). STRUCTURAL MATCH:
`SortObjectsByDepth_candidate` folds it into the draw-order sort key,
and `TickObjectList` flushes a per-layer queued particle list
(`FUN_080317ec`/`FUN_08031358`) as it crosses each layer boundary while
walking the depth-sorted object list. UNCONFIRMED: the previously
recorded "user-verified: layer=1 is an occlusion flag" claim has no
evidence trail here and wasn't reproduced by the above.

## Movement blocking (PROVEN, via `FUN_0802DA20`)

Only types **1-25** trigger the actual position-revert/blocking
response in the movement-resolution function. **Types 26+ are passable
by default** -- `ApplyTileCollisionEffect_candidate` (`0x0802D8F4`,
dispatched from `CheckObjectTileCollision_candidate`/
`ScanCollisionEdge_candidate`, `0x0802D868`/`0x0802DC3C`, which walk an
object's swept movement box in 4px steps) only force-blocks two of
them, and only conditionally:

- `0x1F`: blocks unless a spell-effect object is currently active
  (`DAT_03003FD4`, set by the generic effect-spawner `0x0802E090`) AND
  the player object's `field_0x91` is set.
- `0x29`: blocks every object except ones with `wObjectType==0xF`.

`0x22` force-blocks objects with `wObjectType==0` specifically (exempts
everything else, with an extra 4-corner pushable-adjacent check for
`wObjectType==5`) -- code doesn't independently confirm what game-object
class `wObjectType==0` is, but user-verified "0x22 is unwalkable water"
is consistent with it being the player/common-character type.

## Slope geometry (types 2-25, PROVEN)

Each type indexes a 2-point line segment in `g_aSlopeLineSegments`
(`0x080660A4`, 24 entries, 4-bit `(x0,y0)-(x1,y1)` local to the 8x8
cell); a cross-product test decides which side of the line is solid, so
solidity varies by position within the tile, not just tile identity.
22/24 are a vertical midline (x=4), 23/25 a horizontal midline (y=4) --
straight half-tile cuts, not diagonal.

| Type | Segment | Type | Segment |
|---|---|---|---|
| 2 | (0,8)-(8,4) | 14 | (8,8)-(0,0) |
| 3 | (0,4)-(8,0) | 15 | (4,8)-(0,0) |
| 4 | (0,8)-(8,0) | 16 | (8,8)-(4,0) |
| 5 | (0,8)-(4,0) | 17 | (4,0)-(0,8) |
| 6 | (4,8)-(8,0) | 18 | (8,0)-(4,8) |
| 7 | (0,0)-(4,8) | 19 | (8,0)-(0,8) |
| 8 | (4,0)-(8,8) | 20 | (8,4)-(0,8) |
| 9 | (0,0)-(8,8) | 21 | (8,0)-(0,4) |
| 10 | (0,0)-(8,4) | 22 | (4,8)-(4,0) |
| 11 | (0,4)-(8,8) | 23 | (0,4)-(8,4) |
| 12 | (8,4)-(0,0) | 24 | (4,0)-(4,8) |
| 13 | (8,8)-(0,4) | 25 | (8,4)-(0,4) |

**Resolved: this is a real in-game bug, not an extraction error.**
Room 25 ("Rooftop") and room 29 ("Gryffindor Common Room"), among others,
have slope corners where the rendered collision map disagrees with naive
expectation -- but user-verified live play gets stuck on those exact
corners the same way the map predicts. The game's own slope data/logic is
buggy or incomplete at these corners; the extraction is correct.

Confirmed byte-exact against the ROM along the way (geometry, indexing,
table data, pattern bounds), which is what let the live-play check settle
this as a game bug rather than a modeling error:

- `FUN_0802DB20` is the per-object slope-slide/direction-reversal state
  machine behind the ice/Glacius puzzle (type `0x2D`), driven by
  `FUN_0802DA20`'s `Object.bUnk_0x7C` states 1/2/4/5 -- not a second
  geometry consumer; it indexes `g_aSlopeLineSegments` the same way the
  real solidity test does.
- `GetCollisionTypeAtPixel_candidate` (`0x0802D7A0`) is the real per-pixel
  solidity test, and `tools/collision/dump_collision.py` matches its
  cross product, nibble decode, and per-cell index exactly.
- The 24 raw table entries read from `baserom.us.gba` match the table
  above exactly.
- `FUN_0802E030` (layer accessor) is just `(byte>>6)+1`, no geometry
  feedback.
- Rooms 25/29's tilemap header pattern counts match their behavior
  tables' actual pattern counts exactly (307/307, 80/80), no
  out-of-range pattern IDs.

## Special types 26+ (passable terrain, effects)

Code-confirmed meanings:

| Type | Meaning |
|---|---|
| `0x22` (34) | Force-blocks `wObjectType==0`; pushable-block check for `wObjectType==5` |
| `0x23` (35) | Room switch-state toggle A |
| `0x24` (36) | Room switch-state toggle B |
| `0x29` (41) | Blocks everything except `wObjectType==0xF` |
| `0x2D` (45) | Sets a flag bit on the player object |

User-verified (live gameplay against the rendered collision maps):

| Type | Meaning |
|---|---|
| `0x1B` (27) | Horizontal stairs, bottom-left/top-right |
| `0x1C` (28) | Horizontal stairs, bottom-right/top-left |
| `0x1D` (29) | Vertical stairs, bottom-at-bottom, top-at-top |
| `0x1E` (30) | Vertical stairs, bottom-at-bottom |
| `0x1F` (31) | Lumos crossing -- Harry must cast Lumos to cross |
| `0x25` (37) | Diagonal stairs, bottom-left to top-right |
| `0x26` (38) | Diagonal stairs, bottom-top-left to top-bottom-right |
| `0x27` (39) | Diagonal stairs, bottom-top-right to top-bottom-left (tentative) |
| `0x28` (40) | Diagonal stairs, bottom-right to top-left |
| `0x2B` (43) | Stairs repairable by Hermione's Reparo |
| `0x2D` (45) | Ice -- Hermione's Glacius turns it into a sliding puzzle surface |

Remaining observed-but-unidentified types: `0x1A` (26, by far the most
common -- may just be a generic alternate wall/ground variant, not
necessarily special), `0x20` (32), `0x21` (33, seen only in Potions
Classroom Maze/Path to Hagrid's Hut/Shrieking Shack Path -- no visible
in-game effect found so far, possibly a marker tied to a specific
playable character's action), `0x2A` (42), `0x2C` (44, likely stairs --
vertical bottom-at-top, or diagonal bottom-at-top-right -- not
distinguishable yet).

## Extraction

`just dump-collision` (`tools/collision/dump_collision.py`) renders
every room to `extracted/collision/us/` for visual inspection: a plain
walkability PNG and one annotated with per-type color/pattern + layer
markers (`TYPE_LEGEND.png` in the same directory). Research/debugging
aid only, not build input -- see the script's docstring for why there's
no corresponding `pack` step yet.

## Not yet located

- Which game-object class `wObjectType==0` and `wObjectType==0xF` are.
- Layer values 2 and 3's meaning.
- JP-ROM addresses; everything above is US-only.
