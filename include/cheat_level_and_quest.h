#pragma once

#include "types.h"
#include "actor.h"

typedef struct {
    Actor *pCursorActor;  // 0x00
    u32 dwRow;              // 0x04: 0-2 = character levels, 3 = quest
    u32 adwValue[4];        // 0x08: value of each row, packed into the mode argument (one byte each)
    u32 dwTileCursor;       // 0x18: text tile cursor after drawing the row labels
} CheatLevelAndQuestState;

extern CheatLevelAndQuestState g_CheatLevelAndQuestState;  // 0x030021C8
extern const u8 g_abCheatLevelAndQuestMax[4];        // largest value of each row
extern const u32 g_dwCheatLevelAndQuestBg0Control;
extern const u32 g_dwCheatLevelAndQuestBg1Control;
extern const ActorAssetRecord g_CheatLevelAndQuestAnimFrames;
extern const u8 g_CheatLevelAndQuestAnimData[18];

extern void InitializeCheatLevelAndQuest(void);
extern void UpdateCheatLevelAndQuest(void);
extern void ExitCheatLevelAndQuest(void);

extern void DrawCheatLevelAndQuestRows(void);
extern void DrawCheatLevelAndQuestValues(void);
