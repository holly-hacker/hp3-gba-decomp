#include "types.h"
#include "actor.h"
#include "background.h"
#include "char_block.h"
#include "color.h"
#include "combat.h"
#include "combat_dialog.h"
#include "combat_dialog_inline.h"
#include "combat_dispatch.h"
#include "combat_fighter.h"
#include "constants/items.h"
#include "font.h"
#include "interrupts.h"
#include "mode7.h"
#include "oam.h"
#include "particles.h"
#include "sound.h"
#include "text.h"
#include "windows.h"

// Prints a battle message for the active fighter. value and param depend on code; see
// BattleMessageCode.
void ShowBattleMessage(u8 code, u16 value, u16 param)
{
    BattleFighter *fighter;
    s32 textId;
    u8 spellId;
    u8 fighterType;
    u8 y;
    u8 i;
    const u8 *text;

    fighter = &ACTIVE_FIGHTER;
    g_pFightState->dwBattleMessageShown = 1;
    SetTextTargetFromBgControl(g_dwBattleBg0Control);
    SelectTextFont(1, 0, -1);

    switch (code) {
    case SpellLevelUp:
        SelectTextFont(1, 4, -1);
        PlayJingle(0x1A);
        DrawBattleMessageLine(0x904, BATTLE_TEXT_ROW3_Y, 1);  // "The spell levels-up!"
        break;

    case EscapeBlocked:
        ClearBattleMessageBox();
        DrawBattleMessageLine(0x902, BATTLE_TEXT_ROW0_Y, 0);  // "Your escape has been blocked."
        break;

    case SpecialMoveAnnounce:
        ClearBattleMessageBox();
        // "Harry performs a Special Move:", ...
        DrawBattleMessageLine(fighter->bFighterType + 0x970, BATTLE_TEXT_ROW0_Y, 0);
        switch (fighter->bFighterType) {
        case Harry:
            textId = value + 0x478;  // "Horklump Spores", ...
            break;
        case Hermione:
            textId = value + 0x8FA;  // "Be More Careful", ...
            break;
        case Ron:
            textId = value + 0x8FD;  // "Stink Pellet", ...
            break;
        default:
            textId = 0;
            break;
        }
        DrawBattleMessageLine(textId, BATTLE_TEXT_ROW2_Y, 1);
        break;

    case SpecialAbilityText:
        ClearBattleMessageBox();
        switch (fighter->bFighterType) {
        case Harry:
            ClearBattleMessageBox();
            if (value == 3) {
                // "Harry feels better!", ... for the targeted ally
                textId = g_adwSpecialMoveResultTextIds[3]
                    + g_pFightState->pFighters[g_pFightState->aAllySlotTurnOrderIndex[fighter->bSelectedActionIndex]].bFighterType;
            } else if (value == 6) {
                // "Harry is revived!", ..., "The party is revived!"
                fighterType = g_pFightState->pFaintedAllies[fighter->bSelectedActionIndex].bFighterType;
                textId = g_adwReviveTextIds[fighterType];
            } else if (value == 15) {
                // "Wow! Harry learned all possible spells!", ... for the targeted ally
                textId = g_adwSpecialMoveResultTextIds[15]
                    + g_pFightState->pFighters[g_pFightState->aAllySlotTurnOrderIndex[fighter->bSelectedActionIndex]].bFighterType;
            } else {
                // "Horklump spores appear and blast opponent with pollen.", ...
                textId = g_adwSpecialMoveResultTextIds[value];
            }
            break;
        case Hermione:
            textId = value + 0xA39;  // "Hermione's lecture results in armor.", ...
            break;
        case Ron:
            textId = value + 0xA36;  // "Ron's Stink Pellet damages and stuns opponent.", ...
            break;
        default:
            textId = 0;
            break;
        }
        DrawBattleMessageLine(textId, BATTLE_TEXT_ROW1_Y, 0);
        break;

    case ActionAnnounce:
        if (fighter->bFighterType == Enemy) {
            ClearBattleMessageBox();
            // "The ruby fire crab attacks!", ...
            DrawBattleMessageLine(g_adwFighterActionTextIds[fighter->bRosterIndex + 4], BATTLE_TEXT_ROW0_Y, 0);
            break;
        }

        ClearBattleMessageBox();
        if (fighter->bSpellId == Informus)
            spellId = Informus;
        else
            spellId = g_aabFighterSpellMenu[fighter->bFighterType][g_pFightState->bSpellMenuCursor];
        // "Harry casts a spell:", ..., "Buckbeak attacks!"
        DrawBattleMessageLine(g_adwFighterActionTextIds[fighter->bFighterType], BATTLE_TEXT_ROW0_Y, 0);
        if (fighter->bFighterType == Buckbeak)
            break;

        // Spells with a single cast level don't name the level.
        if (spellId == Diffindo || spellId == Informus || spellId == WingardiumLeviosa
            || spellId == Spongify) {
            textId = spellId + 0x95F;  // "Diffindo", ...
        } else {
            SetTextMacro1String(GetDialogText(spellId + 0x95F));  // "Flipendo", ...
            text = GetDialogText(fighter->bSpellLevel + 0x969);  // "Uno", "Duo", "Tria"
            SetTextMacro2String(text);
            textId = 0x8F6;  // "@1 @2"
        }
        DrawBattleMessageLine(textId, BATTLE_TEXT_ROW2_Y, 1);
        break;

    case AttackResult:
        // Damage above 999 is shown as a first line, then the rest.
        if (value > 999) {
            ClearBattleMessageBox();
            DrawBattleMessageLine(0x995, BATTLE_TEXT_ROW0_Y, 1);  // "Critical hit!"
        }

        switch (param) {
        case 0:
            if (value > 999)
                value -= 999;
            else
                ClearBattleMessageBox();
            SetTextMacro1Number(value);
            DrawBattleMessageLine(0x997, BATTLE_TEXT_ROW1_Y, 1);  // "@1 damage."
            break;

        case 1:
            ClearBattleMessageBox();
            fighterType = fighter->bFighterType;
            textId = 0x996;  // "The spell misses."
            if (fighterType == Enemy)
                textId += 0x85;  // "The attack misses."
            DrawBattleMessageLine(textId, BATTLE_TEXT_ROW2_Y, 1);
            break;

        case 2:
            fighter = &g_pFightState->pFighters[value];
            if (fighter->bFighterType == Enemy)
                // "The ruby fire crab goes away!", ...
                textId = g_adwFighterFaintTextIds[fighter->bRosterIndex + 4];
            else
                // "Harry falls unconscious!", ...
                textId = g_adwFighterFaintTextIds[fighter->bFighterType];
            ClearBattleMessageLine(3);
            DrawBattleMessageLine(textId, BATTLE_TEXT_ROW2_Y, 1);
            break;

        case 3:
            // "Harry is poisoned.", ...
            textId = g_pFightState->pFighters[fighter->bSelectedActionIndex].bFighterType + 0x976;
            DrawBattleMessageLine(textId, BATTLE_TEXT_ROW2_Y, 1);
            break;

        case 4:
            if (fighter->bFighterType == Enemy)
                // "Harry is paralyzed.", ...
                textId = g_pFightState->pFighters[fighter->bSelectedActionIndex].bFighterType + 0x97A;
            else
                textId = 0xA1F;  // "The opponent is paralyzed!"
            DrawBattleMessageLine(textId, BATTLE_TEXT_ROW2_Y, 1);
            break;
        }
        break;

    case FaintResult:
        while (g_pFightState->bHitResultCount != 0) {
            SelectTextFont(1, 0, -1);
            g_pFightState->bHitResultCount--;
            ClearBattleMessageBox();

            // @1 is the target: "Harry", "Hermione", "Ron", "Buckbeak", or a creature from
            // index 4 ("Ruby Fire Crab", ...).
            if (g_pFightState->aHitResults[g_pFightState->bHitResultCount].bTargetKind <= 2)
                SetTextMacro1String(GetDialogText(
                    g_pFightState->aHitResults[g_pFightState->bHitResultCount].bTargetKind + 0x8EC));
            else if (g_pFightState->aHitResults[g_pFightState->bHitResultCount].bTargetKind == 3)
                SetTextMacro1String(GetDialogText(0xA3D));  // "Buckbeak"
            else
                SetTextMacro1String(GetDialogText(
                    g_pFightState->aHitResults[g_pFightState->bHitResultCount].bTargetKind + 0x49E));
            DrawBattleMessageLine(0x997, BATTLE_TEXT_ROW0_Y, 0);  // "@1 damage."

            if (g_pFightState->aHitResults[g_pFightState->bHitResultCount].wDamage > 999) {
                DrawBattleMessageLine(0x995, BATTLE_TEXT_ROW1_Y, 1);  // "Critical hit!"
                g_pFightState->aHitResults[g_pFightState->bHitResultCount].wDamage -= 999;
            }

            if (g_pFightState->aHitResults[g_pFightState->bHitResultCount].bMissed == 1) {
                DrawBattleMessageLine(0xA1B, BATTLE_TEXT_ROW2_Y, 1);  // "The attack misses."
            } else {
                SetTextMacro1Number(g_pFightState->aHitResults[g_pFightState->bHitResultCount].wDamage);
                DrawBattleMessageLine(0x997, BATTLE_TEXT_ROW2_Y, 1);  // "@1 damage."
            }

            for (i = 0; i < 30; i++) {
                TickActiveActors();
                TickParticleEmitters();
                TickBgLayers();
                TickScreenWindows();
                TickPaletteAnimations();
                TickBgTileAnimations();
                UpdateFloorAffineTable();
                HideUnusedOamEntries();
                WaitForVBlankIntr();
                WaitForVBlankIntr();
            }

            if (g_pFightState->bHitResultCount == 0)
                CheckBattleVictory(fighter->pActor);
        }
        break;

    case PotionUseAnnounce:
        ClearBattleMessageBox();
        // "Harry uses a potion:", ...
        DrawBattleMessageLine(fighter->bFighterType + 0x973, BATTLE_TEXT_ROW0_Y, 0);
        DrawBattleMessageLine(value + 0x604, BATTLE_TEXT_ROW2_Y, 1);  // the item's name
        break;

    case StatusRestore:
        ClearBattleMessageBox();
        switch (value) {
        case ITEM_WIGGENWELD_POTION:
        case ITEM_GRAND_WIGGENWELD_POTION:
            // "Harry's SP are replenished.", ...
            textId = g_pFightState->pFighters[g_pFightState->aAllySlotTurnOrderIndex[fighter->bSelectedActionIndex]].bFighterType + 0x98D;
            break;
        case ITEM_PEPPERUP_POTION:
        case ITEM_GRAND_PEPPERUP_POTION:
            textId = 0xA27;  // "Your Magic Points are refilled."
            break;
        case ITEM_ANTIDOTE_TO_COMMON_POISONS:
            // "Harry feels better!", ...
            textId = g_pFightState->pFighters[g_pFightState->aAllySlotTurnOrderIndex[fighter->bSelectedActionIndex]].bFighterType + 0x985;
            break;
        case ITEM_ANTI_PARALYSIS_POTION:
            // "Harry can move again!", ...
            textId = g_pFightState->pFighters[g_pFightState->aAllySlotTurnOrderIndex[fighter->bSelectedActionIndex]].bFighterType + 0x981;
            break;
        default:
            textId = 0;
            break;
        }
        DrawBattleMessageLine(textId, BATTLE_TEXT_ROW1_Y, 1);
        break;

    case SpAmount:
        SetTextMacro1Number(value);
        DrawBattleMessageLine(0x998, BATTLE_TEXT_ROW2_Y, 1);  // "@1 SP"
        break;

    case MpAmount:
        SetTextMacro1Number(value);
        DrawBattleMessageLine(0x999, BATTLE_TEXT_ROW2_Y, 1);  // "@1 MP"
        break;

    case Victory:
        ClearBattleMessageBox();
        DrawBattleMessageLine(0xA1E, BATTLE_TEXT_ROW1_Y, 1);  // "You are victorious!"
        break;

    case Defeat:
        ClearBattleMessageBox();
        DrawBattleMessageLine(0xA1D, BATTLE_TEXT_ROW1_Y, 1);  // "You've been defeated."
        break;

    case CantMove:
        ClearBattleMessageBox();
        if (fighter->bFighterType != Enemy)
            // "Harry can't move.", ...
            textId = g_adwFighterCantMoveTextIds[fighter->bFighterType];
        else
            textId = 0xA1C;  // "The opponent can't move!"
        DrawBattleMessageLine(textId, BATTLE_TEXT_ROW1_Y, 1);
        break;

    case CanMoveAgain:
        ClearBattleMessageBox();
        if (fighter->bFighterType != Enemy)
            textId = fighter->bFighterType + 0x981;  // "Harry can move again!", ...
        else
            textId = 0xA20;  // "The opponent can move again!"
        DrawBattleMessageLine(textId, BATTLE_TEXT_ROW1_Y, 1);
        break;

    case AttackWeakenedMessage:
        ClearBattleMessageBox();
        // "The opponent's attacks are weakened."
        DrawBattleMessageLine(0xA3C, BATTLE_TEXT_ROW1_Y, 1);
        break;

    case HiddenFromView:
        // One line per party member, at its own row.
        if (value == 1)
            ClearBattleMessageBox();
        fighterType = g_pFightState->pFighters[param].bFighterType;
        y = fighterType * 8 + BATTLE_TEXT_ROW0_Y;
        text = GetDialogText(fighterType + 0x991);  // "Harry is hidden from view!", ...
        g_pFightState->dwTextTileCursor =
            DrawTextLines(g_pFightState->dwTextTileCursor, 0xA0, y, 0x90, 0x10, &text, 1);
        break;

    case ImmuneToParalysis:
        ClearBattleMessageBox();
        // "The opponent is immune to paralysis!"
        DrawBattleMessageLine(0xA3E, BATTLE_TEXT_ROW1_Y, 1);
        break;
    }
}
