#include "types.h"
#include "math.h"
#include "input.h"
#include "game/game_modes.h"
#include "graphics/audio.h"
#include "buckbeak_minigame.h"

// Steers Buckbeak, advances the camera and the clock, and checks for rings.
void ProcessBuckbeakMinigameFrame(void)
{
    s32 i;
    u8 frame;
    s32 angle;
    s32 height;
    s32 target;

    if (g_wKeysHeld & KeyLeft)
    {
        u32 bank = 2;

        if (bank != g_pBuckbeakMinigame->dwBankState)
        {
            g_pBuckbeakMinigame->dwBankState = bank;
            frame = g_pBuckbeakMinigame->pBuckbeak->anim.bAnimFrameIndex_candidate;
            SetActorAnimDataAtCommand(g_pBuckbeakMinigame->pBuckbeak, &g_aBuckbeakMinigameBuckbeakAssets[bank],
                                      g_abBuckbeakMinigameFlyAnimData, frame);

            // Banking left shows the banking-right sprite mirrored.
            if (g_pBuckbeakMinigame->dwBankState == 2)
                g_pBuckbeakMinigame->pBuckbeak->oam.hFlip = 1;
            else
                g_pBuckbeakMinigame->pBuckbeak->oam.hFlip = 0;
        }

        if (g_pBuckbeakMinigame->dwTurnRate > -0x13333)
            g_pBuckbeakMinigame->dwTurnRate -= 0x1999;
    }
    else if (g_wKeysHeld & KeyRight)
    {
        u32 bank = 1;

        if (bank != g_pBuckbeakMinigame->dwBankState)
        {
            g_pBuckbeakMinigame->dwBankState = bank;
            frame = g_pBuckbeakMinigame->pBuckbeak->anim.bAnimFrameIndex_candidate;
            SetActorAnimDataAtCommand(g_pBuckbeakMinigame->pBuckbeak, &g_aBuckbeakMinigameBuckbeakAssets[bank],
                                      g_abBuckbeakMinigameFlyAnimData, frame);

            if (g_pBuckbeakMinigame->dwBankState == 2)
                g_pBuckbeakMinigame->pBuckbeak->oam.hFlip = 1;
            else
                g_pBuckbeakMinigame->pBuckbeak->oam.hFlip = 0;
        }

        if (g_pBuckbeakMinigame->dwTurnRate <= 0x13332)
            g_pBuckbeakMinigame->dwTurnRate += 0x1999;
    }
    else
    {
        u32 bank = 0;

        if (bank != g_pBuckbeakMinigame->dwBankState)
        {
            g_pBuckbeakMinigame->dwBankState = bank;
            frame = g_pBuckbeakMinigame->pBuckbeak->anim.bAnimFrameIndex_candidate;
            SetActorAnimDataAtCommand(g_pBuckbeakMinigame->pBuckbeak, &g_aBuckbeakMinigameBuckbeakAssets[bank],
                                      g_abBuckbeakMinigameFlyAnimData, frame);

            if (g_pBuckbeakMinigame->dwBankState == 2)
                g_pBuckbeakMinigame->pBuckbeak->oam.hFlip = 1;
            else
                g_pBuckbeakMinigame->pBuckbeak->oam.hFlip = 0;
        }

        if (g_pBuckbeakMinigame->dwTurnRate > 0)
            g_pBuckbeakMinigame->dwTurnRate -= 0x1999;
        if (g_pBuckbeakMinigame->dwTurnRate < 0)
            g_pBuckbeakMinigame->dwTurnRate += 0x1999;
    }

    // Holding A climbs; letting go dives.
    if (g_wKeysHeld & KeyA)
    {
        if (g_pBuckbeakMinigame->dwClimbRate <= 0x1FFFF)
            g_pBuckbeakMinigame->dwClimbRate += 0xCCC;
    }
    else
    {
        if (g_pBuckbeakMinigame->dwClimbRate > -0x20000)
            g_pBuckbeakMinigame->dwClimbRate -= 0xCCC;
    }

    g_pBuckbeakMinigame->dwHeading.dwValue += g_pBuckbeakMinigame->dwTurnRate;
    g_pBuckbeakMinigame->dwCameraHeading.dwValue +=
        (g_pBuckbeakMinigame->dwHeading.dwValue - g_pBuckbeakMinigame->dwCameraHeading.dwValue) / 4;
    g_pBuckbeakMinigame->player.world.dwHeight += g_pBuckbeakMinigame->dwClimbRate;

    if (g_pBuckbeakMinigame->player.world.dwHeight > 0x1680000)
    {
        g_pBuckbeakMinigame->player.world.dwHeight = 0x1680000;
        g_pBuckbeakMinigame->dwClimbRate = 0;
    }

    if (g_pBuckbeakMinigame->player.world.dwHeight <= 0x19FFFF)
    {
        g_pBuckbeakMinigame->player.world.dwHeight = 0x1A0000;
        g_pBuckbeakMinigame->dwClimbRate = 0;
    }

    g_pBuckbeakMinigame->dwSpeed = 0x20000 - g_pBuckbeakMinigame->dwClimbRate / 2;
    g_pBuckbeakMinigame->player.world.ground.x +=
        FixedMultiply(g_anSineTable[(angle = g_pBuckbeakMinigame->dwHeading.parts.wWhole) & 0xFF],
                      g_pBuckbeakMinigame->dwSpeed);
    g_pBuckbeakMinigame->player.world.ground.y -=
        FixedMultiply(g_anSineTable[(g_pBuckbeakMinigame->dwHeading.parts.wWhole + 0x40) & 0xFF],
                      g_pBuckbeakMinigame->dwSpeed);

    // The camera trails behind along its own, lagging heading.
    g_pBuckbeakMinigame->camera.x =
        g_pBuckbeakMinigame->player.world.ground.x
        - FixedMultiply(g_anSineTable[(angle = g_pBuckbeakMinigame->dwCameraHeading.parts.wWhole) & 0xFF],
                        g_pBuckbeakMinigame->dwCameraDistance);
    g_pBuckbeakMinigame->camera.y =
        g_pBuckbeakMinigame->player.world.ground.y
        + FixedMultiply(g_anSineTable[(g_pBuckbeakMinigame->dwCameraHeading.parts.wWhole + 0x40) & 0xFF],
                        g_pBuckbeakMinigame->dwCameraDistance);
    height = g_pBuckbeakMinigame->dwCameraHeight.dwValue;
    target = height - 0xF0000;
    g_pBuckbeakMinigame->dwCameraHeight.dwValue = height + (g_pBuckbeakMinigame->player.world.dwHeight - target) / 8;

    g_FloorEffect.dwCameraX = g_pBuckbeakMinigame->camera.x >> 8;
    g_FloorEffect.dwCameraY = g_pBuckbeakMinigame->camera.y >> 8;
    g_FloorEffect.dwCameraHeight = g_pBuckbeakMinigame->dwCameraHeight.parts.wWhole;
    angle = g_pBuckbeakMinigame->dwHeading.parts.wWhole;
    SetBuckbeakMinigameSkyScroll(angle);
    PlaceBuckbeakMinigameBuckbeak();

    for (i = 0; i <= 8; i++)
        UpdateBuckbeakMinigameRing(i);

    UpdateFloorAffineTable();

    if (g_pBuckbeakMinigame->dwTimeLeft == 0)
    {
        g_pBuckbeakMinigame->bResultsDelay--;
        if (g_pBuckbeakMinigame->bResultsDelay == 0)
            g_GameModeStackContext.dwModeState = BuckbeakMinigameStateFinished;
    }
    else
    {
        g_pBuckbeakMinigame->dwTimeLeft -= 8;

        if (g_pBuckbeakMinigame->dwTimeLeft <= 0)
        {
            g_pBuckbeakMinigame->dwTimeLeft = 0;
            g_pBuckbeakMinigame->bResultsDelay = 0x64;
            PlaySoundById(0x39);
            DrawBuckbeakMinigameScore();
        }
        else if (HasBuckbeakMinigameRingBeenReached(g_pBuckbeakMinigame->bNextRing))
        {
            PlaySoundById(0xB2);
            g_pBuckbeakMinigame->bNextRing++;
            if (g_pBuckbeakMinigame->bNextRing > 8)
                g_pBuckbeakMinigame->bNextRing = 0;

            g_pBuckbeakMinigame->dwScore++;

            if (g_pBuckbeakMinigame->dwTimeLeft < 0)
            {
                g_pBuckbeakMinigame->dwTimeLeft = 0;
                g_pBuckbeakMinigame->bResultsDelay = 0x64;
                PlaySoundById(0x38);
            }
            else
            {
                g_pBuckbeakMinigame->dwTimeBonus = Multiply8_8(g_pBuckbeakMinigame->dwTimeBonus, 0xCC);
                g_pBuckbeakMinigame->dwTimeLeft += 0x300 + g_pBuckbeakMinigame->dwTimeBonus;
            }

            DrawBuckbeakMinigameScore();
        }

        DrawBuckbeakMinigameTime();
    }
}
