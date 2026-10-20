#pragma once

#include "types.h"

typedef struct {
    const void *src;
    void *dst;
    u32 cnt;
} DmaRegs;

// REG_JOYCNT flags: JOY reset, receive complete and send complete.
#define JOYCNT_RESET 0x0001
#define JOYCNT_RECV  0x0002
#define JOYCNT_SEND  0x0004

#define DISPSTAT_VBLANK      0x0001 // REG_DISPSTAT: set during VBlank (scanlines 160-226)
#define DISPSTAT_HBLANK      0x0002 // REG_DISPSTAT: set during HBlank
#define DISPCNT_FORCED_BLANK 0x0080 // REG_DISPCNT: LCD shows white, VRAM freely accessible
#define DISPCNT_WIN0_ON      0x2000 // REG_DISPCNT: window 0 enabled
#define DISPCNT_WIN1_ON      0x4000 // REG_DISPCNT: window 1 enabled
#define BGCNT_MOSAIC         0x0040 // REG_BGxCNT: mosaic enabled
#define BLDCNT_BRIGHTEN      0x0080 // REG_BLDCNT: brighten the first targets by BLDY
#define BLDCNT_DARKEN        0x00C0 // REG_BLDCNT: darken the first targets by BLDY

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 160

// On-board (EWRAM) and in-chip (IWRAM) work RAM.
#define EWRAM_BASE ((u8 *)0x02000000)
#define EWRAM_END  ((u8 *)0x02040000)
#define IWRAM_BASE ((u8 *)0x03000000)
// Upper IWRAM holding the IRQ and system stacks (gIrqStackTop,
// gSystemStackTop) and the BIOS area; ClearWorkRam stops here.
#define IWRAM_STACKS ((u8 *)0x03007D00)

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

// BG0-BG3 control, indexed by BG number.
#define REG_BGCNT(n) (((volatile u16 *)0x04000008)[n])

// BG0-BG2 control: priority in bits 0-1.
#define REG_BG0CNT  (*(volatile u16 *)0x04000008)
#define REG_BG1CNT  (*(volatile u16 *)0x0400000A)
#define REG_BG2CNT  (*(volatile u16 *)0x0400000C)
#define REG_BG3CNT  (*(volatile u16 *)0x0400000E)

// BG0-BG3 scroll offsets, indexed by BG number.
#define REG_BGHOFS(n) (*(volatile u16 *)(0x04000010 + (n) * 4))
#define REG_BGVOFS(n) (*(volatile u16 *)(0x04000012 + (n) * 4))

// BG2 scroll offsets.
#define REG_BG2HOFS (*(volatile u16 *)0x04000018)
#define REG_BG2VOFS (*(volatile u16 *)0x0400001A)

// BG2 affine parameters (fixed-point 8.8) and reference point. The reference
// point registers are 32-bit; only the low halves are written here.
#define REG_BG2PA   (*(volatile u16 *)0x04000020)
#define REG_BG2PB   (*(volatile u16 *)0x04000022)
#define REG_BG2PC   (*(volatile u16 *)0x04000024)
#define REG_BG2PD   (*(volatile u16 *)0x04000026)
#define REG_BG2X_L  (*(volatile u16 *)0x04000028)
#define REG_BG2X_H  (*(volatile u16 *)0x0400002A)
#define REG_BG2Y_L  (*(volatile u16 *)0x0400002C)

// BG3 affine parameters; the reference point follows PD as BG2's does.
#define REG_BG3PA   (*(volatile u16 *)0x04000030)

// Window 0/1 horizontal (left << 8 | right) and vertical (top << 8 | bottom) extents.
#define REG_WIN0H (*(volatile u16 *)0x04000040)
#define REG_WIN1H (*(volatile u16 *)0x04000042)
#define REG_WIN0V (*(volatile u16 *)0x04000044)
#define REG_WIN1V (*(volatile u16 *)0x04000046)

// WIN0H/WIN1H and WIN0V/WIN1V, indexed by window number.
#define REG_WINH(n) (((volatile u16 *)0x04000040)[n])
#define REG_WINV(n) (((volatile u16 *)0x04000044)[n])

