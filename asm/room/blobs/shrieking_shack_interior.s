    .include "asm/room_blob.inc"

Room43Blob:
    RoomBlob 1
    PlayerEntry 240, 460, 0, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room43V0
    VariantEntry Room43V1

    SubBlock Room43V0, 1, Room43V0Routes, Room43V0Chains, Room43V0End
    OffsetTable Room43V0Groups, 1
    Offsets Room43V0Group0
    EndTable
    Group Room43V0Group0, 1
    Chest 326, 433, flag_id=69, reward_id=104
    OffsetTable Room43V0Routes, 0
    EndTable
    OffsetTable Room43V0Chains, 1
    Offsets Room43V0Chain0
    EndTable
Room43V0Chain0:
    End
    EndSubBlock Room43V0End

    SubBlock Room43V1, 1, Room43V1Routes, Room43V1Chains, Room43V1End
    OffsetTable Room43V1Groups, 8, 1
    Offsets Room43V1Group0, Room43V1Group1, Room43V1Group2, Room43V1Group3, Room43V1Group4, Room43V1Group5
    Offsets Room43V1Group6, Room43V1Group7
    EndTable
    Group Room43V1Group0, 0
    Group Room43V1Group1, 4
    Npc 125, 95, sprite=32, facing=4
    TriggerZone 182, 167, half_width=13, half_height=32, chain=Room43V1Chain2_id
    Npc 153, 103, sprite=4, facing=4
    TriggerZone 306, 232, half_width=14, half_height=40, chain=Room43V1Chain14_id
    Group Room43V1Group2, 1
    Npc 230, 196, sprite=34, facing=2
    Group Room43V1Group3, 2
    Npc 270, 93, sprite=101, facing=6
    Npc 246, 212, sprite=15, facing=6
    Group Room43V1Group4, 1
    Door 241, 495, half_width=23, half_height=8, destination_room=45, exit_param=6
    Group Room43V1Group5, 1
    Npc 190, 109, sprite=15, facing=6
    Group Room43V1Group6, 1
    Npc 153, 103, sprite=100, facing=2
    Group Room43V1Group7, 1
    Npc 180, 93, sprite=101, facing=6
    OffsetTable Room43V1Routes, 10
    Offsets Room43V1Route0, Room43V1Route1, Room43V1Route2, Room43V1Route3, Room43V1Route4, Room43V1Route5
    Offsets Room43V1Route6, Room43V1Route7, Room43V1Route8, Room43V1Route9
    EndTable
Room43V1Route0:
    Route 3
    Waypoint 185, 170
    Waypoint 113, 170
    Waypoint 113, 105
Room43V1Route1:
    Route 4
    Waypoint 210, 190
    Waypoint 210, 179
    Waypoint 105, 179
    Waypoint 105, 115, on_arrival_chain=Room43V1Chain4_id
Room43V1Route2:
    Route 6
    Waypoint 220, 202
    Waypoint 220, 182
    Waypoint 175, 182
    Waypoint 175, 120
    Waypoint 216, 120
    Waypoint 216, 113, on_arrival_chain=Room43V1Chain5_id
Room43V1Route3:
    Route 3
    Waypoint 225, 95
    Waypoint 200, 95, on_arrival_chain=Room43V1Chain10_id
    Waypoint 183, 95
Room43V1Route4:
    Route 2
    Waypoint 214, 111
    Waypoint 193, 111, on_arrival_chain=Room43V1Chain6_id
Room43V1Route5:
    Route 3
    Waypoint 105, 115
    Waypoint 105, 130
    Waypoint 115, 130, on_arrival_chain=Room43V1Chain9_id
Room43V1Route6:
    Route 2
    Waypoint 270, 93
    Waypoint 225, 93, on_arrival_chain=Room43V1Chain11_id
Room43V1Route7:
    Route 2
    Waypoint 115, 105
    Waypoint 115, 130
Room43V1Route8:
    Route 3
    Waypoint 115, 130
    Waypoint 115, 170
    Waypoint 125, 170, on_arrival_chain=Room43V1Chain12_id
Room43V1Route9:
    Route 3
    Waypoint 240, 460
    Waypoint 191, 460
    Waypoint 200, 460, on_arrival_chain=Room43V1Chain1_id
    OffsetTable Room43V1Chains, 15, 1
    Offsets Room43V1Chain0, Room43V1Chain1, Room43V1Chain2, Room43V1Chain3, Room43V1Chain4, Room43V1Chain5
    Offsets Room43V1Chain6, Room43V1Chain7, Room43V1Chain8, Room43V1Chain9, Room43V1Chain10, Room43V1Chain11
    Offsets Room43V1Chain12, Room43V1Chain13, Room43V1Chain14
    EndTable
Room43V1Chain0:
    GotoIfQuestStateCompare 235, 0, 0, Room43V1Chain3_id, 0, 0, Room43V1Group4_id
    End
Room43V1Chain1:
    ArmChainYield 1
    @ "Where are we?"
    @ "I think we're in the Shrieking Shack - the most haunted building in Britain."
    @ "Probably a good place for Black to hide. Ron must be here somewhere... we have to find him!"
    ShowRoomDialog 561
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room43V1Chain2:
    CancelObjectAnimSequence 0, 255
    RemovePartyFollower 6
    RespawnRowAndRunChain Room43V1Group2_id, 0
    Unk02 Room43V1Group2_id, 0, 2
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room43V1Route0_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room43V1Group2_id, 0, 0, 0, Room43V1Route1_id, 0, 1, 0, 0, 0
    End
