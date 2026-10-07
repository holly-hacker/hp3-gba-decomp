#pragma once

#include "types.h"
#include "graphics/object.h"

// Per-tick Owl Care Kit clock, a no-op until the care screen has been visited.
// Counts down the Mail flight timer, otherwise advances the elapsed-tick counter;
// each time that passes 0x95 it resets and, if nGrowCounters is set, raises all
// six care counters by 1 (cap 250). See docs/formats/save.md.
void ProcessOwlCareKitTick(s32 nGrowCounters);

// Owl Care Kit care screen, game mode 0x29 (OwlCareMinigame). The screen's live
// state is the 0xE8-byte block at g_OwlCareKitScreen, cleared by
// InitializeOwlCareKitScreen. The persistent care data lives in
// g_saveStateBlock.owlCareKit.
typedef struct {
    Object *pOwl;                 // 0x00; the owl object
    Object *pCursor;              // 0x04; the menu cursor, released on exit
    void *pUnk08;                 // 0x08; handed to sub_080233C0 on exit
    u8 abUnmapped_0C[0xC8];
    u8 abUnkD4[3];                // 0xD4; all start at 250
    u8 abUnmapped_D7[1];
    s32 dwUnkD8;                  // 0xD8
    u8 bUnkDC;                    // 0xDC
    u8 bUnkDD;                    // 0xDD
    u8 bUnkDE;                    // 0xDE
    u8 bUnkDF;                    // 0xDF
    u8 bUnkE0;                    // 0xE0; starts at 5
    u8 abUnmapped_E1[4];
    u8 bUnkE5;                    // 0xE5; starts at 1
    u8 bUnkE6;                    // 0xE6
    u8 abUnmapped_E7[1];
} OwlCareKitScreenState;          // 0xE8

extern OwlCareKitScreenState g_OwlCareKitScreen;  // 0x03003270

extern const u32 g_dwOwlCareBg3Control;  // 0x080606A8
extern const u32 g_dwOwlCareBg2Control;  // 0x080606AC
extern const u32 g_dwOwlCareBg1Control;  // 0x080606B0
extern const u32 g_dwOwlCareBg0Control;  // 0x080606B4

extern void sub_08021E80(void);
extern u32 sub_08022134(void);  // confirm button: nonzero if the selected care action was accepted
extern void sub_0802238C(void);
extern void sub_0802246C(void);
extern void sub_08022B40(void);
extern void sub_08022EE4(void);
extern void sub_08022F28(void);
extern void sub_08023188(void);  // first visit: sets the visited flag and resets the care counters
extern void sub_080233C0(void *pUnk);
extern void sub_08006A98(u32 bg, const void *pTilemap, u32 arg2, u32 arg3, u32 arg4, u32 arg5, u32 arg6, u32 arg7,
                         u32 width, u32 height);  // 30 x 20 tiles: a full screen
