#include "types.h"
#include "game/save.h"

// Full volume, the first language not yet confirmed, and nothing unlocked.
const SaveHeader g_DefaultSaveHeader = {
#ifdef VERSION_JP
    "HPPOA004",
#else
    "HPPOA001",
#endif
    { 0, 0 },
    10,
    10,
    { 1, 0 },  // abUnknown0
    { 0 },
    0,
};
