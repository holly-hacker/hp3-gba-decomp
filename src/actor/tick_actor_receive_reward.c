#include "types.h"
#include "font.h"
#include "text.h"
#include "actor.h"
#include "items.h"
#include "sound.h"
#include "dialog.h"
#include "dialog_box.h"
#include "overworld/overworld.h"
#include "hero.h"
#include "move.h"
#include "combat.h"

// Action state 0x17: after dwStateTimer ticks, the player holds up the received reward
// (bReceivedRewardId, or g_nBattleGoldReward Sickles) with a dialog box naming it.
void TickActorReceiveReward(Actor *actor)
{
    const void *palette;
    const void *tileGfx;
    const void *frameData;
    Actor *item;
    s32 offsetX;
    s32 offsetY;

    switch (actor->bActionSubState) {
    case 0:
        if (--actor->dwStateTimer == -1) {
            if (g_dwFieldSpellActive != 0 && actor->bFighterIndex == 1)
                EndFieldSpellEffect(g_pFieldSpellEffectActor);
            StopActorMotion(actor);
            actor->bFacing = DirectionDown;
            actor->dwFlags &= ~ActorFlagVisible;
            SetPartyMemberAnim(actor, PartyAnim3);
            actor->dwFlags |= ActorFlagVisible;
            SetActorActionSubState(actor, 10);
        }
        break;
    case 10:
        if (actor->dwFlags & ActorFlagSpecialMoveTrigger) {
            SetDialogTextAlign(1);
            SetDialogTextReveal(0);
            PlaySoundById(0x19);
            if (g_nBattleGoldReward != 0) {
                SetTextMacro1Number(g_nBattleGoldReward);
                ShowDialogBlock(0x7D);  // "You Receive: \n @1 Sickles"
            }
            else {
                SetTextMacro1String(GetDialogText(GetRewardNameTextId(g_pPlayerActor->bReceivedRewardId)));
                if ((u8)(g_pPlayerActor->bReceivedRewardId - 0x50) <= 0x31)
                    SetTextMacro2String(GetDialogText(0x646));
                else
                    SetTextMacro2String(g_sSpace);
                ShowDialogBlock(0x7C);  // "You Receive: \n @1 @2"
            }
            g_DialogState.bArg1C = 0;
            g_DialogState.bArg1D = 0;

            if (g_nBattleGoldReward != 0) {
                palette = g_CoinIconAsset.pPalette;
                tileGfx = g_CoinIconAsset.pTileGfx;
                frameData = g_CoinIconAsset.pFrameData;
                offsetX = 15;
                offsetY = 0x41;
                g_nBattleGoldReward = 0;
            }
            else {
                GetItemImageData(g_pPlayerActor->bReceivedRewardId, &palette, &tileGfx, &frameData);
                offsetX = 0;
                offsetY = 0x32;
            }
            item = SpawnActor(0, (s16)(actor->pos.x >> 16) - offsetX, (s16)(actor->pos.y >> 16) - offsetY, palette);
            g_ReceivedItemGfx.pTileGfx = (void *)tileGfx;
            g_ReceivedItemGfx.pFrameData = (void *)frameData;
            item->anim.bAnimFrameDelay = 0;
            SetActorAssetRecord(item, &g_ReceivedItemGfx);
            SetActorAnimFrame(item, 0);
            item->dwStateTimer = 5;
            item->pfnTick = TickHeldRewardActor;
            actor->dwFlags &= ~ActorFlagSpecialMoveTrigger;
        }
        else if (actor->dwFlags & ActorFlagActionAnimDone) {
            SetActorActionState(actor, 0x24);
            SetDialogTextAlign(0);
        }
        break;
    }
}
