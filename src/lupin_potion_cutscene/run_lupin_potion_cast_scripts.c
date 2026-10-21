#include "lupin_potion_cutscene.h"
#include "modes.h"

const LupinPotionScriptCommand
    g_aLupinPotionCastScripts[LUPIN_POTION_CAST_COUNT][LUPIN_POTION_SCRIPT_LENGTH] = {
    {
        { LupinPotionOpMove, -0x8000, 0, 280 },
        { LupinPotionOpStop, 0, 0, 310 },
        { LupinPotionOpMove, 0x8000, 0, 380 },
        { LupinPotionOpStop, 0, 0, 540 },
        { LupinPotionOpFace, 2, 0, 550 },
        { LupinPotionOpPose, 4, 1, 590 },
        { LupinPotionOpPose, 1, 0, 610 },
        { LupinPotionOpPose, 2, 0, 620 },
        { LupinPotionOpMove, 0x20000, 0x8000, 690 },
        { LupinPotionOpEnd, 0, 0, 0 },
    },
    {
        { LupinPotionOpMove, -0x8000, 0, 280 },
        { LupinPotionOpStop, 0, 0, 309 },
        { LupinPotionOpDialog, 0, 0, 310 },
        { LupinPotionOpMove, -0x8000, 0, 409 },
        { LupinPotionOpStop, 0, 0, 410 },
        { LupinPotionOpPose, 1, 0, 450 },
        { LupinPotionOpPose, 2, 0, 490 },
        { LupinPotionOpMove, -0x20000, 0, 499 },
        { LupinPotionOpStop, 0, 0, 501 },
        { LupinPotionOpMove, -0x20000, 0, 600 },
        { LupinPotionOpStop, 0, 0, 601 },
        { LupinPotionOpEnd, 0, 0, 0 },
    },
    {
        { LupinPotionOpMove, -0x8000, 0, 270 },
        { LupinPotionOpStop, 0, 0, 271 },
        { LupinPotionOpFace, 1, 0, 272 },
        { LupinPotionOpPose, 1, 0, 320 },
        { LupinPotionOpPose, 4, 3, 390 },
        { LupinPotionOpPose, 2, 0, 508 },
        { LupinPotionOpMove, -0x20000, 0, 515 },
        { LupinPotionOpPose, 4, 2, 545 },
        { LupinPotionOpPose, 2, 0, 600 },
        { LupinPotionOpStop, 0, 0, 601 },
        { LupinPotionOpEnd, 0, 0, 0 },
    },
    {
        { LupinPotionOpMove, -0x8000, 0, 280 },
        { LupinPotionOpStop, 0, 0, 330 },
        { LupinPotionOpMove, 0x8000, 0, 350 },
        { LupinPotionOpStop, 0, 0, 500 },
        { LupinPotionOpDialog, 1, 0, 530 },
        { LupinPotionOpMove, -0x20000, 0x8000, 570 },
        { LupinPotionOpStop, 0, 0, 590 },
        { LupinPotionOpFace, 1, 0, 610 },
        { LupinPotionOpPose, 4, 0, 700 },
        { LupinPotionOpPose, 0, 0, 725 },
        { LupinPotionOpEnd, 0, 0, 0 },
    },
    {
        { LupinPotionOpMove, -0x8000, 0, 280 },
        { LupinPotionOpStop, 0, 0, 310 },
        { LupinPotionOpMove, 0x8000, 0, 380 },
        { LupinPotionOpStop, 0, 0, 540 },
        { LupinPotionOpFace, 2, 0, 585 },
        { LupinPotionOpPose, 4, 4, 700 },
        { LupinPotionOpEnd, 0, 0, 0 },
    },
    {
        { LupinPotionOpMove, -0x8000, 0, 280 },
        { LupinPotionOpStop, 0, 0, 330 },
        { LupinPotionOpMove, 0x8000, 0, 340 },
        { LupinPotionOpStop, 0, 0, 630 },
        { LupinPotionOpFace, 2, 0, 660 },
        { LupinPotionOpFace, 3, 0, 680 },
        { LupinPotionOpStop, 0, 0, 710 },
        { LupinPotionOpEnd, 0, 0, 0 },
    },
};

void RunLupinPotionCastScripts(void)
{
    const LupinPotionScriptCommand *pCommand;
    s32 i;

    for (i = 0; i < LUPIN_POTION_CAST_COUNT; i++)
    {
        if (g_LupinPotionCutscene.aCastScripts[i].bActive == 0 || g_LupinPotionCutscene.aCastScripts[i].wTimer == 0
            || --g_LupinPotionCutscene.aCastScripts[i].wTimer != 0)
            continue;

        g_LupinPotionCutscene.aCastScripts[i].wIndex++;
        pCommand = &g_aLupinPotionCastScripts[i][g_LupinPotionCutscene.aCastScripts[i].wIndex];
        g_LupinPotionCutscene.aCastScripts[i].wTimer =
            pCommand->wEndFrame - g_GameModeStackContext.dwCurrentGameModeArg2;
        g_LupinPotionCutscene.aCastScripts[i].dwOp = pCommand->dwOp;
        g_LupinPotionCutscene.aCastScripts[i].nArg = pCommand->nArg1;
        if (pCommand->wEndFrame < g_GameModeStackContext.dwCurrentGameModeArg2)
        {
            g_LupinPotionCutscene.aCastScripts[i].wTimer = 0;
            g_LupinPotionCutscene.aCastScripts[i].bActive = 0;
            // BUG: skips the rest of the cast this frame, delaying their next commands by a
            // frame; every cast script ends this way. Should continue with the next script.
            return;
        }

        switch (pCommand->dwOp)
        {
        case LupinPotionOpMove:
            SetActorVelocity(g_LupinPotionCutscene.apCast[i], pCommand->nArg0, pCommand->nArg1);
            g_LupinPotionCutscene.apCast[i]->bActionFlags |= 2;
            break;
        case LupinPotionOpStop:
            SetActorVelocity(g_LupinPotionCutscene.apCast[i], 0, 0);
            g_LupinPotionCutscene.apCast[i]->bActionFlags |= 2;
            break;
        case LupinPotionOpFace:
            g_LupinPotionCutscene.apCast[i]->bFacing = pCommand->nArg0;
            g_LupinPotionCutscene.apCast[i]->bActionFlags |= 2;
            break;
        case LupinPotionOpPose:
            g_LupinPotionCutscene.apCast[i]->bActionSubState = pCommand->nArg0;
            g_LupinPotionCutscene.apCast[i]->bActionFlags |= 2;
            break;
        case LupinPotionOpDialog:
            g_LupinPotionCutscene.wDialogPage = pCommand->nArg0;
            g_LupinPotionCutscene.wDialogLine = 0;
            g_LupinPotionCutscene.nPanelOffset = 0x28;
            if (ShowNextLupinPotionDialogLine() != 0)
                g_GameModeStackContext.dwModeState = 1;
            break;
        case LupinPotionOpEnd:
        default:
            g_LupinPotionCutscene.aCastScripts[i].wTimer = 0;
            g_LupinPotionCutscene.aCastScripts[i].bActive = 0;
            break;
        }
    }
}