Room43V1Chain3:
    GotoIfStoryStageCompare 0, 23, Room43V1Chain13_id, 0, Room43V1Group1_id, Room43V1Group4_id
    End
Room43V1Chain4:
    ArmChainYield 1
    RespawnRowAndRunChain Room43V1Group3_id, 0
    @ "Ron - are you OK? Where's the dog?"
    @ "Not a dog. Harry, it's a trap... Black is the dog... he's an Animagus..."
    ShowRoomDialog 572
    SetTileObjectFacing Room43V1Group2_id, 0, 2
    SetTileObjectFacing 0, 255, 2
    ArmChainYield 0
    QueueTileObjectMove Room43V1Group3_id, 0, 0, 0, 600, 0
    StartObjectAnimSequence Room43V1Group3_id, 0, 0, 0, Room43V1Route6_id, 0, 1, 0, 0, 0
    End
Room43V1Chain5:
    ArmChainYield 1
    SetTileObjectFacing Room43V1Group3_id, 1, 0
    Unk02 Room43V1Group3_id, 1, 1
    @ "Where is he, Sirius? Where is Peter Pettigrew?"
    @ "Over there..."
    ShowRoomDialog 573
    QueueTileObjectMove Room43V1Group1_id, 2, 0, 0, 1200, 0
    StartTileObjectScript 214, 111, 0, Room43V1Group3_id, 1, 0, 0, 6, 255, 255, 255
    SetTileObjectFacing Room43V1Group3_id, 1, 6
    @ "Squeak!"
    @ "Ah, there you are, Peter. Ready, Sirius?"
    ShowRoomDialog 574
    ArmChainYield 0
    StartObjectAnimSequence Room43V1Group3_id, 0, 0, 0, Room43V1Route3_id, 0, 1, 0, 0, 0
    End
Room43V1Chain6:
    ArmChainYield 1
    PlayTileObjectAnimation Room43V1Group3_id, 0, 26
    PlayTileObjectAnimation Room43V1Group3_id, 1, 18
    DelayedRespawnRowAndRunChainFrames 15, 0, 0
    PlaySoundById 41
    PlayTileObjectAnimation Room43V1Group1_id, 2, 12
    RespawnRowAndRunChain Room43V1Group6_id, 0
    DespawnTileObject Room43V1Group1_id, 2
    RespawnRowAndRunChain Room43V1Group5_id, 0
    RespawnRowAndRunChain Room43V1Group7_id, 0
    DespawnRoomRowObjects Room43V1Group3_id
    PlayCutscene 8, 0, Room43V1Chain7_id
    End
Room43V1Chain7:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 1
    @ "S-Sirius... R-Remus... My friends... my old friends..."
    @ "I broke out of Azkaban, not to get at you, Harry, but to seek revenge on Pettigrew. It was Pettigrew who betrayed your parents, and made it look like I had betrayed them."
    @ "You don't understand! The Dark Lord was taking over everywhere! He would have killed me!"
    @ "You should have realized. If Voldemort didn't kill you, we would. Goodbye, Peter."
    ShowRoomDialog 575
    StartTileObjectScript 115, 105, 0, 0, 255, 0, 0, 2, 255, 255, 255
    SetTileObjectFacing Room43V1Group6_id, 0, 4
    QueueTileObjectMove 0, 255, 0, 0, 400, 0
    @ "NO! You can't kill him. I don't reckon my dad would've wanted his best friends to become killers. He can go to Azkaban."
    @ "Very well, Harry. You're the only person who has the right to decide. We'll take him back to Hogwarts."
    ShowRoomDialog 576
    RespawnRowAndRunChain Room43V1Group4_id, 0
    ArmChainYield 0
    StartObjectAnimSequence Room43V1Group2_id, 0, 0, 0, Room43V1Route5_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room43V1Route7_id, 0, 1, 0, 0, 0
    End
Room43V1Chain8:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    Unk02 Room43V1Group3_id, 1, 2
    ArmChainYield 0
    StartObjectAnimSequence Room43V1Group3_id, 1, 0, 0, Room43V1Route2_id, 0, 1, 0, 0, 0
    QueueTileObjectMove Room43V1Group3_id, 1, 0, 0, 800, 0
    End
Room43V1Chain9:
    ArmChainYield 1
    DespawnTileObject Room43V1Group2_id, 0
    RecruitPartyFollower 6
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room43V1Route8_id, 0, 1, 0, 0, 0
    End
Room43V1Chain10:
    StartObjectAnimSequence Room43V1Group3_id, 1, 0, 0, Room43V1Route4_id, 0, 1, 0, 0, 0
    End
Room43V1Chain11:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    PlayCutscene 7, 0, Room43V1Chain8_id
    End
Room43V1Chain12:
    ArmChainYield 1
    SetQuestState 1, 235
    SetQuestState 48, 25
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room43V1Chain13:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    SetQuestState 55, 25
    StartObjectAnimSequence 0, 255, 0, 0, Room43V1Route9_id, 0, 1, 0, 0, 0
    End
Room43V1Chain14:
    ResetPartyLeaderSelection
    End
    EndSubBlock Room43V1End
