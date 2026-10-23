@ Fixed RAM addresses of the symbols declared extern in C and referenced
@ from asm. ram_symbols.jp.inc holds the JP values in the same layout.

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
.set g_pTimer2DebugPc,        0x030015A0  @ code ptr: IntrMain stores [sp,#0x14] here on a Timer 2 IRQ
                                          @ (saved lr per the BIOS IRQ frame, unverified); read by
                                          @ HandleTimer2Interrupt

@ --- include/actor.h ---
.set g_ActiveActorListState, 0x030015B0  @ {ListNode *pHead; ListNode *pTail;}
.set g_apOamQueue,             0x030015B8  @ Actor *[0x69]: onscreen actors drawn in depth order
.set g_dwOamQueueCount,        0x0300175C
.set g_apSpriteFrameQueue,     0x03001760  @ Actor *[15]: visible actors with sprite cells
.set g_bSpriteFrameQueueCount, 0x0300179C  @ u8
.set g_dwActorDepthSortEnabled, 0x030017A0
.set g_apCollisionQueue,             0x030017A4  @ Actor *[0x69]: actors awaiting the pairwise check
.set g_dwCollisionQueueCount,        0x03001948
.set SortActorsByDepthIwram,            0x0300194C  @ IWRAM copy of SortActorsByDepth
.set CheckActorCollisionsIwram,  0x03001A10  @ IWRAM copy of CheckActorCollisions
.set g_ActorPoolState,              0x03001C08  @ ActorPoolState, 0x1B4 bytes
.set g_pActorPoolAuxBuffer,         0x03001DBC  @ void *: 0x104-byte AllocZeroed'd buffer
.set g_dwActorListTicked_candidate, 0x03001DC0  @ set to 1 by TickActiveActors, never cleared; gates FreeActor's VRAM tile release
.set g_dwOamScaleRoundBias,                0x03001DC4  @ zeroed by InitActorPool
.set g_ReceivedItemGfx,              0x03001DC8  @ ActorGfxRecord: the item TickActorReceiveReward holds up

@ --- include/area.h ---
.set g_adwPartyMemberArrived,          0x03001DD0  @ u32[3]: player and follower 0/1 reached a Spongify pad or raising platform
.set g_wRoomResourceFlags_candidate, 0x03001DDC  @ u16: bit 0 = the room also has a second actor/switch row
.set g_bRoomScriptCurrentChain,        0x03001DDE  @ u8: chain the VM is walking
.set g_pRoomScriptYieldContinuation, 0x03001DE0  @ u32 *: record to resume at after a yield, or 0
.set g_pRoomScriptNextRecord,        0x03001DE4  @ u32 *: record following the one being dispatched
.set g_bRoomScriptCallStackDepth,    0x03001DE8  @ u8: nested chain calls in flight
.set g_bRoomScriptYieldOpcode,            0x03001DE9  @ u8: opcode a running room script yielded on
.set g_pRoomTableBuffer,                  0x03001DEC  @ RoomBlobHeader *: 0x2200-byte buffer holding the room's runtime tables
.set g_dwRoomChainRanThisFrame_candidate, 0x03001DF0  @ u32: set to 1 by RespawnGroupAndRunChain while it runs a room chain; cleared by
                                                      @ HandleOverworldPauseMenuInput each frame, which skips the menu check while it is set
.set g_pRoomActorTable,            0x03001DF4  @ RoomBlobTable *: per-column, per-row tile records
.set g_pRoomRouteTable,       0x03001DF8  @ RoomBlobTable *: per-route waypoint lists
.set g_pRoomScriptChainTable, 0x03001DFC  @ RoomScriptTable *: current room's chain offset table
.set g_aRoomScriptCallStack,        0x03001E00  @ RoomScriptCallFrame[]: saved callers, indexed by depth

@ --- include/background.h ---
.set g_BgState,        0x03001E80  @ BgState: dwFlags, then the BgLayer[4] array that g_aBgLayers addresses
@ Forces one extra CommitBgLayers call this vblank.
.set g_bForcePendingBgWritesFlush,               0x03002038

@ --- include/boggart_minigame.h ---
.set g_dwBoggartMinigameScriptFlag_candidate,    0x03002040  @ u32: set by StartMinigame
.set g_BoggartMinigame,                          0x03002048  @ BoggartMinigameState

@ --- include/buckbeak_minigame.h ---
.set g_dwBuckbeakMinigameForceOverworldExit,           0x03002084  @ u32: set by StartMinigame
.set g_pBuckbeakMinigame,                         0x03002088  @ BuckbeakMinigameState *: allocated for the minigame's duration

@ --- include/camera.h ---
.set g_aCameraEffects_candidate,                 0x03002090  @ CameraEffect[2]: one 0x2C-byte record per control slot
.set g_aCameraFocusSlots,                        0x030020E8  @ CameraFocusSlot[2]: 0x38 bytes each
.set g_aCameraFollowOffsets,                     0x03002158  @ s32[2][2]: per-slot (X, Y) offset set by SetCameraFollowTarget_candidate

@ --- include/char_block.h ---
.set g_bBgTileAnimationCount,                    0x03002168  @ u8: number of registered BG tile animations
.set g_aBgTileAnimations,                        0x0300216C  @ BgTileAnimEntry[4]: 0x10 bytes each; size inferred from the span up to g_apBgTileAnimationBuffers
.set g_apBgTileAnimationBuffers,                 0x030021AC  @ void *[4]: decoded tile buffer of each BG tile animation

@ --- include/cheat.h ---
.set g_CheatState,                     0x030021C0  @ CheatState: {Actor *pCursorActor; u32 dwSelection}

@ --- include/cheat_level_and_quest.h ---
.set g_CheatLevelAndQuestState,        0x030021C8  @ CheatLevelAndQuestState

@ --- include/cheat_map.h ---
.set g_CheatMapState,                  0x030021E8  @ CheatMapState

@ --- include/cheat_party.h ---
.set g_CheatPartyState,                0x030021F8  @ CheatPartyState

@ --- include/cheat_portraits.h ---
.set g_CheatPortraitsState,            0x03002210  @ CheatPortraitsState: {Actor *pPortraitActor; u32 dwSelection}

@ --- include/cheat_sound_test.h ---
.set g_CheatSoundTestState,            0x03002218  @ CheatSoundTestState

@ --- include/cheat_wizard_cards.h ---
.set g_CheatWizardCardsState,          0x03002238  @ CheatWizardCardsState: {Actor *pCardActor; u32 dwSelection}

@ --- include/chest_actor.h ---
.set g_abOpenedChestFlags,         0x03002240  @ u8[32]: one bit per chest flag id; set when the chest is opened, saved with the game

@ --- include/choose_party_member.h ---
.set g_ChooseCharacterState,       0x03002260  @ ChooseCharacterState
.set g_dwChooseCharacterBgRow,     0x0300227C  @ u32: BG2 tile row of the choose-character screen panel

@ --- include/color.h ---
.set g_aColorCycles,               0x03002280  @ ColorCycle[12]
.set g_dwColorCycleActiveMask,     0x030022E0  @ u32: bit n set = color cycle slot n was activated
.set g_dwColorCycleCount,          0x030022E4  @ u32: color cycle slots handed out since the last reset
.set g_dwPaletteRedirect,        0x030022E8  @ u32: nonzero sends palette loads to g_pPaletteWorkBuffer instead of palette RAM
.set g_pPaletteWorkBuffer,        0x030022EC  @ u16 *: 0x400-byte BG+OBJ palette work buffer, allocated by InitGammaPalette
.set g_dwObjPaletteQueueCount,     0x030022F0  @ u32: queued OBJ palette loads (25 max)
.set g_dwPaletteEffectCount,       0x030022F4  @ u32: active palette effects
.set g_aPaletteEffects,            0x030022F8  @ PaletteEffect[12]
.set g_aObjPaletteQueue,            0x030023E8  @ ObjPaletteQueueEntry[25]
.set g_PaletteState,              0x030024B0  @ PaletteState

@ --- include/combat.h ---
.set g_pFightState,                 0x030024E8  @ FightState *, the active battle's state
.set g_aPartyMasterStats,           0x030024EC  @ BattleFighter[], 0x48 stride, by FighterType
.set g_bPendingRoomScriptChain,     0x0300260C  @ u8: switch-state chain to walk on a resume transition
.set g_bPendingRoomScriptRow,       0x0300260D  @ u8: actor row to respawn on a resume transition
.set g_nBattleXpReward,             0x0300260E  @ u16: XP earned this battle, one pool shared by the whole party
.set g_nBattleGoldReward,           0x03002610  @ u16: Sickles earned this battle; also the scratch amount for gold reward grants
.set g_dwOverworldMonstersDisabled, 0x03002614  @ u32: nonzero suppresses wandering-monster spawns
.set g_dwBattleRewardFlagsSnapshot,        0x03002618  @ u32: FightState->bBonusRewardFlags copy, see RollBattleItemDrops

@ --- include/combat_dialog.h ---
.set g_aawTargetFlashPalette,             0x03002620  @ u16[2][16]: target flash frames, the sprite's palette then gBattleEffect002Palette

@ --- include/combat_dispatch.h ---
.set g_dwSelectedBattleMenuIcon,    0x03002660  @ u32: battle menu row whose icon is enlarged
.set g_apBattleMenuIconActors,      0x03002668  @ Actor*[7]: battle menu icons, one per menu row
.set g_pStatsPortraitActor,         0x03002684  @ Actor *: the 40x40 face beside the battle stats panel
.set g_StatsPortraitPaletteLoad,    0x03002688  @ StatsPortraitPaletteLoad: the portrait palette HandleBattleVBlank copies
.set g_aBattleScanlineEffectBuffer, 0x03002690  @ ScanlineEffectEntry[4]: g_aBattleScanlineEffects with the wall line patched in
.set g_dwBattleItemToConsume,       0x030026D0  @ u32: item id the ally target menu consumes, set by ConfirmItemMenu
.set g_anFaintedRosterIndices,      0x030026D8  @ s32[4]: fainted fighters' roster indices this battle, sentinel -1

@ --- include/combat_end.h ---
.set g_dwCombatResultUnusedCounter,              0x030026E8  @ u32: zeroed by InitializeCombatResult; no reader found
.set g_dwCombatResultUnusedDelay,                0x030026EC  @ u32: 0x78 after InitializeCombatResult; no reader found
.set g_dwCombatResultXpRemaining,                0x030026F0  @ u32: XP still to be counted up on the combat result screen
.set g_pCombatResultCoinActor,                   0x030026F4  @ Actor *: coin beside the Sickles total, NULL when no Sickles were earned
.set g_pCombatResultItem0Actor,                  0x030026F8  @ Actor *: icon of the first dropped item, NULL without a drop
.set g_pCombatResultItem1Actor,                  0x030026FC  @ Actor *: icon of the second dropped item, NULL without a second drop
.set g_abCombatResultPartySlots,                 0x03002700  @ u8[3]: party stats slot shown per portrait position
.set g_pCombatResultBg2Tilemap,                  0x03002704  @ void *: BG2 graphic (LoadBgGraphicTiles result), partly copied per party member
.set g_pCombatResultBg1Tilemap,                  0x03002708  @ void *: BG1 graphic (LoadBgGraphicTiles result), partly copied per party member
.set g_wCombatResultTextTileCursor,              0x0300270C  @ u16: next free text tile of the combat result screen
.set g_wCombatResultXpTileCursor,                0x0300270E  @ u16: first tile of the XP number, redrawn each TickCombatResultXpCounter
.set g_aCombatResultPartyRows,                   0x03002710  @ CombatResultPartyRow[3]
.set g_wCombatResultXpNumberX,                   0x03002734  @ u16: screen x of the XP number
.set g_CombatResultItem0Gfx,                     0x03002738  @ ActorGfxRecord: tile/frame data of the first dropped item's icon
.set g_CombatResultItem1Gfx,                     0x03002740  @ ActorGfxRecord: tile/frame data of the second dropped item's icon

@ --- include/combat_fighter.h ---
.set g_bInformusTargetMonster,             0x03002748  @ byte: monster id Informus last targeted; the Folio Bruti opens on it
.set g_bSpellMissStreak,                   0x03002749  @ byte: consecutive-miss streak breaker
.set g_nLastDamage,                        0x0300274A  @ u16: last computed attack/status damage
.set g_bLastTargetIndex,                   0x0300274C  @ byte: last attack's target fighter index

@ --- include/combat_fx.h ---
.set g_effectStaging,                      0x03002750  @ EffectStaging: battle-effect staging area, see TriggerBattleEffect
.set g_queuedBattleBgLoad,                0x03002780  @ QueuedBgLoad: BG load FlushQueuedBattleDma copies to VRAM at vblank

@ --- include/commands.h ---
.set g_dwRoomScriptRunState,    0x0300279C  @ u32: room script run state; InitializeOverworld resets 4 to 0 and only resumes a chain in state 2
.set g_abQuestEventState,       0x030027A0  @ u8[]: quest event state bytes
.set g_bRoomScriptPendingChain, 0x030028A0  @ u8: chain a handler asked to jump to; 0xFF = none
.set g_bCameraShakeSoundHandle,   0x030028A4  @ u8: sound handle TickCameraFocus_candidate stops when a camera shake ends

@ --- include/credits_cutscene.h ---
.set g_dwCreditsScrollRow,    0x030028A8  @ u32: last credits text row the scroll reached
.set g_dwCreditsLine,         0x030028AC  @ u32: next credits text line to draw
.set g_dwCreditsTileCursor,   0x030028B0  @ u32: next free credits text tile
.set g_pLinearCutsceneText,   0x030028B4  @ u8 *: unread remainder of the cutscene's text
.set g_pLinearCutsceneActor, 0x030028B8  @ Actor *
.set g_dwLinearCutsceneIndex, 0x030028BC  @ u32: GameMode - Credits

@ --- include/cursor.h ---
.set g_pMenuCursorEmitter, 0x030028C0  @ ParticleEmitter *: emitter of the cursor actor built by SpawnMenuCursorActor(4)
.set g_nMenuCursorPaletteEffect, 0x030028C4  @ s32: SpawnMenuCursorActor(4)'s palette effect handle, -1 = none
.set g_dwMenuCursorParticleGfxLoaded, 0x030028C8  @ u32: the cursor's particle graphics pool is loaded

@ --- include/decompress.h ---
.set g_pDecompressLzRleEntry,   0x030028CC  @ DecompressFunc: = g_pDecompressLzRleIwram
.set g_pDecompressGammaLzEntry, 0x030028D0  @ DecompressFunc: = g_pDecompressGammaLzIwram
.set g_pDecompressLzRleIwram,   0x030028D4  @ u8[0x1F8]: IWRAM copy of DecompressLzRle
.set g_pDecompressGammaLzIwram, 0x03002ACC  @ u8[0x33C]: IWRAM copy of DecompressGammaLz

@ --- include/default_menu.h ---
.set g_pMenuCursorActor,                              0x03002E08  @ Actor *: cursor actor created by BeginMenuScreen
.set g_nMenuScreenPaletteEffectSlot,                  0x03002E0C  @ s32: selection pulse palette effect of BeginMenuScreen, -1 when none

@ --- include/dementor_minigame.h ---
.set g_dwDementorMinigameScriptFlag_candidate,         0x03002E10  @ u32: set by StartMinigame
.set g_DementorMinigame,                               0x03002E18  @ DementorMinigameState

@ --- include/dialog.h ---
.set g_DialogState_candidate,                          0x03002E88  @ DialogState
.set g_pDialogMacroExpandBuffer,                       0x03002EA8  @ u8 *: 0x400-byte buffer, allocated by InitDialogBox
.set g_awSavedBgPalette0,                              0x03002EAC  @ u16[16]: BG palette bank 0 saved by InitializeDialog and InitializeChooseCharacter, restored by their exits
.set g_adwSavedBgPriority,                             0x03002ED0  @ u32[2]: BG0/BG1 priority saved by InitializeDialog, restored by ExitDialog
.set g_dwDialogTextId,                                 0x03002ED8  @ u32: dialog string id of the line being shown
.set g_dwDialogPortrait,                               0x03002EDC  @ u32: g_aDialogPortraits index of the line being shown
.set g_pDialogBoxTilemap,                              0x03002EE0  @ void *: tilemap of the dialog box BG graphic
.set g_pDialogPortraitActor,                          0x03002EE4  @ Actor *: speaker portrait sprite of the dialog box
.set g_dwDialogBoxY,                                   0x03002EE8  @ u32: screen line of the dialog box's top edge, 0x9F hidden .. 0x7B shown
.set g_pDialogCursorActor,                            0x03002EEC  @ Actor *: menu cursor of the dialog box
.set g_dwDialogPageFull,                               0x03002EF0  @ u32: nonzero once the box's text page is fully drawn
.set g_dwDialogBoxTileRow,                             0x03002EF4  @ u32: BG1 tile row the box's tilemap is drawn at
.set g_awDialogBoxPalette,                             0x03002EF8  @ u16[16]: dialog box BG palette, DMAed to bank 0 at the box's top line

@ --- include/ending_cutscene.h ---
.set g_pHippogriffFliesIntoAirActor,                  0x03002F18  @ Actor *
.set g_pHippogriffFliesIntoAirActor2,                 0x03002F1C  @ Actor *

@ --- include/flipbook.h ---
.set g_aRoomTileAnimations,                            0x03002F24  @ RoomTileAnimation *: 32 entries, allocated by InitRoomTileAnimationTable
.set g_dwRoomTileAnimationCount,                       0x03002F28  @ u32: entries in use in g_aRoomTileAnimations

@ --- include/font.h ---
.set g_aFontDescriptors,                                  0x03002F30  @ FontDescriptor[12][2], filled by LoadFontDescriptor
.set gTextRenderState,                                 0x03003110  @ TextRenderState
.set gSavedTextTarget,                                 0x03003140  @ TextRenderState: target fields saved by SaveTextTarget
.set sTextMacroTable,                                  0x03003170  @ u8 *[4]: 0x40-byte heap buffers (allocated by InitTextMacroTable) holding the strings that 0x40-prefixed text codes 0x31-0x34 expand to

@ --- include/game_state.h ---
.set g_saveStateBlock,                                 0x03003180  @ live save-adjacent state (money, playtime, flags, ...); doc-level array at +0x10
.set g_dwIceStepSoundPending,                                  0x03003234  @ u32: see include/game_state.h

@ --- include/gamecube.h ---
.set g_JoybusLinkState,          0x03003238  @ JoybusLinkState: GameCube link (JOYBUS) session state

@ --- include/hedwig_minigame.h ---
.set g_OwlCareKitScreen,        0x03003270  @ OwlCareKitScreenState: live state of the Owl Care Kit care screen

@ --- include/hero.h ---
.set g_OverworldControlState,                          0x03003358  @ OverworldControlState: 2 x 16-byte control slots, then slot count (+0x20) and index (+0x21)
.set g_nCameraYOffset,               0x0300337C  @ s8: camera Y offset in pixels; 18 after InitRoomBgState
.set g_abRoomScriptExitParams_candidate, 0x0300337D  @ u8[2]: filled by the dialog-close and return-to-overworld opcodes
.set g_pPlayerActor,                    0x03003380  @ Actor *: the player's overworld actor
.set g_pFollowerActor0,                 0x03003384  @ Actor *: first party follower, NULL while empty
.set g_pFollowerActor1,                 0x03003388  @ Actor *: second party follower, NULL while empty
.set g_bPartyCharId0,                    0x0300338C  @ u8: character id of the party leader
.set g_bPartyCharId1,                    0x0300338D  @ u8: character id of the first follower
.set g_bPartyCharId2,                    0x0300338E  @ u8: character id of the second follower
.set g_bSelectedFieldSpell,              0x0300338F  @ u8: index into g_aFieldSpells
.set g_pPlayerShadowActor_candidate,   0x03003390  @ Actor *: type 0x11 actor SpawnPlayerActor creates for the player
.set g_pPartyTrail,                    0x03003398  @ PartyTrailStep *: ring buffer of PARTY_TRAIL_LENGTH player steps the followers replay
.set g_bPartyTrailWriteIndex,          0x0300339C  @ u8: next g_pPartyTrail entry the player's step is written to
.set g_bPartyTrailReadIndex0,          0x0300339D  @ u8: next g_pPartyTrail entry follower 0 replays
.set g_bPartyTrailReadIndex1,          0x0300339E  @ u8: next g_pPartyTrail entry follower 1 replays
.set g_pFieldSpellNameActor,            0x030033A0  @ Actor *: selected field spell name text
.set g_pMapNameTextActor,               0x030033A4  @ Actor *: room name text of ShowMapNamePopup
.set g_dwUnk030033A8,                    0x030033A8  @ u32: zeroed by ResetPartyState and SpawnPartyFollowers; no reader found
.set g_pFieldSpellPortraitActor,        0x030033AC  @ Actor *: face portrait of the selected field spell's character
.set g_pMapNamePopupActor,             0x030033B0  @ Actor *: 240x16 bar sprite behind the room name text
.set g_pFieldSpellIconActor,           0x030033B4  @ Actor *: selected field spell's icon
.set g_PartyTrailLastPos,              0x030033B8  @ FixedPoint: player position at the last g_pPartyTrail step

@ --- include/huffman.h ---
.set gDialogTextBlobBase,    0x030033C0  @ active language blob's base pointer (0 = none installed)
.set gDialogTextOffsetTable, 0x030033C4  @ pointer to the active blob's per-string-ID u32[] offset table
.set gDialogTextTreeNodes,   0x030033C8  @ pointer to the active blob's Huffman tree node table
.set g_aDecompressBgTileIwram,      0x030033CC  @ u8[0x100]: IWRAM copy of DecompressBgTile

@ --- include/initials.h ---
.set g_HighScoreNameEntry,          0x030034D0  @ HighScoreNameEntryState

@ --- include/input.h ---
.set g_wKeysHeld,                0x030034EC  @ u16: current held-key bitmask (standard GBA KEYINPUT bit
                                             @ order), updated once per frame by UpdateKeyInput
.set g_wKeysHeldPrevious,        0x030034EE  @ u16: g_wKeysHeld from the previous frame's update
.set g_wKeysPressed,             0x030034F0  @ u16: keys newly pressed this frame (currentHeld &
                                             @ ~previousHeld)
.set g_wKeysReleased,            0x030034F2  @ u16: keys newly released this frame (previousHeld & ~currentHeld)
.set g_wInputDisabled,           0x030034F4  @ u16: nonzero forces all key state above (and the per-player
                                             @ arrays below) to 0 every frame instead of reading KEYINPUT
.set g_awPlayerKeysHeld,         0x030034F6  @ u16[2]: per-player held-key masks, serial-link input path
.set g_awPlayerKeysHeldPrevious, 0x030034FA  @ u16[2]: previous-frame counterpart of the above
.set g_awPlayerKeysPressed,      0x030034FE  @ u16[2]: per-player newly-pressed masks
.set g_awPlayerKeysReleased,     0x03003502  @ u16[2]: per-player newly-released masks
.set g_awPlayerInputDisabled_candidate, 0x03003506  @ u16[2]: written with g_wInputDisabled by EnableKeyInput and DisableKeyInput; no reader found
.set g_dwScrollListRowCount,     0x0300350C  @ u32: row count of the scrolling list/grid
.set g_dwScrollListTopRow,       0x03003510  @ u32: first visible row
.set g_dwScrollListCursorRow,    0x03003514  @ u32: cursor row within the visible window
.set g_dwScrollGridColumn,       0x03003520  @ u32: grid cursor column
.set g_dwScrollGridItemCount,    0x03003524  @ u32: grid item count
.set g_dwScrollGridColumnCount,  0x03003528  @ u32: grid columns per row
.set g_dwScrollGridVisibleRows,  0x0300352C  @ u32: grid rows visible at once

@ --- include/interrupts.h ---
.set g_VBlankState, 0x03003530  @ the object g_pVBlankState is set to point at
@ Set by InitInterruptSystem to &g_VBlankState; read by every interrupt
@ handler (HandleVBlankInterrupt, HandleHBlankInterrupt,
@ HandleTimer0Interrupt, HandleTimer3Interrupt,
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
@ handler after acking its own bit in IF.
.set g_wPendingIntrFlags, 0x030037A4
@ Reentrancy guard for HandleVBlankInterrupt; body only runs while this
@ reads back as 1.
.set g_dwVBlankIntrNestCount, 0x030037A8
@ OAM DMA half-toggle.
.set g_bOamDmaHalfToggle,                    0x030037AC

@ --- include/items.h ---
.set g_ItemInventory,                     0x030037B0  @ ItemInventory: item counts and equipped items, see include/game/items.h

@ --- include/items_list.h ---
.set g_ItemList,                         0x03003848  @ ItemListState: the scrolling item list
.set g_bItemListScroll,                  0x03003A48  @ s8: index of the item on the top row
.set g_bItemListCursorRow,               0x03003A49  @ s8: on-screen cursor row

@ --- include/landmarks.h ---
.set g_dwUnusedHogwartsMapShownBg,           0x03003A50  @ u32
.set g_pUnusedHogwartsMapCursor,             0x03003A54  @ Actor *
.set g_pUnusedHogwartsMapBg1Tilemap,         0x03003A58  @ void *
.set g_apUnusedHogwartsMapActors,           0x03003A60  @ Actor *[9]

@ --- include/lupin_potion_cutscene.h ---
.set g_LupinPotionCutscene,                  0x03003A84  @ LupinPotionCutsceneState
.set g_aLupinPotionBg2Scroll,                0x03003B3C  @ s32[2]

@ --- include/main.h ---
.set g_dwGameModeFlags,                      0x03003B44  @ u32: GameModeFlags (include/modes.h)
.set g_dwFrameSyncTarget,                    0x03003B48  @ u32: frame-pacing target set once by AgbMain,
                                                         @ consumed only by WaitForVBlank

@ --- include/map.h ---
.set g_bCurrentRoomId,                       0x03003B50  @ byte: current room/map id
.set g_bControlSlotTicks_candidate,          0x03003B58  @ byte: bumped by TickOverworldControlSlots_candidate, zeroed on room entry, never read
.set g_bPendingQuestStateOverride_candidate, 0x03003B5A  @ u8: 0xFF = none; else copied into quest state 0 on room entry
.set g_dwRoomBgFlag_candidate,               0x03003B5C  @ u32: set to 1 by many rooms while loading; also read by EndFieldSpellEffect
.set g_dwPauseMenuLocked,                    0x03003B60  @ u32: nonzero blocks Start/Select menus (SetPauseMenuLocked)
.set g_bRoomSwitchState,                     0x03003B64  @ u8: current room switch state (0 or 1), see SetRoomSwitchState
.set g_pRoomActorStateBuffer,               0x03003B68  @ 0x20BC-byte buffer, allocated by InitRoomState
.set g_dwPauseMenuCooldown,                  0x03003B6C  @ u32: frames until Start/Select may open a menu again; 4 after init/menu open
.set g_bTouchedMonsterRecordCount,           0x03003B70  @ byte: queued (encounter id, kind) pair count
.set g_aTouchedMonsterRecords,               0x03003B74  @ TouchedMonsterRecord[5]: 4-byte touched-monster records
.set g_pTouchedWanderingMonster,             0x03003B88  @ Actor *: armed wandering-monster actor

@ --- include/map_doors.h ---
.set g_dwPortraitPassageExitParam,          0x03003B8C  @ u32: portrait door exit param held across portrait_room_passage

@ --- include/math.h ---
.set g_abIwramDivideCode,                   0x03003B90  @ u8[0x340]: IWRAM copy of the ARM divide routines (InstallIwramDivideRoutines)
.set g_pfnIwramDivideSignedQuotient,        0x03003ED0  @ IWRAM entry of DivideSignedQuotient
.set g_pfnIwramDivideSignedRemainder,       0x03003ED4  @ IWRAM entry of DivideSignedRemainder
.set g_pfnIwramDivideUnsigned,              0x03003ED8  @ IWRAM entry of DivideUnsignedWorker

@ --- include/mem.h ---
.set gMemPool,                               0x03003EE0  @ MemPool[]; only pool 0 (index 0) is ever registered
.set gMemPoolCount,                          0x03003EF0  @ u32: live pool count, incremented by InitMemoryPool

@ --- include/modes.h ---
.set g_GameModeStackContext,                 0x03003EF4  @ {dwCurrentGameMode, dwCurrentGameModeArg1, dwCurrentGameModeArg2, dwCurrentGameModeArg3, ...}
.set g_dwListMenuSelection,                  0x03003F14  @ u32: selected row of the current list menu
.set g_dwPendingGameMode,                    0x03003F18  @ GameMode: mirrors g_GameModeStackContext's layout for the not-yet-applied mode
.set g_PrevGameModeStackContext,             0x03003F3C  @ GameModeStackContext, 0x24 bytes
.set g_dwTickCount,                          0x03003F60  @ u32: incremented once per TickGameModeStack call
.set g_apMenuIconActors, 0x03003F68  @ Actor *[]: actors registered by index via RegisterMenuIconActor

@ --- include/minigame_difficulty_select.h ---
.set g_dwSelectedMinigame,                   0x03003F88  @ u32: minigame index chosen in the minigame menu, read by the difficulty select

@ --- include/mode7.h ---
.set g_FloorEffect,                          0x03003F8C  @ FloorEffectState: camera of the per-scanline floor
.set g_pFloorAffineTable,                    0x03003FAC  @ BgAffineDst *: one BG2 affine record per scanline
.set g_nFloorHorizonLine,                    0x03003FB0  @ s32: first floor scanline
.set g_dwFloorScrollSky,                     0x03003FB4  @ u32: nonzero scrolls BG1 with the floor heading

@ --- include/move.h ---
.set g_dwRoomCollisionPatternCount,           0x03003FB8  @ u32: pattern count from the collision tilemap header
.set g_adwEdgeEndpointTypes,                  0x03003FC0  @ u32[2]
.set g_pRoomCollisionTilemapBuffer,           0x03003FC8  @ u8 *: decompressed collision tilemap resource, 4-byte header then the pattern ids
.set g_pRoomCollisionBehaviorTable,           0x03003FCC  @ u8 *: 16 collision bytes per pattern
.set g_pRoomCollisionTilemap,                 0x03003FD0  @ u16 *: pattern ids of the 32x32-pixel blocks, g_pRoomCollisionTilemapBuffer + 4
.set g_dwFieldSpellActive,                   0x03003FD4  @ u32: 1 while a field spell effect actor exists; cleared on room entry
.set g_pFieldSpellEffectActor,               0x03003FD8  @ Actor *: the field spell effect actor
.set g_pFieldSpellCompanionActor,            0x03003FDC  @ Actor *: Lumos's glow actor
.set g_nLumosScale,                          0x03003FE0  @ s32: 16.16 affine scale of Lumos's light

@ --- include/npc_actor.h ---
.set g_nNpcPaletteEffectSlot,               0x03003FE4  @ s32: StartPaletteEffect handle of an NPC script animation's flash

@ --- include/oam.h ---
.set g_pOamShadowBuffer,         0x03003FE8
.set g_pOamDmaShadowBuffer,      0x03003FEC
.set g_OamShadowBufferA,         0x03003FF0
.set g_OamShadowBufferB,         0x030047F0
.set g_bOamEntryCount,           0x03004FF0
.set g_bOamEntryCountPrev,       0x03004FF1
.set g_bAffineSlotHighWaterMark, 0x03004FF2  @ highest allocated affine slot index + 1; see AllocAffineSlot
.set g_abAffineSlotUsed,         0x03004FF3  @ u8[32], one per affine hardware slot; see AllocAffineSlot/FreeAffineSlot
.set g_aObjAffineSetSource,      0x03005014  @ ObjAffineSource[32] (8-byte stride), fed to bios_ObjAffineSet by CommitObjAffineMatrices

@ --- include/palette.h ---
.set g_aObjPaletteSlots,               0x03005114  @ ObjPaletteSlot[16]

@ --- include/particles.h ---
.set g_pParticleEmitterActiveListHead, 0x03005198  @ ListNode *
.set g_wActiveParticleCount,           0x0300519C  @ u16
.set g_wParticleHighWaterMark,         0x0300519E  @ u16
.set g_wActiveParticleEmitterCount,    0x030051A0  @ u16
.set g_wParticleEmitterHighWaterMark,  0x030051A2  @ u16
.set g_aParticles,                    0x030051A4  @ Particle *: MAX_PARTICLES entries, allocated by InitParticlePools
.set g_aParticleEmitters,             0x030051A8  @ ParticleEmitter *: MAX_PARTICLE_EMITTERS entries
.set g_pParticleFreeListHead,          0x030051AC  @ ListNode *
.set g_pParticleEmitterFreeListHead,   0x030051B0  @ ListNode *
.set g_apParticlesByPriority,         0x030051B8  @ Particle **[4]: active particles bucketed by OAM priority
.set g_abParticlesByPriorityCount,    0x030051C8  @ u8[4]: entries in each g_apParticlesByPriority array
.set g_pParticleActiveListHead,        0x030051CC  @ ListNode *
.set g_bParticleSpawnBlocked,          0x030051D0  @ u8: set when a particle's OAM submit fails (queue full); blocks spawning until TickParticleEmitters clears it
.set g_apParticleGfxPools,             0x030051D8  @ ParticleGfxEntry *[]

@ --- include/patronus_cutscene.h ---
.set g_dwPatronusBgFront,     0x030051E4  @ u32
.set g_dwPatronusBgBack,      0x030051E8  @ u32
.set g_dwPatronusSwapPending, 0x030051EC  @ u32
.set g_bPatronusGraphicIndex, 0x030051F0  @ u8
.set g_swPatronusBgParam,     0x030051F2  @ s16
.set g_nPatronusBgOffset,     0x030051F4  @ s32, 16.16

@ --- include/pause_menu.h ---
.set g_ConnectivityMenu, 0x030051F8  @ ListMenuDefinition: RAM copy of g_ConnectivityMenuTemplate with the active row table
.set g_ListMenuState,                          0x03005220  @ ListMenuState: pause menu cursor row saved by ExitInGameMenu, definition of the list menu on screen

@ --- include/pop_it_minigame.h ---
.set g_dwWizardCrackerPopItForceOverworldExit, 0x03005228  @ u32: set by the StartMinigame room script opcode
.set g_nWizardCrackerPopItBlendHoldFrame,      0x0300522C  @ s32: frame the selection blend pulse paused at, or -1
.set g_pWizardCrackerPopIt,                    0x03005230  @ WizardCrackerPopItState *: allocated for the minigame's duration

@ --- include/pouring_minigame.h ---
.set g_ServePumpkinJuice,                      0x03005238  @ ServePumpkinJuiceState

@ --- include/pscreen_character.h ---
.set g_StatusEquipReturnMode,      0x03005298  @ GameMode: StatusEquipCharacterSelect returns to on B (InGameMenu, InGameMenuFadeIn or ItemsItemSelect)
.set g_StatusEquipNextMode,        0x0300529C  @ GameMode: StatusEquipCharacterSelect advances to on A (StatusEquipSlotSelect or QuantitySelectScreen)
.set g_dwStatusEquipCharacter,     0x030052A0  @ u32: FighterType chosen in StatusEquipCharacterSelect, read by the slot/item screens and ItemUseScreen
.set g_StatusEquipCharacterSelect, 0x030052A8  @ StatusEquipCharacterSelectState: slot presence flags and pending mode
.set g_bStatusEquipCharacterSlot,  0x030052B8  @ u8: StatusEquipCharacterSelect cursor slot

@ --- include/pscreen_connectivity.h ---
.set g_bConnectivityMenuCursor, 0x030052BC  @ s8: Connectivity row restored on re-entry

@ --- include/pscreen_equip.h ---
.set g_dwStatusEquipSlotType,      0x030052C0  @ u32: equipment type (0-5) of the slot chosen in StatusEquipSlotSelect
.set g_StatusEquipItemSelect,      0x030052C8  @ StatusEquipItemSelectState: item select list, stat arrows and saved palette

@ --- include/pscreen_folio.h ---
.set g_bFoliosMenuCursor, 0x030052F8  @ s8: Folios row restored on re-entry

@ --- include/pscreen_folio_bruti.h ---
.set g_FolioBrutiState,            0x03005300  @ FolioBrutiState: the Folio Bruti screen state

@ --- include/pscreen_folio_universitas.h ---
.set g_FolioUniversitasState,      0x03005340  @ FolioUniversitasState: the Folio Universitas screen state

@ --- include/pscreen_information.h ---
.set g_HelpState,                 0x03005370  @ HelpState: the Help / HelpTopicScreen engine state

@ --- include/pscreen_items.h ---
.set g_ItemsItemSelect,            0x030054D8  @ ItemsItemSelectState: item list presence, pending mode and list filter
.set g_ItemsSectionSelectNextMode, 0x030054E4  @ GameMode: pushed once the Items section select fades out
.set g_bItemsSectionCursor,        0x030054E8  @ s8: Items section select row saved on exit
.set g_dwItemUseItem,              0x030054EC  @ u32: item chosen in ItemsItemSelect, used by ItemUseScreen
.set g_dwItemUseQuantity,          0x030054F0  @ u32: quantity chosen in QuantitySelectScreen, used by ItemUseScreen

@ --- include/pscreen_status_equip.h ---
.set g_StatusEquipSlotSelect,      0x030054F8  @ StatusEquipSlotSelectState: slot select screen actors and pending mode
.set g_bStatusEquipSlot,           0x03005564  @ s8: selected equipment slot in StatusEquipSlotSelect

@ --- include/pscreen_trade.h ---
.set g_CardTradeState, 0x03005568  @ CardTradeState: link card trade session

@ --- include/random.h ---
.set gMt19937LastRollByte,      0x03005574  @ low byte of the last tempered value (purpose unconfirmed)
.set gMt19937DrawIndex,         0x03005578  @ cursor 1: running count of numbers drawn
.set gMt19937StatePtr,          0x0300557C  @ base of the 624-word MT state array
.set gMt19937CurPtr,            0x03005580  @ cursor 1: pointer into the state array
.set gMt19937RemainingIndices,  0x03005584  @ cursor 1: untempered words left before regenerating
.set gMt19937CurPtr2,           0x03005588  @ cursor 2: pointer into the state array
.set gMt19937RemainingIndices2, 0x0300558C  @ cursor 2: untempered words left before regenerating
.set gMt19937AutoSeedCallCount, 0x03005590  @ increments each AutoSeed call (purpose unconfirmed)
.set gMt19937SeedValue,         0x03005594  @ accumulating seed value (SetSeed/AutoSeed)

@ --- include/save.h ---
.set g_saveManager,              0x03005598  @ SaveManager: the live RAM copy of the save header (first member) and slot state
.set g_wEepromSavedDispstat,     0x0300561C  @ u16: DISPSTAT saved across EEPROM transfers (EepromTransferBegin/End)

@ --- include/screen_transitions.h ---
.set g_dwScreenPaletteDarkened, 0x03005620  @ u32: set while g_pScreenPaletteBackup holds the undarkened palette
.set g_pScreenPaletteBackup,    0x03005624  @ u16 *: 0x400-byte palette copy kept by DarkenScreenPalette and TransitionOutPaletteFade
.set g_AlphaBlendEvaRamp,       0x03005628  @ AlphaBlendRamp: BLDALPHA EVA coefficient (8.8)
.set g_AlphaBlendEvbRamp,       0x03005630  @ AlphaBlendRamp: BLDALPHA EVB coefficient (8.8)
.set g_dwPaletteFadeColor,      0x03005638  @ u32: BGR555 color TransitionOutPaletteFade fades to
.set g_dwPaletteFadeStepTicks,  0x0300563C  @ u32: step ticks of the palette fades and DarkenScreenPalette/RestoreScreenPalette

@ --- include/scroll.h ---
.set g_CameraPosition, 0x03005640  @ CameraFocusOffset: world-space camera origin used for actor visibility
.set g_RoomSizePixels,           0x03005648  @ RoomSizePixels: width and height of the current room in pixels
.set g_aBgTileCodeTableBuffers,     0x03005650  @ u8[2][0x124]: per tile size class, the Huffman code table DecodeBgTilesetOffsetTable copies from the tileset
.set g_awBgLayerTileCount,          0x03005898  @ u16[4]: per BG layer, distinct tiles held in the BG tile cache
.set g_aBgTilesets,                  0x030058A0  @ BgTileset[2]: per tile size class, the tile offset table and Huffman code table
.set g_adwBgScrollEnabled,           0x030058C0  @ u32[4]: per BG layer, nonzero = scrolled by UpdateOverworldCamera
.set g_adwBgTilesetTileCount,       0x030058D0  @ u32[2]: per tile size class, DecodeBgTilesetOffsetTable's result
.set g_wRoomBgLayer0TilesWide,      0x030058D8  @ u16
.set g_wRoomBgLayer0TilesHigh,      0x030058DA  @ u16
.set g_wRoomBgLayer0BlocksWide,    0x030058DC  @ u16: width of layer 0's block map; the four layers' sizes are u16 {tiles wide, tiles high, blocks wide, blocks high} from 0x030058D8, 8 bytes apart
.set g_wRoomBgLayer0BlocksHigh,     0x030058DE  @ u16
.set g_wRoomBgLayer1TilesWide,     0x030058E0  @ u16
.set g_wRoomBgLayer1TilesHigh,     0x030058E2  @ u16
.set g_wRoomBgLayer1BlocksWide,    0x030058E4  @ u16
.set g_wRoomBgLayer1BlocksHigh,     0x030058E6  @ u16
.set g_wRoomBgLayer2TilesWide,      0x030058E8  @ u16
.set g_wRoomBgLayer2TilesHigh,      0x030058EA  @ u16
.set g_wRoomBgLayer2BlocksWide,    0x030058EC  @ u16
.set g_wRoomBgLayer2BlocksHigh,     0x030058EE  @ u16
.set g_wRoomBgLayer3TilesWide,      0x030058F0  @ u16
.set g_wRoomBgLayer3TilesHigh,      0x030058F2  @ u16
.set g_wRoomBgLayer3BlocksWide,    0x030058F4  @ u16
.set g_wRoomBgLayer3BlocksHigh,     0x030058F6  @ u16
.set g_BgScroll,                    0x030058F8  @ s32[2]: scroll position (x, y) the BG layers' tiles are streamed for
.set g_RoomBgAux,                    0x03005900  @ RoomBgAux: flag byte and two positions set by SetRoomBgAuxFlag2 .. SetRoomBgAuxPosB
.set g_aBgControl,                  0x03005914  @ RoomBgControl[4]: BGxCNT shadow per BG layer
.set g_dwRoomBgLayer0TileWord0,     0x03005924  @ u32: first word of layer 0's block tile table, set by LoadRoomBgBlockTiles0; no reader found
.set g_dwRoomBgLayer1TileWord0,     0x03005928  @ u32
.set g_dwRoomBgLayer2TileWord0,     0x0300592C  @ u32
.set g_dwRoomBgLayer3TileWord0,     0x03005930  @ u32
.set g_RoomBgBlockData,             0x03005934  @ RoomBgBlockData: per-layer block maps and block tile tables
.set g_pRoomBgLayer0MapAlloc,       0x03005954  @ u8 *: heap block holding layer 0's block map (g_RoomBgBlockData.apBlockMaps[0] is 4 bytes in)
.set g_pRoomBgLayer1MapAlloc,       0x03005958  @ u8 *
.set g_pRoomBgLayer2MapAlloc,       0x0300595C  @ u8 *
.set g_pRoomBgLayer3MapAlloc,       0x03005960  @ u8 *
.set g_pRoomBgLayer0TilesAlloc,     0x03005964  @ u32 *: heap block holding layer 0's block tile table, advanced past its block count
.set g_pRoomBgLayer1TilesAlloc,     0x03005968  @ u32 *
.set g_pRoomBgLayer2TilesAlloc,     0x0300596C  @ u32 *
.set g_pRoomBgLayer3TilesAlloc,     0x03005970  @ u32 *
.set g_adwBgBlockAttrOffset,        0x03005974  @ u32[4]: offset of each layer's block attribute bytes within its block tile table
.set g_apBgTileCacheEntries,        0x03005988  @ BgTileCacheEntry *[2]
.set g_apBgTileCacheBuckets,        0x03005990  @ u16 *[2]
.set g_apBgTileCacheFreeSlots,      0x03005998  @ u16 *[2]
.set g_apRoomBgTilesets,            0x030059A0  @ const void *[2]: the room's tileset A and B resources, set by SetupRoomBgControlAndTilesets
.set g_awBgTileCacheFreeCount,       0x030059A8  @ u16[2]: number of entries in each size class's free slot stack
.set g_dwUnk030059AC,               0x030059AC  @ u32: zeroed by InitRoomBgState
.set g_bUnk030059B0,                0x030059B0  @ u8: zeroed by LoadRoomBgTilemap0; no other literal reference found
.set g_BgLoadedScroll,              0x030059B8  @ s32[2]: g_BgScroll as of the last tile load; the window VRAM holds
.set g_wRoomBgLayer0MapSize,        0x030059C0  @ u16: byte size of layer 0's block map, blocks wide * blocks high * 2; no reader found
.set g_wRoomBgLayer1MapSize,        0x030059C2  @ u16
.set g_wRoomBgLayer2MapSize,        0x030059C4  @ u16
.set g_wRoomBgLayer3MapSize,        0x030059C6  @ u16
.set g_aBgStripReleases,            0x030059C8  @ BgStripRelease[2]: tile column (0) and row (1) for FlushBgStripReleases to release

@ --- include/serial.h ---
.set g_SerialLink, 0x030059D8  @ SerialLink: exchange flags and the game's link callbacks
.set g_aSerialRecvMessages, 0x030059E4  @ SerialMessage[2]: latest message received from each peer
.set g_SerialSendMessage, 0x030059FC  @ SerialMessage: message queued for the next exchange
.set g_bSerialTick, 0x03005A08  @ u8: stamped into each queued message; incremented once per processed round
.set g_abSerialLastRecvSeq, 0x03005A09  @ u8[2]: bSeq of the last message handled from each peer
.set g_awSerialKeysReceived,     0x03005A0C  @ u16[2]: per-player key masks received over the link cable
.set g_bSerialUnk03005A10, 0x03005A10  @ u8: zeroed with g_bSerialSeedReceived by StartSerialConnection; never read
.set g_bSerialSeedReceived, 0x03005A11  @ u8: set once the parent's RNG seed message has been applied
.set g_bSerialChecksumRollByte, 0x03005A14  @ u8: gMt19937LastRollByte latched by SubmitSerialMessage for message checksums
.set g_dwSerialMode, 0x03005A18  @ u32: 1 while the exchange loop runs each frame
.set g_dwSerialPlayerCount, 0x03005A1C  @ u32: terminals that answered the last serial interrupt; 5 after a stray protocol word
.set g_bSerialPeerCount, 0x03005A20  @ u8: number of peers in g_aSerialRecvMessages
.set g_bSerialLocalPlayerId, 0x03005A21  @ u8: GetSerialPlayerId() latched when the game session starts
.set g_bSerialPlayerMask, 0x03005A22  @ u8: one bit per multiplayer slot that answered the last serial interrupt
.set g_SerialPlayerState,        0x03005A24  @ SerialPlayerState: serial-link session block
.set g_dwSerialExchangeCount, 0x03005A90  @ u32: completed exchange rounds
.set g_dwSerialChecksumExchangeCount, 0x03005A94  @ u32: g_dwSerialExchangeCount latched by SubmitSerialMessage for message checksums
.set g_dwSerialLastExchangeTime, 0x03005A98  @ u32: dwVBlankCount when the last exchange round finished
.set g_dwSerialPollFlags_candidate, 0x03005A9C  @ u32: bit 0 selects the message type queued by ExchangeSerialFrame_candidate
.set g_dwSerialMaxPlayers, 0x03005AA0  @ u32: SerialConnect argument; a higher terminal ID drops the session
.set g_dwSerialUnk03005AA4, 0x03005AA4  @ u32: zeroed by InitSerial, no other access found
.set g_dwSerialUnk03005AA8, 0x03005AA8  @ u32: zeroed by InitSerial, no other access found
.set g_dwSerialUnk03005AAC, 0x03005AAC  @ u32: zeroed by InitSerial, no other access found
.set g_dwSerialUnk03005AB0, 0x03005AB0  @ u32: zeroed by InitSerial, no other access found
.set g_dwSerialConnectRetries, 0x03005AB4  @ u32: CountSerialConnectRetries call counter
.set g_dwSerialUnusedValue, 0x03005AB8  @ u32: set by SetSerialUnusedValue, returned by GetSerialUnusedValue; neither has a caller
.set g_dwSerialUnk03005ABC, 0x03005ABC  @ u32: zeroed by InitSerial, no other access found

@ --- include/sound.h ---
.set g_bUnreadAudioValue,        0x03005AC0  @ u8: set to 8 by kramInstall and PlayMusicModule; never read
.set g_bMusicPaused,             0x03005AC1  @ u8: PauseMusic latch, cleared by ResumeMusic and StopMusic
.set g_bCurrentMusicModule,      0x03005AC2  @ u8: last module started by PlayMusicModule, 0xFF if none

@ --- include/store.h ---
.set g_FredAndGeorgesShop,       0x03005AC8  @ FredAndGeorgesShopState

@ --- include/tea_leaves_minigame.h ---
.set g_DivinationTea,            0x03005B28  @ DivinationTeaState

@ --- include/text.h ---
.set gDialogTextScratchBuf,      0x03005D08  @ pointer to the fixed 0x400-byte decode scratch buffer
.set gCurrentLanguage,           0x03005D0C  @ byte: language ID (0-7) set by SetLanguage
.set gLocaleThousandsSep,        0x03005D0D  @ byte: locale-specific number-formatting separator

@ --- include/text_actor.h ---
.set g_apTextActors,              0x03005D10  @ Actor *[17]: slots filled by SpawnTextActor; its destructor clears the slot

@ --- include/timers.h ---
.set g_aGameTimers,                0x03005D58  @ GameTimer[4]

@ --- include/timeturner_cutscene.h ---
.set g_HarryHermionePortInTime,  0x03005D98  @ HarryHermionePortInTimeState

@ --- include/title.h ---
.set g_nMainMenuTextCursor,     0x03005DB0  @ s32: text tile cursor returned by the main menu's copyright text
.set g_MainMenuState,            0x03005DB8  @ MainMenuState: {Actor *pCursorActor; u32 dwLoadGameAvailable; s32 nPaletteEffectSlot}

@ --- include/title_new.h ---
.set g_bSaveSlotScreenResult,    0x03005DC4  @ u8: SaveSlotScreenResult set by HandleSaveSlotInput

@ --- include/title_load.h ---
.set g_pSaveSlotCursorActor,     0x03005DC8  @ Actor *: opaque save slot bar over the selected slot

@ --- include/title_options.h ---
.set g_OptionsState,             0x03005DD0  @ OptionsState: 8 actor pointers, then the value of each row
.set g_dwOptionsReturnMode,      0x03005E04  @ u32: GameMode that opened the options screen
.set g_bOptionsSavedMusicVolume, 0x03005E08  @ u8: settings kept across the language select trip
.set g_bOptionsSavedSoundVolume, 0x03005E09  @ u8
.set g_bOptionsSavedGammaHigh,   0x03005E0A  @ u8
.set g_dwOptionsEntryLanguage,   0x03005E0C  @ u32: language when the options screen was entered

@ --- include/torch_actor.h ---
.set g_nFlamePillarSoundHandle,  0x03005E10  @ s32: handle of the flame pillar ignition sound

@ --- include/train_cutscene.h ---
.set g_wCoolTrainTimer,          0x03005E14  @ u16: frames left in the Cool Train cutscene

@ --- include/trigger_actor.h ---
.set g_bRestoringRoomActors_candidate, 0x03005E18  @ u8: 1 while RestoreRoomActorState respawns actors; also set when the overworld pushes a pause menu
.set g_nSwitchSoundHandle,       0x03005E1C  @ s32: handle of the switch actor sound

@ --- include/video.h ---
.set g_ScanlineEffectState,      0x03005E20  @ pending flag, active index, 19 live entries
.set g_ScanlineEffectStaging,    0x03005F58  @ 19 staged entries, committed to the live table by CommitScanlineEffects

@ --- include/vram.h ---
.set FindFreeObjTileRunIwram, 0x03006088  @ u8[0x9C]: IWRAM copy of FindFreeObjTileRun
.set g_abObjTileAllocBitmap,    0x03006128  @ u8[128]: set bit = tile in use
.set g_abObjTileFreeMask,       0x030061A8  @ u8[128]: clear bit = free pending the next OAM swap

@ --- include/windows.h ---
.set g_aScreenWindows,          0x03006228  @ ScreenWindow[2]; see TickScreenWindow

@ --- include/hw/eeprom.h ---
.set g_pEepromInterface,         0x030062C8  @ EepromInterface *: chosen by EepromSelectInterface

@ --- Boot + runtime (asm) ---
.set gSystemStackTop,            0x03007EA0  @ top of the AGB system-mode stack
.set gIrqStackTop,               0x03007FA0  @ top of the AGB IRQ-mode stack

@ --- include/interrupts.h ---
.set gIntrVectorPtr,             0x03007FFC  @ BIOS-called user interrupt handler pointer

@ --- include/text.h ---
.set sDialogLanguageTable,       0x0806BD78  @ ROM: 8 x u32, one string-table blob pointer per language
