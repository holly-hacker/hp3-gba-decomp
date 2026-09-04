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

@ --- Interrupt dispatch (see src/interrupts/) ---
.set gIntrTable, 0x03003570  @ 13 x u32 function-pointer slots, refreshed from a ROM
                              @ template by InitInterruptSystem; dispatched by IntrMain
.set gIntrHandlerIwram, 0x030035A4  @ 0x200-byte IWRAM buffer InstallInterruptHandler
                                     @ CpuSets the live handler code into; gIntrVectorPtr
                                     @ points here

@ --- main / game-mode stack (see src/main.c) ---
.set g_dwGameModeFlags,   0x03003B44  @ u32: broad flags word read/written across
                                       @ overworld/room/cutscene transitions and
                                       @ TickGameModeStack_candidate; individual bits
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
.set g_dwBattleRewardFlagsSnapshot, 0x03002618  @ u32: FightState->bBonusRewardFlags copy, see RollBattleItemDrops
.set g_anFaintedRosterIndices, 0x030026D8  @ s32[4]: fainted fighters' roster indices this battle, sentinel -1
.set g_aBgScrollState,   0x03001E80  @ u32[]; [0x25] == 0x03001F14
.set g_PrevGameModeCtx, 0x03003F3C  @ GameModeContext, 0x24 bytes; see docs/memory-map/game_modes.md
.set g_abBgPriority,     0x03003F8C  @ u8[]; [4] == 0x03003F90
.set g_nXpAccum,         0x0300260E  @ u16: running XP-reward accumulator
.set g_nGoldAccum,       0x03002610  @ u16: running gold-reward accumulator
.set g_bSelectedFighterSlot_candidate, 0x03002660  @ u32: fighter slot with the "selected" sprite scale applied
.set g_apFighterObjects_candidate, 0x03002668  @ Object*[7]; one slot per active BattleFighter
.set g_pBattleMessageIconObject_candidate, 0x03002684  @ Object *: icon shown alongside ShowBattleMessage's text
.set g_BattleMessageIconState_candidate, 0x03002688  @ {byte bIndex (sentinel 0xFF=none), pad[3], u32 dwParam}
.set g_bCurrentRoomId,   0x03003B50  @ byte: current room/map id
.set g_GameModeStackContext_candidate, 0x03003EF4  @ {dwCurrentGameMode, dwCurrentGameModeArg1, pad[4], dwStoryStageCache}

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
.set sDialogLanguageTable,   0x0806BD78  @ ROM: 8 x u32, one string-table blob pointer per language

@ --- MT19937 PRNG (see docs/memory-map/rng.md) ---
@ Names mostly match jogotu's BizHawk script naming, cross-checked
@ against our own disassembly there. That script tracks cursor 1 only;
@ cursor 2 is undocumented by it and comes from this project's own
@ disassembly (see rng.md for what's confirmed and what's still open
@ about it).
.set gMt19937SeedSourceCounter,  0x030034EC  @ external halfword counter AutoSeed also reads
.set gMt19937LastRollByte,       0x03005574  @ low byte of the last tempered value (purpose unconfirmed)
.set gMt19937DrawIndex,          0x03005578  @ cursor 1: running count of numbers drawn
.set gMt19937StatePtr,           0x0300557C  @ base of the 624-word MT state array
.set gMt19937CurPtr,             0x03005580  @ cursor 1: pointer into the state array
.set gMt19937RemainingIndices,   0x03005584  @ cursor 1: untempered words left before regenerating
.set gMt19937CurPtr2,            0x03005588  @ cursor 2: pointer into the state array
.set gMt19937RemainingIndices2,  0x0300558C  @ cursor 2: untempered words left before regenerating
.set gMt19937AutoSeedCallCount,  0x03005590  @ increments each AutoSeed call (purpose unconfirmed)
.set gMt19937SeedValue,          0x03005594  @ accumulating seed value (SetSeed/AutoSeed)
