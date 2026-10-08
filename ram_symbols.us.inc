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

@ --- Statically linked RAM sections (see include/hw/mem.h and ClearWorkRam) ---
.set g_EwramSectionStart,     0x02000000
.set g_EwramSectionEnd,       0x020027F8  @ ClearWorkRam zeroes EWRAM from here
.set g_abEwramHeap,          0x02002800  @ InitHeap's pool 0, up to the end of EWRAM
.set g_IwramSectionStart,     0x03000000  @ IWRAM image kramInstall copies from ROM
.set IwramTimer1Handler,      0x03000004  @ gIntrTableTemplate's timer 1 handler, in that image
.set g_IwramSectionEnd,       0x03001598  @ end of that image; ClearWorkRam zeroes from here

.set g_pTimer2DebugPc,        0x030015A0  @ code ptr: IntrMain stores [sp,#0x14] here on a Timer 2 IRQ
                                          @ (saved lr per the BIOS IRQ frame, unverified); read by
                                          @ HandleTimer2Interrupt
.set g_ActiveObjectListState, 0x030015B0  @ {ListNode *pHead; ListNode *pUnk4;}; see include/hw/mem.h

@ --- Per-tick object queues (see include/hw/mem.h and TickObjectList) ---
.set g_apOamQueue,             0x030015B8  @ Object *[0x69]: onscreen objects drawn in depth order
.set g_dwOamQueueCount,        0x0300175C
.set g_apSpriteFrameQueue,     0x03001760  @ Object *[15]: visible objects with sprite cells
.set g_bSpriteFrameQueueCount, 0x0300179C  @ u8

.set g_dwObjectListActive_candidate, 0x030017A0
.set g_apCollisionQueue,             0x030017A4  @ Object *[0x69]: objects awaiting the pairwise check
.set g_dwCollisionQueueCount,        0x03001948

@ --- Object pool (see docs/memory-map/heap.md and include/hw/mem.h) ---
.set g_pSortObjectsIwram,            0x0300194C  @ IWRAM copy of SortObjectsByDepth
.set g_pCheckObjectCollisionsIwram,  0x03001A10  @ IWRAM copy of CheckObjectCollisions
.set g_ObjectPoolState,              0x03001C08  @ ObjectPoolState, 0x1B4 bytes; see include/hw/mem.h
.set g_pObjectPoolAuxBuffer,         0x03001DBC  @ void *: 0x104-byte AllocZeroed'd buffer
.set g_dwObjectListTicked_candidate, 0x03001DC0  @ set to 1 by TickActiveObjects, never cleared; gates FreeObject's VRAM tile release
.set g_dwUnk03001DC4,                0x03001DC4  @ zeroed by InitObjectPool; see include/hw/mem.h
.set g_adwRoomObjUnkACState,         0x03001DD0  @ u32[3]: zeroed by the type 10 and 12 room object constructors

.set g_wRoomResourceFlags_candidate, 0x03001DDC  @ u16: bit 0 = the room also has a second object/switch row

@ --- Room-script VM (see include/overworld/room_script.h) ---
.set g_bRoomScriptCurrentRow,        0x03001DDE  @ u8: chain the VM is walking
.set g_pRoomScriptYieldContinuation, 0x03001DE0  @ u32 *: record to resume at after a yield, or 0
.set g_pRoomScriptNextRecord,        0x03001DE4  @ u32 *: record following the one being dispatched
.set g_bRoomScriptCallStackDepth,    0x03001DE8  @ u8: nested chain calls in flight

.set g_bRoomScriptYieldOpcode,            0x03001DE9  @ u8: opcode a running room script yielded on
.set g_pRoomTableBuffer,                  0x03001DEC  @ RoomBlobHeader *: 0x2200-byte buffer holding the room's runtime tables
.set g_dwRoomChainRanThisFrame_candidate, 0x03001DF0  @ u32: set to 1 by RespawnRowAndRunChain_candidate while it runs a room chain; cleared by
                                                      @ HandleOverworldPauseMenuInput each frame, which skips the menu check while it is set

@ --- Room-script VM (see include/overworld/room_script.h) ---
.set g_pRoomObjectTable,            0x03001DF4  @ RoomBlobTable *: per-column, per-row tile records
.set g_pRoomWarpTriggerTable,       0x03001DF8  @ RoomBlobTable *: per-column warp trigger lists
.set g_pRoomSwitchStateObjectTable, 0x03001DFC  @ RoomScriptTable *: current room's chain offset table
.set g_aRoomScriptCallStack,        0x03001E00  @ RoomScriptCallFrame[]: saved callers, indexed by depth

.set g_aBgScrollState, 0x03001E80  @ u32[]; [0x25] == 0x03001F14

@ Forces one extra sub_08007130 call this vblank; see include/hw/vblank.h.
.set g_bForcePendingBgWritesFlush,               0x03002038
.set g_dwRiddikulusMinigameScriptFlag_candidate, 0x03002040  @ u32: set by StartMinigame
.set g_Riddikulus,                               0x03002048  @ RiddikulusState
.set g_dwHippogriffForceOverworldExit,           0x03002084  @ u32: set by StartMinigame
.set g_pHippogriffGlide,                         0x03002088  @ HippogriffGlideState *: allocated for the minigame's duration
.set g_aCameraEffects_candidate,                 0x03002090  @ CameraEffect[2]: one 0x2C-byte record per control slot
.set g_aCameraFocusSlots,                        0x030020E8  @ CameraFocusSlot[2]: 0x38 bytes each
.set g_aCameraFollowOffsets,                     0x03002158  @ s32[2][2]: per-slot (X, Y) offset set by SetCameraFollowTarget_candidate
.set g_bBgTileAnimationCount,                    0x03002168  @ u8: number of registered BG tile animations
.set g_aBgTileAnimations,                        0x0300216C  @ BgTileAnimEntry[4]: 0x10 bytes each; size inferred from the span up to g_apBgTileAnimationBuffers
.set g_apBgTileAnimationBuffers,                 0x030021AC  @ void *[4]: decoded tile buffer of each BG tile animation

@ --- Dialog/UI text engine (US only) ---
.set g_DebugMenuMainState,            0x030021C0  @ DebugMenuMainState: {Object *pCursorObject; u32 dwSelection}; see include/menu/debug_menu.h
.set g_DebugLevelAndQuestSelectState, 0x030021C8  @ DebugLevelAndQuestSelectState; see include/menu/debug_menu.h
.set g_DebugMapSelectState,           0x030021E8  @ DebugMapSelectState; see include/menu/debug_menu.h
.set g_DebugCharacterSelectState,     0x030021F8  @ DebugCharacterSelectState; see include/menu/debug_menu.h
.set g_DebugPortraitsState,           0x03002210  @ DebugPortraitsState: {Object *pPortraitObject; u32 dwSelection}; see include/menu/debug_menu.h
.set g_DebugSoundTestState,           0x03002218  @ DebugSoundTestState; see include/menu/debug_menu.h
.set g_DebugCollectorCardsState,      0x03002238  @ DebugCollectorCardsState: {Object *pCardObject; u32 dwSelection}; see include/menu/debug_menu.h

.set g_abOpenedChestFlags,         0x03002240  @ u8[32]: one bit per chest flag id; set when the chest is opened, saved with the game
.set g_LoadingScreenState,         0x03002260  @ LoadingScreenState; see include/menu/loading_screen.h
.set g_dwLoadingScreenBgRow,       0x0300227C  @ u32: BG2 tile row of the loading screen panel
.set g_aColorCycles,               0x03002280  @ ColorCycle[12]; see include/graphics/palette.h
.set g_dwColorCycleActiveMask,     0x030022E0  @ u32: bit n set = color cycle slot n was activated
.set g_dwColorCycleCount,          0x030022E4  @ u32: color cycle slots handed out since the last reset
.set g_pPaletteWorkBuffer,        0x030022EC  @ u16 *: 0x400-byte BG+OBJ palette work buffer, allocated by InitGammaPalette
.set g_dwObjPaletteQueueCount,     0x030022F0  @ u32: queued OBJ palette loads (25 max)
.set g_dwPaletteEffectCount,       0x030022F4  @ u32: active palette effects
.set g_aPaletteEffects,            0x030022F8  @ PaletteEffect[12]; see include/graphics/palette.h
.set g_PaletteState,              0x030024B0  @ PaletteState; see include/graphics/palette.h
.set g_pFightState,                 0x030024E8  @ FightState *, the active battle's state
.set g_aPartyMasterStats,           0x030024EC  @ BattleFighter[], 0x48 stride, by FighterType
.set g_bPendingRoomScriptChain,     0x0300260C  @ u8: switch-state chain to walk on a resume transition
.set g_bPendingRoomScriptRow,       0x0300260D  @ u8: object row to respawn on a resume transition
.set g_nBattleXpReward,             0x0300260E  @ u16: XP earned this battle, one pool shared by the whole party
.set g_nBattleGoldReward,           0x03002610  @ u16: Sickles earned this battle; also the scratch amount for gold reward grants
.set g_dwOverworldMonstersDisabled, 0x03002614  @ u32: nonzero suppresses wandering-monster spawns

@ --- Battle system (see docs/memory-map/battle.md) ---
.set g_dwBattleRewardFlagsSnapshot,        0x03002618  @ u32: FightState->bBonusRewardFlags copy, see RollBattleItemDrops
.set g_bSelectedFighterSlot_candidate,     0x03002660  @ u32: fighter slot with the "selected" sprite scale applied
.set g_apFighterObjects_candidate,         0x03002668  @ Object*[7]; one slot per active BattleFighter
.set g_pBattleMessageIconObject_candidate, 0x03002684  @ Object *: icon shown alongside ShowBattleMessage's text
.set g_BattleMessageIconState_candidate,   0x03002688  @ {byte bIndex (sentinel 0xFF=none), byte bCountdown (2-frame delay), pad[2], u32 dwParam}
.set g_anFaintedRosterIndices,             0x030026D8  @ s32[4]: fainted fighters' roster indices this battle, sentinel -1
.set g_dwVictoryUnk26E8,                    0x030026E8  @ u32: zeroed by InitializeVictoryScreen; no reader found
.set g_dwVictoryUnk26EC,                    0x030026EC  @ u32: 0x78 after InitializeVictoryScreen; no reader found
.set g_dwVictoryXpRemaining,                0x030026F0  @ u32: XP still to be counted up on the victory screen, see include/battle/victory_screen.h
.set g_dwVictoryUnk26F4,                    0x030026F4  @ u32: zeroed by InitializeVictoryScreen
.set g_dwVictoryUnk26F8,                    0x030026F8  @ u32: zeroed by InitializeVictoryScreen
.set g_dwVictoryUnk26FC,                    0x030026FC  @ u32: zeroed by InitializeVictoryScreen
.set g_abVictoryPartySlots,                 0x03002700  @ u8[3]: party stats slot shown per portrait position, see include/battle/victory_screen.h
.set g_pVictoryBg2Tilemap,                  0x03002704  @ void *: BG2 graphic (LoadBgGraphicTiles_candidate result), partly copied per party member
.set g_pVictoryBg1Tilemap,                  0x03002708  @ void *: BG1 graphic (LoadBgGraphicTiles_candidate result), partly copied per party member
.set g_wVictoryTextTileCursor,              0x0300270C  @ u16: next free text tile of the victory screen
.set g_wVictoryUnk2734,                     0x03002734  @ u16: zeroed by InitializeVictoryScreen
.set g_bDefeatWarpParam,                   0x03002748  @ byte
.set g_bSpellMissStreak,                   0x03002749  @ byte: consecutive-miss streak breaker
.set g_nLastDamage,                        0x0300274A  @ u16: last computed attack/status damage
.set g_bLastTargetIndex,                   0x0300274C  @ byte: last attack's target fighter index
.set g_effectStaging,                      0x03002750  @ EffectStaging: battle-effect staging area, see TriggerBattleEffect
.set g_bReviveInsertCount_candidate,        0x03002773  @ u8: incremented by ReviveFighter_candidate when the revived fighter is inserted at or before the active one; no reader found

.set g_dwRoomScriptRunState,    0x0300279C  @ u32: room script run state; InitializeOverworld resets 4 to 0 and only resumes a chain in state 2
.set g_abQuestEventState,       0x030027A0  @ u8[]: quest event state bytes, see docs/formats/save.md
.set g_bRoomScriptPendingChain, 0x030028A0  @ u8: chain a handler asked to jump to; 0xFF = none

@ --- Serve Pumpkin Juice minigame (see include/minigame/serve_pumpkin_juice.h) ---
.set g_dwCreditsScrollRow,    0x030028A8  @ u32: last credits text row the scroll reached
.set g_dwCreditsLine,         0x030028AC  @ u32: next credits text line to draw
.set g_dwCreditsTileCursor,   0x030028B0  @ u32: next free credits text tile
.set g_pLinearCutsceneText,   0x030028B4  @ u8 *: unread remainder of the cutscene's text
.set g_pLinearCutsceneObject, 0x030028B8  @ Object *; see include/cutscene/linear_cutscene.h
.set g_dwLinearCutsceneIndex, 0x030028BC  @ u32: GameMode - Credits

.set g_pMenuCursorEmitter, 0x030028C0  @ ParticleEmitter *: emitter of the cursor object built by sub_0801D940(4)

@ --- IWRAM-installed decompression codecs (see docs/formats/graphics.md's
@ "resource-decompression dispatcher") ---
.set g_pDecompressLzRleEntry,   0x030028CC  @ DecompressFunc: = g_pDecompressLzRleIwram
.set g_pDecompressGammaLzEntry, 0x030028D0  @ DecompressFunc: = g_pDecompressGammaLzIwram
.set g_pDecompressLzRleIwram,   0x030028D4  @ u8[0x1F8]: IWRAM copy of DecompressLzRle
.set g_pDecompressGammaLzIwram, 0x03002ACC  @ u8[0x33C]: IWRAM copy of DecompressGammaLz

.set g_pMenuCursorObject,                              0x03002E08  @ Object *: cursor object created by BeginMenuScreen; see include/menu/main_menu.h
.set g_dwHarryVsDementorsMinigameScriptFlag_candidate, 0x03002E10  @ u32: set by StartMinigame
.set g_HarryVsDementors,                               0x03002E18  @ HarryVsDementorsState
.set g_DialogState_candidate,                          0x03002E88  @ DialogState; see include/menu/dialog.h
.set g_pDialogMacroExpandBuffer,                       0x03002EA8  @ u8 *: 0x400-byte buffer, allocated by InitDialogBox
.set g_awSavedBgPalette0,                              0x03002EAC  @ u16[16]: BG palette bank 0 saved by InitializeDialogue and InitializeLoadingScreen, restored by their exits
.set g_adwSavedBgPriority,                             0x03002ED0  @ u32[2]: BG0/BG1 priority saved by InitializeDialogue, restored by ExitDialogue
.set g_dwDialogTextId,                                 0x03002ED8  @ u32: dialog string id of the line being shown
.set g_dwDialogTextEntry,                              0x03002EDC  @ u32: first word of the dialog text table entry for g_dwDialogTextId
.set g_pDialogBoxTilemap,                              0x03002EE0  @ void *: tilemap of the dialog box BG graphic
.set g_pDialogBoxObject,                               0x03002EE4  @ Object *: dialog box panel sprite
.set g_dwDialogBoxY,                                   0x03002EE8  @ u32: screen line of the dialog box's top edge, 0x9F hidden .. 0x7B shown
.set g_pDialogCursorObject,                            0x03002EEC  @ Object *: menu cursor of the dialog box
.set g_dwDialogTextActive,                             0x03002EF0  @ u32: nonzero once the box's text has started
.set g_dwDialogBoxTileRow,                             0x03002EF4  @ u32: BG1 tile row the box's tilemap is drawn at
.set g_pHippogriffFliesIntoAirObject,                  0x03002F18  @ Object *; see include/cutscene/hippogriff_flies_into_air_cutscene.h
.set g_pHippogriffFliesIntoAirObject2,                 0x03002F1C  @ Object *
.set g_aRoomTileAnimations,                            0x03002F24  @ RoomTileAnimation *: 32 entries, allocated by InitRoomTileAnimationTable
.set g_dwRoomTileAnimationCount,                       0x03002F28  @ u32: entries in use in g_aRoomTileAnimations
.set g_aFontDescriptors,                                  0x03002F30  @ FontDescriptor[12][2], filled by LoadFontDescriptor
.set gTextRenderState,                                 0x03003110  @ struct: font descriptor pointers (+0x00/+0x04) and other
                                                                   @ text-rendering fields (e.g. +0x11 = line height); not
                                                                   @ fully mapped, see include/graphics/text.h
.set sTextMacroTable,                                  0x03003170  @ u8 *[4]: 0x40-byte heap buffers (allocated by InitTextMacroTable) holding the strings that 0x40-prefixed text codes 0x31-0x34 expand to
.set g_saveStateBlock,                                 0x03003180  @ live save-adjacent state (money, playtime, flags, ...); doc-level array at +0x10
.set g_dwUnk03003234,                                  0x03003234  @ u32: one-shot flag TickObject clears; see src/object/tick_object.c
.set g_GameCubeLinkScreenState, 0x03003238  @ GameCubeLinkScreenState: status/result text bookkeeping for the GameCube link screen
.set g_OwlCareKitScreen,        0x03003270  @ OwlCareKitScreenState: live state of the Owl Care Kit care screen, see include/minigame/owlcare.h
.set g_OverworldControlState,                          0x03003358  @ OverworldControlState: 2 x 16-byte control slots, then slot count (+0x20) and index (+0x21)

@ --- Overworld object tracking (see include/overworld/overworld.h) ---
.set g_nCameraYOffset,               0x0300337C  @ s8: camera Y offset in pixels; 18 after InitRoomBgState_candidate
.set g_abRoomScriptExitParams_candidate, 0x0300337D  @ u8[2]: filled by the dialog-close and return-to-overworld opcodes
.set g_pPlayerObject,                    0x03003380  @ Object *: the player's overworld object
.set g_pFollowerObject0,                 0x03003384  @ Object *: first party follower, NULL while empty
.set g_pFollowerObject1,                 0x03003388  @ Object *: second party follower, NULL while empty
.set g_bPartyCharId0,                    0x0300338C  @ u8: character id of the party leader
.set g_bPartyCharId1,                    0x0300338D  @ u8: character id of the first follower
.set g_bPartyCharId2,                    0x0300338E  @ u8: character id of the second follower
.set g_bSelectedFieldSpell,              0x0300338F  @ u8: index into the field spell table at 0x08060BAC; see include/overworld/overworld.h
.set g_pFieldSpellNameObject,            0x030033A0  @ Object *: selected field spell name text
.set g_pMapNameTextObject,               0x030033A4  @ Object *: room name text of ShowMapNamePopup
.set g_dwUnk030033A8,                    0x030033A8  @ u32: zeroed by ResetPartyState and sub_080248E8; no reader found
.set g_pFieldSpellPortraitObject,        0x030033AC  @ Object *: face portrait of the selected field spell's character
.set g_pMapNamePopupObject,             0x030033B0  @ Object *: 240x16 bar sprite behind the room name text

.set gDialogTextBlobBase,    0x030033C0  @ active language blob's base pointer (0 = none installed)
.set gDialogTextOffsetTable, 0x030033C4  @ pointer to the active blob's per-string-ID u32[] offset table
.set gDialogTextTreeNodes,   0x030033C8  @ pointer to the active blob's Huffman tree node table

@ --- Controller input (see docs/memory-map/input.md; UpdateKeyInput/
@ ResetKeyInput, 0x080254A8/0x080258F8) ---
.set g_aDecompressBgTileIwram,      0x030033CC  @ u8[0x100]: IWRAM copy of DecompressBgTile
.set g_HighScoreNameEntry,          0x030034D0  @ HighScoreNameEntryState; see include/minigame/high_score_name_entry.h
.set g_wKeysHeld,                0x030034EC  @ u16: current held-key bitmask (standard GBA KEYINPUT bit
                                             @ order), updated once per frame by UpdateKeyInput; also
                                             @ folded into Mt19937AutoSeed's seed as a cheap entropy
                                             @ source (see docs/memory-map/rng.md) -- that's not what the
                                             @ address is for
.set g_wKeysHeldPrevious,        0x030034EE  @ u16: g_wKeysHeld from the previous frame's update
.set g_wKeysPressed,             0x030034F0  @ u16: keys newly pressed this frame (currentHeld &
                                             @ ~previousHeld); bit 0x01 (A) tested by
                                             @ TickBattleTurnStateMachine's message-wait fast-forward
                                             @ check, bits 0x10/0x20 (Right/Left) read elsewhere -- see
                                             @ docs/memory-map/input.md, docs/formats/folio_bruti.md,
                                             @ docs/memory-map/battle-ui.md
.set g_wKeysReleased,            0x030034F2  @ u16: keys newly released this frame (previousHeld & ~currentHeld)
.set g_wInputDisabled,           0x030034F4  @ u16: nonzero forces all key state above (and the per-player
                                             @ arrays below) to 0 every frame instead of reading KEYINPUT
.set g_awPlayerKeysHeld,         0x030034F6  @ u16[2]: per-player held-key masks, serial-link input path
.set g_awPlayerKeysHeldPrevious, 0x030034FA  @ u16[2]: previous-frame counterpart of the above
.set g_awPlayerKeysPressed,      0x030034FE  @ u16[2]: per-player newly-pressed masks
.set g_awPlayerKeysReleased,     0x03003502  @ u16[2]: per-player newly-released masks
.set g_awPlayerInputDisabled_candidate, 0x03003506  @ u16[2]: written with g_wInputDisabled by EnableKeyInput and sub_08025978; no reader found

.set g_VBlankState, 0x03003530  @ the object g_pVBlankState is set to point at

@ Set by InitInterruptSystem to &g_VBlankState; read by every interrupt
@ handler (HandleVBlankInterrupt, HandleHBlankInterrupt,
@ HandleTimer0Interrupt, HandleTimer3OrSerialInterrupt,
@ HandleVCountInterrupt), not just vblank-related code -- Mt19937AutoSeed
@ also reads its dwVBlankCount field for entropy, but that's a secondary
@ consumer, not what the struct is for.
.set g_pVBlankState,    0x0300356C
.set gIntrTable,        0x03003570  @ 13 x u32 function-pointer slots, refreshed from a ROM
                                    @ template by InitInterruptSystem; dispatched by IntrMain
.set gIntrHandlerIwram, 0x030035A4  @ 0x200-byte IWRAM buffer InstallInterruptHandler
                                    @ CpuSets the live handler code into; gIntrVectorPtr
                                    @ points here

@ Sticky software copy of acked hardware IF bits, ORed by every interrupt
@ handler after acking its own bit in IF. See include/hw/vblank.h.
.set g_wPendingIntrFlags, 0x030037A4

@ Reentrancy guard for HandleVBlankInterrupt; body only runs while this
@ reads back as 1. See include/hw/vblank.h.
.set g_dwVBlankIntrNestCount, 0x030037A8

@ OAM DMA half-toggle; see include/hw/vblank.h.
.set g_bOamDmaHalfToggle,                    0x030037AC
.set g_abItemQuantities,                     0x030037B0  @ u8[132]: owned count per item id, see docs/formats/save.md
.set g_dwUnusedHogwartsMapShownBg,           0x03003A50  @ u32; see include/menu/unused_hogwarts_map_screen.h
.set g_pUnusedHogwartsMapCursor,             0x03003A54  @ Object *
.set g_pUnusedHogwartsMapBg1Tilemap,         0x03003A58  @ void *
.set g_apUnusedHogwartsMapObjects,           0x03003A60  @ Object *[9]
.set g_LupinPotionCutscene,                  0x03003A84  @ LupinPotionCutsceneState
.set g_aLupinPotionBg2Scroll,                0x03003B3C  @ s32[2]
.set g_dwGameModeFlags,                      0x03003B44  @ u32: broad flags word read/written across
                                                         @ overworld/room/cutscene transitions and
                                                         @ TickGameModeStack; individual bits
                                                         @ unconfirmed
.set g_dwFrameSyncTarget,                    0x03003B48  @ u32: frame-pacing target set once by AgbMain,
                                                         @ consumed only by WaitForVBlank
.set g_bCurrentRoomId,                       0x03003B50  @ byte: current room/map id
.set g_bControlSlotTicks_candidate,          0x03003B58  @ byte: bumped by TickOverworldControlSlots_candidate, zeroed on room entry, never read
.set g_bPendingQuestStateOverride_candidate, 0x03003B5A  @ u8: 0xFF = none; else copied into quest state 0 on room entry
.set g_dwRoomBgFlag_candidate,               0x03003B5C  @ u32: set to 1 by many rooms while loading; also read by sub_0802E6FC
.set g_dwPauseMenuLocked,                    0x03003B60  @ u32: nonzero blocks Start/Select menus (SetPauseMenuLocked)
.set g_bRoomSwitchState,                     0x03003B64  @ u8: current room switch state (0 or 1), see SetRoomSwitchState
.set g_pRoomObjectStateBuffer,               0x03003B68  @ 0x20BC-byte buffer, allocated by InitRoomState; see docs/formats/save.md
.set g_dwPauseMenuCooldown,                  0x03003B6C  @ u32: frames until Start/Select may open a menu again; 4 after init/menu open
.set g_bTouchedMonsterRecordCount,           0x03003B70  @ byte: queued (encounter id, kind) pair count
.set g_abTouchedMonsterRecords,              0x03003B74  @ u8[20]: 5 x 4-byte touched-monster records
.set g_pTouchedWanderingMonster,             0x03003B88  @ Object *: armed wandering-monster object
.set g_abIwramDivideCode,                   0x03003B90  @ u8[0x340]: IWRAM copy of the ARM divide routines (InstallIwramDivideRoutines)
.set g_pfnIwramDivideSignedQuotient,        0x03003ED0  @ IWRAM entry of DivideSignedQuotient
.set g_pfnIwramDivideSignedRemainder,       0x03003ED4  @ IWRAM entry of DivideSignedRemainder
.set g_pfnIwramDivideUnsigned,              0x03003ED8  @ IWRAM entry of DivideUnsignedWorker
.set gMemPool,                               0x03003EE0  @ MemPool[]; only pool 0 (index 0) is ever registered
.set gMemPoolCount,                          0x03003EF0  @ u32: live pool count, incremented by InitMemoryPool
.set g_GameModeStackContext,                 0x03003EF4  @ {dwCurrentGameMode, dwCurrentGameModeArg1, dwCurrentGameModeArg2, dwCurrentGameModeArg3, ...}
.set g_dwListMenuSelection,                  0x03003F14  @ u32: selected row of the current list menu; see include/menu/minigame_menu.h
.set g_dwPendingGameMode,                    0x03003F18  @ GameMode: mirrors g_GameModeStackContext's layout for the not-yet-applied mode; see docs/memory-map/game_modes.md
.set g_PrevGameModeStackContext,             0x03003F3C  @ GameModeStackContext, 0x24 bytes; see docs/memory-map/game_modes.md
.set g_dwTickCount,                          0x03003F60  @ u32: incremented once per TickGameModeStack call; see docs/memory-map/game_modes.md
.set g_apMenuIconObjects, 0x03003F68  @ Object *[]: objects registered by index via RegisterMenuIconObject
.set g_dwSelectedMinigame,                   0x03003F88  @ u32: minigame index chosen in the minigame menu, read by the difficulty select
.set g_abBgPriority,                         0x03003F8C  @ u8[]; [4] == 0x03003F90
.set g_dwRoomCollisionPatternCount,           0x03003FB8  @ u32: pattern count from the collision tilemap header
.set g_adwEdgeEndpointTypes,                  0x03003FC0  @ u32[2]: see include/overworld/terrain.h
.set g_pRoomCollisionTilemapBuffer,           0x03003FC8  @ u8 *: decompressed collision tilemap resource, 4-byte header then the pattern ids
.set g_pRoomCollisionBehaviorTable,           0x03003FCC  @ u8 *: 16 collision bytes per pattern, see docs/formats/collision.md
.set g_pRoomCollisionTilemap,                 0x03003FD0  @ u16 *: pattern ids of the 32x32-pixel blocks, g_pRoomCollisionTilemapBuffer + 4
.set g_dwPendingCameraFocusFlag,             0x03003FD4  @ u32: cleared on room entry
.set g_pPendingCameraFocus_candidate,        0x03003FD8  @ void *: argument RestorePendingCameraFocus_candidate is called with

@ --- OAM shadow buffer, see include/graphics/oam.h ---
.set g_pOamShadowBuffer,         0x03003FE8
.set g_pOamDmaShadowBuffer,      0x03003FEC
.set g_OamShadowBufferA,         0x03003FF0
.set g_OamShadowBufferB,         0x030047F0
.set g_bOamEntryCount,           0x03004FF0
.set g_bOamEntryCountPrev,       0x03004FF1
.set g_bAffineSlotHighWaterMark, 0x03004FF2  @ highest allocated affine slot index + 1; see AllocAffineSlot
.set g_abAffineSlotUsed,         0x03004FF3  @ u8[32], one per affine hardware slot; see AllocAffineSlot/FreeAffineSlot
.set g_aObjAffineSetSource,      0x03005014  @ ObjAffineSource[32] (8-byte stride), fed to bios_ObjAffineSet by CommitObjAffineMatrices

@ --- Resource cache / particle emitters (see docs/formats/graphics.md and
@ docs/formats/battle_scripts.md's TickParticleEmitters note) ---
.set g_aResourceCache,                 0x03005114  @ ResourceCacheSlot[16]
.set g_pParticleEmitterActiveListHead, 0x03005198  @ ListNode *
.set g_wActiveParticleCount,           0x0300519C  @ u16
.set g_wParticleHighWaterMark,         0x0300519E  @ u16
.set g_wActiveParticleEmitterCount,    0x030051A0  @ u16
.set g_wParticleEmitterHighWaterMark,  0x030051A2  @ u16
.set g_aParticles,                    0x030051A4  @ Particle *: MAX_PARTICLES entries, allocated by InitResourceCachePools
.set g_aParticleEmitters,             0x030051A8  @ ParticleEmitter *: MAX_PARTICLE_EMITTERS entries
.set g_pParticleFreeListHead,          0x030051AC  @ ListNode *
.set g_pParticleEmitterFreeListHead,   0x030051B0  @ ListNode *
.set g_apParticlesByPriority,         0x030051B8  @ Particle **[4]: active particles bucketed by OAM priority
.set g_abParticlesByPriorityCount,    0x030051C8  @ u8[4]: entries in each g_apParticlesByPriority array
.set g_pParticleActiveListHead,        0x030051CC  @ ListNode *
.set g_bParticleSpawnBlocked,          0x030051D0  @ u8: set when a particle's OAM submit fails (queue full); blocks spawning until TickParticleEmitters clears it
.set g_apParticleGfxPools,             0x030051D8  @ ParticleGfxEntry *[]

@ --- Serve Pumpkin Juice minigame (see include/minigame/serve_pumpkin_juice.h) ---
.set g_dwPatronusBgFront,     0x030051E4  @ u32; see include/cutscene/harry_patronus_cutscene.h
.set g_dwPatronusBgBack,      0x030051E8  @ u32
.set g_dwPatronusSwapPending, 0x030051EC  @ u32
.set g_bPatronusGraphicIndex, 0x030051F0  @ u8
.set g_swPatronusBgParam,     0x030051F2  @ s16
.set g_nPatronusBgOffset,     0x030051F4  @ s32, 16.16
.set g_ConnectivityMenu, 0x030051F8  @ ListMenuDefinition: RAM copy of g_ConnectivityMenuTemplate with the active row table

.set g_ListMenuState,                          0x03005220  @ ListMenuState: pause menu cursor row saved by ExitInGameMenu, definition of the list menu on screen
.set g_dwWizardCrackerPopItForceOverworldExit, 0x03005228  @ u32: set by the StartMinigame room script opcode
.set g_pWizardCrackerPopIt,                    0x03005230  @ WizardCrackerPopItState *: allocated for the minigame's duration
.set g_ServePumpkinJuice,                      0x03005238  @ ServePumpkinJuiceState

@ --- Dialog/UI text engine (US only) ---
.set g_StatusEquipReturnMode,      0x03005298  @ GameMode: StatusEquipCharacterSelect returns to on B (InGameMenu, InGameMenuFadeIn or ItemsItemSelect)
.set g_StatusEquipNextMode,        0x0300529C  @ GameMode: StatusEquipCharacterSelect advances to on A (StatusEquipSlotSelect or QuantitySelectScreen)
.set g_dwStatusEquipCharacter,     0x030052A0  @ u32: FighterType chosen in StatusEquipCharacterSelect, read by the slot/item screens and ItemUseScreen
.set g_StatusEquipCharacterSelect, 0x030052A8  @ StatusEquipCharacterSelectState: slot presence flags and pending mode; see include/menu/status_equip.h
.set g_bStatusEquipCharacterSlot,  0x030052B8  @ u8: StatusEquipCharacterSelect cursor slot
.set g_bConnectivityMenuCursor, 0x030052BC  @ s8: Connectivity row restored on re-entry
.set g_dwStatusEquipSlotType,      0x030052C0  @ u32: equipment type (0-5) of the slot chosen in StatusEquipSlotSelect
.set g_StatusEquipItemSelect,      0x030052C8  @ StatusEquipItemSelectState: item select list, stat arrows and saved palette; see include/menu/status_equip.h
.set g_bFoliosMenuCursor, 0x030052F8  @ s8: Folios row restored on re-entry
.set g_FolioBrutiState,            0x03005300  @ FolioBrutiState: the Folio Bruti screen state; see include/menu/folio_bruti.h
.set g_FolioUniversitasState,      0x03005340  @ FolioUniversitasState: the Folio Universitas screen state; see include/menu/folio_universitas.h
.set g_HelpState,                 0x03005370  @ HelpState: the Help / HelpTopicScreen engine state; see include/menu/help.h
.set g_ItemsItemSelect,            0x030054D8  @ ItemsItemSelectState: item list presence, pending mode and list filter; see include/menu/items_menu.h
.set g_ItemsSectionSelectNextMode, 0x030054E4  @ GameMode: pushed once the Items section select fades out
.set g_bItemsSectionCursor,        0x030054E8  @ s8: Items section select row saved on exit
.set g_dwItemUseItem,              0x030054EC  @ u32: item chosen in ItemsItemSelect, used by ItemUseScreen
.set g_dwItemUseQuantity,          0x030054F0  @ u32: quantity chosen in QuantitySelectScreen, used by ItemUseScreen
.set g_StatusEquipSlotSelect,      0x030054F8  @ StatusEquipSlotSelectState: slot select screen objects and pending mode; see include/menu/status_equip.h
.set g_bStatusEquipSlot,           0x03005564  @ s8: selected equipment slot in StatusEquipSlotSelect
.set g_CardTradeState, 0x03005568  @ CardTradeState: link card trade session; see include/menu/card_trade.h

@ --- MT19937 PRNG (see docs/memory-map/rng.md) ---
@ Names mostly match jogotu's BizHawk script naming, cross-checked
@ against our own disassembly there. That script tracks cursor 1 only;
@ cursor 2 is undocumented by it and comes from this project's own
@ disassembly (see rng.md for what's confirmed and what's still open
@ about it).
.set gMt19937LastRollByte,      0x03005574  @ low byte of the last tempered value (purpose unconfirmed)
.set gMt19937DrawIndex,         0x03005578  @ cursor 1: running count of numbers drawn
.set gMt19937StatePtr,          0x0300557C  @ base of the 624-word MT state array
.set gMt19937CurPtr,            0x03005580  @ cursor 1: pointer into the state array
.set gMt19937RemainingIndices,  0x03005584  @ cursor 1: untempered words left before regenerating
.set gMt19937CurPtr2,           0x03005588  @ cursor 2: pointer into the state array
.set gMt19937RemainingIndices2, 0x0300558C  @ cursor 2: untempered words left before regenerating
.set gMt19937AutoSeedCallCount, 0x03005590  @ increments each AutoSeed call (purpose unconfirmed)
.set gMt19937SeedValue,         0x03005594  @ accumulating seed value (SetSeed/AutoSeed)

.set g_saveManager,              0x03005598  @ SaveManager: the live RAM copy of the save header (first member) and slot state; see include/game/save.h and docs/formats/save.md
.set g_wEepromSavedDispstat,     0x0300561C  @ u16: DISPSTAT saved across EEPROM transfers (EepromTransferBegin/End)
.set g_pScreenPaletteBackup,        0x03005624  @ u16 *: 0x400-byte palette copy kept by DarkenScreenPalette
.set g_dwUnk03005638,                      0x03005638  @ u32: set by SetScreenDarkenParams_candidate; no reader found
.set g_dwScreenDarkenStepTicks_candidate, 0x0300563C  @ u32: palette step ticks of DarkenScreenPalette/RestoreScreenPalette
.set g_CameraPosition_candidate, 0x03005640  @ CameraFocusOffset: world-space camera origin used for object visibility
.set g_RoomSizePixels,           0x03005648  @ RoomSizePixels: width and height of the current room in pixels
.set g_adwBgScrollEnabled,           0x030058C0  @ u32[4]: per BG layer, nonzero = scrolled by UpdateOverworldCamera_candidate
.set g_apBgTileCacheEntries,        0x03005988  @ BgTileCacheEntry *[2]; see include/overworld/room.h
.set g_apBgTileCacheBuckets,        0x03005990  @ u16 *[2]
.set g_apBgTileCacheFreeSlots,      0x03005998  @ u16 *[2]
.set g_dwUnk030059AC,               0x030059AC  @ u32: zeroed by InitRoomBgState_candidate
.set g_awLinkKeysReceived,       0x03005A0C  @ u16[2]: per-player key masks received over the link cable
.set g_LinkPlayerState,          0x03005A24  @ LinkPlayerState: serial-link session block; see include/link/link.h
.set g_bUnk03005AC0,             0x03005AC0  @ u8: set to 8 by kramInstall and PlayMusicModule
.set g_bMusicPaused,             0x03005AC1  @ u8: PauseMusic latch, cleared by ResumeMusic and StopMusic
.set g_bCurrentMusicModule,      0x03005AC2  @ u8: last module started by PlayMusicModule, 0xFF if none
.set g_FredAndGeorgesShop,       0x03005AC8  @ FredAndGeorgesShopState; see include/menu/fred_and_georges_shop.h
.set g_DivinationTea,            0x03005B28  @ DivinationTeaState
.set gDialogTextScratchBuf,      0x03005D08  @ pointer to the fixed 0x400-byte decode scratch buffer
.set gCurrentLanguage,           0x03005D0C  @ byte: language ID (0-7) set by SetLanguage
.set gLocaleThousandsSep,        0x03005D0D  @ byte: locale-specific number-formatting separator
.set g_adwHippogriffGlideUnk,    0x03005D10  @ u32[3]: cleared on init, meaning not yet established
.set g_aGameTimers,                0x03005D58  @ GameTimer[4]; see include/game/game_timer.h
.set g_HarryHermionePortInTime,  0x03005D98  @ HarryHermionePortInTimeState

@ --- Dialog/UI text engine (US only) ---
.set g_dwMainMenuTextCursor,     0x03005DB0  @ u32: text tile cursor returned by the main menu's copyright text; see include/menu/main_menu.h
.set g_MainMenuState,            0x03005DB8  @ MainMenuState: {Object *pCursorObject; u32 dwLoadGameAvailable; s32 nPaletteEffectSlot_candidate}; see include/menu/main_menu.h
.set g_bSaveSlotScreenResult,    0x03005DC4  @ u8: SaveSlotScreenResult set by HandleSaveSlotInput_candidate
.set g_OptionsState,             0x03005DD0  @ OptionsState: 8 object pointers, then music, sound and gamma settings; see include/menu/options.h
.set g_dwOptionsReturnMode,      0x03005E04  @ u32: GameMode that opened the options screen
.set g_bOptionsSavedMusicVolume, 0x03005E08  @ u8: settings kept across the language select trip
.set g_bOptionsSavedSoundVolume, 0x03005E09  @ u8
.set g_bOptionsSavedGammaHigh,   0x03005E0A  @ u8
.set g_dwOptionsEntryLanguage,   0x03005E0C  @ u32: language when the options screen was entered

.set g_wCoolTrainTimer,          0x03005E14  @ u16: frames left in the Cool Train cutscene
.set g_bRestoringRoomObjects_candidate, 0x03005E18  @ u8: 1 while RestoreRoomObjectState respawns objects; also set when the overworld pushes a pause menu
.set g_ScanlineEffectState,      0x03005E20  @ pending flag, active index, 19 live entries; see docs/memory-map/scanline_effects.md
.set g_ScanlineEffectStaging,    0x03005F58  @ 19 staged entries, committed to the live table by CommitScanlineEffects
.set g_pFindFreeObjTileRunIwram, 0x03006088  @ u8[0x9C]: IWRAM copy of FindFreeObjTileRun
.set g_adwObjTileAllocBitmap,    0x03006128  @ u32[32]: set bit = tile in use
.set g_adwObjTileFreeMask,       0x030061A8  @ u32[32]: clear bit = free pending the next OAM swap
.set g_pEepromInterface,         0x030062C8  @ EepromInterface *: chosen by EepromSelectInterface
.set gSystemStackTop,            0x03007EA0  @ top of the AGB system-mode stack
.set gIrqStackTop,               0x03007FA0  @ top of the AGB IRQ-mode stack
.set gIntrVectorPtr,             0x03007FFC  @ BIOS-called user interrupt handler pointer
.set sDialogLanguageTable,       0x0806BD78  @ ROM: 8 x u32, one string-table blob pointer per language
