#include "types.h"
#include "menu/choose_character.h"

const u8 g_abChooseCharacterStages[7] = { 0x00, 0x05, 0x08, 0x04, 0x16, 0x1A, 0xFF };

const u8 g_aabChooseCharacterOptionRows[6][4] = {
    { 2, 4, 0, 0x6 },
    { 3, 5, 0, 0x7 },
    { 2, 4, 0, 0x6 },
    { 3, 6, 0, 0x7 },
    { 1, 2, 0, 0x3 },
    { 1, 2, 0, 0x3 },
};

const u32 g_aadwChooseCharacterObjectiveTextIds[6][CHOOSE_CHARACTER_OPTION_COUNT] = {
    { 0x90F, 0x90E, 0xFFFFFFFF },  // "Find the train conductor.", "Find chocolate for Harry."
    { 0x90C, 0x90D, 0xFFFFFFFF },  // "Go to the cellar and find Crookshanks.", "... Scabbers."
    { 0x90F, 0x90E, 0xFFFFFFFF },  // "Find the train conductor.", "Find chocolate for Harry."
    { 0x911, 0x911, 0xFFFFFFFF },  // "Collect Ingredients."
    { 0x912, 0x912, 0xFFFFFFFF },  // "Find the path to the Shrieking Shack."
    { 0x913, 0x913, 0xFFFFFFFF },  // "Rescue Sirius Black."
};

const u8 g_aaabChooseCharacterActorX[6][3][3] = {
    {
        { 92, 68, 172 },
        { 148, 68, 172 },
        { 0, 0, 0 },
    },
    {
        { 92, 68, 172 },
        { 148, 68, 172 },
        { 0, 0, 0 },
    },
    {
        { 0, 80, 160 },
        { 0, 80, 160 },
        { 0, 0, 0 },
    },
    {
        { 68, 92, 172 },
        { 68, 148, 172 },
        { 0, 0, 0 },
    },
    {
        { 80, 160, 160 },
        { 80, 160, 160 },
        { 0, 0, 0 },
    },
    {
        { 80, 160, 160 },
        { 80, 160, 160 },
        { 0, 0, 0 },
    },
};

const u8 g_abChooseCharacterTwoOptions[6] = { 1, 1, 1, 1, 1, 1 };
