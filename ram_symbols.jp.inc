@ Named RAM addresses referenced from asm/*.s files -- see
@ ram_symbols.us.inc for the full explanation. JP-side values for the
@ MT19937 symbols shared with US-side extracted files (the dialog-text
@ symbols aren't defined here at all -- that engine isn't present in
@ the JP ROM).

@ --- crt0 (see asm/crt0.s) ---
.set gSystemStackTop,  0x03007EA0
.set gIrqStackTop,     0x03007FA0
.set gIntrVectorPtr,   0x03007FFC

@ --- Interrupts / VBlank state (see include/vblank.h) ---
.set g_pVBlankState, 0x030035CC
.set gIntrTable,      0x030035D0  @ 13 x u32 handler slots dispatched by IntrMain
.set g_wPendingIntrFlags, 0x03003804  @ see ram_symbols.us.inc
.set g_pTimer2DebugPc, 0x030015A0  @ see ram_symbols.us.inc

@ --- Object pool and active-object list (see include/mem.h) ---
.set g_dwObjectListActive_candidate, 0x030017A0
.set g_pSortObjectsIwram,            0x0300194C
.set g_pCheckObjectCollisionsIwram,  0x03001A10
.set g_ActiveObjectListState, 0x030015B0
.set g_ObjectPoolState,       0x03001C08
.set g_pObjectPoolAuxBuffer,  0x03001DBC
.set g_dwUnk03001DC0,         0x03001DC0
.set g_dwUnk03001DC4,         0x03001DC4

@ --- main / game-mode stack (see src/main.c) ---
.set g_dwGameModeFlags,   0x03003BA4  @ see ram_symbols.us.inc
.set g_dwFrameSyncTarget, 0x03003BA8  @ see ram_symbols.us.inc

@ --- Battle state (see include/battle.h) ---
.set g_pFightState,   0x030024E8
.set g_effectStaging, 0x03002750

@ --- Controller input (see docs/memory-map/input.md) ---
.set g_wKeysHeld,  0x0300354C  @ u16: current held-key bitmask, see
                                @ ram_symbols.us.inc/docs/memory-map/input.md


@ --- Save state / playtime ---
.set g_saveStateBlock, 0x030031E0
@ --- MT19937 PRNG (see docs/memory-map/rng.md) ---
.set gMt19937LastRollByte,       0x030055D4
.set gMt19937DrawIndex,          0x030055D8
.set gMt19937StatePtr,           0x030055DC
.set gMt19937CurPtr,             0x030055E0
.set gMt19937RemainingIndices,   0x030055E4
.set gMt19937CurPtr2,            0x030055E8
.set gMt19937RemainingIndices2,  0x030055EC
.set gMt19937AutoSeedCallCount,  0x030055F0
.set gMt19937SeedValue,          0x030055F4
.set g_CameraPosition_candidate, 0x030056A0  @ CameraFocusOffset: world-space camera origin used for object visibility

@ --- Overworld wandering monsters (see include/overworld.h) ---
.set g_bTouchedMonsterRecordCount, 0x03003BD0  @ byte: queued (encounter id, kind) pair count
.set g_abTouchedMonsterRecords,    0x03003BD4  @ u8[20]: 5 x 4-byte touched-monster records
.set g_pTouchedWanderingMonster,    0x03003BE8  @ Object *: armed wandering-monster object

@ --- Overworld control slots and pause menu (see include/overworld.h) ---
.set g_dwGameModeFlags,            0x03003BA4  @ u32: broad game-mode flags word
.set g_OverworldControlState,     0x030033B8  @ OverworldControlState: 2 x 16-byte control slots, then slot count (+0x20) and index (+0x21)
.set g_bControlSlotTicks_candidate, 0x03003BB8  @ byte: bumped by TickOverworldControlSlots_candidate, zeroed on room entry, never read
.set g_dwPauseMenuLocked,          0x03003BC0  @ u32: nonzero blocks Start/Select menus (SetPauseMenuLocked)
.set g_dwPauseMenuCooldown,        0x03003BCC  @ u32: frames until Start/Select may open a menu again; 4 after init/menu open
