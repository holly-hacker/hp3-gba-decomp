#pragma once

#include "types.h"

// Current vertical scanline, range 0..227. See:
// https://problemkaputt.de/gbatek.htm#lcdiointerruptsandstatus
#define REG_VCOUNT  (*(volatile u16 *)0x04000006)
// Active-low button state; UpdateKeyInput XORs with 0x3FF for active-high.
// Also SIOMLT_RECV (player 0's slot) during a multiplayer link session.
#define REG_KEYINPUT (*(volatile u16 *)0x04000130)
#define REG_IF      (*(volatile u16 *)0x04000202)
#define REG_WAITCNT (*(volatile u16 *)0x04000204)
#define REG_IME     (*(volatile u16 *)0x04000208)

// BIOS-owned RAM mirror of acked interrupt flags (GBATEK "Interrupt Check
// Flag"), not an MMIO register -- SWI IntrWait/VBlankIntrWait poll it.
#define REG_IFBIOS  (*(volatile u16 *)0x03007FF8)
