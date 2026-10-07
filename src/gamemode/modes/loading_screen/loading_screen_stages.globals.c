#include "types.h"
#include "menu/loading_screen.h"

const LoadingScreenTables g_LoadingScreenTables = {
    { 0x00, 0x05, 0x08, 0x04, 0x16, 0x1A, 0xFF },
    {
        { 2, 4, 0, 0x6 },
        { 3, 5, 0, 0x7 },
        { 2, 4, 0, 0x6 },
        { 3, 6, 0, 0x7 },
        { 1, 2, 0, 0x3 },
        { 1, 2, 0, 0x3 },
    },
};
