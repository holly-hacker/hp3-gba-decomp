#include "types.h"
#include "pscreen_folio_universitas.h"

u32 GetFolioUniversitasSelectedCard(void)
{
    return g_FolioUniversitasState.dwCategory * 10 + g_FolioUniversitasState.dwSlot;
}
