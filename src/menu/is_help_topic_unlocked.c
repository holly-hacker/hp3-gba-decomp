#include "types.h"
#include "game/save.h"
#include "menu/help.h"

s32 IsHelpTopicUnlocked(const u32 *pTextId)
{
    switch (*pTextId)
    {
    case 0xA4A:  // "Wizard Cracker Pop-it"
        return (g_saveManager.header.bHeaderFlags.all >> 1) & 1;
    case 0xA4B:  // "Buckbeak's Hippogriff Glide"
        return (g_saveManager.header.bHeaderFlags.all >> 2) & 1;
    case 0xA4C:  // "Riddikulus Boggart Challenge"
        return (g_saveManager.header.bHeaderFlags.all >> 3) & 1;
    case 0xA4D:  // "Tea Leaf Divination"
        return (g_saveManager.header.bHeaderFlags.all >> 4) & 1;
    case 0xA4E:  // "Dementor Challenge"
        return (g_saveManager.header.bHeaderFlags.all >> 5) & 1;
    case 0x3F6:  // "Owl Care Kit"
        return g_saveManager.header.bHeaderFlags.all & flOwlCareKitUnlocked;
    default:
        return 1;
    }
}
