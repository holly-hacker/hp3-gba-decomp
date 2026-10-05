#include "types.h"
#include "menu/status_equip.h"

// Two columns of three slots; bUp/bDown/bLeft/bRight wrap around the grid.
const StatusEquipSlot g_aStatusEquipSlots[6] = {
    { 122,  36, 2, 0x5A2, 4, 2, 1, 1 },
    { 200,  36, 4, 0x5A4, 5, 3, 0, 0 },
    { 122,  76, 0, 0x5A0, 0, 4, 3, 3 },
    { 200,  76, 5, 0x5A5, 1, 5, 2, 2 },
    { 122, 116, 3, 0x5A3, 2, 0, 5, 5 },
    { 200, 116, 1, 0x5A1, 3, 1, 4, 4 },
};
