#include "types.h"
#include "modes.h"
#include "language_select.h"

void DrawLanguageSelectEntries(void)
{
    u32 i;

    for (i = 0; i < 8; i++)
        DrawLanguageSelectEntry(i, g_GameModeStackContext.dwModeScratchB);
}
