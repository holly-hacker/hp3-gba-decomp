# Heap allocator / actor pool — memory map

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
  `LinkFreeBlock`, `UnlinkFreeBlock`, `memset`, `AllocBlock`,
  `AllocZeroed` are all matched in `src/mem/`. Types in `include/mem.h`.
  See also "Generic intrusive list / active-actor list" below for
  `BuildFreeList` and the `List_*` functions.

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

## Actor pool — STRUCTURAL MATCH

`InitActorPool` (matched, `src/actor/init_actor_pool.c`) carves a second,
fixed-size-slot pool out of the heap:

- `g_ActorPoolState.pBuffer`/`.pFreeListHead` are adjacent words
  (`0x03001C08`/`0x03001C0C`, modeled as one `ActorPoolState` struct in
  `include/actor.h` since the real code reaches the second through the
  first at `+4`) — a 0x7968-byte `AllocZeroed`'d buffer (0x69 actors *
  0x128-byte stride), carved into a free list by `BuildFreeList`.
- `g_pActorPoolAuxBuffer` (`0x03001DBC`) — a second, 0x104-byte
  `AllocZeroed`'d buffer; `InitActorPool`'s only write to it. Five
  `ActorPoolAuxRecord`s of 0x34 bytes, indexed by `Actor.bActorPoolAuxSlot`:
  `awTileAllocIds[12]` at `+8` and `abRefCounts[20]` at `+0x20`. Actors whose
  `bDrawFlags & 3` is nonzero share VRAM tiles through a record;
  `ReleaseActorOffscreenVramTiles` (matched, `src/actor/`) decrements the
  refcount and calls `FreeObjVramTileAllocation` (`0x08045514`) when it
  reaches 0. Actors with `bDrawFlags & 3 == 0` free their own allocation and
  the variant slot's (when bit `0x40` is set) directly. Record fields beyond
  those two arrays are unconfirmed.
- `SortActorsByDepthIwram`/`CheckActorCollisionsIwram` (`0x0300194C`/
  `0x03001A10`) — `SortActorsByDepth`/
  `CheckActorCollisions` relocated into IWRAM via
  `bios_CPUSet`, the standard GBA hot-loop-in-IWRAM pattern.
- `g_dwActorListActive_candidate` (`0x030017A0`) — set to 1 by
  `InitActorPool`, also written by `FUN_08001d90`; read by
  `TickActorList`.
- `ActorPoolState` continues past the two pointers: `+0x08` is the count
  byte and `+0x0C` the 0x69-entry queue of actors whose
  `UpdateActorOamCells` result was 2, drained by
  `CommitQueuedActorTileUpdates` on vblanks that swap the OAM buffers;
  `+0x1B0` (`0x03001DB8`) is a byte enabling `TickActorList`'s extra OAM pass.
  Its low two bits set the OAM priority of the pass's copies, which
  `WriteActorOamCells` mirrors vertically and hides on alternate vblanks
  (`SetExtraOamPassPriority`, unused). `ClearActorPoolAuxBuffer` (unused)
  zeroes `g_pActorPoolAuxBuffer`.
  The queue is a struct member: `TickActorList` (matched,
  `src/actor/tick_actor_list.c`) indexes it through the struct.
- `g_dwUnk03001DC4` — zeroed by `InitActorPool`. `WriteActorOamCells`
  adds it to the magnitude of a 16.16 scaled cell offset before shifting
  out the fraction, a rounding bias. No other literal reference exists in
  US code, so it is presumably always 0; not enough evidence for a real
  name yet.

## Per-tick actor queues — PROVEN

`TickActorList(list, mode)` (US/JP `0x08000918`, matched) resets these
counts, runs `TickActor` over the list (which fills the queues), then drains
them. `mode == 1` is the full pass that also updates OAM.

