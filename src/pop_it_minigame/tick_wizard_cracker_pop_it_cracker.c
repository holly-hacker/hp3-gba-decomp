#include "types.h"
#include "actor.h"
#include "modes.h"
#include "sound.h"
#include "pop_it_minigame.h"
#include "pop_it_minigame_inline.h"

void TickWizardCrackerPopItCracker(Actor *pCracker)
{
    u32 score;

    switch (pCracker->bActionState)
    {
    case 0:
        // Idle on the board.
        break;
    case 4:
        // Selected: pops after its place in the group's order.
        if (--pCracker->dwStateTimer == 0)
        {
            SetWizardCrackerPopItCrackerPopAnim(pCracker);
            SetActorActionState(pCracker, 1);
            pCracker->dwStateTimer = 22;
            g_pWizardCrackerPopIt->dwPopBonus += 5 << g_GameModeStackContext.dwCurrentGameModeArg3;
            score = g_pWizardCrackerPopIt->dwScore + g_pWizardCrackerPopIt->dwPopBonus;
            if (score > g_pWizardCrackerPopIt->dwScore)
                g_pWizardCrackerPopIt->dwScore = score;
            DrawWizardCrackerPopItScore();
        }
        break;
    case 1:
        if (--pCracker->dwStateTimer == 0)
            pCracker->dwFlags = (pCracker->dwFlags & ~ActorFlagVisible) | ActorFlagPendingDestroy | ActorFlagAnimFrameLoaded;
        break;
    case 15:
        // Rising into a gap or sliding over an empty column.
        if (pCracker->pos.x == pCracker->moveTarget.x && pCracker->pos.y == pCracker->moveTarget.y)
        {
            PlaySoundById(g_pWizardCrackerPopIt->bLandSoundId);
            g_pWizardCrackerPopIt->bLandSoundId++;
            if (g_pWizardCrackerPopIt->bLandSoundId > 0xB1)
                g_pWizardCrackerPopIt->bLandSoundId = 0xAA;
            SetActorActionState(pCracker, 0);
        }
        else
        {
            if (pCracker->vel.y < -0xC0000)
                pCracker->accel.y = 0;
            if (pCracker->pos.y < pCracker->moveTarget.y)
            {
                pCracker->pos.y = pCracker->moveTarget.y;
                pCracker->vel.y = 0;
                pCracker->accel.y = 0;
            }
        }
        break;
    }
}
