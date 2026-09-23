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

#define REG_DMA3SAD   (*(volatile u32 *)0x040000D4)
#define REG_DMA3DAD   (*(volatile u32 *)0x040000D8)
#define REG_DMA3CNT   (*(volatile u32 *)0x040000DC)
#define REG_DMA3CNT_H (*(volatile u16 *)0x040000DE)

// Serial EEPROM bus, memory-mapped over the SRAM-area mirror while a
// game-pak DMA is in flight; only the low bit of each transferred
// halfword is wired to the chip. See EepromDma3Transfer.
#define EEPROM_PORT ((void *)0x0D000000)

// BIOS-owned RAM mirror of acked interrupt flags (GBATEK "Interrupt Check
// Flag"), not an MMIO register -- SWI IntrWait/VBlankIntrWait poll it.
#define REG_IFBIOS  (*(volatile u16 *)0x03007FF8)

// Start of video RAM.
#define VRAM_BASE ((void *)0x06000000)

// Background palette RAM, 256 colors.
#define BG_PLTT ((volatile u16 *)0x05000000)

// BG2 affine parameters (fixed-point 8.8) and reference point. The reference
// point registers are 32-bit; only the low halves are written here.
#define REG_BG2PA   (*(volatile u16 *)0x04000020)
#define REG_BG2PB   (*(volatile u16 *)0x04000022)
#define REG_BG2PC   (*(volatile u16 *)0x04000024)
#define REG_BG2PD   (*(volatile u16 *)0x04000026)
#define REG_BG2X_L  (*(volatile u16 *)0x04000028)
#define REG_BG2Y_L  (*(volatile u16 *)0x0400002C)
