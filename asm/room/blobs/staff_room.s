    .include "asm/room_blob.inc"

Room27Blob:
    RoomBlob 1
    PlayerEntry 312, 283, 0, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room27V0
    VariantEntry Room27V1

    SubBlock Room27V0, 1, Room27V0Routes, Room27V0Chains, Room27V0End
    OffsetTable Room27V0Groups, 1
    Offsets Room27V0Group0
    EndTable
    Group Room27V0Group0, 2
    Door 346, 274, half_width=7, half_height=39, destination_room=16, exit_param=4
    Chest 69, 418, flag_id=28, reward_id=126
    OffsetTable Room27V0Routes, 0
    EndTable
    OffsetTable Room27V0Chains, 1
    Offsets Room27V0Chain0
    EndTable
Room27V0Chain0:
    SetDefeatWarpSelector 2
    End
    EndSubBlock Room27V0End

    SubBlock Room27V1, 1, Room27V1Routes, Room27V1Chains, Room27V1End
    OffsetTable Room27V1Groups, 6, 1
    Offsets Room27V1Group0, Room27V1Group1, Room27V1Group2, Room27V1Group3, Room27V1Group4, Room27V1Group5
    EndTable
    Group Room27V1Group0, 0
    Group Room27V1Group1, 10
    Npc 138, 227, sprite=59, facing=4
    Npc 105, 258, sprite=15, facing=2, interact_cooldown=3, interact_mode=1, chain=Room27V1Chain15_id
    Npc 164, 237, sprite=63, facing=4
    Npc 186, 237, sprite=39, facing=4
    Npc 175, 307, sprite=51, facing=0
    Npc 177, 215, sprite=55, facing=4
    Npc 195, 289, sprite=47, facing=6
    Npc 205, 308, sprite=43, facing=6
    TriggerZone 269, 324, half_width=8, half_height=127, chain=Room27V1Chain12_id
    TriggerZone 298, 200, half_width=17, half_height=14, chain=Room27V1Chain12_id
    Group Room27V1Group2, 1
    Npc 248, 267, sprite=32, facing=6
    Group Room27V1Group3, 1
    Npc 228, 267, sprite=34, facing=6
    Group Room27V1Group4, 3
    TriggerZone 269, 280, half_width=9, half_height=55, chain=Room27V1Chain5_id
    TriggerZone 297, 228, half_width=15, half_height=12, chain=Room27V1Chain5_id
    TriggerZone 297, 339, half_width=16, half_height=13, chain=Room27V1Chain5_id
    Group Room27V1Group5, 1
    Npc 104, 240, sprite=15, facing=2, interact_cooldown=3, interact_mode=1, chain=Room27V1Chain15_id
    OffsetTable Room27V1Routes, 9
    Offsets Room27V1Route0, Room27V1Route1, Room27V1Route2, Room27V1Route3, Room27V1Route4, Room27V1Route5
    Offsets Room27V1Route6, Room27V1Route7, Room27V1Route8
    EndTable
Room27V1Route0:
    Route 7
    Waypoint 150, 228
    Waypoint 165, 228
    Waypoint 165, 242
    Waypoint 185, 242
    Waypoint 185, 258
    Waypoint 200, 258
    Waypoint 325, 258
Room27V1Route1:
    Route 6
    Waypoint 183, 300
    Waypoint 195, 300
    Waypoint 209, 300
    Waypoint 315, 300
    Waypoint 315, 285
    Waypoint 325, 285
Room27V1Route2:
    Route 2
    Waypoint 209, 271
    Waypoint 300, 271, on_arrival_chain=Room27V1Chain7_id
Room27V1Route3:
    Route 2
    Waypoint 221, 288
    Waypoint 288, 288, on_arrival_chain=Room27V1Chain6_id
Room27V1Route4:
    Route 2
    Waypoint 138, 227
    Waypoint 138, 248
Room27V1Route5:
    Route 2
    Waypoint 209, 271
    Waypoint 174, 271, on_arrival_chain=Room27V1Chain10_id
Room27V1Route6:
    Route 2
    Waypoint 175, 303
    Waypoint 175, 287
