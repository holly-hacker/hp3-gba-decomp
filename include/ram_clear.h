#pragma once

#include "types.h"

// Start/end of the statically linked IWRAM and EWRAM sections, as ROM
// pointer constants. kramInstall copies the ROM image of these sections
// to RAM; ClearWorkRam zeroes the RAM above them.
extern u8 g_IwramSectionStart[];  // 0x03000000
extern u8 g_IwramSectionEnd[];    // 0x03001598
extern u8 g_EwramSectionStart[];  // 0x02000000
extern u8 g_EwramSectionEnd[];    // 0x020027F8
// ROM images of those sections, stored back to back.
extern const u8 g_IwramSectionRomImage[];
extern const u8 g_EwramSectionRomImage[];
extern u8 *const g_pIwramSectionStart;
extern u8 *const g_pIwramSectionEnd;
extern u8 *const g_pEwramSectionStart;
extern u8 *const g_pEwramSectionEnd;

void ClearSystemMemory(void);
void ClearWorkRam(void);
// ClearVram, ClearOamDma, then ClearPaletteRamDma.
void ClearVideoMemory(void);
void ClearVram(void);
void ClearOamDma(void);
void ClearPaletteRamDma(void);
