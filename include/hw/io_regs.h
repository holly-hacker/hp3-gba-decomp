#pragma once

#include "types.h"

// BIOS-owned RAM mirror of acked interrupt flags (GBATEK "Interrupt Check
// Flag"), not an MMIO register -- SWI IntrWait/VBlankIntrWait poll it.
#define REG_IFBIOS  (*(volatile u16 *)0x03007FF8)

// Display control: layer enables and display mode.
#define REG_DISPCNT (*(volatile u16 *)0x04000000)

// Display status: blank flags and the VBlank/HBlank/VCount IRQ enables.
#define REG_DISPSTAT (*(volatile u16 *)0x04000004)

// Current vertical scanline, range 0..227. See:
// https://problemkaputt.de/gbatek.htm#lcdiointerruptsandstatus
#define REG_VCOUNT  (*(volatile u16 *)0x04000006)

// BG0-BG2 control: priority in bits 0-1.
#define REG_BG0CNT  (*(volatile u16 *)0x04000008)
#define REG_BG1CNT  (*(volatile u16 *)0x0400000A)
#define REG_BG2CNT  (*(volatile u16 *)0x0400000C)

// BG2 affine parameters (fixed-point 8.8) and reference point. The reference
// point registers are 32-bit; only the low halves are written here.
#define REG_BG2PA   (*(volatile u16 *)0x04000020)
#define REG_BG2PB   (*(volatile u16 *)0x04000022)
#define REG_BG2PC   (*(volatile u16 *)0x04000024)
#define REG_BG2PD   (*(volatile u16 *)0x04000026)
#define REG_BG2X_L  (*(volatile u16 *)0x04000028)
#define REG_BG2Y_L  (*(volatile u16 *)0x0400002C)

// Window 0/1 inside layer enables.
#define REG_WININ (*(volatile u16 *)0x04000048)

// Window outside/OBJ-window layer enables.
#define REG_WINOUT (*(volatile u16 *)0x0400004A)

// Color effects: blend control and brightness coefficient.
#define REG_BLDCNT (*(volatile u16 *)0x04000050)
#define REG_BLDY   (*(volatile u16 *)0x04000054)

#define REG_DMA3SAD   (*(volatile u32 *)0x040000D4)
#define REG_DMA3DAD   (*(volatile u32 *)0x040000D8)
#define REG_DMA3CNT   (*(volatile u32 *)0x040000DC)
#define REG_DMA3CNT_H (*(volatile u16 *)0x040000DE)

// Active-low button state; UpdateKeyInput XORs with 0x3FF for active-high.
// Also SIOMLT_RECV (player 0's slot) during a multiplayer link session.
#define REG_KEYINPUT (*(volatile u16 *)0x04000130)
// Timer 3 control (the link cable's serial pump) and serial communication.
#define REG_TM3CNT_H     (*(volatile u16 *)0x0400010E)
#define REG_SIOCNT       (*(volatile u16 *)0x04000128)
#define REG_SIOMLT_SEND  (*(volatile u16 *)0x0400012A)
// Interrupt enable and request/acknowledge flags.
#define REG_IE      (*(volatile u16 *)0x04000200)
#define REG_IF      (*(volatile u16 *)0x04000202)
#define REG_WAITCNT (*(volatile u16 *)0x04000204)
#define REG_IME     (*(volatile u16 *)0x04000208)

// On-board (EWRAM) and in-chip (IWRAM) work RAM.
#define EWRAM_BASE ((u8 *)0x02000000)
#define EWRAM_END  ((u8 *)0x02040000)
#define IWRAM_BASE ((u8 *)0x03000000)

// Background palette RAM, 256 colors.
#define BG_PLTT ((volatile u16 *)0x05000000)

// Sprite (OBJ) palette RAM, 256 colors.
#define OBJ_PLTT ((volatile u16 *)0x05000200)

// Start of video RAM.
#define VRAM_BASE ((void *)0x06000000)
#define VRAM_SIZE 0x18000
#define OBJ_VRAM_TILES ((u8 *)0x06010000)

// Serial EEPROM bus, memory-mapped over the SRAM-area mirror while a
// game-pak DMA is in flight; only the low bit of each transferred
// halfword is wired to the chip. See EepromDma3Transfer.
#define EEPROM_PORT ((void *)0x0D000000)