Room27V1Route7:
    Route 2
    Waypoint 164, 237
    Waypoint 164, 254, on_arrival_chain=Room27V1Chain11_id
Room27V1Route8:
    Route 2
    Waypoint 265, 263
    Waypoint 198, 263, on_arrival_chain=Room27V1Chain1_id
    OffsetTable Room27V1Chains, 17, 1
    Offsets Room27V1Chain0, Room27V1Chain1, Room27V1Chain2, Room27V1Chain3, Room27V1Chain4, Room27V1Chain5
    Offsets Room27V1Chain6, Room27V1Chain7, Room27V1Chain8, Room27V1Chain9, Room27V1Chain10, Room27V1Chain11
    Offsets Room27V1Chain12, Room27V1Chain13, Room27V1Chain14, Room27V1Chain15, Room27V1Chain16
    EndTable
Room27V1Chain0:
    GotoIfStoryStageCompare 0, 5, Room27V1Chain14_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 6, Room27V1Chain16_id, 0, Room27V1Group5_id, 0
    End
Room27V1Chain1:
    ArmChainYield 1
    RespawnRowAndRunChain Room27V1Group2_id, 0
    RemovePartyFollower 7
    RespawnRowAndRunChain Room27V1Group3_id, 0
    RemovePartyFollower 6
    StartTileObjectScript 207, 15, 1, Room27V1Group2_id, 0, 0, 0, 6, 255, 255, 255
    StartTileObjectScript 213, 32, 1, Room27V1Group3_id, 0, 0, 0, 6, 255, 255, 255
    QueueTileObjectMove Room27V1Group1_id, 1, 0, 0, 1400, 0
    @ "Good afternoon. Today's will be a practical lesson."
    @ "I draw your attention to this wardrobe. There's a Boggart in there. Now, what is a Boggart?"
    @ "It's a shape-shifter. It can take the shape of whatever it thinks will frighten us most."
    @ "Well put. The charm that repels a Boggart is simple. It forces the Boggart to assume a shape that you find amusing. The incantation is Riddikulus."
    ShowRoomDialog 347
    @ "Neville, Lavender, Ron and Parvati, please come forward."
    ShowRoomDialog 348
    ArmChainYield 0
    InvokeChainIfEnabled 0, Room27V1Chain8_id
    End
Room27V1Chain2:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "Now, please return to your common room."
    @ "The Riddikulus Boggart Challenge can now be accessed from the Mini-Games menu found on the Title Screen."
    ShowRoomDialog 351
    ArmChainYield 0
    RespawnRowAndRunChain 0, Room27V1Chain3_id
    ArmChainYield 1
    QueueTileObjectMove 0, 255, 0, 0, 1600, 0
    DelayedRespawnRowAndRunChain 8, 0, 0
    StartTileObjectScript 127, 7, 1, 0, 255, 0, 0, 5, 255, 255, 255
    RespawnRowAndRunChain 0, Room27V1Chain4_id
    @ "Anything worrying you, Harry?"
    @ "Yes. Why didn't you let me fight the Boggart?"
    @ "I assumed that if the Boggart faced you, it would assume the shape of Lord Voldemort."
    @ "I did think of him, at first. But then I remembered those Dementors."
    @ "The Dementors affect you worse than the others because there are horrors in your past that the others don't have. I can help you resist them with some Anti-Dementor lessons..."
    @ "Thank you very much, Professor."
    @ "I'll come and find you for the lessons. Now, I'd advise you to go to your common room."
    @ "Bye, Professor."
    ShowRoomDialog 352
    RespawnRowAndRunChain Room27V1Group4_id, 0
    SetQuestState QUEST_OBJ_GO_TO_COMMON_ROOM_AFTER_POTIONS, QUEST_OBJECTIVE_INDEX
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room27V1Chain3:
    StartObjectAnimSequence Room27V1Group1_id, 0, 0, 0, Room27V1Route0_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room27V1Group1_id, 5, 0, 0, Room27V1Route0_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room27V1Group1_id, 2, 0, 0, Room27V1Route0_id, 2, 1, 0, 0, 0
    StartObjectAnimSequence Room27V1Group1_id, 3, 0, 0, Room27V1Route0_id, 3, 1, 0, 0, 0
    StartObjectAnimSequence Room27V1Group1_id, 4, 0, 0, Room27V1Route1_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room27V1Group1_id, 6, 0, 0, Room27V1Route1_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room27V1Group1_id, 7, 0, 0, Room27V1Route1_id, 2, 1, 0, 0, 0
    StartObjectAnimSequence Room27V1Group2_id, 0, 0, 0, Room27V1Route2_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room27V1Group3_id, 0, 0, 0, Room27V1Route3_id, 0, 1, 0, 0, 0
    End
