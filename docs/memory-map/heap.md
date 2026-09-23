# Heap allocator / object pool — memory map

See [`../README.md`](../README.md) for the confidence-key legend
(PROVEN / STRUCTURAL MATCH / UNCONFIRMED) used throughout, and for the
document index.

## Heap allocator — PROVEN

A small first-fit allocator over one or more pools, only pool 0 ever
registered (by `InitHeap`, spanning ~all of EWRAM):

- `gMemPool` (`0x03003EE0`) — `MemPool[]`, one 0x10-byte record per pool
  (`pBase`, `pFreeListHead`, `dwCapacity`, `pEnd`); `gMemPoolCount`
  (`0x03003EF0`) is the live count.
- Every block carries a 0x10-byte `MemBlock` header immediately before its
  payload: `pNextByAddr`/`pPrevByAddr` thread every block (free or
  allocated) in address order; `pNextFree`/`pPrevFree` thread only the
  free ones. An allocated block repurposes the free-list fields: `+8`
  becomes the owning pool index, `+0xC` becomes `-1` as a live marker.
- `InitMemoryPool`, `GetFreeBlockSize`, `LinkBlockByAddress`,
  `LinkFreeBlock`, `UnlinkFreeBlock`, `List_PushHead`, `memset`,
  `BuildFreeList`, `AllocBlock`, `AllocZeroed` are all matched in
  `src/mem/`. Types in `include/mem.h`. See also "Generic intrusive list
  / active-object list" below for `List_PopHead`/`List_Remove`/
  `List_MoveToHead`/`AllocObjectFromFreeList`.

`memset` (`0x0802C450`) is **not** the vendored newlib copy in `src/libc/`,
despite being the classic newlib shape (byte-fill to alignment, word-fill
the middle, byte-fill the remainder): it sits nowhere near the confirmed
libgcc/libc block (`0x0804A2C0`-`0x0804BDBC`, see `../compiler.md`), and
its return sequence (`pop {r4-r7}; pop {r1}; bx r1`) is the interworking
form `-mthumb-interwork` game code uses, not the plain `pop {...,pc}`
newlib compiles to without interworking (confirmed against the matched
`memcpy`/`bzero` in `src/libc/`) — compiling it under the libc profile
produces the wrong return sequence and doesn't match.

Two agbcc codegen quirks needed for `memset`/`AllocZeroed` to match
byte-exact, both requiring specific C shapes rather than being reachable
by flag changes:

- `memset`'s word-fill loop must be written as indexed
  (`((u32*)ptr)[i] = pattern`), not a walking `*aligned++`. Written as
  indexed, `loop.c`'s strength-reduction pass derives the walking
  pointer itself and places its init in the loop preheader, after the
  zero-trip guard — matching real. Written as an explicit walking
  pointer, the same init lands before the guard instead.
- `AllocZeroed`'s round-up-to-16 (`len = (size+0xf) & ~0xf`) must be
  written as three in-place statements on one variable (`len = size;
  len += 0xf; len &= ~0xf;`), and its pool-walk loop must be a real
  `do`/`while`, not flattened `goto`s. The stepwise form is what gets
  the constant `0xf` into a register agbcc's reload pass then derives
  the `~0xf` mask from directly (`sub r0, r0, #0x1f` instead of loading
  `-0x10` fresh); the real loop is what gives `len` enough
  loop-depth-weighted references to win a callee-saved register over
  `pFreeListHeadSlot` — a `goto`-flattened loop weighs every reference
  as depth 1 and loses that tie.

## Object pool — STRUCTURAL MATCH

`InitObjectPool` (matched, `src/mem/init_object_pool.c`) carves a second,
fixed-size-slot pool out of the heap:

- `g_ObjectPoolState.pBuffer`/`.pFreeListHead` are adjacent words
  (`0x03001C08`/`0x03001C0C`, modeled as one `ObjectPoolState` struct in
  `include/mem.h` since the real code reaches the second through the
  first at `+4`) — a 0x7968-byte `AllocZeroed`'d buffer (0x69 objects *
  0x128-byte stride), carved into a free list by `BuildFreeList`.
- `g_pObjectPoolAuxBuffer` (`0x03001DBC`) — a second, 0x104-byte
  `AllocZeroed`'d buffer; `InitObjectPool`'s only write to it. Five
  `ObjectPoolAuxRecord`s of 0x34 bytes, indexed by `Object.bObjectPoolAuxSlot`:
  `awTileAllocIds[12]` at `+8` and `abRefCounts[20]` at `+0x20`. Objects whose
  `bFlags_0x115 & 3` is nonzero share VRAM tiles through a record;
  `ReleaseObjectOffscreenVramTiles` (matched, `src/object/`) decrements the
  refcount and calls `FreeObjectVramTileAllocation` (`0x08045514`) when it
  reaches 0. Objects with `bFlags_0x115 & 3 == 0` free their own allocation and
  the variant slot's (when bit `0x40` is set) directly. Record fields beyond
  those two arrays are unconfirmed.
