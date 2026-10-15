#pragma once

#include "types.h"

extern const u32 g_dwLanguageSelectBg3Control;
extern const u32 g_dwLanguageSelectBg2Control;
extern const u32 g_dwLanguageSelectBg1Control;

extern void DrawLanguageSelectEntries(void);
extern void DrawLanguageSelectEntry(u32 index, u32 selectedIndex);
extern void DrawLanguageSelectFlag(u32 selectedIndex);
