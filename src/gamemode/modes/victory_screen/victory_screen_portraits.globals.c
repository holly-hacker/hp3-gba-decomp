#include "types.h"
#include "battle/victory_screen.h"

const VictoryPortraitRect g_aVictoryBg1PortraitRects[3] = {
    { 10, 2, 10, 20 },
    { 2, 2, 10, 20 },
    { 19, 2, 10, 20 },
};

const VictoryPortraitPosition g_aVictoryBg1PortraitPositions[3] = {
    { 0, 1 },
    { 20, 1 },
    { 10, 1 },
};

const s8 g_abVictoryPortraitScrollX[3] = { 3, -3, 0 };

const VictoryPortraitRect g_aVictoryBg2PortraitRects[3] = {
    { 0, 0, 10, 20 },
    { 0, 0, 10, 20 },
    { 0, 0, 10, 20 },
};

const VictoryPortraitPosition g_aVictoryBg2PortraitPositions[3] = {
    { 0, 1 },
    { 18, 1 },
    { 9, 1 },
};
