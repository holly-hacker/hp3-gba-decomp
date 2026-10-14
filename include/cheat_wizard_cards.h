#pragma once

#include "types.h"
#include "actor.h"
#include "gen/graphics/menus.h"

typedef struct {
    Actor *pCardActor;  // 0x00: sprite showing the selected card
    u32 dwSelection;      // 0x04: card index, 0..0x32
} CheatWizardCardsState;

extern CheatWizardCardsState g_CheatWizardCardsState;  // 0x03002238
extern const u32 g_dwCheatWizardCardsBg0Control;  // 0x0804CEC0
extern const u32 g_dwCheatWizardCardsBg1Control;  // 0x0804CEBC
extern const u32 g_dwCheatWizardCardsBg2Control;  // 0x0804CEB8

extern const u8 sFamousWizardCardNames[51][32];  // 0x0804CEC4

extern void ShowCheatWizardCard(void);
