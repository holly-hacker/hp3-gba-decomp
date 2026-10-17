#pragma once

#include "types.h"
#include "actor.h"
#include "gen/graphics/menus.h"

typedef struct {
    Actor *pCursorActor;   // 0x00
    u32 dwRow;               // 0x04: 0 = sound effect, 1 = music module
    u32 adwSelection[2];     // 0x08: chosen sound effect id (0..0xB2) and music module (0..0x33)
    u32 dwTileCursor;        // 0x10: text tile cursor after drawing the row labels
    u32 dwMusicPlaying;      // 0x14
    s32 nSoundHandle;        // 0x18: handle from PlaySoundById; CHEAT_SOUND_TEST_NO_HANDLE if none
} CheatSoundTestState;

#define CHEAT_SOUND_TEST_NO_HANDLE 0xB3

extern CheatSoundTestState g_CheatSoundTestState;  // 0x03002218
extern const u32 g_dwCheatSoundTestBg0Control;  // 0x0804CE8C
extern const u32 g_dwCheatSoundTestBg1Control;  // 0x0804CE90
extern const ActorAssetRecord g_CheatSoundTestAnimFrames;  // 0x0804CE94
extern const u8 g_CheatSoundTestAnimData[18];    // 0x0804CEA4

extern void InitializeCheatSoundTest(void);
extern void UpdateCheatSoundTest(void);
extern void ExitCheatSoundTest(void);

extern void DrawCheatSoundTestRows(void);
extern void DrawCheatSoundTestValues(void);
