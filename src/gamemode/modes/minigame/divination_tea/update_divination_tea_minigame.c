#include "types.h"
#include "audio.h"
#include "display.h"
#include "divination_tea.h"
#include "game_modes.h"
#include "input.h"
#include "mt19937.h"
#include "text.h"

void UpdateDivinationTeaMinigame(void)
{
    DivinationTeaLeaf *pLeaf;
    Object *pObject;
    u32 score;
    s32 roll;
    s32 i;

    if (g_DivinationTea.dwUnk1D8 != 0)
    {
        sub_080422D0();
        return;
    }

    g_DivinationTea.dwFrame++;

    if (g_DivinationTea.dwUnk1C0 != 0)
    {
        if (g_DivinationTea.dwUnk1C4 == 0)
            sub_08041FA0();
    }

    if (g_DivinationTea.dwUnk1C4 == 0)
    {
        for (i = 0; i < DIVINATION_TEA_LEAF_COUNT; i++)
        {
            roll = Mt19937RandRange(1, 2);
            pLeaf = &g_DivinationTea.aLeaves[i];
            pObject = pLeaf->pObject;
            pLeaf->wAngle += (roll * (pObject->wUnk58 >> 7)) << 8;
            pLeaf->wAngle = pLeaf->wAngle % 0x10000;
            SetObjectAffineTransform(pObject, (pLeaf->wScaleX / 256) << 16, (pLeaf->wScaleY / 256) << 16,
                                     pLeaf->wAngle, 1);
        }
    }
    else if (g_GameModeStackContext.dwModeState == DivinationTeaStateIntro)
    {
        sub_0804200C();
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
            sub_080421B8();
        }
        else if (g_wKeysPressed & KeyA)
        {
            if (g_DivinationTea.dwUnk1C0 != 0)
                break;

            if (g_DivinationTea.dwFrame > g_DivinationTea.dwUnk1D4)
            {
                sub_08042288(g_DivinationTea.dwUnk1D0
                             + (1000 / (g_DivinationTea.dwFrame - g_DivinationTea.dwUnk1D4) >> 3));
                g_DivinationTea.dwUnk1D4 = g_DivinationTea.dwFrame;
            }
        }
        else if (g_wKeysPressed & KeyB)
        {
            if (g_DivinationTea.dwUnk1C0 == 0)
            {
                PlaySoundById(1);
                sub_08007CD4(2, 1);
                for (i = 0; i < 4; i++)
                    SetObjectAnimData(g_DivinationTea.apCupObjects[i], (void *)g_DivinationTeaCupAnimA,
                                      (void *)g_DivinationTeaCupAnimB, 1);
            }

            g_DivinationTea.dwUnk1C0 = 1;
        }
        else if (g_DivinationTea.dwUnk1C0 == 0 && g_DivinationTea.dwUnk1C4 == 0)
        {
            score = g_DivinationTea.dwUnk1D0;
            score -= (score - 0x40) / 0x46;
            sub_08042288(score);
        }
        break;
    case DivinationTeaStateFadeIn:
        g_DivinationTea.dwFadeStep += 2;
        SetAlphaBlendCoefficients(g_DivinationTea.dwFadeStep, 0x10 - g_DivinationTea.dwFadeStep);
        if (g_DivinationTea.dwFadeStep == 0x10)
        {
            for (i = 0; i < 8; i++)
                g_DivinationTea.apFadeObjects[i]->oam.objMode = 0;

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
