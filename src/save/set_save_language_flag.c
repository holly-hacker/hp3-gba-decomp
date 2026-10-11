#include "types.h"
#include "text.h"
#include "game/save.h"

// Records the current language in the save header and marks it as chosen.
s32 SetSaveLanguageFlag(void)
{
    g_saveManager.header.language.bLanguageIndex = GetLanguage();
    g_saveManager.header.language.flLanguageConfigured = 1;
    return 1;
}
