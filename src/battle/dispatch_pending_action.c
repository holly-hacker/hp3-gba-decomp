#include "types.h"
#include "battle/battle.h"
#include "game/game_modes.h"
#include "graphics/audio.h"
#include "mt19937.h"
#include "overworld/room.h"

// Starts the active fighter's queued menu action (spell, item, Special Move
// or flee attempt): announces it and puts the fighter's Object into the
// matching action state. The parameter is ignored; the active fighter is
// read from FightState.
void DispatchPendingAction(s32 fighterType)
{
    BattleFighter *fighter = &ACTIVE_FIGHTER;
    u8 spellId;

    switch (fighter->bPendingActionKind) {
    case PendingActionNone:
    case PendingActionInformus:
        ShowBattleMessage(ActionAnnounce, 0, 0);
        spellId = fighter->bSpellId;
        TrackSpellFamiliarity(fighter->bFighterType, spellId, fighter->bSpellLevel, &fighter->wHp);
        SetObjectActionState(fighter->pObject, 0x1A);
        fighter->pObject->bActionFlags = 0x21;
        break;

    case PendingActionSpecialMove:
        if (fighter->bFighterType == Harry)
            fighter->bSpellId = g_nFolioUniversitasSlot;

        ShowBattleMessage(SpecialMoveAnnounce, fighter->bSpellId, 0);
        SetObjectActionState(fighter->pObject, 0x15);

        if (fighter->bFighterType == Hermione)
            g_pFightState->dwHermioneSpecialUsed = 1;
        else if (fighter->bFighterType == Ron)
            g_pFightState->dwRonSpecialUsed = 1;

        break;

    case PendingActionUseItem:
        ShowBattleMessage(ItemUseAnnounce, fighter->bSpellLevel, 0);
        SetObjectActionState(fighter->pObject, 4);
        break;

    case PendingActionFlee:
        if (Mt19937Chance(75)) {
            PlaySoundById(0x9D);
            PushGameMode_2(Overworld, 3, g_bCurrentRoomId);
        } else {
            ShowBattleMessage(EscapeBlocked, 0, 0);
            SetObjectActionState(fighter->pObject, 5);
        }

        break;
    }
}
