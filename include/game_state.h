#pragma once

#include "types.h"
#include "save.h"

void DeserializeGameStateFromSaveBuffer(void);
void SerializeGameStateToSaveBuffer(void);
void NoopInit(void);
void ResetSaveStateForNewGame(void);
void ResetQuestStateForNewGame(u32 newGamePlus);
void StartNewGamePlaytime(void);
void UnpackSaveSlotPreview(SaveSlotPreview *preview);
// Advances the Owl Care Kit's timers and need counters while walking around.
void TickOwlCareKitFromOverworld(void);
void ProcessPlaytimeTick(void);
void SetSickles(u32 amount);
// Adds a signed amount of Sickles to the player's money, clamped to
// 0..999999, and returns the new total.
u32 AddSickles(s32 amount);
s32 GetSickles(void);  // returns g_saveStateBlock.dwMoney

extern const Playtime g_stPlaytimeZero;
extern const Playtime g_stPlaytimeFrameDelta;
extern const Playtime g_stPlaytimeHourLimit;

extern SaveStateBlock g_saveStateBlock;
// Cleared by the next TickActor pass that ticks an actor's movement; that
// actor plays sound 0x47 if its position changed. Its writer is unidentified.
extern u32 g_dwUnk03003234;
