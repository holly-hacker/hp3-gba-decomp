#pragma once

#include "types.h"

extern void InitializeStartup(void);
extern void UpdateStartup(void);
extern void ExitStartup(void);

extern const u32 g_dwStartupBg3Control;  // 0x0805E280
extern const u32 g_dwStartupBg2Control;  // 0x0805E284
extern const u32 g_dwStartupBg1Control;  // 0x0805E288
