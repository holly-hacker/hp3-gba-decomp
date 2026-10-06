#include "types.h"
#include "game/save.h"

// Writes the Folio Universitas card counts (one nibble per card) and the
// seen and new-card bit sets.
void SerializeFolioUniversitas(void)
{
    PackNibblesToSaveStream(g_saveStateBlock.abFolioUniversitasCounts, sizeof(g_saveStateBlock.abFolioUniversitasCounts));
    PackBytesToSaveStream(g_saveStateBlock.abFolioUniversitasSeen, sizeof(g_saveStateBlock.abFolioUniversitasSeen));
    PackBytesToSaveStream(g_saveStateBlock.abFolioUniversitasCardIsNew, sizeof(g_saveStateBlock.abFolioUniversitasCardIsNew));
}
