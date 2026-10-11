#include "types.h"
#include "input.h"
#include "menu/dialog.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "overworld/room_actor.h"
#include "overworld/room_script.h"

// Collision callback of a chest (room actor type 9): decides whether the
// player or a spell effect opens it. See docs/formats/rooms.md.
void HandleChestTouch(Actor *pSelf, Actor *pOther)
{
    u8 kind = pSelf->modeState.chest.bKind;
    u8 opened = pSelf->modeState.chest.bOpened;
    u8 pageGroup;
    u32 canOpen;

    if (g_DialogState_candidate.dwState != 0)
        return;

    switch (pOther->wActorType)
    {
    case RoomActorType_Player:
        if (pOther->bActionState != 0x21)
            return;

        if (kind == 0 && opened == 0 && (g_wKeysPressed & KeyA))
        {
            pSelf->modeState.chest.bOpened = 1;
            SetActorActionSubState(pSelf, 8);
            CancelActorMove_candidate(pOther);
            pOther->anim.bAnimFrameCounter = kind;
            if (pOther->pLinkedActor_candidate != NULL)
                pOther->pLinkedActor_candidate->anim.bAnimFrameCounter = kind;
            SetActorActionState(pOther, 0);
            SetActorAnimSubState_candidate(pOther, 0);
        }

        if (kind == 3 && opened == 0)
        {
            // Wizard Card Collectors Club: reward ids 0x87-0x8B select Folio
            // Universitas page groups 0-4. The chest opens while its group is
            // unlocked and its reward has not been given; otherwise A runs
            // the pair.
            if (g_wKeysPressed & KeyA)
            {
                pageGroup = pSelf->modeState.chest.wRewardId + 0x79;
                canOpen = IsFolioPageGroupUnlocked_candidate(pageGroup);
                if (canOpen)
                    canOpen = g_abQuestEventState[pageGroup + 0x14] == 0;
                if (canOpen)
                {
                    pSelf->modeState.chest.bOpened = 1;
                    SetActorActionSubState(pSelf, 8);
                    CancelActorMove_candidate(pOther);
                    pOther->anim.bAnimFrameCounter = opened;
                    if (pOther->pLinkedActor_candidate != NULL)
                        pOther->pLinkedActor_candidate->anim.bAnimFrameCounter = opened;
                    SetActorActionState(pOther, 0);
                    SetActorAnimSubState_candidate(pOther, 0);
                }
                else if (pSelf->modeState.chest.pair.wPair != 0)
                {
                    RespawnRowAndRunChain_candidate(pSelf->modeState.chest.pair.bytes.bRespawnGroup,
                                                    pSelf->modeState.chest.pair.bytes.bChain);
                }
            }
        }
        // Kind 2 (spawned hidden) also needs these conditions; why is unconfirmed.
        else if ((g_wKeysPressed & KeyA) && g_dwPendingCameraFocusFlag != 0
                 && pOther->bFighterIndex == 1 && kind == 2 && opened == 0)
        {
            pSelf->modeState.chest.bOpened = 1;
            SetActorActionSubState(pSelf, 8);
            CancelActorMove_candidate(pOther);
            pOther->anim.bAnimFrameCounter = opened;
            if (pOther->pLinkedActor_candidate != NULL)
                pOther->pLinkedActor_candidate->anim.bAnimFrameCounter = opened;
            SetActorActionState(pOther, 0);
            SetActorAnimSubState_candidate(pOther, 0);
        }
        break;

    case 0xF:
        // Overworld spell effect 3 unchains a kind 1 chest, which then opens
        // like kind 0.
        if (pOther->wCharacterId_candidate != 3)
            return;
        if (kind == 1 && opened == 0 && pSelf->modeState.chest.bUnchaining == 0)
        {
            pSelf->modeState.chest.bUnchaining = kind;
            SetActorAnimData(pSelf, g_apRoomChestAnimFrames[kind], g_abRoomChestAnimData[kind], 10);
            pSelf->modeState.chest.bKind = 0;
            CancelActorMove_candidate(g_pPlayerActor);
            g_pPlayerActor->anim.bAnimFrameCounter = 0;
            if (g_pPlayerActor->pLinkedActor_candidate != NULL)
                g_pPlayerActor->pLinkedActor_candidate->anim.bAnimFrameCounter = 0;
            SetActorActionState(g_pPlayerActor, 0);
            SetActorAnimSubState_candidate(g_pPlayerActor, 0);
        }
        sub_0802E2BC(pOther, pSelf);
        break;
    }
}
