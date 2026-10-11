#pragma once

#include "types.h"

// Dialog text lookup, language selection and number formatting; see
// docs/formats/text.md.

// Language ids, as stored in gCurrentLanguage and used to index sDialogTextTable.
typedef enum {
    LanguageEnglishUS = 0,
    LanguageEnglishGB = 1,
    LanguageFrench    = 2,
    LanguageGerman    = 3,
    LanguageSpanish   = 4,
    LanguageItalian   = 5,
    LanguageDutch     = 6,
    LanguageDanish    = 7,
} Language;

extern u8 *gDialogTextScratchBuf;  // 0x400-byte buffer GetDialogText decodes into
extern u8 gCurrentLanguage;
extern u8 gLocaleThousandsSep;

u8 *FormatDecimal(s32 value, u8 *pBuf);
void InitDialogTextEngine(void);
void SetLanguage(u32 languageId);
u32 GetLanguage(void);
u8 *GetDialogText(s32 stringId);
u8 *AppendDialogText(u8 *pDest, s32 stringId);
u8 *AppendString(u8 *pDest, const u8 *pSrc);
u8 *FormatHex(s32 value, s32 digitCount, u8 *pBuf);