- `g_pSortObjectsIwram`/`g_pCheckObjectCollisionsIwram` (`0x0300194C`/
  `0x03001A10`) — `SortObjectsByDepth`/
  `CheckObjectCollisions` relocated into IWRAM via
  `bios_CPUSet`, the standard GBA hot-loop-in-IWRAM pattern.
- `g_dwObjectListActive_candidate` (`0x030017A0`) — set to 1 by
  `InitObjectPool`, also written by `FUN_08001d90`; read by
  `TickObjectList`.
- `g_dwUnk03001DC4` — zeroed by `InitObjectPool`. Read in
  `WriteObjectOamCells` as what looks like a fixed-point rounding/scale
  constant, unrelated to the pool itself; not enough evidence for a real
  name yet.

## Generic intrusive list / active-object list — PROVEN

The object pool's free list is built on a small generic doubly-linked-list
library (`ListNode` in `include/mem.h`) that a *second* list, the active
object list, also uses. All four matched in `src/mem/`.

- `List_PopHead` (`0x08028728`) — `ListNode *List_PopHead(ListNode
  **listHead)`. Pops and returns the head node, fixing up the new head's
  `pPrev` and clearing the popped node's own `pNext`.
- `List_Remove` (`0x08028760`) — `void List_Remove(ListNode **listHead,
  ListNode *node)`. Unlinks `node` from wherever it sits in the list:
  patches `*listHead` if `node` was first, patches both neighbors, clears
  `node`'s own `pNext`/`pPrev`. `listHead` reads as a bare `ListNode*` in
  a naive decompile (`param_1->pNext`) because dereferencing a
  `ListNode**` and reading a `ListNode`'s first field are the same
  memory access; it's genuinely `ListNode**`, same as `List_PushHead`.
- `List_MoveToHead` (`0x0802870C`) — `void List_MoveToHead(ListNode
  **destListHead, ListNode **srcListHead, ListNode *node)`. `List_Remove`
  then `List_PushHead` — moves `node` from one list to the front of
  another (or the same list twice, a requeue/MRU pattern).
- `AllocObjectFromFreeList` (`0x080286D8`) — `void
  *AllocObjectFromFreeList(ListNode **freeListHead, ListNode
  **activeListHead, uint size)`. Pops a node off `freeListHead`, zeroes
  it, pushes it onto `activeListHead`, returns it (`NULL` if the free
  list was empty). Called by `AllocDefaultObject`/`SpawnObject` with `&g_ObjectPoolState.pFreeListHead` and
  `&sActiveObjectListHead` — the real "allocate an object" entry point,
  one level above `AllocObjectOfType`/`AllocDefaultObject`.
- `sActiveObjectListHead` (`0x030015B0`) — `ListNode *`, head of the
  active-object list objects join via `AllocObjectFromFreeList`.

## `SortObjectsByDepth` / `CheckObjectCollisions` — ARM-mode

Both are **confirmed ARM-mode** by disassembly (`arm_func` seeds in
`functions.us.cfg`, byte-verified via `just disasm-compare`):
`SortObjectsByDepth` (`0x08006440`-`0x08006508`) and
`CheckObjectCollisions` (`0x08005F10`-ends within the same
`0x08005EE8`-`0x08006508` span, alongside two other unnamed ARM/Thumb
functions in between that aren't part of this pair). Neither is reachable
via `bl` anywhere in the ROM -- they're only ever taken by address
(`InitObjectPool` passes both to `bios_CPUSet` to relocate into IWRAM),
which is why `gbadisasm`'s branch-following never found their boundaries
on its own; they needed explicit seeding.

`SortObjectsByDepth` is a Shell sort (gap sequence 21/7/3/1, packed
byte-wise into one `0x15070301` constant) over an array of object
pointers. **PROVEN** by decompile: the key is `((bGfxSlotAndFlags & 0xC)
<< 22) | (bDepthSortBias << 16) - Y` (`+0x3A`) -- draw layer, then bias,
then descending screen Y.

`CheckObjectCollisions` does the per-frame pairwise collision pass.
**PROVEN** by decompile: each object has two `ObjectCollisionBox` slots
(`Object.aCollisionBoxes`, `include/object.h`) and a matching 2-entry
callback array (`Object.apfnCollisionCallback`). On AABB overlap, gated
on `g_GameModeStackContext.dwCurrentGameMode == Overworld`, it calls
each object's callback for the overlapping box slot with the other
object as the argument.

Both are kept as assembly (`asm/check_object_collisions.s`,
`asm/sort_objects_by_depth.s`): the available compilers are Thumb-only (see
"ARM-mode code" in [`../compiler.md`](../compiler.md)).
