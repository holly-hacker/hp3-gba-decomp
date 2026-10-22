#include "types.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dispatch.h"
#include "combat_dispatch_inline.h"
#include "modes.h"
#include "sound.h"
#include "pscreen_folio_universitas.h"

// Folio Universitas and Help return to Battle with the arguments it was entered with.
static inline void SaveBattleResumeArgs(void)
{
    g_pFightState->abBattleResumeArgs[0] = g_GameModeStackContext.dwCurrentGameModeArg1;
    g_pFightState->abBattleResumeArgs[1] = g_GameModeStackContext.dwCurrentGameModeArg2;
    g_pFightState->abBattleResumeArgs[2] = g_GameModeStackContext.dwCurrentGameModeArg3;
}

// Runs the top menu row on the cursor. Hermione and Ron can use their Special Move once per
// battle; Harry's opens the Folio Universitas. Informus and Flee are refused in scripted
// battles (mode argument 3 is 0xFF).
void ConfirmBattleTopMenu(u32 fighterType, BattleFighter *pFighter)
{
    switch (g_pFightState->bMenuCursor) {
    case 0:  // Cast Spell
        PlaySoundById(0);
        ShowSpellChoiceMenu(g_pFightState->bMenuFighterIndex, 0);
        break;

    case 1:  // Special Move
        if ((g_pFightState->dwHermioneSpecialUsed && fighterType == Hermione)
            || (g_pFightState->dwRonSpecialUsed && fighterType == Ron)) {
            PlaySoundById(3);
            break;
        }

        PlaySoundById(0);
        if (fighterType == Harry) {
            pFighter->bPendingActionKind = PendingActionSpecialMove;
            SaveBattleResumeArgs();
            PushGameMode_2(FolioUniversitas, FolioUniversitasPickCombo, 0);
        } else {
            OpenSpecialMoveMenu(g_pFightState->bMenuFighterIndex);
        }
        break;

    case 3:  // Use Item
        PlaySoundById(1);
        pFighter->bSelectedActionIndex = 0;
        OpenItemMenu(g_pFightState->bMenuFighterIndex);
        g_pFightState->bMenuScreen = BattleMenuItem;
        break;

    case 2:  // Informus
        if (g_GameModeStackContext.dwCurrentGameModeArg3 == 0xFF) {
            PlaySoundById(3);
            break;
        }

        PlaySoundById(1);
        pFighter->bSelectedActionIndex = 0;
        pFighter->bSpellId = Informus;
        pFighter->bPendingActionKind = PendingActionInformus;
        pFighter->bSpellLevel = 0;
        ShowEnemyTargetMenu(g_pFightState->bMenuFighterIndex);
        break;

    case 4:  // Flee
        if (g_dwPendingGameMode.dwCurrentGameModeArg3 == 0xFF) {
            PlaySoundById(3);
            break;
        }

        PlaySoundById(1);
        g_pFightState->bMenuScreen = BattleMenuNone;
        pFighter->bPendingActionKind = PendingActionFlee;
        pFighter->bSelectedActionIndex = 0;
        break;

    case 5:  // Folio Bruti
        PlaySoundById(1);
        PushGameMode(FolioBruti);
        break;

    case 6:  // Help
        PlaySoundById(1);
        SaveBattleResumeArgs();
        PushGameMode_3(HelpTopicScreen, g_GameModeStackContext.dwCurrentGameModeArg1, 6,
                       g_GameModeStackContext.dwCurrentGameModeArg3);
        break;
    }
}
