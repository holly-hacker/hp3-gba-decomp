#include "types.h"
#include "font.h"
#include "text.h"
#include "hw/bios.h"
#include "sound.h"
#include "buckbeak_minigame.h"
#include "text_actor.h"

void DrawBuckbeakMinigameTime(void)
{
    BuckbeakMinigameState *pState = g_pBuckbeakMinigame;
    s32 seconds = pState->dwTimeLeft >> 8;
    s32 hundredths = ((pState->dwTimeLeft & 0xFF) * 100) >> 8;
    u8 digits[3];
    const u8 *pText;

    // Beeps, and draws the time in the warning color, for the last six seconds.
    if (seconds <= 6)
    {
        if (pState->bWarningDelay == 0)
        {
            PlaySoundById(3);
            if (seconds <= 3)
                g_pBuckbeakMinigame->bWarningDelay = 0xF;
            else
                g_pBuckbeakMinigame->bWarningDelay = 0x1E;
        }
        else
            pState->bWarningDelay--;

        SelectTextFont(6, 3, 0);
    }
    else
        SelectTextFont(6, 0, 0);

    ReleaseBuckbeakMinigameActor(&g_apTextActors[BuckbeakMinigameTextTime]);
    SetTextMacro1Number(seconds);
    digits[0] = bios_Div(hundredths, 10) + '0';
    digits[1] = bios_Mod(hundredths, 10) + '0';
    digits[2] = 0;
    SetTextMacro2String(digits);
    pText = GetDialogText(0xA5E);  // "Time: @1:@2"
    SpawnTextActor(&pText, BuckbeakMinigameTextTime);
    SetTextActorCenterPosition(g_apTextActors[BuckbeakMinigameTextTime], 0xB4, 0x90);
    g_apTextActors[BuckbeakMinigameTextTime]->oam.priority = 0;
    SelectTextFont(6, 0, 0);
}
