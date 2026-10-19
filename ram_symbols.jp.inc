@ Named RAM addresses referenced from C and asm/*.s files -- see
@ ram_symbols.us.inc for the full explanation. JP-side values, laid out
@ like the US file. Symbols with no JP counterpart yet are omitted.

@ --- include/sound.h ---
.set g_KrawallEwramStart,     0x02000000
.set g_KrawallEwramEnd,       0x020027F8  @ ClearWorkRam zeroes EWRAM from here

@ --- include/mem.h ---
.set g_abEwramHeap,          0x02002800  @ InitHeap's pool 0, up to the end of EWRAM

@ --- include/sound.h ---
.set g_KrawallIwramStart,     0x03000000  @ IWRAM image kramInstall copies from ROM

@ --- include/sound.h ---
.set g_KrawallIwramEnd,       0x03001598  @ end of that image; ClearWorkRam zeroes from here

@ --- Boot + runtime (asm) ---
.set g_pTimer2DebugPc,        0x030015A0

@ --- include/actor.h ---
.set g_ActiveActorListState, 0x030015B0
.set g_apOamQueue,             0x030015B8
.set g_dwOamQueueCount,        0x0300175C
.set g_apSpriteFrameQueue,     0x03001760
.set g_bSpriteFrameQueueCount, 0x0300179C
.set g_dwActorListActive_candidate, 0x030017A0
.set g_apCollisionQueue,             0x030017A4
.set g_dwCollisionQueueCount,        0x03001948
.set SortActorsByDepthIwram,            0x0300194C
.set CheckActorCollisionsIwram,  0x03001A10
.set g_ActorPoolState,              0x03001C08
.set g_pActorPoolAuxBuffer,         0x03001DBC
.set g_dwActorListTicked_candidate, 0x03001DC0
.set g_dwUnk03001DC4,                0x03001DC4
.set g_ReceivedItemGfx,              0x03001DC8

@ --- include/area.h ---
.set g_adwRoomActorUnkACState,         0x03001DD0  @ u32[3]: zeroed by the type 10 and 12 room actor constructors
.set g_wRoomResourceFlags_candidate, 0x03001DDC
.set g_bRoomScriptCurrentChain,        0x03001DDE
.set g_pRoomScriptYieldContinuation, 0x03001DE0
.set g_pRoomScriptNextRecord,        0x03001DE4
.set g_bRoomScriptCallStackDepth,    0x03001DE8
.set g_bRoomScriptYieldOpcode,            0x03001DE9
.set g_pRoomTableBuffer,                  0x03001DEC
.set g_dwRoomChainRanThisFrame_candidate, 0x03001DF0
                                                      @ HandleOverworldPauseMenuInput each frame, which skips the menu check while it is set
.set g_pRoomActorTable,            0x03001DF4
.set g_pRoomRouteTable,       0x03001DF8
.set g_pRoomScriptChainTable, 0x03001DFC
.set g_aRoomScriptCallStack,        0x03001E00

@ --- include/background.h ---
.set g_BgState,        0x03001E80
@ Forces one extra CommitBgLayers call this vblank.
.set g_bForcePendingBgWritesFlush,               0x03002038

@ --- include/boggart_minigame.h ---
.set g_dwBoggartMinigameScriptFlag_candidate,    0x03002040  @ set by StartMinigame
.set g_BoggartMinigame,                          0x03002048

@ --- include/buckbeak_minigame.h ---
.set g_dwBuckbeakMinigameForceOverworldExit,           0x03002084  @ set by StartMinigame
.set g_pBuckbeakMinigame,                         0x03002088

@ --- include/camera.h ---
.set g_aCameraEffects_candidate,                 0x03002090
.set g_aCameraFocusSlots,                        0x030020E8
.set g_aCameraFollowOffsets,                     0x03002158

@ --- include/char_block.h ---
.set g_bBgTileAnimationCount,                    0x03002168
.set g_aBgTileAnimations,                        0x0300216C
.set g_apBgTileAnimationBuffers,                 0x030021AC

@ --- include/cheat.h ---
.set g_CheatState,                     0x030021C0

@ --- include/cheat_level_and_quest.h ---
.set g_CheatLevelAndQuestState,        0x030021C8

@ --- include/cheat_map.h ---
.set g_CheatMapState,                  0x030021E8

@ --- include/cheat_party.h ---
.set g_CheatPartyState,                0x030021F8

@ --- include/cheat_portraits.h ---
.set g_CheatPortraitsState,            0x03002210

@ --- include/cheat_sound_test.h ---
.set g_CheatSoundTestState,            0x03002218

@ --- include/cheat_wizard_cards.h ---
.set g_CheatWizardCardsState,          0x03002238

@ --- include/chest_actor.h ---
.set g_abOpenedChestFlags,         0x03002240  @ u8[32]: one bit per chest flag id; set when the chest is opened, saved with the game

@ --- include/choose_party_member.h ---
.set g_ChooseCharacterState,       0x03002260
.set g_dwChooseCharacterBgRow,     0x0300227C

@ --- include/color.h ---
.set g_aColorCycles,               0x03002280  @ ColorCycle[12]
.set g_dwColorCycleActiveMask,     0x030022E0  @ u32: bit n set = color cycle slot n was activated
.set g_dwColorCycleCount,          0x030022E4  @ u32: color cycle slots handed out since the last reset
.set g_dwPaletteRedirect,        0x030022E8  @ u32: nonzero sends palette loads to g_pPaletteWorkBuffer instead of palette RAM
.set g_pPaletteWorkBuffer,        0x030022EC  @ u16 *: 0x400-byte BG+OBJ palette work buffer, allocated by InitGammaPalette
.set g_dwObjPaletteQueueCount,     0x030022F0  @ u32: queued OBJ palette loads (25 max)
.set g_dwPaletteEffectCount,       0x030022F4  @ u32: active palette effects
.set g_aPaletteEffects,            0x030022F8  @ PaletteEffect[12]
.set g_aObjPaletteQueue,            0x030023E8
.set g_PaletteState,              0x030024B0  @ PaletteState

@ --- include/combat.h ---
.set g_pFightState,                 0x030024E8
.set g_aPartyMasterStats,           0x030024EC  @ BattleFighter[], 0x48 stride
.set g_bPendingRoomScriptChain,     0x0300260C  @ chain resumed after a game mode
.set g_bPendingRoomScriptRow,       0x0300260D  @ actor row resumed after a game mode
.set g_nBattleXpReward,             0x0300260E
.set g_nBattleGoldReward,           0x03002610
.set g_dwOverworldMonstersDisabled, 0x03002614
.set g_dwBattleRewardFlagsSnapshot,        0x03002618

@ --- include/combat_dispatch.h ---
.set g_bSelectedFighterSlot_candidate,     0x03002660
.set g_apFighterActors_candidate,         0x03002668
.set g_pBattleMessageIconActor_candidate, 0x03002684
.set g_BattleMessageIconState_candidate,   0x03002688
.set g_aBattleScanlineEffectBuffer,       0x03002690  @ ScanlineEffectEntry[4]: g_aBattleScanlineEffects with the wall line patched in
.set g_anFaintedRosterIndices,             0x030026D8

@ --- include/combat_end.h ---
.set g_dwCombatResultUnusedCounter,               0x030026E8
.set g_dwCombatResultUnusedDelay,               0x030026EC
.set g_dwCombatResultXpRemaining,           0x030026F0
.set g_pCombatResultCoinActor,               0x030026F4
.set g_pCombatResultItem0Actor,               0x030026F8
.set g_pCombatResultItem1Actor,               0x030026FC
.set g_abCombatResultPartySlots,            0x03002700
.set g_pCombatResultBg2Tilemap,             0x03002704
.set g_pCombatResultBg1Tilemap,             0x03002708
.set g_wCombatResultTextTileCursor,         0x0300270C
.set g_wCombatResultXpTileCursor,           0x0300270E
.set g_aCombatResultPartyRows,              0x03002710
.set g_wCombatResultXpNumberX,              0x03002734
.set g_CombatResultItem0Gfx,                0x03002738
.set g_CombatResultItem1Gfx,                0x03002740

@ --- include/combat_fighter.h ---
.set g_bInformusTargetMonster,             0x03002748
.set g_bSpellMissStreak,                   0x03002749
.set g_nLastDamage,                        0x0300274A
.set g_bLastTargetIndex,                   0x0300274C

@ --- include/combat_fx.h ---
.set g_effectStaging,                      0x03002750
.set g_queuedBattleBgLoad,                0x03002780

@ --- include/commands.h ---
.set g_dwRoomScriptRunState,    0x0300279C  @ room script run state
.set g_abQuestEventState,       0x030027A0  @ quest event state bytes
.set g_bRoomScriptPendingChain, 0x030028A0
.set g_bCameraShakeSoundHandle,   0x030028A4

@ --- include/credits_cutscene.h ---
.set g_dwCreditsScrollRow,    0x030028A8
.set g_dwCreditsLine,         0x030028AC
.set g_dwCreditsTileCursor,   0x030028B0
.set g_pLinearCutsceneText,   0x030028B4
.set g_pLinearCutsceneActor, 0x030028B8
.set g_dwLinearCutsceneIndex, 0x030028BC

@ --- include/cursor.h ---
.set g_pMenuCursorEmitter, 0x030028C0
.set g_nMenuCursorPaletteEffect, 0x030028C4
.set g_dwMenuCursorParticleGfxLoaded, 0x030028C8

@ --- include/decompress.h ---
.set g_pDecompressLzRleEntry,   0x030028CC
.set g_pDecompressGammaLzEntry, 0x030028D0
.set g_pDecompressLzRleIwram,   0x030028D4
.set g_pDecompressGammaLzIwram, 0x03002ACC

@ --- include/default_menu.h ---
.set g_pMenuCursorActor,                              0x03002E08
.set g_nMenuScreenPaletteEffectSlot,                  0x03002E0C

@ --- include/dementor_minigame.h ---
.set g_dwDementorMinigameScriptFlag_candidate,         0x03002E10  @ set by StartMinigame
.set g_DementorMinigame,                               0x03002E18

@ --- include/dialog.h ---
.set g_DialogState_candidate,                          0x03002E88
.set g_pDialogMacroExpandBuffer,                       0x03002EA8
.set g_awSavedBgPalette0,                              0x03002EAC
.set g_adwSavedBgPriority,                             0x03002ED0
.set g_dwDialogTextId,                                 0x03002ED8
.set g_dwDialogPortrait,                               0x03002EDC
.set g_pDialogBoxTilemap,                              0x03002EE0
.set g_pDialogPortraitActor,                          0x03002EE4
.set g_dwDialogBoxY,                                   0x03002EE8
.set g_pDialogCursorActor,                            0x03002EEC
.set g_dwDialogPageFull,                               0x03002EF0
.set g_dwDialogBoxTileRow,                             0x03002EF4
.set g_awDialogBoxPalette,                             0x03002EF8

@ --- include/ending_cutscene.h ---
.set g_pHippogriffFliesIntoAirActor,                  0x03002F18
.set g_pHippogriffFliesIntoAirActor2,                 0x03002F1C

@ --- include/flipbook.h ---
.set g_aRoomTileAnimations,                            0x03002F24
.set g_dwRoomTileAnimationCount,                       0x03002F28

@ --- include/font.h ---
.set g_aFontDescriptors,                                  0x03002F30
.set gTextRenderState,                                 0x03003170  @ TextRenderState
.set gSavedTextTarget,                                 0x030031A0  @ TextRenderState: target fields saved by SaveTextTarget
.set sTextMacroTable,                                  0x030031D0

@ --- include/game_state.h ---
.set g_saveStateBlock,                                 0x030031E0
.set g_dwUnk03003234,                                  0x03003294

@ --- include/gamecube.h ---
.set g_JoybusLinkState,          0x03003298

@ --- include/hedwig_minigame.h ---
.set g_OwlCareKitScreen,        0x030032D0

@ --- include/hero.h ---
.set g_OverworldControlState,                          0x030033B8  @ OverworldControlState: 2 x 16-byte control slots, then slot count (+0x20) and index (+0x21)
.set g_nCameraYOffset,                  0x030033DC
.set g_abRoomScriptExitParams_candidate, 0x030033DD
.set g_pPlayerActor,                    0x030033E0
.set g_pFollowerActor0,                 0x030033E4
.set g_pFollowerActor1,                 0x030033E8
.set g_bPartyCharId0,                    0x030033EC
.set g_bPartyCharId1,                    0x030033ED
.set g_bPartyCharId2,                    0x030033EE
.set g_bSelectedFieldSpell,             0x030033EF
.set g_pPlayerShadowActor_candidate,   0x030033F0
.set g_pFieldSpellNameActor,           0x03003400
.set g_pMapNameTextActor,              0x03003404
.set g_dwUnk030033A8,                   0x03003408
.set g_pFieldSpellPortraitActor,      0x0300340C
.set g_pMapNamePopupActor,             0x03003410

@ --- include/huffman.h ---
.set gDialogTextBlobBase,    0x03003420
.set gDialogTextOffsetTable, 0x03003424
.set gDialogTextTreeNodes,   0x03003428
.set g_aDecompressBgTileIwram,          0x0300342C

@ --- include/initials.h ---
.set g_HighScoreNameEntry,              0x03003530

@ --- include/input.h ---
.set g_wKeysHeld,                0x0300354C
.set g_wKeysHeldPrevious,        0x0300354E
.set g_wKeysPressed,             0x03003550
.set g_wKeysReleased,            0x03003552
.set g_wInputDisabled,           0x03003554
.set g_awPlayerKeysHeld,         0x03003556
.set g_awPlayerKeysHeldPrevious, 0x0300355A
.set g_awPlayerKeysPressed,      0x0300355E
.set g_awPlayerKeysReleased,     0x03003562
.set g_awPlayerInputDisabled_candidate, 0x03003566
.set g_dwScrollListRowCount,     0x0300356C
.set g_dwScrollListTopRow,       0x03003570
.set g_dwScrollListCursorRow,    0x03003574
.set g_dwScrollGridColumn,       0x03003580
.set g_dwScrollGridItemCount,    0x03003584
.set g_dwScrollGridColumnCount,  0x03003588
.set g_dwScrollGridVisibleRows,  0x0300358C

@ --- include/interrupts.h ---
.set g_VBlankState, 0x03003590
@ Set by InitInterruptSystem to &g_VBlankState; read by every interrupt
@ handler (HandleVBlankInterrupt, HandleHBlankInterrupt,
@ HandleTimer0Interrupt, HandleTimer3Interrupt,
@ HandleVCountInterrupt), not just vblank-related code -- Mt19937AutoSeed
@ also reads its dwVBlankCount field for entropy, but that's a secondary
@ consumer, not what the struct is for.
.set g_pVBlankState,    0x030035CC
.set gIntrTable,        0x030035D0  @ 13 x u32 handler slots dispatched by IntrMain
                                    @ template by InitInterruptSystem; dispatched by IntrMain
.set gIntrHandlerIwram, 0x03003604  @ CpuSets the live handler code into; gIntrVectorPtr
                                    @ points here
@ Sticky software copy of acked hardware IF bits, ORed by every interrupt
@ handler after acking its own bit in IF.
.set g_wPendingIntrFlags, 0x03003804
@ Reentrancy guard for HandleVBlankInterrupt; body only runs while this
@ reads back as 1.
.set g_dwVBlankIntrNestCount, 0x03003808
@ OAM DMA half-toggle.
.set g_bOamDmaHalfToggle,                    0x0300380C

@ --- include/items.h ---
.set g_ItemInventory,                     0x03003810

@ --- include/items_list.h ---
.set g_ItemList,                         0x030038A8
.set g_bItemListScroll,                  0x03003AA8
.set g_bItemListCursorRow,               0x03003AA9

@ --- include/landmarks.h ---
.set g_dwUnusedHogwartsMapShownBg,           0x03003AB0
.set g_pUnusedHogwartsMapCursor,             0x03003AB4
.set g_pUnusedHogwartsMapBg1Tilemap,         0x03003AB8
.set g_apUnusedHogwartsMapActors,           0x03003AC0

@ --- include/lupin_potion_cutscene.h ---
.set g_LupinPotionCutscene,                  0x03003AE4
.set g_aLupinPotionBg2Scroll,                0x03003B9C

@ --- include/main.h ---
.set g_dwGameModeFlags,                      0x03003BA4  @ u32: broad game-mode flags word
                                                         @ overworld/room/cutscene transitions and
                                                         @ TickGameModeStack; individual bits
                                                         @ unconfirmed
.set g_dwFrameSyncTarget,                    0x03003BA8

@ --- include/map.h ---
.set g_bCurrentRoomId,                       0x03003BB0
.set g_bControlSlotTicks_candidate,          0x03003BB8  @ byte: bumped by TickOverworldControlSlots_candidate, zeroed on room entry, never read
.set g_bPendingQuestStateOverride_candidate, 0x03003BBA
.set g_dwRoomBgFlag_candidate,               0x03003BBC
.set g_dwPauseMenuLocked,                    0x03003BC0  @ u32: nonzero blocks Start/Select menus (SetPauseMenuLocked)
.set g_bRoomSwitchState,                     0x03003BC4
.set g_pRoomActorStateBuffer,          0x03003BC8
.set g_dwPauseMenuCooldown,                  0x03003BCC  @ u32: frames until Start/Select may open a menu again; 4 after init/menu open
.set g_bTouchedMonsterRecordCount,           0x03003BD0  @ byte: queued (encounter id, kind) pair count
.set g_abTouchedMonsterRecords,              0x03003BD4  @ u8[20]: 5 x 4-byte touched-monster records
.set g_pTouchedWanderingMonster,             0x03003BE8  @ Actor *: armed wandering-monster actor

@ --- include/math.h ---
.set g_abIwramDivideCode,                   0x03003BF0
.set g_pfnIwramDivideSignedQuotient,        0x03003F30
.set g_pfnIwramDivideSignedRemainder,       0x03003F34
.set g_pfnIwramDivideUnsigned,              0x03003F38

@ --- include/mem.h ---
.set gMemPool,                               0x03003F40
.set gMemPoolCount,                          0x03003F50

@ --- include/modes.h ---
.set g_GameModeStackContext,                 0x03003F54
.set g_dwListMenuSelection,                  0x03003F74
.set g_dwPendingGameMode,                    0x03003F78
.set g_PrevGameModeStackContext,             0x03003F9C
.set g_dwTickCount,                          0x03003FC0
.set g_apMenuIconActors, 0x03003FC8

@ --- include/minigame_difficulty_select.h ---
.set g_dwSelectedMinigame,                   0x03003FE8

@ --- include/mode7.h ---
.set g_FloorEffect,                          0x03003FEC
.set g_pFloorAffineTable,                    0x0300400C
.set g_nFloorHorizonLine,                    0x03004010
.set g_dwFloorScrollSky,                     0x03004014

@ --- include/move.h ---
.set g_dwRoomCollisionPatternCount,           0x03004018
.set g_adwEdgeEndpointTypes,                  0x03004020
.set g_pRoomCollisionTilemapBuffer,           0x03004028
.set g_pRoomCollisionBehaviorTable,           0x0300402C
.set g_pRoomCollisionTilemap,                 0x03004030
.set g_dwPendingCameraFocusFlag,             0x03004034
.set g_pPendingCameraFocus_candidate,        0x03004038

@ --- include/oam.h ---
.set g_pOamShadowBuffer,    0x03004048
.set g_pOamDmaShadowBuffer, 0x0300404C
.set g_OamShadowBufferA,    0x03004050
.set g_OamShadowBufferB,    0x03004850
.set g_bOamEntryCount,      0x03005050
.set g_bOamEntryCountPrev,  0x03005051
.set g_bAffineSlotHighWaterMark, 0x03005052
.set g_abAffineSlotUsed,         0x03005053
.set g_aObjAffineSetSource, 0x03005074

@ --- include/palette.h ---
.set g_aObjPaletteSlots,               0x03005174

@ --- include/particles.h ---
.set g_pParticleEmitterActiveListHead, 0x030051F8
.set g_wActiveParticleCount,           0x030051FC
.set g_wParticleHighWaterMark,         0x030051FE
.set g_wActiveParticleEmitterCount,    0x03005200
.set g_wParticleEmitterHighWaterMark,  0x03005202
.set g_aParticles,                      0x03005204
.set g_aParticleEmitters,               0x03005208
.set g_pParticleFreeListHead,          0x0300520C
.set g_pParticleEmitterFreeListHead,   0x03005210
.set g_apParticlesByPriority,           0x03005218
.set g_abParticlesByPriorityCount,      0x03005228
.set g_pParticleActiveListHead,        0x0300522C
.set g_bParticleSpawnBlocked,          0x03005230
.set g_apParticleGfxPools,             0x03005238

@ --- include/patronus_cutscene.h ---
.set g_dwPatronusBgFront,     0x03005244
.set g_dwPatronusBgBack,      0x03005248
.set g_dwPatronusSwapPending, 0x0300524C
.set g_bPatronusGraphicIndex, 0x03005250
.set g_swPatronusBgParam,     0x03005252
.set g_nPatronusBgOffset,     0x03005254

@ --- include/pause_menu.h ---
.set g_ConnectivityMenu, 0x03005258
.set g_ListMenuState,                          0x03005280

@ --- include/pop_it_minigame.h ---
.set g_dwWizardCrackerPopItForceOverworldExit, 0x03005288
.set g_pWizardCrackerPopIt,                    0x03005290

@ --- include/pouring_minigame.h ---
.set g_ServePumpkinJuice,                      0x03005298

@ --- include/pscreen_character.h ---
.set g_StatusEquipReturnMode,      0x030052F8
.set g_StatusEquipNextMode,        0x030052FC
.set g_dwStatusEquipCharacter,     0x03005300
.set g_StatusEquipCharacterSelect, 0x03005308
.set g_bStatusEquipCharacterSlot,  0x03005318

@ --- include/pscreen_connectivity.h ---
.set g_bConnectivityMenuCursor, 0x0300531C

@ --- include/pscreen_equip.h ---
.set g_dwStatusEquipSlotType,      0x03005320
.set g_StatusEquipItemSelect,      0x03005328

@ --- include/pscreen_folio.h ---
.set g_bFoliosMenuCursor, 0x03005358

@ --- include/pscreen_folio_bruti.h ---
.set g_FolioBrutiState,            0x03005360

@ --- include/pscreen_folio_universitas.h ---
.set g_FolioUniversitasState,      0x030053A0

@ --- include/pscreen_information.h ---
.set g_HelpState,                 0x030053D0

@ --- include/pscreen_items.h ---
.set g_ItemsItemSelect,            0x03005538
.set g_ItemsSectionSelectNextMode, 0x03005544
.set g_bItemsSectionCursor,        0x03005548
.set g_dwItemUseItem,              0x0300554C
.set g_dwItemUseQuantity,          0x03005550

@ --- include/pscreen_status_equip.h ---
.set g_StatusEquipSlotSelect,      0x03005558
.set g_bStatusEquipSlot,           0x030055C4

@ --- include/pscreen_trade.h ---
.set g_CardTradeState, 0x030055C8

@ --- include/random.h ---
.set gMt19937LastRollByte,      0x030055D4
.set gMt19937DrawIndex,         0x030055D8
.set gMt19937StatePtr,          0x030055DC
.set gMt19937CurPtr,            0x030055E0
.set gMt19937RemainingIndices,  0x030055E4
.set gMt19937CurPtr2,           0x030055E8
.set gMt19937RemainingIndices2, 0x030055EC
.set gMt19937AutoSeedCallCount, 0x030055F0
.set gMt19937SeedValue,         0x030055F4

@ --- include/save.h ---
.set g_saveManager,              0x030055F8
.set g_wEepromSavedDispstat,     0x0300567C

@ --- include/screen_transitions.h ---
.set g_dwScreenPaletteDarkened,     0x03005680  @ u32: set while g_pScreenPaletteBackup holds the undarkened palette
.set g_pScreenPaletteBackup,            0x03005684
.set g_dwUnk03005638,                   0x03005698
.set g_dwScreenDarkenStepTicks_candidate, 0x0300569C

@ --- include/scroll.h ---
.set g_CameraPosition_candidate, 0x030056A0  @ CameraFocusOffset: world-space camera origin used for actor visibility
.set g_RoomSizePixels,           0x030056A8
.set g_awBgLayerTileCount,          0x030058F8
.set g_aBgTilesets,                  0x03005900
.set g_adwBgScrollEnabled,              0x03005920
.set g_wRoomBgLayer0BlocksWide,       0x0300593C
.set g_wRoomBgLayer1TilesWide,        0x03005940
.set g_wRoomBgLayer1TilesHigh,        0x03005942
.set g_wRoomBgLayer1BlocksWide,       0x03005944
.set g_wRoomBgLayer2BlocksWide,       0x0300594C
.set g_wRoomBgLayer3BlocksWide,       0x03005954
.set g_BgScroll,                       0x03005958
.set g_RoomBgAux,                       0x03005960
.set g_aBgControl,                     0x03005974
.set g_RoomBgBlockData,                0x03005994
.set g_adwBgBlockAttrOffset,           0x030059D4
.set g_apBgTileCacheEntries,            0x030059E8
.set g_apBgTileCacheBuckets,            0x030059F0
.set g_apBgTileCacheFreeSlots,          0x030059F8
.set g_awBgTileCacheFreeCount,       0x03005A08
.set g_dwUnk030059AC,                   0x03005A0C
.set g_BgLoadedScroll,                 0x03005A18

@ --- include/serial.h ---
.set g_SerialLink, 0x03005A38
.set g_aSerialRecvMessages, 0x03005A44  @ SerialMessage[2]: latest message received from each peer
.set g_SerialSendMessage, 0x03005A5C  @ SerialMessage: message queued for the next exchange
.set g_bSerialTick, 0x03005A68  @ u8: stamped into each queued message; incremented once per processed round
.set g_abSerialLastRecvSeq, 0x03005A69  @ u8[2]: bSeq of the last message handled from each peer
.set g_awSerialKeysReceived,     0x03005A6C
.set g_bSerialUnk03005A10, 0x03005A70
.set g_bSerialSeedReceived, 0x03005A71  @ u8: set once the parent's RNG seed message has been applied
.set g_bSerialChecksumRollByte, 0x03005A74
.set g_dwSerialMode, 0x03005A78  @ u32: 1 while the exchange loop runs each frame
.set g_dwSerialPlayerCount, 0x03005A7C
.set g_bSerialPeerCount, 0x03005A80  @ u8: number of peers in g_aSerialRecvMessages
.set g_bSerialLocalPlayerId, 0x03005A81
.set g_bSerialPlayerMask, 0x03005A82
.set g_SerialPlayerState,        0x03005A84
.set g_dwSerialExchangeCount, 0x03005AF0  @ u32: completed exchange rounds
.set g_dwSerialChecksumExchangeCount, 0x03005AF4
.set g_dwSerialLastExchangeTime, 0x03005AF8  @ u32: dwVBlankCount when the last exchange round finished
.set g_dwSerialPollFlags_candidate, 0x03005AFC  @ u32: bit 0 selects the message type queued by ExchangeSerialFrame_candidate
.set g_dwSerialMaxPlayers, 0x03005B00
.set g_dwSerialUnk03005AA4, 0x03005B04
.set g_dwSerialUnk03005AA8, 0x03005B08
.set g_dwSerialUnk03005AAC, 0x03005B0C
.set g_dwSerialUnk03005AB0, 0x03005B10
.set g_dwSerialConnectRetries, 0x03005B14
.set g_dwSerialUnk03005AB8, 0x03005B18
.set g_dwSerialUnk03005ABC, 0x03005B1C

@ --- include/sound.h ---
.set g_bUnreadAudioValue,        0x03005B20
.set g_bMusicPaused,             0x03005B21
.set g_bCurrentMusicModule,      0x03005B22

@ --- include/store.h ---
.set g_FredAndGeorgesShop,       0x03005B28

@ --- include/tea_leaves_minigame.h ---
.set g_DivinationTea,            0x03005B88

@ --- include/text.h ---
.set gDialogTextScratchBuf,      0x03005D68
.set gCurrentLanguage,           0x03005D6C
.set gLocaleThousandsSep,        0x03005D6D

@ --- include/text_actor.h ---
.set g_apTextActors,              0x03005D70

@ --- include/timers.h ---
.set g_aGameTimers,                     0x03005DB8

@ --- include/timeturner_cutscene.h ---
.set g_HarryHermionePortInTime,  0x03005DF8

@ --- include/title.h ---
.set g_nMainMenuTextCursor,     0x03005E10
.set g_MainMenuState,            0x03005E18

@ --- include/title_new.h ---
.set g_bSaveSlotScreenResult,    0x03005E24

@ --- include/title_load.h ---
.set g_pSaveSlotCursorActor,     0x03005E28

@ --- include/title_options.h ---
.set g_OptionsState,             0x03005E30
.set g_dwOptionsReturnMode,      0x03005E5C

@ --- include/train_cutscene.h ---
.set g_wCoolTrainTimer,          0x03005E64  @ u16: frames left in the Cool Train cutscene

@ --- include/trigger_actor.h ---
.set g_bRestoringRoomActors_candidate, 0x03005E68

@ --- include/video.h ---
.set g_ScanlineEffectState,      0x03005E70
.set g_ScanlineEffectStaging,    0x03005FA8

@ --- include/vram.h ---
.set FindFreeObjTileRunIwram, 0x030060D8
.set g_abObjTileAllocBitmap,    0x03006178
.set g_abObjTileFreeMask,       0x030061F8

@ --- include/windows.h ---
.set g_aScreenWindows,          0x03006278  @ ScreenWindow[2]; see TickScreenWindow

@ --- include/hw/eeprom.h ---
.set g_pEepromInterface,         0x03006318

@ --- Boot + runtime (asm) ---
.set gSystemStackTop,            0x03007EA0
.set gIrqStackTop,               0x03007FA0

@ --- include/interrupts.h ---
.set gIntrVectorPtr,             0x03007FFC
