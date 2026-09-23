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

@ --- IWRAM-installed decompression codecs (see docs/formats/graphics.md) ---
.set g_pDecompressType4Entry, 0x030028CC
.set g_pDecompressType6Entry, 0x030028D0
.set g_pDecompressType4Iwram, 0x030028D4
.set g_pDecompressType6Iwram, 0x03002ACC

@ --- main / game-mode stack (see src/main.c) ---
.set g_GameModeStackContext, 0x03003F54  @ see ram_symbols.us.inc
.set g_dwFrameSyncTarget, 0x03003BA8  @ see ram_symbols.us.inc

@ --- Battle state (see include/battle.h) ---
.set g_pFightState,   0x030024E8
.set g_effectStaging, 0x03002750

@ --- Controller input (see docs/memory-map/input.md) ---
.set g_wKeysHeld,          0x0300354C  @ see ram_symbols.us.inc/docs/memory-map/input.md
.set g_wKeysHeldPrevious,  0x0300354E
.set g_wKeysPressed,       0x03003550
.set g_wKeysReleased,      0x03003552
.set g_wInputDisabled,     0x03003554
.set g_awPlayerKeysHeld,          0x03003556
.set g_awPlayerKeysHeldPrevious,  0x0300355A
.set g_awPlayerKeysPressed,       0x0300355E
.set g_awPlayerKeysReleased,      0x03003562
.set g_awLinkKeysReceived, 0x03005A6C
.set g_LinkPlayerState,    0x03005A84  @ see include/link.h


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
.set g_aCameraEffects_candidate,     0x03002090  @ see ram_symbols.us.inc
.set g_aCameraFocusSlots,            0x030020E8  @ see ram_symbols.us.inc
.set g_aCameraFollowOffsets,         0x03002158  @ see ram_symbols.us.inc
.set g_pPlayerObject,                0x030033E0  @ see ram_symbols.us.inc
.set g_dwRoomChainRanThisFrame_candidate, 0x03001DF0  @ see ram_symbols.us.inc
.set g_bUnk03005E18,                 0x03005E68  @ see ram_symbols.us.inc
.set g_bStatusEquipCharacterSlot,     0x03005318  @ see ram_symbols.us.inc
.set g_bStatusEquipSlot,              0x030055C4  @ see ram_symbols.us.inc
.set g_dwStatusEquipCharacter,        0x03005300  @ see ram_symbols.us.inc
.set g_pMenuCursorObject,             0x03002E08  @ see ram_symbols.us.inc
.set g_StatusEquipCharacterSelect,    0x03005308  @ see ram_symbols.us.inc
.set g_StatusEquipItemSelect,         0x03005328  @ see ram_symbols.us.inc
.set g_StatusEquipNextMode,           0x030052FC  @ see ram_symbols.us.inc
.set g_StatusEquipReturnMode,         0x030052F8  @ see ram_symbols.us.inc
.set g_StatusEquipSlotSelect,         0x03005558  @ see ram_symbols.us.inc
.set g_ItemsItemSelect,              0x03005538  @ see ram_symbols.us.inc
.set g_ItemsSectionSelectNextMode,   0x03005544  @ see ram_symbols.us.inc
.set g_bItemsSectionCursor,          0x03005548  @ see ram_symbols.us.inc
.set g_dwItemUseItem,                0x0300554C  @ see ram_symbols.us.inc
.set g_dwItemUseQuantity,            0x03005550  @ see ram_symbols.us.inc
.set g_pHippogriffGlide,             0x03002088  @ see ram_symbols.us.inc
.set g_adwHippogriffGlideUnk,        0x03005D70  @ see ram_symbols.us.inc
.set g_saveManager,                  0x030055F8  @ see ram_symbols.us.inc
.set g_dwPendingGameMode,            0x03003F78  @ see ram_symbols.us.inc
.set g_Riddikulus,                   0x03002048  @ see ram_symbols.us.inc
.set g_dwListMenuSelection,          0x03003F74  @ see ram_symbols.us.inc
.set g_HarryVsDementors,             0x03002E18  @ see ram_symbols.us.inc
.set g_pWizardCrackerPopIt,          0x03005290  @ see ram_symbols.us.inc
.set g_dwWizardCrackerPopItForceOverworldExit, 0x03005288  @ see ram_symbols.us.inc
.set g_DivinationTea,                0x03005B88  @ see ram_symbols.us.inc
.set g_ServePumpkinJuice,            0x03005298  @ see ram_symbols.us.inc
.set g_dwPendingCameraFocusFlag,     0x03004034  @ see ram_symbols.us.inc
.set g_pPendingCameraFocus_candidate, 0x03004038  @ see ram_symbols.us.inc
.set g_pLinearCutsceneText,          0x030028B4  @ see ram_symbols.us.inc
.set g_pLinearCutsceneObject,        0x030028B8  @ see ram_symbols.us.inc
.set g_dwLinearCutsceneIndex,        0x030028BC  @ see ram_symbols.us.inc
.set g_dwCreditsScrollRow,           0x030028A8  @ see ram_symbols.us.inc
.set g_dwCreditsLine,                0x030028AC  @ see ram_symbols.us.inc
.set g_dwCreditsTileCursor,          0x030028B0  @ see ram_symbols.us.inc
.set g_wCoolTrainTimer,                 0x03005E64  @ u16: frames left in the Cool Train cutscene
.set g_bCurrentRoomId,               0x03003BB0  @ see ram_symbols.us.inc
.set g_abRoomScriptExitParams_candidate, 0x030033DD  @ see ram_symbols.us.inc
.set g_HarryHermionePortInTime,        0x03005DF8  @ see ram_symbols.us.inc
.set g_dwPatronusBgFront,            0x03005244  @ see ram_symbols.us.inc
.set g_dwPatronusBgBack,             0x03005248
.set g_dwPatronusSwapPending,        0x0300524C
.set g_bPatronusGraphicIndex,        0x03005250
.set g_swPatronusBgParam,            0x03005252
.set g_nPatronusBgOffset,            0x03005254
.set g_pHippogriffFliesIntoAirObject, 0x03002F18  @ see ram_symbols.us.inc
.set g_pHippogriffFliesIntoAirObject2, 0x03002F1C
.set g_LupinPotionCutscene,          0x03003AE4  @ see ram_symbols.us.inc
.set g_aLupinPotionBg2Scroll,        0x03003B9C
.set g_aResourceCache,               0x03005174  @ see ram_symbols.us.inc
