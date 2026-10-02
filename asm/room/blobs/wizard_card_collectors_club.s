    .include "asm/room_blob.inc"

Room37Blob:
    RoomBlob 1
    PlayerEntry 448, 433, 0, 6
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room37V0
    VariantEntry Room37V1

    SubBlock Room37V0, 1, Room37V0Routes, Room37V0Chains, Room37V0End
    OffsetTable Room37V0Groups, 1
    Offsets Room37V0Group0
    EndTable
    Group Room37V0Group0, 1
    Door 500, 440, half_width=15, half_height=28, destination_room=22, exit_param=3
    OffsetTable Room37V0Routes, 0
    EndTable
    OffsetTable Room37V0Chains, 1
    Offsets Room37V0Chain0
    EndTable
Room37V0Chain0:
    End
    EndSubBlock Room37V0End

    SubBlock Room37V1, 1, Room37V1Routes, Room37V1Chains, Room37V1End
    OffsetTable Room37V1Groups, 1, 1
    Offsets Room37V1Group0
    EndTable
    Group Room37V1Group0, 6
    Npc 244, 386, sprite=47, facing=2, interact_cooldown=3, interact_mode=1, chain=Room37V1Chain21_id
    Chest 127, 118, flag_id=201, reward_id=135, kind=3, chain=Room37V1Chain1_id
    Chest 191, 118, flag_id=202, reward_id=136, kind=3, chain=Room37V1Chain2_id
    Chest 319, 118, flag_id=203, reward_id=137, kind=3, chain=Room37V1Chain3_id
    Chest 446, 118, flag_id=204, reward_id=138, kind=3, chain=Room37V1Chain4_id
    Chest 510, 118, flag_id=205, reward_id=139, kind=3, chain=Room37V1Chain5_id
    OffsetTable Room37V1Routes, 0
    EndTable
    OffsetTable Room37V1Chains, 35, 1
    Offsets Room37V1Chain0, Room37V1Chain1, Room37V1Chain2, Room37V1Chain3, Room37V1Chain4, Room37V1Chain5
    Offsets Room37V1Chain6, Room37V1Chain7, Room37V1Chain8, Room37V1Chain9, Room37V1Chain10, Room37V1Chain11
    Offsets Room37V1Chain12, Room37V1Chain13, Room37V1Chain14, Room37V1Chain15, Room37V1Chain16, Room37V1Chain17
    Offsets Room37V1Chain18, Room37V1Chain19, Room37V1Chain20, Room37V1Chain21, Room37V1Chain22, Room37V1Chain23
    Offsets Room37V1Chain24, Room37V1Chain25, Room37V1Chain26, Room37V1Chain27, Room37V1Chain28, Room37V1Chain29
    Offsets Room37V1Chain30, Room37V1Chain31, Room37V1Chain32, Room37V1Chain33, Room37V1Chain34
    EndTable
Room37V1Chain0:
    End
Room37V1Chain1:
    GotoIfQuestStateCompare 20, 0, 0, Room37V1Chain8_id, 0, 0, 0
    End
Room37V1Chain2:
    GotoIfQuestStateCompare 21, 0, 0, Room37V1Chain9_id, 0, 0, 0
    End
Room37V1Chain3:
    GotoIfQuestStateCompare 22, 0, 0, Room37V1Chain12_id, 0, 0, 0
    End
Room37V1Chain4:
    GotoIfQuestStateCompare 23, 0, 0, Room37V1Chain15_id, 0, 0, 0
    End
Room37V1Chain5:
    GotoIfQuestStateCompare 24, 0, 0, Room37V1Chain18_id, 0, 0, 0
    End
Room37V1Chain6:
    SetQuestState 1, 20
    UnlockMinigame 3
    ArmChainYield 1
    ShowFolioCategoryStatusMessage 0, 1
    ShowMinigameUnlockedMessage 3
    End
Room37V1Chain7:
    ShowFolioCategoryStatusMessage 0, 0
    End
Room37V1Chain8:
    GotoIfFolioPageGroupComplete 0, 0, Room37V1Chain6_id, 0, Room37V1Chain7_id, 255, 255, 255
    End
Room37V1Chain9:
    GotoIfFolioPageGroupComplete 1, 0, Room37V1Chain10_id, 0, Room37V1Chain11_id, 255, 255, 255
    End
Room37V1Chain10:
    SetQuestState 1, 21
    GrantRoomReward 54, 0
    GrantRoomReward 53, 0
    GrantRoomReward 51, 0
    ArmChainYield 1
    ShowFolioCategoryStatusMessage 1, 1
    ShowRewardPickupMessage 53
    ShowRewardPickupMessage 54
    ShowRewardPickupMessage 51
    End
