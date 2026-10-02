    .include "asm/room_blob.inc"

Room41Blob:
    RoomBlob 1
    PlayerEntry 148, 248, 0, 0
    StageIndex 3
    StageToVariant 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1
    VariantEntry Room41V0
    VariantEntry Room41V1
    VariantEntry Room41V2

    SubBlock Room41V0, 1, Room41V0Routes, Room41V0Chains, Room41V0End
    OffsetTable Room41V0Groups, 1
    Offsets Room41V0Group0
    EndTable
    Group Room41V0Group0, 3
    TileAnimation 135, 90, anim_id=12
    Prop 231, 179, kind=0, facing=5, arg_10=1, arg_13=0
    Door 149, 276, half_width=24, half_height=9, destination_room=40, exit_param=1
    OffsetTable Room41V0Routes, 0
    EndTable
    OffsetTable Room41V0Chains, 1
    Offsets Room41V0Chain0
    EndTable
Room41V0Chain0:
    End
    EndSubBlock Room41V0End

    SubBlock Room41V1, 1, Room41V1Routes, Room41V1Chains, Room41V1End
    OffsetTable Room41V1Groups, 2, 1
    Offsets Room41V1Group0, Room41V1Group1
    EndTable
    Group Room41V1Group0, 1
    Chest 225, 144, flag_id=1, reward_id=113
    Group Room41V1Group1, 2
    Npc 96, 142, sprite=37, facing=0, arg_0f=0
    Prop 111, 143, kind=83, arg_13=0
    OffsetTable Room41V1Routes, 0
    EndTable
    OffsetTable Room41V1Chains, 10, 1
    Offsets Room41V1Chain0, Room41V1Chain1, Room41V1Chain2, Room41V1Chain3, Room41V1Chain4, Room41V1Chain5
    Offsets Room41V1Chain6, Room41V1Chain7, Room41V1Chain8, Room41V1Chain9
    EndTable
Room41V1Chain0:
    GotoIfQuestStateCompare 244, 0, 0, Room41V1Chain6_id, 0, Room41V1Group1_id, 0
    GotoIfQuestStateCompare 244, 0, 2, Room41V1Chain7_id, 0, Room41V1Group1_id, 0
    End
Room41V1Chain1:
    SetTileObjectAnimState Room41V0Group0_id, 0
    PlayScreenTransitionIn
    @ "Here, Harry. Take these collector's cards. They might help you during a magical encounter."
    @ "Thank you, Minister."
    ShowRoomDialog 5
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room41V1Chain2:
    ArmChainYield 1
    PlayScreenTransitionIn
    StartTileObjectScript 94, 182, 0, 0, 255, 0, 0, 4, 255, 255, 255
    SetQuestState 2, 25
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room41V1Chain3:
    SetTileObjectAnimState Room41V0Group0_id, 0
    End
Room41V1Chain4:
    SetTileObjectAnimState Room41V0Group0_id, 0
    End
Room41V1Chain5:
    SetQuestState 1, 244
    ArmChainYield 1
    SetStoryStage 2
    CancelObjectAnimSequence 0, 255
    @ "You have a new item. To equip it, press START and then select Status/Equip. Select a character, move the cursor over the boxes surrounding that character, and press the A Button to change items."
    ShowRoomDialog 612
    @ "Thank goodness for that! I think I'll turn in for the night."
    ShowRoomDialog 23
    StartTileObjectScript 94, 182, 0, 0, 255, 0, 0, 0, 255, 255, 255
    PlayRoomSoundEffect 10
    PlayScreenTransitionOut
    SetQuestState 0, 26
    PlayCutscene 0, 0, Room41V1Chain2_id
    End
Room41V1Chain6:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartTileObjectScript 103, 182, 0, 0, 255, 0, 0, 0, 255, 255, 255
    @ "There's a package on my bed..."
    @ "There's a card... It's from Hagrid! He remembered my birthday!"
    @ "It's a book! 'The Monster Book of Monsters'."
    @ "Uh oh..."
    ShowRoomDialog 20
    DespawnTileObject Room41V1Group1_id, 1
    @ "You are about to enter a magical encounter. Each character and creature takes a turn to perform an action, however, they can only perform one action per turn. Your characters have Stamina Points and Magic Points. Stamina Points (SP) indicate how healthy your character is and Magic Points (MP) allow a character to cast spells. Each spell uses a different number of points. Click on the Help icon in the Magical Encounter Menu for more information."
    ShowRoomDialog 613
    PlayTileObjectAnimation Room41V1Group1_id, 0, 11
    SetQuestState 1, 5
    SetQuestState 2, 244
    DespawnTileObject Room41V1Group1_id, 0
    StartBattle 0, 0, Room41V1Chain5_id
    End