| Queue | Array | Count | Drained by |
| --- | --- | --- | --- |
| OAM (depth-sorted) | `g_apOamQueue` `0x030015B8`[0x69] | u32 `0x0300175C` | `SortActorsByDepth` (mode 1, `g_dwActorListActive_candidate` set, count > 1), then `UpdateActorSpriteFrame` + `UpdateActorOamCells` per actor |
| Sprite frame | `g_apSpriteFrameQueue` `0x03001760`[15] | u8 `0x0300179C` | same per-actor updates, walked tail to head before the OAM queue |
| Collision | `g_apCollisionQueue` `0x030017A4`[0x69] | u32 `0x03001948` | `CheckActorCollisions(count, array)`, active list only, skipped when game-mode flag `0x800` is set |

Before draining the sorted OAM queue, `TickActorList` buckets the live particles by OAM
priority (`BucketParticlesByPriority`). While draining it, it calls `TickParticleLayer(n)`
for each draw layer `n` (`Actor.oam.priority`) the sort has passed, then for the
remaining layers up to 3, so particles are queued among the actors of their priority
(see [`particles.md`](particles.md)). Mode 1 ends with `CommitObjAffineMatrices`. It
returns 1 if any queue-drain `UpdateActorOamCells` call returned nonzero.

## Generic intrusive list / active-actor list — PROVEN

The actor pool's free list is built on a small generic doubly-linked-list
library (`ListNode` in `include/list.h`) that a *second* list, the active
actor list, also uses. `BuildFreeList`, `AllocObjectFromFreeList`, and the
`List_*` functions are matched in `src/list/`.

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
  list was empty). Called by `AllocDefaultActor`/`SpawnActor` with `&g_ActorPoolState.pFreeListHead` and
  `&g_ActiveActorListState.pHead` — the real "allocate an actor" entry point,
  one level above `AllocActorOfType`/`AllocDefaultActor`.
- `g_ActiveActorListState` (`0x030015B0`) — `pHead` is the head of the
  active-actor list actors join via `AllocObjectFromFreeList`; `TickActorList`
  walks `pUnk4` (`+4`) backwards via `pPrev`, so it is likely the tail.

## `SortActorsByDepth` / `CheckActorCollisions` — ARM-mode

Both are **confirmed ARM-mode** by disassembly (`arm_func` seeds in
`functions.us.cfg`, byte-verified via `just disasm-compare`):
`SortActorsByDepth` (`0x08006440`-`0x08006508`) and
`CheckActorCollisions` (`0x08005F10`-ends within the same
`0x08005EE8`-`0x08006508` span, alongside two other unnamed ARM/Thumb
functions in between that aren't part of this pair). Neither is reachable
via `bl` anywhere in the ROM -- they're only ever taken by address
(`InitActorPool` passes both to `bios_CPUSet` to relocate into IWRAM),
which is why `gbadisasm`'s branch-following never found their boundaries
on its own; they needed explicit seeding.

`SortActorsByDepth` is a Shell sort (gap sequence 21/7/3/1, packed
byte-wise into one `0x15070301` constant) over an array of actor
pointers. **PROVEN** by decompile: the key is `(oam.priority << 24)`
(byte `0xD5`'s bits 2-3, read as `(byte & 0xC) << 22`) | (bDepthSortBias << 16) - Y` (`+0x3A`) -- draw layer, then bias,
then descending screen Y.

`CheckActorCollisions` does the per-frame pairwise collision pass.
**PROVEN** by decompile: each actor has two `ActorCollisionBox` slots
(`Actor.aCollisionBoxes`, `include/actor.h`) and a matching 2-entry
callback array (`Actor.apfnCollisionCallback`). On AABB overlap, gated
on `g_GameModeStackContext.dwCurrentGameMode == Overworld`, it calls
each actor's callback for the overlapping box slot with the other
actor as the argument.

Both are kept as assembly (`asm/check_actor_collisions.s`,
`asm/sort_actors_by_depth.s`): the available compilers are Thumb-only (see
"ARM-mode code" in [`../compiler.md`](../compiler.md)).
