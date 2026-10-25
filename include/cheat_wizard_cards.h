#pragma once

#include "types.h"
#include "actor.h"

typedef struct {
    Actor *pCardActor;  // 0x00: sprite showing the selected card
    u32 dwSelection;      // 0x04: card index, 0..0x32
} CheatWizardCardsState;

extern CheatWizardCardsState g_CheatWizardCardsState;  // 0x03002238
extern const u32 g_dwCheatWizardCardsBg0Control;
extern const u32 g_dwCheatWizardCardsBg1Control;
extern const u32 g_dwCheatWizardCardsBg2Control;

extern const u8 sFamousWizardCardNames[51][32];

extern void InitializeCheatWizardCards(void);
extern void UpdateCheatWizardCards(void);
extern void ExitCheatWizardCards(void);

extern void ShowCheatWizardCard(void);
