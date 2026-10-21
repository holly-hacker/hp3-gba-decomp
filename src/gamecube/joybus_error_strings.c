#include "gamecube.h"

// Names of the JOYBUS_ERROR_* codes. No reader of the table was found.
char *g_apJoybusErrorStrings[JOYBUS_ERROR_COUNT] = {
    "Error: None",
    "Error: Game Code Send",
    "Error: Game Code Recv",
    "Error: Timeout",
    "Error: Invalid Command",
    "Error: Invalid Mode",
    "Error: Recv Missing Packet",
    "Error: Recv CRC",
    "Error: Recv Overrun",
    "Error: Send Overrun",
};