// Window 0/1 inside layer enables.
#define REG_WININ (*(volatile u16 *)0x04000048)
// WININ without volatile, which lets `& 0xFF` narrow to a byte load
// (SetScreenWindowLayers).
#define REG_WININ_NONVOLATILE (*(u16 *)0x04000048)

// Window outside/OBJ-window layer enables.
#define REG_WINOUT (*(volatile u16 *)0x0400004A)

// Mosaic sizes minus one: BG H, BG V, OBJ H, OBJ V in successive nibbles.
#define REG_MOSAIC (*(volatile u16 *)0x0400004C)

// Color effects: blend control, alpha and brightness coefficients.
#define REG_BLDCNT   (*(volatile u16 *)0x04000050)
#define REG_BLDALPHA (*(volatile u16 *)0x04000052)
#define REG_BLDY     (*(volatile u16 *)0x04000054)

#define REG_DMA0SAD   (*(volatile u32 *)0x040000B0)
#define REG_DMA0DAD   (*(volatile u32 *)0x040000B4)
#define REG_DMA0CNT   (*(volatile u32 *)0x040000B8)
#define REG_DMA0CNT_H (*(volatile u16 *)0x040000BA)

#define REG_DMA3      (*(volatile DmaRegs *)0x040000D4)
#define REG_DMA3SAD   (*(volatile u32 *)0x040000D4)
#define REG_DMA3DAD   (*(volatile u32 *)0x040000D8)
#define REG_DMA3CNT   (*(volatile u32 *)0x040000DC)
#define REG_DMA3CNT_H (*(volatile u16 *)0x040000DE)

// Timer 3 control (the link cable's serial pump) and serial communication.
#define REG_TM3CNT_L     (*(volatile u16 *)0x0400010C)
#define REG_TM3CNT_H     (*(volatile u16 *)0x0400010E)
// SIOMULTI0-3: the word each multiplayer terminal sent in the last transfer.
#define REG_SIOMULTI(n)  (((volatile u16 *)0x04000120)[n])
#define REG_SIOCNT       (*(volatile u16 *)0x04000128)
#define REG_SIOMLT_SEND  (*(volatile u16 *)0x0400012A)
// Active-low button state; UpdateKeyInput XORs with 0x3FF for active-high.
// Also SIOMLT_RECV (player 0's slot) during a multiplayer link session.
#define REG_KEYINPUT     (*(volatile u16 *)0x04000130)
#define REG_RCNT         (*(volatile u16 *)0x04000134)
// JOY Bus (GameCube link) control, receive/transmit words and status.
#define REG_JOYCNT       (*(volatile u16 *)0x04000140)
#define REG_JOY_RECV     (*(volatile u32 *)0x04000150)
#define REG_JOY_TRANS    (*(volatile u32 *)0x04000154)
#define REG_JOYSTAT      (*(volatile u16 *)0x04000158)
// Interrupt enable and request/acknowledge flags.
#define REG_IE      (*(volatile u16 *)0x04000200)
#define REG_IF      (*(volatile u16 *)0x04000202)
#define REG_WAITCNT (*(volatile u16 *)0x04000204)
#define REG_IME     (*(volatile u16 *)0x04000208)

// Background palette RAM, 256 colors.
#define BG_PLTT ((volatile u16 *)0x05000000)

// Sprite (OBJ) palette RAM, 256 colors.
#define OBJ_PLTT ((volatile u16 *)0x05000200)

// Start of video RAM.
#define VRAM_BASE ((void *)0x06000000)
#define VRAM_SIZE 0x18000
#define OBJ_VRAM_TILES ((u8 *)0x06010000)

// Game Pak ROM.
#define ROM_BASE ((u8 *)0x08000000)

// Serial EEPROM bus, memory-mapped over the SRAM-area mirror while a
// game-pak DMA is in flight; only the low bit of each transferred
// halfword is wired to the chip. See EepromDma3Transfer.
#define EEPROM_PORT ((void *)0x0D000000)
