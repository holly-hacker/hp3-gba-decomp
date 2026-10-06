@ Named RAM addresses referenced from C and asm/*.s files -- see
@ ram_symbols.us.inc for the full explanation. JP-side values, laid out
@ like the US file. Symbols with no JP counterpart yet are omitted.

@ --- Statically linked RAM sections (see include/hw/mem.h and ClearWorkRam) ---
.set g_EwramSectionStart,     0x02000000
.set g_EwramSectionEnd,       0x020027F8  @ ClearWorkRam zeroes EWRAM from here
.set g_abEwramHeap,          0x02002800  @ InitHeap's pool 0, up to the end of EWRAM
.set g_IwramSectionStart,     0x03000000  @ IWRAM image kramInstall copies from ROM
.set IwramTimer1Handler,      0x03000004  @ gIntrTableTemplate's timer 1 handler, in that image
.set g_IwramSectionEnd,       0x03001598  @ end of that image; ClearWorkRam zeroes from here

.set g_pTimer2DebugPc,        0x030015A0  @ see ram_symbols.us.inc
.set g_ActiveObjectListState, 0x030015B0

@ --- Per-tick object queues (see include/hw/mem.h and TickObjectList) ---
.set g_apOamQueue,             0x030015B8
.set g_dwOamQueueCount,        0x0300175C
.set g_apSpriteFrameQueue,     0x03001760
.set g_bSpriteFrameQueueCount, 0x0300179C

.set g_dwObjectListActive_candidate, 0x030017A0
.set g_apCollisionQueue,             0x030017A4
.set g_dwCollisionQueueCount,        0x03001948

@ --- Object pool (see docs/memory-map/heap.md and include/hw/mem.h) ---
.set g_pSortObjectsIwram,            0x0300194C
.set g_pCheckObjectCollisionsIwram,  0x03001A10
.set g_ObjectPoolState,              0x03001C08
.set g_pObjectPoolAuxBuffer,         0x03001DBC
.set g_dwObjectListTicked_candidate, 0x03001DC0
.set g_dwUnk03001DC4,                0x03001DC4
.set g_adwRoomObjUnkACState,         0x03001DD0  @ u32[3]: zeroed by the type 10 and 12 room object constructors

.set g_wRoomResourceFlags_candidate, 0x03001DDC  @ see ram_symbols.us.inc

@ --- Room-script VM (see include/overworld/room_script.h) ---
.set g_bRoomScriptCurrentRow,        0x03001DDE
.set g_pRoomScriptYieldContinuation, 0x03001DE0
.set g_pRoomScriptNextRecord,        0x03001DE4
.set g_bRoomScriptCallStackDepth,    0x03001DE8

.set g_bRoomScriptYieldOpcode,            0x03001DE9
.set g_pRoomTableBuffer,                  0x03001DEC  @ see ram_symbols.us.inc
.set g_dwRoomChainRanThisFrame_candidate, 0x03001DF0  @ see ram_symbols.us.inc
                                                      @ HandleOverworldPauseMenuInput each frame, which skips the menu check while it is set

@ --- Room-script VM (see include/overworld/room_script.h) ---
.set g_pRoomObjectTable,            0x03001DF4  @ see ram_symbols.us.inc
.set g_pRoomWarpTriggerTable,       0x03001DF8  @ see ram_symbols.us.inc
.set g_pRoomSwitchStateObjectTable, 0x03001DFC  @ see ram_symbols.us.inc
.set g_aRoomScriptCallStack,        0x03001E00

.set g_aBgScrollState, 0x03001E80  @ see ram_symbols.us.inc

@ Forces one extra sub_08007130 call this vblank; see include/hw/vblank.h.
.set g_bForcePendingBgWritesFlush,               0x03002038
.set g_dwRiddikulusMinigameScriptFlag_candidate, 0x03002040  @ set by StartMinigame
.set g_Riddikulus,                               0x03002048  @ see ram_symbols.us.inc
.set g_dwHippogriffForceOverworldExit,           0x03002084  @ set by StartMinigame
.set g_pHippogriffGlide,                         0x03002088  @ see ram_symbols.us.inc
.set g_aCameraEffects_candidate,                 0x03002090  @ see ram_symbols.us.inc
.set g_aCameraFocusSlots,                        0x030020E8  @ see ram_symbols.us.inc
.set g_aCameraFollowOffsets,                     0x03002158  @ see ram_symbols.us.inc

@ --- Dialog/UI text engine ---
.set g_DebugMenuMainState,            0x030021C0
.set g_DebugLevelAndQuestSelectState, 0x030021C8
.set g_DebugMapSelectState,           0x030021E8
.set g_DebugCharacterSelectState,     0x030021F8
.set g_DebugPortraitsState,           0x03002210
.set g_DebugSoundTestState,           0x03002218
.set g_DebugCollectorCardsState,      0x03002238

.set g_abOpenedChestFlags,         0x03002240  @ u8[32]: one bit per chest flag id; set when the chest is opened, saved with the game
.set g_aColorCycles,               0x03002280  @ ColorCycle[12]; see include/graphics/palette.h
.set g_dwColorCycleActiveMask,     0x030022E0  @ u32: bit n set = color cycle slot n was activated
.set g_dwColorCycleCount,          0x030022E4  @ u32: color cycle slots handed out since the last reset
.set g_pPaletteWorkBuffer,        0x030022EC  @ u16 *: 0x400-byte BG+OBJ palette work buffer, allocated by InitGammaPalette
.set g_dwObjPaletteQueueCount,     0x030022F0  @ u32: queued OBJ palette loads (25 max)
.set g_dwPaletteEffectCount,       0x030022F4  @ u32: active palette effects
.set g_aPaletteEffects,            0x030022F8  @ PaletteEffect[12]; see include/graphics/palette.h
.set g_PaletteState,              0x030024B0  @ PaletteState; see include/graphics/palette.h
.set g_pFightState,                 0x030024E8
.set g_aPartyMasterStats,           0x030024EC  @ BattleFighter[], 0x48 stride
.set g_bPendingRoomScriptChain,     0x0300260C  @ chain resumed after a game mode
.set g_bPendingRoomScriptRow,       0x0300260D  @ object row resumed after a game mode
.set g_nBattleXpReward,             0x0300260E  @ see ram_symbols.us.inc
.set g_nBattleGoldReward,           0x03002610  @ see ram_symbols.us.inc
.set g_dwOverworldMonstersDisabled, 0x03002614

@ --- Battle system (see docs/memory-map/battle.md) ---
.set g_dwBattleRewardFlagsSnapshot,        0x03002618
.set g_bSelectedFighterSlot_candidate,     0x03002660
.set g_apFighterObjects_candidate,         0x03002668
.set g_pBattleMessageIconObject_candidate, 0x03002684
.set g_BattleMessageIconState_candidate,   0x03002688
.set g_anFaintedRosterIndices,             0x030026D8  @ see ram_symbols.us.inc
.set g_bDefeatWarpParam,                   0x03002748  @ see ram_symbols.us.inc
.set g_bSpellMissStreak,                   0x03002749
.set g_nLastDamage,                        0x0300274A
.set g_bLastTargetIndex,                   0x0300274C
.set g_effectStaging,                      0x03002750

.set g_dwRoomScriptRunState,    0x0300279C  @ room script run state
.set g_abQuestEventState,       0x030027A0  @ quest event state bytes
.set g_bRoomScriptPendingChain, 0x030028A0

@ --- Serve Pumpkin Juice minigame (see include/minigame/serve_pumpkin_juice.h) ---
.set g_dwCreditsScrollRow,    0x030028A8  @ see ram_symbols.us.inc
.set g_dwCreditsLine,         0x030028AC  @ see ram_symbols.us.inc
.set g_dwCreditsTileCursor,   0x030028B0  @ see ram_symbols.us.inc
.set g_pLinearCutsceneText,   0x030028B4  @ see ram_symbols.us.inc
.set g_pLinearCutsceneObject, 0x030028B8  @ see ram_symbols.us.inc
.set g_dwLinearCutsceneIndex, 0x030028BC  @ see ram_symbols.us.inc

.set g_pMenuCursorEmitter, 0x030028C0

@ --- IWRAM-installed decompression codecs (see docs/formats/graphics.md's
@ "resource-decompression dispatcher") ---
.set g_pDecompressLzRleEntry,   0x030028CC
.set g_pDecompressGammaLzEntry, 0x030028D0
.set g_pDecompressLzRleIwram,   0x030028D4
.set g_pDecompressGammaLzIwram, 0x03002ACC

.set g_pMenuCursorObject,                              0x03002E08  @ see ram_symbols.us.inc
.set g_dwHarryVsDementorsMinigameScriptFlag_candidate, 0x03002E10  @ set by StartMinigame
.set g_HarryVsDementors,                               0x03002E18  @ see ram_symbols.us.inc
.set g_DialogState_candidate,                          0x03002E88
.set g_pDialogMacroExpandBuffer,                       0x03002EA8
.set g_pHippogriffFliesIntoAirObject,                  0x03002F18  @ see ram_symbols.us.inc
.set g_pHippogriffFliesIntoAirObject2,                 0x03002F1C
.set g_aRoomTileAnimations,                            0x03002F24
.set g_dwRoomTileAnimationCount,                       0x03002F28
.set g_aFontDescriptors,                                  0x03002F30
.set gTextRenderState,                                 0x03003170  @ text-rendering fields (e.g. +0x11 = line height); not
                                                                   @ fully mapped, see include/graphics/text.h
.set sTextMacroTable,                                  0x030031D0  @ see ram_symbols.us.inc
.set g_saveStateBlock,                                 0x030031E0
.set g_dwUnk03003234,                                  0x03003294  @ see ram_symbols.us.inc
.set g_OverworldControlState,                          0x030033B8  @ OverworldControlState: 2 x 16-byte control slots, then slot count (+0x20) and index (+0x21)

@ --- Overworld object tracking (see include/overworld/overworld.h) ---
.set g_nCameraYOffset,                  0x030033DC
.set g_abRoomScriptExitParams_candidate, 0x030033DD  @ see ram_symbols.us.inc
.set g_pPlayerObject,                    0x030033E0  @ see ram_symbols.us.inc
.set g_pFollowerObject0,                 0x030033E4
.set g_pFollowerObject1,                 0x030033E8
.set g_bPartyCharId0,                    0x030033EC
.set g_bPartyCharId1,                    0x030033ED
.set g_bPartyCharId2,                    0x030033EE
.set g_bSelectedFieldSpell,             0x030033EF
.set g_pFieldSpellNameObject,           0x03003400
.set g_pMapNameTextObject,              0x03003404
.set g_dwUnk030033A8,                   0x03003408
.set g_pFieldSpellPortraitObject,      0x0300340C
.set g_pMapNamePopupObject,             0x03003410

.set gDialogTextBlobBase,    0x03003420
.set gDialogTextOffsetTable, 0x03003424
.set gDialogTextTreeNodes,   0x03003428

@ --- Controller input (see docs/memory-map/input.md; UpdateKeyInput/
@ ResetKeyInput, 0x080254A8/0x080258F8) ---
.set g_aDecompressBgTileIwram,          0x0300342C
.set g_wKeysHeld,                0x0300354C  @ see ram_symbols.us.inc/docs/memory-map/input.md
                                             @ order), updated once per frame by UpdateKeyInput; also
                                             @ folded into Mt19937AutoSeed's seed as a cheap entropy
                                             @ source (see docs/memory-map/rng.md) -- that's not what the
                                             @ address is for
.set g_wKeysHeldPrevious,        0x0300354E
.set g_wKeysPressed,             0x03003550  @ ~previousHeld); bit 0x01 (A) tested by
                                             @ TickBattleTurnStateMachine's message-wait fast-forward
                                             @ check, bits 0x10/0x20 (Right/Left) read elsewhere -- see
                                             @ docs/memory-map/input.md, docs/formats/folio_bruti.md,
                                             @ docs/memory-map/battle-ui.md
.set g_wKeysReleased,            0x03003552
.set g_wInputDisabled,           0x03003554  @ arrays below) to 0 every frame instead of reading KEYINPUT
.set g_awPlayerKeysHeld,         0x03003556
.set g_awPlayerKeysHeldPrevious, 0x0300355A
.set g_awPlayerKeysPressed,      0x0300355E
.set g_awPlayerKeysReleased,     0x03003562
.set g_awPlayerInputDisabled_candidate, 0x03003566

.set g_VBlankState, 0x03003590

@ Set by InitInterruptSystem to &g_VBlankState; read by every interrupt
@ handler (HandleVBlankInterrupt, HandleHBlankInterrupt,
@ HandleTimer0Interrupt, HandleTimer3OrSerialInterrupt,
@ HandleVCountInterrupt), not just vblank-related code -- Mt19937AutoSeed
@ also reads its dwVBlankCount field for entropy, but that's a secondary
@ consumer, not what the struct is for.
.set g_pVBlankState,    0x030035CC
.set gIntrTable,        0x030035D0  @ 13 x u32 handler slots dispatched by IntrMain
                                    @ template by InitInterruptSystem; dispatched by IntrMain
.set gIntrHandlerIwram, 0x03003604  @ CpuSets the live handler code into; gIntrVectorPtr
                                    @ points here

@ Sticky software copy of acked hardware IF bits, ORed by every interrupt
@ handler after acking its own bit in IF. See include/hw/vblank.h.
.set g_wPendingIntrFlags, 0x03003804  @ see ram_symbols.us.inc

@ Reentrancy guard for HandleVBlankInterrupt; body only runs while this
@ reads back as 1. See include/hw/vblank.h.
.set g_dwVBlankIntrNestCount, 0x03003808

@ OAM DMA half-toggle; see include/hw/vblank.h.
.set g_bOamDmaHalfToggle,                    0x0300380C
.set g_abItemQuantities,                     0x03003810
.set g_LupinPotionCutscene,                  0x03003AE4  @ see ram_symbols.us.inc
.set g_aLupinPotionBg2Scroll,                0x03003B9C
.set g_dwGameModeFlags,                      0x03003BA4  @ u32: broad game-mode flags word
                                                         @ overworld/room/cutscene transitions and
                                                         @ TickGameModeStack; individual bits
                                                         @ unconfirmed
.set g_dwFrameSyncTarget,                    0x03003BA8  @ see ram_symbols.us.inc
.set g_bCurrentRoomId,                       0x03003BB0  @ see ram_symbols.us.inc
.set g_bControlSlotTicks_candidate,          0x03003BB8  @ byte: bumped by TickOverworldControlSlots_candidate, zeroed on room entry, never read
.set g_bPendingQuestStateOverride_candidate, 0x03003BBA
.set g_dwRoomBgFlag_candidate,               0x03003BBC
.set g_dwPauseMenuLocked,                    0x03003BC0  @ u32: nonzero blocks Start/Select menus (SetPauseMenuLocked)
.set g_pRoomObjectStateBuffer,          0x03003BC8
.set g_dwPauseMenuCooldown,                  0x03003BCC  @ u32: frames until Start/Select may open a menu again; 4 after init/menu open
.set g_bTouchedMonsterRecordCount,           0x03003BD0  @ byte: queued (encounter id, kind) pair count
.set g_abTouchedMonsterRecords,              0x03003BD4  @ u8[20]: 5 x 4-byte touched-monster records
.set g_pTouchedWanderingMonster,             0x03003BE8  @ Object *: armed wandering-monster object
.set g_abIwramDivideCode,                   0x03003BF0
.set g_pfnIwramDivideSignedQuotient,        0x03003F30
.set g_pfnIwramDivideSignedRemainder,       0x03003F34
.set g_pfnIwramDivideUnsigned,              0x03003F38
.set gMemPool,                               0x03003F40
.set gMemPoolCount,                          0x03003F50
.set g_GameModeStackContext,                 0x03003F54  @ see ram_symbols.us.inc
.set g_dwListMenuSelection,                  0x03003F74  @ see ram_symbols.us.inc
.set g_dwPendingGameMode,                    0x03003F78  @ see ram_symbols.us.inc
.set g_PrevGameModeStackContext,             0x03003F9C
.set g_dwTickCount,                          0x03003FC0
.set g_dwSelectedMinigame,                   0x03003FE8
.set g_abBgPriority,                         0x03003FEC  @ see ram_symbols.us.inc
.set g_dwPendingCameraFocusFlag,             0x03004034  @ see ram_symbols.us.inc
.set g_pPendingCameraFocus_candidate,        0x03004038  @ see ram_symbols.us.inc

@ --- OAM shadow buffer, see include/graphics/oam.h ---
.set g_pOamShadowBuffer,    0x03004048
.set g_pOamDmaShadowBuffer, 0x0300404C
.set g_aOamShadowBufferA,   0x03004050
.set g_aOamShadowBufferB,   0x03004850
.set g_bOamEntryCount,      0x03005050
.set g_bOamEntryCountPrev,  0x03005051
.set g_bAffineSlotHighWaterMark, 0x03005052
.set g_abAffineSlotUsed,         0x03005053
.set g_aObjAffineSetSource, 0x03005074

@ --- Resource cache / particle emitters (see docs/formats/graphics.md and
@ docs/formats/battle_scripts.md's TickParticleEmitters note) ---
.set g_aResourceCache,                 0x03005174  @ see ram_symbols.us.inc
.set g_pParticleEmitterActiveListHead, 0x030051F8  @ see ram_symbols.us.inc
.set g_wActiveParticleCount,           0x030051FC
.set g_wParticleHighWaterMark,         0x030051FE
.set g_wActiveParticleEmitterCount,    0x03005200
.set g_wParticleEmitterHighWaterMark,  0x03005202
.set g_aParticles,                      0x03005204
.set g_aParticleEmitters,               0x03005208
.set g_pParticleFreeListHead,          0x0300520C
.set g_pParticleEmitterFreeListHead,   0x03005210
.set g_apParticlesByPriority,           0x03005218
.set g_pParticleActiveListHead,        0x0300522C
.set g_bParticleSpawnBlocked,          0x03005230
.set g_apParticleGfxPools,             0x03005238

@ --- Serve Pumpkin Juice minigame (see include/minigame/serve_pumpkin_juice.h) ---
.set g_dwPatronusBgFront,     0x03005244  @ see ram_symbols.us.inc
.set g_dwPatronusBgBack,      0x03005248
.set g_dwPatronusSwapPending, 0x0300524C
.set g_bPatronusGraphicIndex, 0x03005250
.set g_swPatronusBgParam,     0x03005252
.set g_nPatronusBgOffset,     0x03005254

.set g_ListMenuState,                          0x03005280
.set g_dwWizardCrackerPopItForceOverworldExit, 0x03005288  @ see ram_symbols.us.inc
.set g_pWizardCrackerPopIt,                    0x03005290  @ see ram_symbols.us.inc
.set g_ServePumpkinJuice,                      0x03005298  @ see ram_symbols.us.inc

@ --- Dialog/UI text engine ---
.set g_StatusEquipReturnMode,      0x030052F8  @ see ram_symbols.us.inc
.set g_StatusEquipNextMode,        0x030052FC  @ see ram_symbols.us.inc
.set g_dwStatusEquipCharacter,     0x03005300  @ see ram_symbols.us.inc
.set g_StatusEquipCharacterSelect, 0x03005308  @ see ram_symbols.us.inc
.set g_bStatusEquipCharacterSlot,  0x03005318  @ see ram_symbols.us.inc
.set g_StatusEquipItemSelect,      0x03005328  @ see ram_symbols.us.inc
.set g_ItemsItemSelect,            0x03005538  @ see ram_symbols.us.inc
.set g_ItemsSectionSelectNextMode, 0x03005544  @ see ram_symbols.us.inc
.set g_bItemsSectionCursor,        0x03005548  @ see ram_symbols.us.inc
.set g_dwItemUseItem,              0x0300554C  @ see ram_symbols.us.inc
.set g_dwItemUseQuantity,          0x03005550  @ see ram_symbols.us.inc
.set g_StatusEquipSlotSelect,      0x03005558  @ see ram_symbols.us.inc
.set g_bStatusEquipSlot,           0x030055C4  @ see ram_symbols.us.inc

@ --- MT19937 PRNG (see docs/memory-map/rng.md) ---
@ Names mostly match jogotu's BizHawk script naming, cross-checked
@ against our own disassembly there. That script tracks cursor 1 only;
@ cursor 2 is undocumented by it and comes from this project's own
@ disassembly (see rng.md for what's confirmed and what's still open
@ about it).
.set gMt19937LastRollByte,      0x030055D4
.set gMt19937DrawIndex,         0x030055D8
.set gMt19937StatePtr,          0x030055DC
.set gMt19937CurPtr,            0x030055E0
.set gMt19937RemainingIndices,  0x030055E4
.set gMt19937CurPtr2,           0x030055E8
.set gMt19937RemainingIndices2, 0x030055EC
.set gMt19937AutoSeedCallCount, 0x030055F0
.set gMt19937SeedValue,         0x030055F4

.set g_saveManager,              0x030055F8  @ see ram_symbols.us.inc
.set g_wEepromSavedDispstat,     0x0300567C  @ see ram_symbols.us.inc
.set g_pScreenPaletteBackup,            0x03005684
.set g_dwUnk03005638,                   0x03005698
.set g_dwScreenDarkenStepTicks_candidate, 0x0300569C
.set g_CameraPosition_candidate, 0x030056A0  @ CameraFocusOffset: world-space camera origin used for object visibility
.set g_adwBgScrollEnabled,              0x03005920
.set g_apBgTileCacheEntries,            0x030059E8
.set g_apBgTileCacheBuckets,            0x030059F0
.set g_apBgTileCacheFreeSlots,          0x030059F8
.set g_dwUnk030059AC,                   0x03005A0C
.set g_awLinkKeysReceived,       0x03005A6C
.set g_LinkPlayerState,          0x03005A84  @ see include/link/link.h
.set g_bUnk03005AC0,             0x03005B20
.set g_bMusicPaused,             0x03005B21
.set g_bCurrentMusicModule,      0x03005B22
.set g_DivinationTea,            0x03005B88  @ see ram_symbols.us.inc
.set gDialogTextScratchBuf,      0x03005D68
.set gCurrentLanguage,           0x03005D6C
.set gLocaleThousandsSep,        0x03005D6D  @ see ram_symbols.us.inc
.set g_adwHippogriffGlideUnk,    0x03005D70  @ see ram_symbols.us.inc
.set g_aGameTimers,                     0x03005DB8
.set g_HarryHermionePortInTime,  0x03005DF8  @ see ram_symbols.us.inc
.set g_dwMainMenuTextCursor,     0x03005E10
.set g_MainMenuState,            0x03005E18
.set g_bSaveSlotScreenResult,    0x03005E24
.set g_OptionsState,             0x03005E30
.set g_dwOptionsReturnMode,      0x03005E5C
.set g_wCoolTrainTimer,          0x03005E64  @ u16: frames left in the Cool Train cutscene
.set g_bRestoringRoomObjects_candidate, 0x03005E68  @ see ram_symbols.us.inc
.set g_ScanlineEffectState,      0x03005E70
.set g_ScanlineEffectStaging,    0x03005FA8
.set g_pFindFreeObjTileRunIwram, 0x030060D8
.set g_adwObjTileAllocBitmap,    0x03006178
.set g_adwObjTileFreeMask,       0x030061F8
.set g_pEepromInterface,         0x03006318
.set gSystemStackTop,            0x03007EA0
.set gIrqStackTop,               0x03007FA0
.set gIntrVectorPtr,             0x03007FFC