Room37V1Chain11:
    ShowFolioCategoryStatusMessage 1, 0
    End
Room37V1Chain12:
    GotoIfFolioPageGroupComplete 2, 0, Room37V1Chain14_id, 0, Room37V1Chain13_id, 255, 255, 255
    End
Room37V1Chain13:
    ShowFolioCategoryStatusMessage 2, 0
    End
Room37V1Chain14:
    SetQuestState 1, 22
    GrantRoomReward 18, 0
    ArmChainYield 1
    ShowFolioCategoryStatusMessage 2, 1
    ShowRewardPickupMessage 18
    End
Room37V1Chain15:
    GotoIfFolioPageGroupComplete 3, 0, Room37V1Chain17_id, 0, Room37V1Chain16_id, 255, 255, 255
    End
Room37V1Chain16:
    ShowFolioCategoryStatusMessage 3, 0
    End
Room37V1Chain17:
    SetQuestState 1, 23
    GrantPartyLevelUps 2
    ArmChainYield 1
    ShowFolioCategoryStatusMessage 3, 1
    ShowPartyLevelUpMessage 2
    End
Room37V1Chain18:
    GotoIfFolioPageGroupComplete 4, 0, Room37V1Chain20_id, 0, Room37V1Chain19_id, 255, 255, 255
    End
Room37V1Chain19:
    ShowFolioCategoryStatusMessage 4, 0
    End
Room37V1Chain20:
    SetQuestState 1, 24
    GrantPartyLevelUps 1
    GrantRoomReward 19, 0
    ArmChainYield 1
    ShowFolioCategoryStatusMessage 4, 1
    ShowRewardPickupMessage 19
    ShowPartyLevelUpMessage 1
    End
Room37V1Chain21:
    CancelObjectAnimSequence 0, 255
    GotoIfAllQuestFlagsSet Room37V1Chain34_id, Room37V1Chain24_id, 0, 0
    End
Room37V1Chain22:
    @ "Welcome back to the Wizard Card Collectors' Club! You can trade cards with your friends here, or anywhere in and around Hogwarts. And, when you've collected all the cards in a category, one of the chests at the back of the room will unlock. You can open the chest to get special prizes!"
    ShowRoomDialog 650
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room37V1Chain23:
    @ "I see that you've collected all of the cards in one of the categories. Go to the back of the room and unlock the corresponding chest!"
    ShowRoomDialog 651
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room37V1Chain24:
    GotoIfQuestStateCompare 20, 0, 1, Room37V1Chain25_id, Room37V1Chain29_id, 0, 0
    End
Room37V1Chain25:
    GotoIfQuestStateCompare 21, 0, 1, Room37V1Chain26_id, Room37V1Chain30_id, 0, 0
    End
Room37V1Chain26:
    GotoIfQuestStateCompare 22, 0, 1, Room37V1Chain27_id, Room37V1Chain31_id, 0, 0
    End
Room37V1Chain27:
    GotoIfQuestStateCompare 23, 0, 1, Room37V1Chain28_id, Room37V1Chain32_id, 0, 0
    End
Room37V1Chain28:
    GotoIfQuestStateCompare 24, 0, 1, Room37V1Chain22_id, Room37V1Chain33_id, 0, 0
    End
Room37V1Chain29:
    GotoIfFolioPageGroupComplete 0, 0, Room37V1Chain23_id, 0, Room37V1Chain25_id, 255, 255, 255
    End
Room37V1Chain30:
    GotoIfFolioPageGroupComplete 1, 0, Room37V1Chain23_id, 0, Room37V1Chain26_id, 255, 255, 255
    End
Room37V1Chain31:
    GotoIfFolioPageGroupComplete 2, 0, Room37V1Chain23_id, 0, Room37V1Chain27_id, 255, 255, 255
    End
Room37V1Chain32:
    GotoIfFolioPageGroupComplete 3, 0, Room37V1Chain23_id, 0, Room37V1Chain28_id, 255, 255, 255
    End
Room37V1Chain33:
    GotoIfFolioPageGroupComplete 4, 0, Room37V1Chain23_id, 0, Room37V1Chain22_id, 255, 255, 255
    End
Room37V1Chain34:
    @ "Congratulations, you got all the cards! There's nothing more to unlock here."
    ShowRoomDialog 652
    SetTileObjectAnimStateWithSpeed 0, 255
    End
    EndSubBlock Room37V1End
