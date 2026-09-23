#pragma once

#include "types.h"
#include "object.h"

typedef struct {
    Object *pCursorObject;  // 0x00
    u32 dwSelection;        // 0x04: row of the debug main menu
} DebugMenuMainState;

extern DebugMenuMainState g_DebugMenuMainState;  // 0x030021C0

typedef struct {
    Object *pPortraitObject;  // 0x00: sprite showing the selected portrait
    u32 dwSelection;          // 0x04: portrait index, 0..0x86
} DebugPortraitsState;

extern DebugPortraitsState g_DebugPortraitsState;  // 0x03002210

typedef struct {
    Object *pCardObject;  // 0x00: sprite showing the selected card
    u32 dwSelection;      // 0x04: card index, 0..0x32
} DebugCollectorCardsState;

extern DebugCollectorCardsState g_DebugCollectorCardsState;  // 0x03002238

typedef struct {
    Object *pCursorObject;   // 0x00
    u32 dwRow;               // 0x04: 0 = sound effect, 1 = music module
    u32 adwSelection[2];     // 0x08: chosen sound effect id (0..0xB2) and music module (0..0x33)
    u32 dwTileCursor;        // 0x10: text tile cursor after drawing the row labels
    u32 dwMusicPlaying;      // 0x14
    s32 nSoundHandle;        // 0x18: handle from PlaySoundById; DEBUG_SOUND_TEST_NO_HANDLE if none
} DebugSoundTestState;

#define DEBUG_SOUND_TEST_NO_HANDLE 0xB3

extern DebugSoundTestState g_DebugSoundTestState;  // 0x03002218

typedef struct {
    Object *pCursorObject;  // 0x00
    u32 dwRow;              // 0x04: 0-2 = character levels, 3 = quest
    u32 adwValue[4];        // 0x08: value of each row, packed into the mode argument (one byte each)
    u32 dwTileCursor;       // 0x18: text tile cursor after drawing the row labels
} DebugLevelAndQuestSelectState;

extern DebugLevelAndQuestSelectState g_DebugLevelAndQuestSelectState;  // 0x030021C8

typedef struct {
    Object *pCursorObject;  // 0x00
    u32 dwCursorRow;        // 0x04: visible row, 0..0x11
    s32 nScrollY;           // 0x08: BG1 vertical scroll in pixels; the map index is nScrollY / 8 + dwCursorRow
} DebugMapSelectState;

extern DebugMapSelectState g_DebugMapSelectState;  // 0x030021E8

typedef struct {
    Object *pCursorObject;  // 0x00
    u32 dwRow;              // 0x04: party slot, 0..2
    u32 adwCharacter[3];    // 0x08: chosen character per slot; 0 = empty, else party character id + 1
    u32 dwTileCursor;       // 0x14: text tile cursor after drawing the slot labels
} DebugCharacterSelectState;

extern DebugCharacterSelectState g_DebugCharacterSelectState;  // 0x030021F8

extern const u32 g_dwDebugMenuMainBg0Control;  // 0x0804C444
extern const u32 g_dwDebugMenuMainBg1Control;  // 0x0804C448
extern const u32 g_dwDebugPortraitsBg1Control;  // 0x0804C618
extern const u32 g_dwDebugCollectorCardsBg0Control;  // 0x0804CEC0
extern const u32 g_dwDebugCollectorCardsBg1Control;  // 0x0804CEBC
extern const u32 g_dwDebugCollectorCardsBg2Control;  // 0x0804CEB8
extern const u8 g_DebugCollectorCardsBg0Graphic[];   // 0x08D9AAD0
extern const u32 g_dwDebugSoundTestBg0Control;  // 0x0804CE8C
extern const u32 g_dwDebugSoundTestBg1Control;  // 0x0804CE90
extern const u8 g_DebugSoundTestAnimFrames[];   // 0x0804CE94
extern const u8 g_DebugSoundTestAnimData[];     // 0x0804CEA4
extern const u8 g_abDebugLevelAndQuestMax[4];        // 0x0804C470: largest value of each row
extern const u32 g_dwDebugLevelAndQuestBg0Control;  // 0x0804C474
extern const u32 g_dwDebugLevelAndQuestBg1Control;  // 0x0804C478
extern const u8 g_DebugLevelAndQuestAnimFrames[];   // 0x0804C47C
extern const u8 g_DebugLevelAndQuestAnimData[];     // 0x0804C48C
extern const u32 g_dwDebugMapSelectBg0Control;  // 0x0804C4A0
extern const u32 g_dwDebugMapSelectBg1Control;  // 0x0804C4A4
extern const u8 g_DebugMapSelectAnimFrames[];   // 0x0804C4A8
extern const u8 g_DebugMapSelectAnimData[];     // 0x0804C4B8
extern const u32 g_dwDebugCharacterSelectBg0Control;  // 0x0804C4CC
extern const u32 g_dwDebugCharacterSelectBg1Control;  // 0x0804C4D0
extern const u8 g_DebugCharacterSelectAnimFrames[];   // 0x0804C4D4
extern const u8 g_DebugCharacterSelectAnimData[];     // 0x0804C4E4
extern const u8 g_DebugMenuGraphic[];          // 0x08D9A360
extern const u8 g_DebugMenuCursorSpawnData[];  // 0x080BC538
extern const u8 g_DebugMenuMainAnimFrames[];   // 0x0804C44C
extern const u8 g_DebugMenuMainAnimData[];     // 0x0804C45C

extern void ResetDebugPartyFromArgs_candidate(void);
extern void DrawDebugMenuMainEntries_candidate(void);
extern void sub_0800B52C(void);
extern void sub_0800BAF8(void);
extern void sub_0800B8F0(void);
extern void sub_0800B344(void);
extern void sub_0800B40C(void);
extern void sub_0800B4B0(void);
extern void sub_0800B120(void);
extern void sub_0800B158(u32 scrollUp);
extern void sub_0800AD94(void);
extern void sub_0800AE68(void);
extern void sub_0800B9BC(void);
