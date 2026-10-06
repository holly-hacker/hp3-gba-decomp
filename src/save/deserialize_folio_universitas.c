#include "types.h"
#include "game/save.h"

// Reads the Folio Universitas card counts (one nibble per card) and the
// seen and new-card bit sets.
void DeserializeFolioUniversitas(void)
{
    UnpackNibblesFromSaveStream(g_saveStateBlock.abFolioUniversitasCounts, sizeof(g_saveStateBlock.abFolioUniversitasCounts));
    UnpackBytesFromSaveStream(g_saveStateBlock.abFolioUniversitasSeen, sizeof(g_saveStateBlock.abFolioUniversitasSeen));
    UnpackBytesFromSaveStream(g_saveStateBlock.abFolioUniversitasCardIsNew, sizeof(g_saveStateBlock.abFolioUniversitasCardIsNew));
}
