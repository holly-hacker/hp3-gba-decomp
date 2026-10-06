#include "types.h"
#include "game/save.h"
#include "menu/folio_universitas.h"

extern void *memset(void *dst, int value, u32 size);

void ClearFolioUniversitasNewCards(void)
{
    memset(g_saveStateBlock.abFolioUniversitasCardIsNew, 0, sizeof(g_saveStateBlock.abFolioUniversitasCardIsNew));
}
