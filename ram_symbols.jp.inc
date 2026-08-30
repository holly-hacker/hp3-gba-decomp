@ Named RAM addresses referenced from asm/*.s files -- see
@ ram_symbols.us.inc for the full explanation. JP-side values for the
@ MT19937 symbols shared with US-side extracted files (the dialog-text
@ symbols aren't defined here at all -- that engine isn't present in
@ the JP ROM).

@ --- crt0 (see asm/crt0.s) ---
.set gSystemStackTop,  0x03007EA0
.set gIrqStackTop,     0x03007FA0
.set gIntrVectorPtr,   0x03007FFC
.set gMainEntryPoint,  0x080296ED

@ --- MT19937 PRNG (see docs/memory-map/rng.md) ---
.set gMt19937SeedSourceCounter,  0x0300354C
.set gMt19937SeedSourceStruct,   0x030035CC
.set gMt19937LastRollByte,       0x030055D4
.set gMt19937DrawIndex,          0x030055D8
.set gMt19937StatePtr,           0x030055DC
.set gMt19937CurPtr,             0x030055E0
.set gMt19937RemainingIndices,   0x030055E4
.set gMt19937CurPtr2,            0x030055E8
.set gMt19937RemainingIndices2,  0x030055EC
.set gMt19937AutoSeedCallCount,  0x030055F0
.set gMt19937SeedValue,          0x030055F4
