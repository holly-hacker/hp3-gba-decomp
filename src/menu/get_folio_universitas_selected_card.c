#include "types.h"
#include "menu/folio_universitas.h"

u32 GetFolioUniversitasSelectedCard(void)
{
    return g_FolioUniversitasState.dwCategory * 10 + g_FolioUniversitasState.dwSlot;
}
