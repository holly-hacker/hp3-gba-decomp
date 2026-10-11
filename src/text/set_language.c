#include "types.h"
#include "graphics/text.h"
#include "text.h"

// Selects the active language's dialog text blob and the thousands separator
// used when formatting numbers.
void SetLanguage(u32 languageId)
{
    gCurrentLanguage = languageId;
    InitDialogTextTable(sDialogTextTable[languageId]);

#ifdef VERSION_JP
    gLocaleThousandsSep = ',';
#else
    if (gCurrentLanguage == LanguageFrench)
        gLocaleThousandsSep = ' ';
    else if (gCurrentLanguage == LanguageItalian || gCurrentLanguage == LanguageDutch)
        gLocaleThousandsSep = '.';
    else
        gLocaleThousandsSep = ',';
#endif
}
