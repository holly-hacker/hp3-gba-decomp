#include "types.h"
#include "save.h"
#include "game_state.h"

// The playtime a new game starts from.
const Playtime g_stPlaytimeZero = { 0 };

// Added to the playtime every frame, until it reaches the 99 hour cap.
const Playtime g_stPlaytimeFrameDelta = { 0, 0, 0, 0, 1 };
const Playtime g_stPlaytimeHourLimit = { 0, 99 };
