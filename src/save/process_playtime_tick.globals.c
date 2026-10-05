#include "types.h"
#include "game/save.h"

// Added to the playtime every frame, until it reaches the 99 hour cap.
const Playtime g_stPlaytimeFrameDelta = { 0, 0, 0, 0, 1 };
const Playtime g_stPlaytimeHourLimit = { 0, 99 };
