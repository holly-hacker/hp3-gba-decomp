@ Named RAM/ROM addresses referenced (via `ldr rX, =SYMBOL`-style
@ literal-pool loads) from asm/*.s files, so the source reads by
@ meaning rather than raw hex. Assembles to identical bytes either way
@ (.set defines a plain absolute constant) -- purely a readability aid,
@ not something the build depends on for correctness.
@
@ US-side values. Symbols also used from a JP-side extracted file (the
@ MT19937 ones below) have a matching, differently-valued definition in
@ ram_symbols.jp.inc -- that's what lets the identical .s source in
@ e.g. asm/rng/mt19937_regenerate.s assemble correctly for both ROMs.
@ The dialog-text-engine symbols have no JP counterpart at all (that
@ engine isn't present in the JP ROM -- see docs/formats/text.md).

@ --- crt0 (see asm/crt0.s) ---
.set gSystemStackTop,  0x03007EA0  @ top of the AGB system-mode stack
.set gIrqStackTop,     0x03007FA0  @ top of the AGB IRQ-mode stack
.set gIntrVectorPtr,   0x03007FFC  @ BIOS-called user interrupt handler pointer

@ --- Interrupts / VBlank state (see include/vblank.h) ---
@ Set by InitInterruptSystem to &g_VBlankState; read by every interrupt
@ handler (HandleVBlankInterrupt, HandleHBlankInterrupt,
@ HandleTimer0Interrupt, HandleTimer3OrSerialInterrupt,
@ HandleVCountInterrupt), not just vblank-related code -- Mt19937AutoSeed
@ also reads its dwVBlankCount field for entropy, but that's a secondary
@ consumer, not what the struct is for.
.set g_pVBlankState, 0x0300356C
.set g_VBlankState, 0x03003530  @ the object g_pVBlankState is set to point at

@ Sticky software copy of acked hardware IF bits, ORed by every interrupt
@ handler after acking its own bit in IF. See include/vblank.h.
.set g_wPendingIntrFlags, 0x030037A4
@ Reentrancy guard for HandleVBlankInterrupt; body only runs while this
@ reads back as 1. See include/vblank.h.
.set g_dwVBlankIntrNestCount, 0x030037A8
@ OAM DMA half-toggle; see include/vblank.h.
.set g_bOamDmaHalfToggle, 0x030037AC
@ Forces one extra sub_08007130 call this vblank; see include/vblank.h.
.set g_bForcePendingBgWritesFlush, 0x03002038

@ --- OAM shadow buffer, see include/oam.h ---
.set g_pOamShadowBuffer, 0x03003FE8
.set g_pOamDmaShadowBuffer, 0x03003FEC
.set g_aOamShadowBufferA, 0x03003FF0
.set g_aOamShadowBufferB, 0x030047F0
.set g_bOamEntryCount, 0x03004FF0
.set g_bOamEntryCountPrev, 0x03004FF1
.set g_bAffineSlotHighWaterMark, 0x03004FF2  @ highest allocated affine slot index + 1; see AllocAffineSlot
.set g_abAffineSlotUsed, 0x03004FF3          @ u8[32], one per affine hardware slot; see AllocAffineSlot/FreeAffineSlot
.set g_aObjAffineSetSource, 0x03005014       @ ObjAffineSource[32] (8-byte stride), fed to bios_ObjAffineSet by sub_08030140

@ --- Interrupt dispatch (see src/interrupts/) ---
.set gIntrTable, 0x03003570  @ 13 x u32 function-pointer slots, refreshed from a ROM
                              @ template by InitInterruptSystem; dispatched by IntrMain
.set gIntrHandlerIwram, 0x030035A4  @ 0x200-byte IWRAM buffer InstallInterruptHandler
                                     @ CpuSets the live handler code into; gIntrVectorPtr
                                     @ points here
.set g_pTimer2DebugPc, 0x030015A0  @ code ptr: IntrMain stores [sp,#0x14] here on a Timer 2 IRQ
                                     @ (saved lr per the BIOS IRQ frame, unverified); read by
                                     @ HandleTimer2Interrupt

@ --- main / game-mode stack (see src/main.c) ---
.set g_dwGameModeFlags,   0x03003B44  @ u32: broad flags word read/written across
                                       @ overworld/room/cutscene transitions and
                                       @ TickGameModeStack; individual bits
                                       @ unconfirmed
.set g_dwFrameSyncTarget, 0x03003B48  @ u32: frame-pacing target set once by AgbMain,
                                       @ consumed only by WaitForVBlank

@ --- Battle system (see docs/memory-map/battle.md) ---
.set g_pFightState,      0x030024E8  @ FightState *, the active battle's state
.set g_aPartyMasterStats,0x030024EC  @ BattleFighter[], 0x48 stride, by FighterType
.set g_bDefeatWarpParam, 0x03002748  @ byte
.set g_bSpellMissStreak, 0x03002749  @ byte: consecutive-miss streak breaker
.set g_nLastDamage,      0x0300274A  @ u16: last computed attack/status damage
.set g_bLastTargetIndex, 0x0300274C  @ byte: last attack's target fighter index
.set g_effectStaging,        0x03002750  @ EffectStaging: battle-effect staging area, see TriggerBattleEffect
.set g_dwBattleRewardFlagsSnapshot, 0x03002618  @ u32: FightState->bBonusRewardFlags copy, see RollBattleItemDrops
.set g_anFaintedRosterIndices, 0x030026D8  @ s32[4]: fainted fighters' roster indices this battle, sentinel -1
.set g_saveStateBlock, 0x03003180  @ live save-adjacent state (money, playtime, flags, ...); doc-level array at +0x10
.set g_aBgScrollState,   0x03001E80  @ u32[]; [0x25] == 0x03001F14
.set g_PrevGameModeCtx, 0x03003F3C  @ GameModeStackContext, 0x24 bytes; see docs/memory-map/game_modes.md
.set g_abBgPriority,     0x03003F8C  @ u8[]; [4] == 0x03003F90
.set g_nBattleXpReward, 0x0300260E  @ u16: XP earned this battle, one pool shared by the whole party
.set g_nBattleGoldReward, 0x03002610  @ u16: Sickles earned this battle; also the scratch amount for gold reward grants
.set g_abItemQuantities, 0x030037B0  @ u8[132]: owned count per item id, see docs/formats/save.md
.set g_bSelectedFighterSlot_candidate, 0x03002660  @ u32: fighter slot with the "selected" sprite scale applied
.set g_apFighterObjects_candidate, 0x03002668  @ Object*[7]; one slot per active BattleFighter
.set g_pBattleMessageIconObject_candidate, 0x03002684  @ Object *: icon shown alongside ShowBattleMessage's text
.set g_BattleMessageIconState_candidate, 0x03002688  @ {byte bIndex (sentinel 0xFF=none), byte bCountdown (2-frame delay), pad[2], u32 dwParam}
.set g_bCurrentRoomId,   0x03003B50  @ byte: current room/map id
.set g_GameModeStackContext, 0x03003EF4  @ {dwCurrentGameMode, dwCurrentGameModeArg1, dwCurrentGameModeArg2, dwCurrentGameModeArg3, ...}
.set g_dwPendingGameMode, 0x03003F18  @ GameMode: mirrors g_GameModeStackContext's layout for the not-yet-applied mode; see docs/memory-map/game_modes.md
.set g_dwPendingGameModeArg1, 0x03003F1C  @ u32: g_dwPendingGameMode's arg1, i.e. dwCurrentGameModeArg1's pending counterpart
.set g_dwPendingGameModeArg3, 0x03003F24  @ u32: g_dwPendingGameMode's arg3, i.e. dwCurrentGameModeArg3's pending counterpart
.set g_dwTickCount, 0x03003F60  @ u32: incremented once per TickGameModeStack call; see docs/memory-map/game_modes.md

@ --- Controller input (see docs/memory-map/input.md; UpdateKeyInput/
@ ResetKeyInput, 0x080254A8/0x080258F8) ---
.set g_wKeysHeld,         0x030034EC  @ u16: current held-key bitmask (standard GBA KEYINPUT bit
                                       @ order), updated once per frame by UpdateKeyInput; also
                                       @ folded into Mt19937AutoSeed's seed as a cheap entropy
                                       @ source (see docs/memory-map/rng.md) -- that's not what the
                                       @ address is for
.set g_wKeysHeldPrevious, 0x030034EE  @ u16: g_wKeysHeld from the previous frame's update
.set g_wKeysPressed,      0x030034F0  @ u16: keys newly pressed this frame (currentHeld &
                                       @ ~previousHeld); bit 0x01 (A) tested by
                                       @ TickBattleTurnStateMachine's message-wait fast-forward
                                       @ check, bits 0x10/0x20 (Right/Left) read elsewhere -- see
                                       @ docs/memory-map/input.md, docs/formats/folio_bruti.md,
                                       @ docs/memory-map/battle-ui.md
.set g_wKeysReleased,     0x030034F2  @ u16: keys newly released this frame (previousHeld & ~currentHeld)
.set g_wInputDisabled,    0x030034F4  @ u16: nonzero forces all key state above (and the per-player
                                       @ arrays below) to 0 every frame instead of reading KEYINPUT
.set g_awPlayerKeysHeld,          0x030034F6  @ u16[2]: per-player held-key masks, serial-link input path
.set g_awPlayerKeysHeldPrevious,  0x030034FA  @ u16[2]: previous-frame counterpart of the above
.set g_awPlayerKeysPressed,       0x030034FE  @ u16[2]: per-player newly-pressed masks
.set g_awPlayerKeysReleased,      0x03003502  @ u16[2]: per-player newly-released masks
.set g_awLinkKeysReceived,        0x03005A0C  @ u16[2]: per-player key masks received over the link cable
.set g_LinkPlayerState,           0x03005A24  @ LinkPlayerState: serial-link session block; see include/link.h

@ --- Overworld wandering monsters (see include/overworld.h) ---
.set g_bTouchedMonsterRecordCount, 0x03003B70  @ byte: queued (encounter id, kind) pair count
.set g_abTouchedMonsterRecords,    0x03003B74  @ u8[20]: 5 x 4-byte touched-monster records
.set g_pTouchedWanderingMonster,    0x03003B88  @ Object *: armed wandering-monster object

@ --- Overworld control slots and pause menu (see include/overworld.h) ---
.set g_OverworldControlState,     0x03003358  @ OverworldControlState: 2 x 16-byte control slots, then slot count (+0x20) and index (+0x21)
.set g_bControlSlotTicks_candidate, 0x03003B58  @ byte: bumped by TickOverworldControlSlots_candidate, zeroed on room entry, never read
.set g_dwPauseMenuLocked,          0x03003B60  @ u32: nonzero blocks Start/Select menus (SetPauseMenuLocked)
.set g_dwPauseMenuCooldown,        0x03003B6C  @ u32: frames until Start/Select may open a menu again; 4 after init/menu open
.set g_dwRoomChainRanThisFrame_candidate, 0x03001DF0  @ u32: set to 1 by RespawnRowAndRunChain_candidate while it runs a room chain; cleared by
                                                       @ HandleOverworldPauseMenuInput each frame, which skips the menu check while it is set
.set g_bUnk03005E18, 0x03005E18  @ u8: set to 1 when the overworld pushes a pause menu; RestoreRoomObjectState sets it to 1 at entry and 0 at exit

@ --- Dialog/UI text engine (US only) ---
.set gTextRenderState,       0x03003110  @ struct: font descriptor pointers (+0x00/+0x04) and other
                                         @ text-rendering fields (e.g. +0x11 = line height); not
                                         @ fully mapped, see draw_text_line.s/print_text_box.s
.set sTextMacroTable,        0x03003170  @ ROM: pointer table for 0x40-prefixed escape/macro codes
.set gDialogTextBlobBase,    0x030033C0  @ active language blob's base pointer (0 = none installed)
.set gDialogTextOffsetTable, 0x030033C4  @ pointer to the active blob's per-string-ID u32[] offset table
.set gDialogTextTreeNodes,   0x030033C8  @ pointer to the active blob's Huffman tree node table
.set gDialogTextScratchBuf,  0x03005D08  @ pointer to the fixed 0x400-byte decode scratch buffer
.set gCurrentLanguage,       0x03005D0C  @ byte: language ID (0-7) set by SetLanguage
.set gLocaleThousandsSep,    0x03005D0D  @ byte: locale-specific number-formatting separator
.set g_dwMainMenuTextCursor, 0x03005DB0  @ u32: text tile cursor returned by the main menu's copyright text; see include/main_menu.h
.set g_MainMenuState,       0x03005DB8  @ MainMenuState: {Object *pCursorObject; u32 dwLoadGameAvailable; s32 nPaletteEffectSlot_candidate}; see include/main_menu.h
.set g_ScanlineEffectState,  0x03005E20  @ pending flag, active index, 19 live entries; see docs/memory-map/scanline_effects.md
.set g_ScanlineEffectStaging, 0x03005F58  @ 19 staged entries, committed to the live table by CommitScanlineEffects
.set sDialogLanguageTable,   0x0806BD78  @ ROM: 8 x u32, one string-table blob pointer per language

@ --- Heap allocator (see docs/memory-map/heap.md and include/mem.h) ---
.set gMemPool,      0x03003EE0  @ MemPool[]; only pool 0 (index 0) is ever registered
.set gMemPoolCount, 0x03003EF0  @ u32: live pool count, incremented by InitMemoryPool

@ --- Object pool (see docs/memory-map/heap.md and include/mem.h) ---
.set g_dwObjectListActive_candidate, 0x030017A0
.set g_pSortObjectsIwram,            0x0300194C  @ IWRAM copy of SortObjectsByDepth_candidate
.set g_pCheckObjectCollisionsIwram,  0x03001A10  @ IWRAM copy of CheckObjectCollisions_candidate
.set g_ObjectPoolState,               0x03001C08  @ {void *pBuffer; void *pFreeListHead;}; pBuffer is the
                                                    @ 0x7968-byte AllocZeroed'd buffer BuildFreeList carves up
.set sFreeObjectListHead,            0x03001C0C
.set g_pObjectPoolAuxBuffer,         0x03001DBC  @ void *: 0x104-byte AllocZeroed'd buffer
.set g_dwUnk03001DC0,                0x03001DC0  @ FreeObject calls ReleaseObjectOffscreenVramTiles when this == 1
.set g_dwUnk03001DC4,                0x03001DC4  @ zeroed by InitObjectPool; see include/mem.h
.set g_ActiveObjectListState,        0x030015B0  @ {ListNode *pHead; ListNode *pUnk4;}; see include/mem.h

@ --- Resource cache / particle emitters (see docs/formats/graphics.md and
@ docs/formats/battle_scripts.md's TickParticleEmitters note) ---
.set g_aResourceCache,                    0x03005114  @ ResourceCacheSlot[15]
.set g_pParticleEmitterFreeListHead,      0x030051B0  @ ListNode *
.set g_wActiveParticleEmitterCount,       0x030051A0  @ u16
.set g_pParticleEmitterActiveListHead,    0x03005198  @ ListNode *

@ --- MT19937 PRNG (see docs/memory-map/rng.md) ---
@ Names mostly match jogotu's BizHawk script naming, cross-checked
@ against our own disassembly there. That script tracks cursor 1 only;
@ cursor 2 is undocumented by it and comes from this project's own
@ disassembly (see rng.md for what's confirmed and what's still open
@ about it).
.set gMt19937LastRollByte,       0x03005574  @ low byte of the last tempered value (purpose unconfirmed)
.set gMt19937DrawIndex,          0x03005578  @ cursor 1: running count of numbers drawn
.set gMt19937StatePtr,           0x0300557C  @ base of the 624-word MT state array
.set gMt19937CurPtr,             0x03005580  @ cursor 1: pointer into the state array
.set gMt19937RemainingIndices,   0x03005584  @ cursor 1: untempered words left before regenerating
.set gMt19937CurPtr2,            0x03005588  @ cursor 2: pointer into the state array
.set gMt19937RemainingIndices2,  0x0300558C  @ cursor 2: untempered words left before regenerating
.set gMt19937AutoSeedCallCount,  0x03005590  @ increments each AutoSeed call (purpose unconfirmed)
.set gMt19937SeedValue,          0x03005594  @ accumulating seed value (SetSeed/AutoSeed)
.set g_saveHeader,               0x03005598  @ SaveHeader; the live RAM copy, SaveManager.header; see docs/formats/save.md
.set g_CameraPosition_candidate, 0x03005640  @ CameraFocusOffset: world-space camera origin used for object visibility

@ --- Room load / room script state (see include/room.h) ---
.set g_bRoomScriptYieldOpcode,        0x03001DE9  @ u8: opcode a running room script yielded on
.set g_wRoomResourceFlags_candidate,  0x03001DDC  @ u16: bit 0 = the room also has a second object/switch row
.set g_dwScanlineBandActiveMask,      0x030022E0  @ u32: bit n set = scanline band slot n is active
.set g_dwRoomScriptRunState,          0x0300279C  @ u32: room script run state; InitializeOverworld resets 4 to 0 and only resumes a chain in state 2
.set g_abQuestEventState,             0x030027A0  @ u8[]: quest event state bytes, see docs/formats/save.md
.set g_dwOverworldMonstersDisabled,   0x03002614  @ u32: nonzero suppresses wandering-monster spawns
.set g_bPendingRoomScriptChain,       0x0300260C  @ u8: switch-state chain to walk on a resume transition
.set g_bPendingRoomScriptRow,         0x0300260D  @ u8: object row to respawn on a resume transition
.set g_bPendingQuestStateOverride_candidate, 0x03003B5A  @ u8: 0xFF = none; else copied into quest state 0 on room entry
.set g_dwRoomBgFlag_candidate,        0x03003B5C  @ u32: set to 1 by many rooms while loading; also read by sub_0802E6FC
.set g_dwPendingCameraFocusFlag,      0x03003FD4  @ u32: cleared on room entry

@ --- Room-script VM (see include/room_script.h) ---
.set g_bRoomScriptCurrentRow,          0x03001DDE  @ u8: chain the VM is walking
.set g_pRoomScriptYieldContinuation,   0x03001DE0  @ u32 *: record to resume at after a yield, or 0
.set g_pRoomScriptNextRecord,          0x03001DE4  @ u32 *: record following the one being dispatched
.set g_bRoomScriptCallStackDepth,      0x03001DE8  @ u8: nested chain calls in flight
.set g_pRoomSwitchStateObjectTable,    0x03001DFC  @ RoomScriptTable *: current room's chain offset table
.set g_aRoomScriptCallStack,           0x03001E00  @ RoomScriptCallFrame[]: saved callers, indexed by depth
.set g_bRoomScriptPendingChain,         0x030028A0  @ u8: chain a handler asked to jump to; 0xFF = none

@ --- Overworld object tracking (see include/overworld.h) ---
.set g_pPlayerObject,        0x03003380  @ Object *: the player's overworld object
.set g_aCameraEffects_candidate, 0x03002090  @ CameraEffect[2]: one 0x2C-byte record per control slot
.set g_aCameraFocusSlots,    0x030020E8  @ CameraFocusSlot[2]: 0x38 bytes each
.set g_aCameraFollowOffsets, 0x03002158  @ s32[2][2]: per-slot (X, Y) offset set by SetCameraFollowTarget_candidate
.set g_pPendingCameraFocus_candidate, 0x03003FD8  @ void *: argument RestorePendingCameraFocus_candidate is called with
.set g_pFollowerObject0, 0x03003384  @ Object *: first party follower, NULL while empty
.set g_pFollowerObject1, 0x03003388  @ Object *: second party follower, NULL while empty
.set g_bPartyCharId0, 0x0300338C  @ u8: character id of the party leader
.set g_bPartyCharId1, 0x0300338D  @ u8: character id of the first follower
.set g_bPartyCharId2, 0x0300338E  @ u8: character id of the second follower
.set g_abRoomScriptExitParams_candidate, 0x0300337D  @ u8[2]: filled by the dialog-close and return-to-overworld opcodes
.set g_DialogState_candidate, 0x03002E88  @ DialogState; see include/dialog.h
