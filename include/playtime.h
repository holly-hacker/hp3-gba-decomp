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
typedef struct {
    u32 dwMoney;
    Playtime stPlaytime;
    u8 bSaveFlags;
} SaveStateBlock;

extern SaveStateBlock g_saveStateBlock;
extern const Playtime g_stPlaytimeFrameDelta;
extern const Playtime g_stPlaytimeHourLimit;

u32 AddPlaytimeDelta(Playtime *playtime, const Playtime *toAdd);
u32 ComparePlaytimeField(const Playtime *playtime, const Playtime *mask, u32 fieldMask);
void ProcessPlaytimeTick(void);