Room41V1Chain7:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartTileObjectScript 103, 182, 0, 0, 255, 0, 0, 0, 255, 255, 255
    DelayedRespawnRowAndRunChain 1, 0, 0
    PlayTileObjectAnimation Room41V1Group1_id, 0, 11
    DespawnTileObject Room41V1Group1_id, 0
    StartBattle 0, 0, Room41V1Chain5_id
    End
Room41V1Chain8:
    End
Room41V1Chain9:
    HideBackgroundLayer 2
    End
    EndSubBlock Room41V1End

    SubBlock Room41V2, 1, Room41V2Routes, Room41V2Chains, Room41V2End
    OffsetTable Room41V2Groups, 3, 1
    Offsets Room41V2Group0, Room41V2Group1, Room41V2Group2
    EndTable
    Group Room41V2Group0, 0
    Group Room41V2Group1, 2
    Npc 101, 142, sprite=37, facing=0, arg_0f=0
    Chest 224, 144, flag_id=1, reward_id=113
    Group Room41V2Group2, 1
    Npc 147, 186, sprite=13, facing=4
    OffsetTable Room41V2Routes, 0
    EndTable
    OffsetTable Room41V2Chains, 6, 1
    Offsets Room41V2Chain0, Room41V2Chain1, Room41V2Chain2, Room41V2Chain3, Room41V2Chain4, Room41V2Chain5
    EndTable
Room41V2Chain0:
    GotoIfQuestStateCompare 244, 0, 2, Room41V2Chain2_id, Room41V2Chain1_id, Room41V2Group1_id, Room41V2Group2_id
    ArmChainYield 1
    DelayedRespawnRowAndRunChainFrames 1, 0, 0
    End
Room41V2Chain1:
    CancelObjectAnimSequence 0, 255
    FullHealParty
    @ "Harry! You must be more careful. Tom found you lying on the floor unconscious. I had to give you some Wiggenweld Potion to make you feel better."
    ShowRoomDialog 44
    StartTileObjectScript 147, 18, 1, Room41V2Group2_id, 0, 0, 0, 4, 255, 255, 255
    DespawnTileObject Room41V2Group2_id, 0
    DelayedRespawnRowAndRunChain 2, 0, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room41V2Chain2:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartTileObjectScript 94, 182, 0, 0, 255, 0, 0, 0, 255, 255, 255
    DelayedRespawnRowAndRunChain 1, 0, 0
    PlayTileObjectAnimation Room41V2Group1_id, 0, 11
    SetStoryStage 31
    DespawnTileObject Room41V2Group1_id, 0
    StartBattle 0, 0, Room41V2Chain3_id
    End
Room41V2Chain3:
    ArmChainYield 1
    SetQuestState 0, 5
    SetQuestState 1, 244
    CancelObjectAnimSequence 0, 255
    @ "Thank goodness for that! I think I'll turn in for the night."
    ShowRoomDialog 23
    StartTileObjectScript 94, 182, 0, 0, 255, 0, 0, 0, 255, 255, 255
    PlayRoomSoundEffect 10
    SetQuestState 0, 26
    PlayScreenTransitionOut
    PlayCutscene 0, 0, Room41V2Chain4_id
    End
Room41V2Chain4:
    ArmChainYield 1
    PlayScreenTransitionIn
    StartTileObjectScript 94, 182, 0, 0, 255, 0, 0, 4, 255, 255, 255
    SetStoryStage 2
    SetQuestState 2, 25
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room41V2Chain5:
    @ "You've received some collector's cards! Collect all the cards to unlock secrets and items in the Wizard Card Collectors' Club in classroom 5B. Collecting certain groups of cards will allow Harry to use Card Combos during magical encounters. To view your card collection, choose Folios and then Folio Universitas."
    ShowRoomDialog 623
    End
    EndSubBlock Room41V2End
