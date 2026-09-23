#pragma once

#include "types.h"
#include "object.h"

// Harry vs Dementors, game mode 0x33 (HarryVsDementorsMinigame).

// The mode's screen state at 0x03002E18, driven by g_GameModeStackContext.dwModeState.
typedef struct {
    u8 abUnmapped_0[0x14];
    Object *pCursorObject;   // 0x14; released on exit when set
    Object *pObject18;       // 0x18; hidden when dwHideTimer5C expires
    Object *pObject1C;       // 0x1C; hidden when dwHideTimer68 expires
    void *pObjectGroup20;    // 0x20; freed on exit
    void *pObjectGroup24;    // 0x24; freed on exit
    void *pObjectGroup28;    // 0x28; freed on exit
    u32 dwUnk2C;
    u8 abUnmapped_30[0x10];
    s32 dwUnk40;
    u32 dwUnk44;
    u32 dwUnk48;
    u8 bUnk4C;
    u8 abUnmapped_4D[3];
    u32 dwUnk50;
    u8 bUnk54;
    u8 abUnmapped_55[3];
    u32 dwUnk58;
    u32 dwHideTimer5C;       // 0x5C; frames until pObject18 is hidden
    u32 dwEventTimer60;      // 0x60; frames until sub_0801ED48(dwEventArg64) runs
    u32 dwEventArg64;
    u32 dwHideTimer68;       // 0x68; frames until pObject1C is hidden
} HarryVsDementorsState;

extern HarryVsDementorsState g_HarryVsDementors;  // 0x03002E18

// BG control words, per-level BG0 graphics and the two spawned objects' data.
extern const u32 g_dwHarryVsDementorsBg0Control;  // 0x0805E174
extern const u32 g_dwHarryVsDementorsBg3Control;  // 0x0805E178
extern const u8 g_HarryVsDementorsBgGraphicA[];   // 0x08E5EB80: levels 0 and 1
extern const u8 g_HarryVsDementorsBgGraphicB[];   // 0x08E62538: level 2
extern const ObjPalette g_HarryVsDementorsObject18SpawnData[];  // 0x080BD710
extern const ObjPalette g_HarryVsDementorsObject1CSpawnData[];  // 0x080BF5E4

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    HarryVsDementorsStatePlaying = 0,
    HarryVsDementorsStateResultsMenu = 1,
    HarryVsDementorsStatePauseMenu = 2,
} HarryVsDementorsMode;

extern void sub_0801E414(void);
extern void sub_0801E564(void);
extern void sub_0801E5F4(void);
extern void sub_0801E6A0(void);
extern void sub_0801E8CC(void);
extern void sub_0801EAF8(u32 direction);
extern void sub_0801ED48(u32 arg);
extern void sub_0801EE64(void);
extern void sub_0801EF48(void);
extern void sub_0801EFA0(void);
extern void sub_0801EFF4(void);
extern void sub_0801F108(void);
