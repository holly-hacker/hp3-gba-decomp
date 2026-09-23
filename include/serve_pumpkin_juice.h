#pragma once

#include "types.h"

// Serve Pumpkin Juice, game mode 0x24 (UnusedServePumpkinJuiceMinigame). No
// screen pushes this mode, but its handlers are present in the dispatch table.

// The mode's screen state at 0x03005238, driven by g_GameModeStackContext.dwModeState.
typedef struct {
    u32 dwUnk0;           // 0x00; nonzero refreshes the score display each frame
    u32 dwScore;          // 0x04; grows when a round ends
    u8 abUnmapped_8[4];
    u32 dwRound;          // 0x0C
    u32 dwMenuSelection;  // 0x10; row of the pause/results menu
    u32 dwUnk14;          // 0x14; starts at 0x55
    u8 abUnmapped_18[4];
    u32 dwTileCursor;     // 0x1C; text tile cursor for the caption strings
    s32 adwUnk20[3];      // 0x20
    u32 dwUnk2C;          // 0x2C; starts at 0xA8
    u32 dwUnk30;          // 0x30; starts at 0x57
    u32 dwUnk34;          // 0x34; starts at 0xB8
    u32 dwUnk38;          // 0x38; starts at 0x80
    u32 dwUnk3C;          // 0x3C; starts at 0xC8
    u32 dwUnk40;          // 0x40; starts at 0xA8
    u8 abUnmapped_44[0x14];
    void *pBg1Tilemap;    // 0x58; LoadBgGraphic's result for BG1
} ServePumpkinJuiceState;

extern ServePumpkinJuiceState g_ServePumpkinJuice;  // 0x03005238

// BG control words, graphics and strings.
extern const u32 g_dwServePumpkinJuiceBg0Control;  // 0x08069184
extern const u32 g_dwServePumpkinJuiceBg1Control;  // 0x08069188
extern const u32 g_dwServePumpkinJuiceBg2Control;  // 0x0806918C
extern const u32 g_dwServePumpkinJuiceBg3Control;  // 0x08069190
extern const u8 g_ServePumpkinJuiceBg0Graphic[];   // 0x08D97428
extern const u8 g_ServePumpkinJuiceBg1Graphic[];   // 0x08D989F4
extern const u8 g_ServePumpkinJuiceBg2Graphic[];   // 0x08D99900
extern const u8 g_ServePumpkinJuiceTable[];        // 0x08069328
extern const u8 g_ServePumpkinJuicePanelData[];    // 0x08DA08BE
extern const u8 g_ServePumpkinJuicePauseText[];    // 0x080693B0
extern const u8 g_ServePumpkinJuiceResultsText[];  // 0x080693C0

// dwModeState values. The names describe the observed behavior and are
// provisional.
typedef enum {
    ServePumpkinJuiceStatePlaying = 0,
    ServePumpkinJuiceStateWaitInput = 1,
    ServePumpkinJuiceStateNextRound = 2,
    ServePumpkinJuiceStatePauseMenu = 3,
    ServePumpkinJuiceStateResults = 4,
    ServePumpkinJuiceStateRoundOver = 5,
} ServePumpkinJuiceMode;

extern void sub_08007AF0(u32 bg, u32 arg1, u32 arg2);
extern void sub_0800D57C(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4, const void *pData, u32 arg6);
extern void sub_08034F20(s32 arg0, u32 arg1, u32 arg2);
extern void sub_0803518C(void);
extern void sub_0803526C(void);
extern void sub_08035330(void);
extern void sub_0803539C(void);
extern void sub_08035418(void);
extern u32 sub_08035474(void);
