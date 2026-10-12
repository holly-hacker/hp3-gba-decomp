#include "types.h"
#include "combat_result.h"

const CombatResultPortraitRect g_aCombatResultBg1PortraitRects[3] = {
    { 10, 2, 10, 20 },
    { 2, 2, 10, 20 },
    { 19, 2, 10, 20 },
};

const CombatResultPortraitPosition g_aCombatResultBg1PortraitPositions[3] = {
    { 0, 1 },
    { 20, 1 },
    { 10, 1 },
};

const s8 g_abCombatResultPortraitScrollX[3] = { 3, -3, 0 };

const CombatResultPortraitRect g_aCombatResultBg2PortraitRects[3] = {
    { 0, 0, 10, 20 },
    { 0, 0, 10, 20 },
    { 0, 0, 10, 20 },
};

const CombatResultPortraitPosition g_aCombatResultBg2PortraitPositions[3] = {
    { 0, 1 },
    { 18, 1 },
    { 9, 1 },
};
