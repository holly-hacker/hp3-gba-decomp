#include "types.h"
#include "hw/input.h"
#include "menu/dialog.h"
#include "overworld/overworld.h"
#include "overworld/room.h"
#include "overworld/room_object.h"
#include "overworld/room_script.h"

// Collision callback of a chest (room object type 9): decides whether the
// player or a spell effect opens it. See docs/formats/rooms.md.
void HandleChestTouch(Object *pSelf, Object *pOther)
{
    u8 kind = pSelf->modeState.chest.bKind;
    u8 opened = pSelf->modeState.chest.bOpened;
    u8 pageGroup;
    u32 canOpen;

    if (g_DialogState_candidate.dwState != 0)
        return;

    switch (pOther->wObjectType)
    {
    case RoomObjectType_Player:
        if (pOther->bActionState != 0x21)
            return;

        if (kind == 0 && opened == 0 && (g_wKeysPressed & KeyA))
        {
            pSelf->modeState.chest.bOpened = 1;
            SetObjectActionSubState(pSelf, 8);
            CancelObjectMove_candidate(pOther);
            pOther->bAnimFrameCounter = kind;
            if (pOther->pLinkedObject_candidate != NULL)
                pOther->pLinkedObject_candidate->bAnimFrameCounter = kind;
            SetObjectActionState(pOther, 0);
            SetObjectAnimSubState_candidate(pOther, 0);
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
                    SetObjectActionSubState(pSelf, 8);
                    CancelObjectMove_candidate(pOther);
                    pOther->bAnimFrameCounter = opened;
                    if (pOther->pLinkedObject_candidate != NULL)
                        pOther->pLinkedObject_candidate->bAnimFrameCounter = opened;
                    SetObjectActionState(pOther, 0);
                    SetObjectAnimSubState_candidate(pOther, 0);
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
            SetObjectActionSubState(pSelf, 8);
            CancelObjectMove_candidate(pOther);
            pOther->bAnimFrameCounter = opened;
            if (pOther->pLinkedObject_candidate != NULL)
                pOther->pLinkedObject_candidate->bAnimFrameCounter = opened;
            SetObjectActionState(pOther, 0);
            SetObjectAnimSubState_candidate(pOther, 0);
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
            SetObjectAnimData(pSelf, g_apRoomChestAnimFrames[kind], g_abRoomChestAnimData[kind], 10);
            pSelf->modeState.chest.bKind = 0;
            CancelObjectMove_candidate(g_pPlayerObject);
            g_pPlayerObject->bAnimFrameCounter = 0;
            if (g_pPlayerObject->pLinkedObject_candidate != NULL)
                g_pPlayerObject->pLinkedObject_candidate->bAnimFrameCounter = 0;
            SetObjectActionState(g_pPlayerObject, 0);
            SetObjectAnimSubState_candidate(g_pPlayerObject, 0);
        }
        sub_0802E2BC(pOther, pSelf);
        break;
    }
}
