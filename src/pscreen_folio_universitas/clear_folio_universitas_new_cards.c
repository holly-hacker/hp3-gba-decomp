#include "types.h"
#include "save.h"
#include "pscreen_folio_universitas.h"
#include "mem.h"

void ClearFolioUniversitasNewCards(void)
{
    memset(g_saveStateBlock.abFolioUniversitasCardIsNew, 0, sizeof(g_saveStateBlock.abFolioUniversitasCardIsNew));
}
