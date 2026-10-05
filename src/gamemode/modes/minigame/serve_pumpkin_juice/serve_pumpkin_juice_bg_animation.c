#include "types.h"
#include "graphics/display.h"
#include "minigame/serve_pumpkin_juice.h"
#include "gen/graphics/minigames/pumpkin.h"

// BG2's animation, registered with g_dwServePumpkinJuiceBg2Control.
const BgTileAnimation16 g_ServePumpkinJuiceTable = {
    2, 16, 1, 0x780,
    {
        { gServePumpkinJuiceFrame001, 3 },
        { gServePumpkinJuiceFrame002, 3 },
        { gServePumpkinJuiceFrame003, 3 },
        { gServePumpkinJuiceFrame004, 3 },
        { gServePumpkinJuiceFrame005, 3 },
        { gServePumpkinJuiceFrame006, 3 },
        { gServePumpkinJuiceFrame007, 3 },
        { gServePumpkinJuiceFrame008, 3 },
        { gServePumpkinJuiceFrame009, 3 },
        { gServePumpkinJuiceFrame010, 3 },
        { gServePumpkinJuiceFrame011, 3 },
        { gServePumpkinJuiceFrame012, 3 },
        { gServePumpkinJuiceFrame013, 3 },
        { gServePumpkinJuiceFrame014, 3 },
        { gServePumpkinJuiceFrame015, 3 },
        { gServePumpkinJuiceFrame016, 3 },
    },
};
