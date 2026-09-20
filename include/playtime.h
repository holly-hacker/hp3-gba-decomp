#pragma once

#include "types.h"

typedef struct {
    s16 wHourCarry;
    s8 bHours;
    s8 bMinutes;
    s8 bSeconds;
    s8 bFrames;
    u8 aUnused[2];
} Playtime;

typedef enum {
    PlaytimeCounterActive = 0x01,
    ContinueRestartsIntro = 0x02,
    Unknown_0x04 = 0x04,
} SaveFlags;
// Live save-adjacent state block at 0x03003180 (money, playtime, save flags,
// ...); see docs/formats/save.md. abMonsterDocLevel is accessed as a member
// to reproduce the ROM's base+0x10 address shape shared by three code sites.
typedef struct {
    u32 dwMoney;
    Playtime stPlaytime;
    u8 bSaveFlags;
    u8 pad_0D[0x03];
    u8 abMonsterDocLevel[69];
} SaveStateBlock;

extern SaveStateBlock g_saveStateBlock;
extern const Playtime g_stPlaytimeFrameDelta;
extern const Playtime g_stPlaytimeHourLimit;

u32 AddPlaytimeDelta(Playtime *playtime, const Playtime *toAdd);
u32 ComparePlaytimeField(const Playtime *playtime, const Playtime *mask, u32 fieldMask);
void ProcessPlaytimeTick(void);
