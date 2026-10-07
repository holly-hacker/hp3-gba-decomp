#pragma once

#include "types.h"

// Game mode 0x2E (FredAndGeorgesShop), the Weasleys' Wizard Wheezes shop. dwModeState selects the
// screen being handled; UpdateFredAndGeorgesShop runs one handler per state, and only the odd-numbered
// states 1..13 and state 14 have one.
//
// Only the fields the lifetime functions touch are named.
typedef struct FredAndGeorgesShopState {
    u32 dwSavedModeState;  // 0x00; dwModeState when the shop's selection popup opened
    u8 abUnk04[4];
    u8 bUnk08;  // 0x08; cleared by InitializeFredAndGeorgesShop
    u8 abUnk09[0x17];
    u32 adwUnk20[7];  // 0x20; cleared by InitializeFredAndGeorgesShop
    u8 abUnk3C[0x20];
    u8 bUnk5C;  // 0x5C; cleared by InitializeFredAndGeorgesShop
} FredAndGeorgesShopState;
extern FredAndGeorgesShopState g_FredAndGeorgesShop;  // 0x03005AC8
extern const u32 g_dwFredAndGeorgesShopBg1Control;    // 0x0806BAF0

extern void InitializeFredAndGeorgesShop(void);
extern void UpdateFredAndGeorgesShop(void);
extern void ExitFredAndGeorgesShop(void);

extern void sub_08040720(void);  // draws the shop's item list
extern void sub_08040A38(void);
extern void sub_08040CA4(void);
extern void sub_08040F04(void);
extern void sub_0804132C(void);
extern void sub_08041360(void);
extern void sub_08041454(void);  // frees the shop's objects
extern void sub_08041590(void);
extern void sub_080416CC(void);
extern void sub_080418BC(void);
extern void sub_080407CC(void);
