#pragma once

#include "types.h"

extern const u32 g_dwLanguageSelectBg3Control;
extern const u32 g_dwLanguageSelectBg2Control;
extern const u32 g_dwLanguageSelectBg1Control;

extern void DrawLanguageSelectEntries_candidate(void);
extern void DrawLanguageSelectEntry_candidate(u32 index, u32 selectedIndex);
extern void DrawLanguageSelectPicture_candidate(u32 selectedIndex);
