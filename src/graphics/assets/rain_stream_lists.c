#include "types.h"
#include "battle/effect_script.h"
#include "gen/graphics/overworld.h"

// Rain streak and splash streams, each behind the 8-byte control block of an effect BG record
// (docs/formats/graphic_blob.md).
const EffectStreamList32 g_RainStreakList_candidate = {
    { 0x02a01f03, 0x400 },
    {
        { (void *)gRainStreak01, 1 },
        { (void *)gRainStreak02, 1 },
        { (void *)gRainStreak03, 1 },
        { (void *)gRainStreak04, 1 },
        { (void *)gRainStreak05, 1 },
        { (void *)gRainStreak06, 1 },
        { (void *)gRainStreak07, 1 },
        { (void *)gRainStreak08, 1 },
        { (void *)gRainStreak09, 1 },
        { (void *)gRainStreak10, 1 },
        { (void *)gRainStreak11, 1 },
        { (void *)gRainStreak12, 1 },
        { (void *)gRainStreak13, 1 },
        { (void *)gRainStreak14, 1 },
        { (void *)gRainStreak15, 1 },
        { (void *)gRainStreak16, 1 },
        { (void *)gRainStreak17, 1 },
        { (void *)gRainStreak18, 1 },
        { (void *)gRainStreak19, 1 },
        { (void *)gRainStreak20, 1 },
        { (void *)gRainStreak21, 1 },
        { (void *)gRainStreak22, 1 },
        { (void *)gRainStreak23, 1 },
        { (void *)gRainStreak24, 1 },
        { (void *)gRainStreak25, 1 },
        { (void *)gRainStreak26, 1 },
        { (void *)gRainStreak27, 1 },
        { (void *)gRainStreak28, 1 },
        { (void *)gRainStreak29, 1 },
        { (void *)gRainStreak30, 1 },
        { (void *)gRainStreak31, 1 },
        { (void *)gRainStreak32, 1 },
    },
};

const EffectStreamList8 g_RainSplashList_candidate = {
    { 0x031c0802, 0x120 },
    {
        { (void *)gRainSplash01, 2 },
        { (void *)gRainSplash02, 2 },
        { (void *)gRainSplash03, 2 },
        { (void *)gRainSplash04, 2 },
        { (void *)gRainSplash05, 2 },
        { (void *)gRainSplash06, 2 },
        { (void *)gRainSplash07, 2 },
        { (void *)gRainSplash08, 2 },
    },
};
