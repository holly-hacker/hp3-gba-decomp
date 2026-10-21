#include "types.h"
#include "background.h"
#include "sound.h"
#include "tea_leaves_minigame.h"
#include "modes.h"
#include "input.h"
#include "random.h"
#include "font.h"
#include "text.h"
#include "screen_transitions.h"

void UpdateDivinationTeaMinigame(void)
{
    DivinationTeaLeaf *pLeaf;
    Actor *pActor;
    u32 speed;
    s32 roll;
    s32 i;

    if (g_DivinationTea.dwPaused != 0)
    {
        UpdateDivinationTeaPauseMenu();
        return;
    }

    g_DivinationTea.dwFrame++;

    if (g_DivinationTea.dwStopped != 0)
    {
        if (g_DivinationTea.dwSettled == 0)
            SettleDivinationTeaLeaves();
    }

    if (g_DivinationTea.dwSettled == 0)
    {
        for (i = 0; i < DIVINATION_TEA_LEAF_COUNT; i++)
        {
            roll = Mt19937RandRange(1, 2);
            pLeaf = &g_DivinationTea.aLeaves[i];
            pActor = pLeaf->pActor;
            pLeaf->wAngle += (roll * (pActor->orbitState.orbit.wAngleVelX >> 7)) << 8;
            pLeaf->wAngle = pLeaf->wAngle % 0x10000;
            SetActorAffineTransform(pActor, (pLeaf->wScaleX / 256) << 16, (pLeaf->wScaleY / 256) << 16,
                                     pLeaf->wAngle, 1);
        }
    }
    else if (g_GameModeStackContext.dwModeState == DivinationTeaStateIntro)
    {
        StartDivinationTeaFortune();
    }

    switch (g_GameModeStackContext.dwModeState)
    {
    case DivinationTeaStateIntro:
        if (g_GameModeStackContext.dwModeTimer != 0)
        {
            g_GameModeStackContext.dwModeTimer--;
            break;
        }

        if (g_wKeysPressed & KeyStart)
        {
            ShowDivinationTeaPauseMenu();
        }
        else if (g_wKeysPressed & KeyA)
        {
            if (g_DivinationTea.dwStopped != 0)
                break;

            if (g_DivinationTea.dwFrame > g_DivinationTea.dwLastStirFrame)
            {
                SetDivinationTeaSwirlSpeed(g_DivinationTea.dwSwirlSpeed
                             + (1000 / (g_DivinationTea.dwFrame - g_DivinationTea.dwLastStirFrame) >> 3));
                g_DivinationTea.dwLastStirFrame = g_DivinationTea.dwFrame;
            }
        }
        else if (g_wKeysPressed & KeyB)
        {
            if (g_DivinationTea.dwStopped == 0)
            {
                PlaySoundById(1);
                SetBgZoomStep(2, 1);
                for (i = 0; i < ARRAY_COUNT(g_DivinationTea.apCupActors); i++)
                    SetActorAnimData(g_DivinationTea.apCupActors[i], &g_DivinationTeaCupSprite,
                                      (void *)g_DivinationTeaCupAnimData, 1);
            }

            g_DivinationTea.dwStopped = 1;
        }
        else if (g_DivinationTea.dwStopped == 0 && g_DivinationTea.dwSettled == 0)
        {
            speed = g_DivinationTea.dwSwirlSpeed;
            speed -= (speed - 0x40) / 0x46;
            SetDivinationTeaSwirlSpeed(speed);
        }
        break;
    case DivinationTeaStateFadeIn:
        g_DivinationTea.dwFadeStep += 2;
        SetAlphaBlendCoefficients(g_DivinationTea.dwFadeStep, 0x10 - g_DivinationTea.dwFadeStep);
        if (g_DivinationTea.dwFadeStep == 0x10)
        {
            for (i = 0; i < ARRAY_COUNT(g_DivinationTea.apFadeActors); i++)
                g_DivinationTea.apFadeActors[i]->oam.objMode = 0;

            g_GameModeStackContext.dwModeState = DivinationTeaStateReveal;
        }
        break;
    case DivinationTeaStateReveal:
        g_DivinationTea.dwFadeStep = 0;
        SetAlphaBlendCoefficients(0, 0x10);
        SetAlphaBlendTargets(1, 0x10);
        g_GameModeStackContext.dwModeState = DivinationTeaStateFadeText;
        g_DivinationTea.pFortuneText = GetDialogText(Mt19937RandRange(0, 0x5A) + 0xA5F);
        g_DivinationTea.dwFortuneTextCursor = PrintTextBox(1, 0x78, 0x20, 0xE0, g_DivinationTea.pFortuneText, 1);
        break;
    case DivinationTeaStateFadeText:
        g_DivinationTea.dwFadeStep += 2;
        SetAlphaBlendCoefficients(g_DivinationTea.dwFadeStep, 0x10 - g_DivinationTea.dwFadeStep);
        if (g_DivinationTea.dwFadeStep == 0x10)
            g_GameModeStackContext.dwModeState = DivinationTeaStateShowFortune;
        break;
    case DivinationTeaStateShowFortune:
        if (g_wKeysPressed & (KeyA | KeyB))
        {
            PlaySoundById(1);
            PushGameMode_2(MinigameMenu, 6, 3);
        }
        break;
    }
}