Room27V1Chain4:
    DespawnTileObject Room27V1Group1_id, 0
    DespawnTileObject Room27V1Group1_id, 4
    DespawnTileObject Room27V1Group1_id, 2
    DespawnTileObject Room27V1Group1_id, 6
    DespawnTileObject Room27V1Group1_id, 7
    DespawnTileObject Room27V1Group1_id, 3
    DespawnTileObject Room27V1Group1_id, 5
    End
Room27V1Chain5:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    StartTileObjectScript 288, 21, 1, 0, 255, 0, 0, 2, 255, 255, 255
    StartTileObjectScript 288, 21, 1, Room27V1Group3_id, 0, 0, 0, 2, 255, 255, 255
    StartTileObjectScript 288, 21, 1, Room27V1Group2_id, 0, 0, 0, 2, 255, 255, 255
    RecruitPartyFollower 7
    DespawnTileObject Room27V1Group2_id, 0
    RecruitPartyFollower 6
    DespawnTileObject Room27V1Group3_id, 0
    DespawnTileObject Room27V1Group4_id, 0
    DespawnTileObject Room27V1Group4_id, 1
    DespawnTileObject Room27V1Group4_id, 2
    SetStoryStage 6
    ClearQuestStateUpperHalf
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room27V1Chain6:
    SetTileObjectFacing Room27V1Group3_id, 0, 6
    End
Room27V1Chain7:
    SetTileObjectFacing Room27V1Group2_id, 0, 6
    End
Room27V1Chain8:
    StartObjectAnimSequence Room27V1Group1_id, 0, 0, 0, Room27V1Route4_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room27V1Group1_id, 4, 0, 0, Room27V1Route6_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room27V1Group2_id, 0, 0, 0, Room27V1Route5_id, 0, 1, 0, 0, 0
    End
Room27V1Chain9:
    StartObjectAnimSequence Room27V1Group1_id, 2, 0, 0, Room27V1Route7_id, 0, 1, 0, 0, 0
    End
Room27V1Chain10:
    ArmChainYield 1
    @ "Oh! I... erm... OK, I s'pose..."
    ShowRoomDialog 349
    ArmChainYield 0
    InvokeChainIfEnabled 0, Room27V1Chain9_id
    End
Room27V1Chain11:
    ArmChainYield 1
    @ "Now, are you ready?"
    @ "Erm... OK, I s'pose..."
    @ "Remember to think of something amusing and cast Riddikulus. I'm going to let the Boggart out of the wardrobe now..."
    ShowRoomDialog 350
    UnlockMinigame 2
    StartMinigame 2, 0, 1, 0, Room27V1Chain2_id
    End
Room27V1Chain12:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnTileObject Room27V1Group1_id, 8
    DespawnTileObject Room27V1Group1_id, 9
    SetQuestState 1, 229
    InvokeChainIfEnabled 0, Room27V1Chain13_id
    End
Room27V1Chain13:
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room27V1Route8_id, 0, 1, 0, 0, 0
    End
Room27V1Chain14:
    SetOverworldMonstersDisabled
    GotoIfQuestStateCompare 229, 0, 0, 0, 0, Room27V1Group1_id, Room27V1Group5_id
    End
Room27V1Chain15:
    @ "I'd advise you to go to your common room."
    ShowRoomDialog 353
    End
Room27V1Chain16:
    SetOverworldMonstersDisabled
    End
    EndSubBlock Room27V1End
