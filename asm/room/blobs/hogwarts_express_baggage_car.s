    .include "asm/room_blob.inc"

Room05Blob:
    RoomBlob 2
    PlayerEntry 130, 279, 0, 2
    PlayerEntry 407, 283, 1, 6
    StageIndex 5
    StageToVariant 1, 2, 4, 2, 4, 2, 2, 4, 1, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
    VariantEntry Room05V0
    VariantEntry Room05V1
    VariantEntry Room05V2
    VariantEntry Room05V3
    VariantEntry Room05V4

    SubBlock Room05V0, 1, Room05V0Routes, Room05V0Chains, Room05V0End
    OffsetTable Room05V0Groups, 1
    Offsets Room05V0Group0
    EndTable
    Group Room05V0Group0, 11
    Prop 636, 380, kind=1, arg_0f=1
    Prop 636, 410, kind=2, arg_0f=1
    Prop 636, 436, kind=1, arg_0f=1
    Prop 80, 212, kind=26
    Prop 463, 212, kind=29
    Prop 245, 182, kind=44
    Prop 188, 164, kind=41, arg_08=213, arg_0a=213, arg_0f=1, arg_13=0
    Prop 330, 166, kind=41, arg_08=213, arg_0a=213, arg_0f=1, arg_13=0
    Prop 205, 190, kind=31
    Prop 338, 193, kind=32
    Prop 167, 236, kind=34, arg_13=0
    OffsetTable Room05V0Routes, 0
    EndTable
    OffsetTable Room05V0Chains, 1
    Offsets Room05V0Chain0
    EndTable
Room05V0Chain0:
    End
    EndSubBlock Room05V0End

    SubBlock Room05V1, 1, Room05V1Routes, Room05V1Chains, Room05V1End
    OffsetTable Room05V1Groups, 30, 1
    Offsets Room05V1Group0, Room05V1Group1, Room05V1Group2, Room05V1Group3, Room05V1Group4, Room05V1Group5
    Offsets Room05V1Group6, Room05V1Group7, Room05V1Group8, Room05V1Group9, Room05V1Group10, Room05V1Group11
    Offsets Room05V1Group12, Room05V1Group13, Room05V1Group14, Room05V1Group15, Room05V1Group16, Room05V1Group17
    Offsets Room05V1Group18, Room05V1Group19, Room05V1Group20, Room05V1Group21, Room05V1Group22, Room05V1Group23
    Offsets Room05V1Group24, Room05V1Group25, Room05V1Group26, Room05V1Group27, Room05V1Group28, Room05V1Group29
    EndTable
    Group Room05V1Group0, 3
    Prop 235, 168, kind=87, arg_08=213, arg_0a=213, arg_0f=1, chain=Room05V1Chain5_id
    Prop 380, 170, kind=87, arg_08=26, arg_0a=12, arg_0e=0, arg_0f=1, arg_13=0, chain=Room05V1Chain10_id
    Prop 245, 182, kind=44
    Group Room05V1Group1, 1
    Prop 338, 193, kind=30, arg_13=0
    Group Room05V1Group2, 1
    Prop 379, 170, kind=40, arg_08=26, arg_0a=12, arg_0e=0, arg_13=0
    Group Room05V1Group3, 1
    Prop 246, 199, kind=42
    Group Room05V1Group4, 1
    Prop 246, 199, kind=43, arg_0f=1, arg_13=0, chain=Room05V1Chain8_id
    Group Room05V1Group5, 1
    Prop 105, 167, kind=33, arg_13=0
    Group Room05V1Group6, 1
    Npc 435, 292, sprite=15, facing=6
    Group Room05V1Group7, 1
    Npc 339, 189, sprite=12, facing=4
    Group Room05V1Group8, 1
    Prop 102, 128, kind=35, arg_13=0
    Group Room05V1Group9, 1
    Prop 254, 128, kind=36, arg_13=0
    Group Room05V1Group10, 1
    Prop 255, 167, kind=34, arg_13=0
    Group Room05V1Group11, 1
    Prop 235, 168, kind=40, arg_08=26, arg_0a=12, arg_0e=0, arg_13=0
    Group Room05V1Group12, 1
    Prop 204, 190, kind=27, arg_08=26, arg_0a=12, arg_0e=0, arg_13=0
    Group Room05V1Group13, 1
    Npc 203, 189, sprite=12, facing=4
    Group Room05V1Group14, 1
    Npc 127, 289, sprite=15, facing=2
    Group Room05V1Group15, 1
    Npc 106, 296, sprite=12, facing=2
    Group Room05V1Group16, 0
    Group Room05V1Group17, 9
    TriggerZone 128, 164, half_width=0, half_height=0
    TriggerZone 201, 196, half_width=0, half_height=0
    TriggerZone 273, 167, half_width=0, half_height=0
    TriggerZone 339, 197, half_width=0, half_height=0
    TriggerZone 269, 209, half_width=0, half_height=0
    TriggerZone 387, 288, half_width=0, half_height=0
    TriggerZone 153, 276, half_width=0, half_height=0
    TriggerZone 197, 264, half_width=0, half_height=0
    TriggerZone 271, 259, half_width=0, half_height=0
    Group Room05V1Group18, 1
    Npc 194, 264, sprite=16, facing=0
    Group Room05V1Group19, 1
    Npc 288, 253, sprite=107, facing=0, arg_0f=0
    Group Room05V1Group20, 2
    TriggerZone 440, 292, half_width=11, half_height=25, chain=Room05V1Chain25_id
    TriggerZone 100, 291, half_width=11, half_height=25, chain=Room05V1Chain18_id
    Group Room05V1Group21, 3
    Prop 234, 168, kind=87, arg_08=213, arg_0a=213, arg_0f=1
    Prop 380, 171, kind=87, arg_08=26, arg_0a=12, arg_0e=0, arg_0f=1, arg_13=0
    Prop 245, 182, kind=44
    Group Room05V1Group22, 1
    Npc 173, 275, sprite=32, facing=2, arg_0f=0
    Group Room05V1Group23, 1
    Npc 174, 275, sprite=34, facing=2, arg_0f=0
    Group Room05V1Group24, 1
    Prop 235, 168, kind=39, arg_08=213, arg_0a=213, arg_0f=1, chain=Room05V1Chain5_id
    Group Room05V1Group25, 0
    Group Room05V1Group26, 1
    Prop 380, 170, kind=87, arg_08=26, arg_0a=12, arg_0e=0, arg_0f=1, arg_13=0, chain=Room05V1Chain10_id
    Group Room05V1Group27, 1
    Prop 380, 170, kind=39, arg_08=26, arg_0a=12, arg_0e=0, arg_0f=1, arg_13=0, chain=Room05V1Chain10_id
    Group Room05V1Group28, 2
    TriggerZone 98, 288, half_width=11, half_height=25, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room05V1Chain21_id
    TriggerZone 440, 290, half_width=11, half_height=25, rearm_delay=3, trigger_kind=1, chain=Room05V1Chain21_id
    Group Room05V1Group29, 2
    TriggerZone 99, 291, half_width=11, half_height=25, chain=Room05V1Chain24_id
    TriggerZone 440, 293, half_width=11, half_height=25, chain=Room05V1Chain19_id
    OffsetTable Room05V1Routes, 0
    EndTable
    OffsetTable Room05V1Chains, 26, 1
    Offsets Room05V1Chain0, Room05V1Chain1, Room05V1Chain2, Room05V1Chain3, Room05V1Chain4, Room05V1Chain5
    Offsets Room05V1Chain6, Room05V1Chain7, Room05V1Chain8, Room05V1Chain9, Room05V1Chain10, Room05V1Chain11
    Offsets Room05V1Chain12, Room05V1Chain13, Room05V1Chain14, Room05V1Chain15, Room05V1Chain16, Room05V1Chain17
    Offsets Room05V1Chain18, Room05V1Chain19, Room05V1Chain20, Room05V1Chain21, Room05V1Chain22, Room05V1Chain23
    Offsets Room05V1Chain24, Room05V1Chain25
    EndTable
Room05V1Chain0:
    SetOverworldMonstersDisabled
    GotoIfQuestStateCompare 6, 0, 1, Room05V1Chain17_id, Room05V1Chain20_id, Room05V1Group19_id, Room05V1Group29_id
    End
Room05V1Chain1:
    ArmChainYield 1
    DespawnTileObject Room05V0Group0_id, 7
    DespawnTileObject Room05V0Group0_id, 9
    DelayedRespawnRowAndRunChain 0, Room05V1Group1_id, 0
    SetTileObjectAnimState Room05V1Group1_id, 0
    DelayedRespawnRowAndRunChain 0, 0, Room05V1Chain11_id
    End
Room05V1Chain2:
    RespawnRowAndRunChain Room05V1Group3_id, 0
    SetTileObjectAnimState Room05V1Group3_id, 0
    DespawnTileObject Room05V1Group3_id, 0
    RespawnRowAndRunChain Room05V1Group4_id, 0
    End
Room05V1Chain3:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetQuestState QUEST_OBJ_FIND_TREVOR, QUEST_OBJECTIVE_INDEX
    @ "There he is!"
    @ "Let's get him and get back to..."
    ShowRoomDialog 146
    DelayedRespawnRowAndRunChain 0, Room05V1Group5_id, 0
    QueueTileObjectMove Room05V1Group17_id, 0, 0, 0, 1500, 1
    DelayedRespawnRowAndRunChain 2, 0, 0
    SetTileObjectAnimState Room05V1Group5_id, 0
    DelayedRespawnRowAndRunChain 3, Room05V1Group8_id, 0
    DespawnTileObject Room05V1Group5_id, 0
    SetTileObjectAnimState Room05V1Group8_id, 0
    QueueTileObjectMove 0, 255, 0, 0, 1500, 1
    SetTileObjectAnimState Room05V0Group0_id, 8
    PlayScreenTransitionOut
    DespawnTileObject Room05V1Group19_id, 0
    RemovePartyFollower 5
    PlaySoundById 156
    DelayedRespawnRowAndRunChain 1, Room05V1Group18_id, 0
    PlayScreenTransitionIn
    SetQuestState 50, QUEST_CAMERA_Y_OFFSET
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "Uhhh..."
    @ "Harry!"
    ShowRoomDialog 147
    DelayedRespawnRowAndRunChain 1, 0, 0
    SetTileObjectAnimState Room05V0Group0_id, 8
    DelayedRespawnRowAndRunChain 1, 0, 0
    ArmChainYield 0
    DespawnTileObject Room05V1Group0_id, 0
    DespawnTileObject Room05V1Group0_id, 1
    DelayedRespawnRowAndRunChainFrames 0, Room05V1Group24_id, 0
    DelayedRespawnRowAndRunChainFrames 0, Room05V1Group27_id, 0
    ArmChainYield 1
    SetTileObjectAnimStateWithSpeed 0, 255
    DelayedRespawnRowAndRunChain 1, 0, 0
    SetTileObjectAnimState Room05V0Group0_id, 8
    DelayedRespawnRowAndRunChain 1, 0, 0
    GotoIfQuestStateCompare 128, 0, 1, Room05V1Chain6_id, 0, 0, 0
    @ "It's trying to get in! We have to bar the door!"
    ShowRoomDialog 148
    DelayedRespawnRowAndRunChain 2, 0, 0
    SetTileObjectAnimState Room05V0Group0_id, 8
    GotoIfQuestStateCompare 128, 0, 1, Room05V1Chain6_id, 0, 0, 0
    DelayedRespawnRowAndRunChain 2, 0, 0
    SetTileObjectAnimState Room05V0Group0_id, 8
    DelayedRespawnRowAndRunChain 3, 0, 0
    SetTileObjectAnimState Room05V0Group0_id, 8
    GotoIfQuestStateCompare 128, 0, 1, Room05V1Chain6_id, Room05V1Chain7_id, 0, 0
    End
Room05V1Chain4:
    ArmChainYield 1
    DelayedRespawnRowAndRunChainFrames 1, 0, 0
    SetTileObjectFacing 0, 255, 0
    DespawnTileObject Room05V0Group0_id, 8
    DelayedRespawnRowAndRunChain 0, Room05V1Group12_id, 0
    DespawnTileObject Room05V0Group0_id, 6
    SetTileObjectAnimState Room05V1Group12_id, 0
    SetQuestState 5, 224
    PlaySoundById 32
    DelayedRespawnRowAndRunChain 0, Room05V1Group13_id, 0
    QueueTileObjectMove Room05V1Group13_id, 0, 0, 0, 1500, 2
    CancelObjectAnimSequence 0, 255
    SetTileObjectFacing 0, 255, 0
    DelayedRespawnRowAndRunChain 0, Room05V1Group14_id, 0
    @ "Oh no! It's broken through!"
    ShowRoomDialog 158
    QueueTileObjectMove Room05V1Group14_id, 0, 0, 0, 1500, 1
    PlaySoundById 22
    StartTileObjectScript 154, 25, 1, Room05V1Group14_id, 0, 0, 0, 2, 255, 255, 255
    StartTileObjectScript 165, 230, 0, Room05V1Group14_id, 0, 0, 0, 2, 255, 255, 255
    @ "None of us is hiding Sirius Black under our cloaks! Go!"
    ShowRoomDialog 159
    StartTileObjectScript 184, 183, 0, Room05V1Group13_id, 0, 0, 0, 6, 255, 255, 255
    DespawnTileObject Room05V1Group13_id, 0
    PlayMusicModuleAndFlagIfChain1 51
    QueueTileObjectMove 0, 255, 0, 0, 1500, 1
    DelayedRespawnRowAndRunChain 1, 0, Room05V1Chain13_id
    SetTileObjectAnimStateWithSpeed 0, 255
    @ "What was that thing? And what's the matter with Harry?"
    @ "That was a Dementor. One of the Dementors of Azkaban. For some reason its presence caused Harry to collapse."
    @ "Can't we do something?"
    @ "Mr. Weasley, I'd like you to go and find some chocolate so that we can revive Harry."
    @ "What can I do to help, Professor?"
    @ "Miss Granger, I'd like you to go and find the conductor and get the train going again."
    ShowRoomDialog 114
    DelayedRespawnRowAndRunChainFrames 0, Room05V1Group21_id, 0
    DespawnTileObject Room05V1Group24_id, 0
    DespawnTileObject Room05V1Group27_id, 0
    DespawnTileObject Room05V1Group0_id, 2
    InvokeChainIfEnabled 0, Room05V1Chain16_id
    End
Room05V1Chain5:
    SetQuestState 1, 128
    GrantPartyExperience 10, 65535
    PlaySoundById 2
    End
Room05V1Chain6:
    ArmChainYield 1
    GotoIfQuestStateCompare 249, 0, 0, Room05V1Chain22_id, Room05V1Chain23_id, 0, 0
    End
Room05V1Chain7:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    DelayedRespawnRowAndRunChain 3, 0, 0
    SetTileObjectAnimState Room05V0Group0_id, 8
    GotoIfQuestStateCompare 128, 0, 1, Room05V1Chain6_id, 0, 0, 0
    DelayedRespawnRowAndRunChain 5, 0, 0
    SetTileObjectAnimState Room05V0Group0_id, 8
    DelayedRespawnRowAndRunChain 2, 0, 0
    GotoIfQuestStateCompare 128, 0, 1, Room05V1Chain6_id, Room05V1Chain4_id, 0, 0
    End
Room05V1Chain8:
    SetQuestState 1, 128
    GrantPartyExperience 5, 65535
    PlaySoundById 2
    End
Room05V1Chain9:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    SetTileObjectAnimState Room05V0Group0_id, 9
    DelayedRespawnRowAndRunChain 1, 0, 0
    DelayedRespawnRowAndRunChain 4, 0, 0
    SetTileObjectAnimState Room05V0Group0_id, 9
    DelayedRespawnRowAndRunChain 3, 0, 0
    GotoIfQuestStateCompare 249, 0, 1, Room05V1Chain11_id, Room05V1Chain12_id, 0, 0
    End
Room05V1Chain10:
    SetQuestState 1, 249
    GrantPartyExperience 10, 65535
    PlaySoundById 2
    End
Room05V1Chain11:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 0, Room05V1Group2_id, 0
    DespawnTileObject Room05V1Group27_id, 0
    SetTileObjectAnimState Room05V1Group2_id, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    DespawnTileObject Room05V1Group2_id, 0
    DespawnTileObject Room05V0Group0_id, 7
    DespawnTileObject Room05V0Group0_id, 9
    DelayedRespawnRowAndRunChain 0, Room05V1Group1_id, 0
    SetTileObjectAnimState Room05V1Group1_id, 0
    PlaySoundById 32
    CancelObjectAnimSequence 0, 255
    SetTileObjectFacing 0, 255, 0
    DelayedRespawnRowAndRunChain 0, Room05V1Group7_id, 0
    QueueTileObjectMove Room05V1Group7_id, 0, 0, 0, 1500, 1
    DelayedRespawnRowAndRunChain 0, Room05V1Group14_id, 0
    QueueTileObjectMove Room05V1Group14_id, 0, 0, 0, 1500, 1
    Unk02 Room05V1Group14_id, 0, 3
    StartTileObjectScript 338, 230, 0, Room05V1Group14_id, 0, 0, 0, 0, 255, 255, 255
    SetTileObjectFacing Room05V1Group14_id, 0, 0
    @ "None of us is hiding Sirius Black under our cloaks! Go!"
    ShowRoomDialog 159
    StartTileObjectScript 324, 189, 0, Room05V1Group7_id, 0, 0, 0, 6, 255, 255, 255
    DespawnTileObject Room05V1Group7_id, 0
    PlayMusicModuleAndFlagIfChain1 51
    DelayedRespawnRowAndRunChain 1, 0, 0
    QueueTileObjectMove 0, 255, 0, 0, 1500, 1
    SetTileObjectAnimStateWithSpeed 0, 255
    @ "What was that thing? And what's the matter with Harry?"
    @ "That was a Dementor. One of the Dementors of Azkaban. For some reason its presence caused Harry to collapse."
    @ "Can't we do something?"
    @ "Mr. Weasley, I'd like you to go and find some chocolate so that we can revive Harry."
    @ "What can I do to help, Professor?"
    @ "Miss Granger, I'd like you to go and find the conductor and get the train going again."
    ShowRoomDialog 114
    InvokeChainIfEnabled 0, Room05V1Chain16_id
    End
Room05V1Chain12:
    ArmChainYield 1
    DelayedRespawnRowAndRunChainFrames 1, 0, 0
    SetTileObjectFacing 0, 255, 0
    DespawnTileObject Room05V0Group0_id, 7
    DespawnTileObject Room05V0Group0_id, 9
    DelayedRespawnRowAndRunChain 0, Room05V1Group1_id, 0
    SetTileObjectAnimState Room05V1Group1_id, 0
    CancelObjectAnimSequence 0, 255
    SetTileObjectFacing 0, 255, 0
    DelayedRespawnRowAndRunChain 0, Room05V1Group7_id, 0
    QueueTileObjectMove Room05V1Group7_id, 0, 0, 0, 1500, 2
    PlaySoundById 32
    DelayedRespawnRowAndRunChain 0, Room05V1Group14_id, 0
    @ "The Dementor's inside!"
    ShowRoomDialog 157
    PlaySoundById 22
    QueueTileObjectMove Room05V1Group14_id, 0, 0, 0, 1500, 1
    Unk02 Room05V1Group14_id, 0, 3
    StartTileObjectScript 338, 230, 0, Room05V1Group14_id, 0, 0, 0, 0, 255, 255, 255
    SetTileObjectFacing Room05V1Group14_id, 0, 0
    @ "None of us is hiding Sirius Black under our cloaks! Go!"
    ShowRoomDialog 159
    StartTileObjectScript 322, 189, 0, Room05V1Group7_id, 0, 0, 0, 6, 255, 255, 255
    DespawnTileObject Room05V1Group7_id, 0
    PlayMusicModuleAndFlagIfChain1 51
    QueueTileObjectMove 0, 255, 0, 0, 1500, 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    @ "What was that thing? And what's the matter with Harry?"
    @ "That was a Dementor. One of the Dementors of Azkaban. For some reason its presence caused Harry to collapse."
    @ "Can't we do something?"
    @ "Mr. Weasley, I'd like you to go and find some chocolate so that we can revive Harry."
    @ "What can I do to help, Professor?"
    @ "Miss Granger, I'd like you to go and find the conductor and get the train going again."
    ShowRoomDialog 114
    DespawnTileObject Room05V1Group27_id, 0
    DelayedRespawnRowAndRunChainFrames 0, Room05V1Group26_id, 0
    InvokeChainIfEnabled 0, Room05V1Chain16_id
    End
Room05V1Chain13:
    SetQuestState 5, 224
    End
Room05V1Chain14:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    RemovePartyFollower 6
    DelayedRespawnRowAndRunChainFrames 0, Room05V1Group23_id, 0
    SetQuestState 3, 6
    SetQuestState 0, QUEST_ALT_PRESENTATION
    SetQuestState 2, 250
    SetQuestState QUEST_OBJ_FIND_CHOCOLATE, QUEST_OBJECTIVE_INDEX
    DelayedRespawnRowAndRunChain 0, Room05V1Group20_id, 0
    PlayScreenTransitionIn
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room05V1Chain15:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    QueueTileObjectMove 0, 255, 0, 0, 1200, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    RemovePartyFollower 7
    DelayedRespawnRowAndRunChainFrames 0, Room05V1Group22_id, 0
    SetQuestState 0, 226
    SetQuestState 7, 6
    SetQuestState 0, QUEST_ALT_PRESENTATION
    SetQuestState QUEST_OBJ_FIND_CONDUCTOR, QUEST_OBJECTIVE_INDEX
    SetQuestState 1, 250
    DelayedRespawnRowAndRunChain 0, Room05V1Group20_id, 0
    PlayScreenTransitionIn
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room05V1Chain16:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetQuestState 0, 246
    SetQuestState 0, QUEST_CAMERA_Y_OFFSET
    DespawnRoomRowObjects Room05V1Group28_id
    SetDefeatWarpSelector 18
    DelayedRespawnRowAndRunChainFrames 0, Room05V1Group17_id, 0
    QueueTileObjectMove Room05V1Group17_id, 8, 0, 0, 1200, 0
    ShowLoadingScreenTransition 9, 10, 32, 255
    PlayScreenTransitionOut
    GotoIfStoryStageCompare 0, 9, Room05V1Chain15_id, Room05V1Chain14_id, 0, 0
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room05V1Chain17:
    SetPauseMenuLocked 1, 255, 255, 255
    PlayMusicModuleAndFlagIfChain1 9
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DelayedRespawnRowAndRunChain 0, Room05V1Group17_id, 0
    SetQuestState 0, 249
    StartTileObjectScript 196, 23, 1, 0, 255, 0, 0, 2, 255, 255, 255
    DelayedRespawnRowAndRunChainFrames 0, Room05V1Group28_id, 0
    InvokeChainIfEnabled 0, Room05V1Chain3_id
    End
Room05V1Chain18:
    SetStoryStage 3
    ClearOverworldMonstersDisabled
    SetPauseMenuLocked 0, 255, 255, 255
    ReturnToOverworld 6, 0
    End
Room05V1Chain19:
    SetStoryStage 2
    SetPauseMenuLocked 0, 255, 255, 255
    ReturnToOverworld 5, 0
    End
Room05V1Chain20:
    DespawnTileObject Room05V1Group0_id, 1
    DespawnTileObject Room05V1Group0_id, 0
    DespawnTileObject Room05V1Group0_id, 2
    RespawnRowAndRunChain Room05V1Group21_id, 0
    End
Room05V1Chain21:
    @ "Locked."
    ShowRoomDialog 624
    End
Room05V1Chain22:
    ArmChainYield 1
    @ "That's done it! But, what about the other door?"
    ShowRoomDialog 155
    DelayedRespawnRowAndRunChain 0, Room05V1Group10_id, 0
    DelayedRespawnRowAndRunChain 2, 0, 0
    SetTileObjectAnimState Room05V1Group10_id, 0
    DelayedRespawnRowAndRunChain 2, 0, 0
    DelayedRespawnRowAndRunChain 0, Room05V1Group9_id, 0
    SetTileObjectAnimState Room05V1Group9_id, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    DelayedRespawnRowAndRunChain 1, 0, Room05V1Chain9_id
    End
Room05V1Chain23:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 0, Room05V1Group10_id, 0
    DelayedRespawnRowAndRunChain 2, 0, 0
    SetTileObjectAnimState Room05V1Group10_id, 0
    DelayedRespawnRowAndRunChain 2, 0, 0
    DelayedRespawnRowAndRunChain 0, Room05V1Group9_id, 0
    SetTileObjectAnimState Room05V1Group9_id, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    DelayedRespawnRowAndRunChain 1, 0, Room05V1Chain9_id
    End
Room05V1Chain24:
    SetStoryStage 3
    SetPauseMenuLocked 0, 255, 255, 255
    ReturnToOverworld 6, 0
    End
Room05V1Chain25:
    SetStoryStage 2
    SetPauseMenuLocked 0, 255, 255, 255
    ClearOverworldMonstersDisabled
    ReturnToOverworld 5, 0
    End
    EndSubBlock Room05V1End

    SubBlock Room05V2, 1, Room05V2Routes, Room05V2Chains, Room05V2End
    OffsetTable Room05V2Groups, 7, 1
    Offsets Room05V2Group0, Room05V2Group1, Room05V2Group2, Room05V2Group3, Room05V2Group4, Room05V2Group5
    Offsets Room05V2Group6
    EndTable
    Group Room05V2Group0, 5
    Npc 181, 260, sprite=15, facing=2, arg_0f=0
    Npc 208, 261, sprite=16, facing=0
    Prop 245, 182, kind=44
    TriggerZone 102, 288, half_width=9, half_height=33, chain=Room05V2Chain3_id
    TriggerZone 440, 297, half_width=9, half_height=33, chain=Room05V2Chain4_id
    Group Room05V2Group1, 0
    Group Room05V2Group2, 1
    Npc 208, 261, sprite=31, facing=4
    Group Room05V2Group3, 1
    TriggerZone 197, 273, half_width=29, half_height=89, chain=Room05V2Chain1_id
    Group Room05V2Group4, 1
    TriggerZone 197, 274, half_width=29, half_height=89, chain=Room05V2Chain5_id
    Group Room05V2Group5, 1
    Npc 182, 285, sprite=32, facing=2, arg_0f=0
    Group Room05V2Group6, 1
    Npc 182, 285, sprite=34, facing=2, arg_0f=0
    OffsetTable Room05V2Routes, 0
    EndTable
    OffsetTable Room05V2Chains, 11, 1
    Offsets Room05V2Chain0, Room05V2Chain1, Room05V2Chain2, Room05V2Chain3, Room05V2Chain4, Room05V2Chain5
    Offsets Room05V2Chain6, Room05V2Chain7, Room05V2Chain8, Room05V2Chain9, Room05V2Chain10
    EndTable
Room05V2Chain0:
    SetOverworldMonstersDisabled
    DelayedRespawnRowAndRunChainFrames 1, 0, Room05V2Chain10_id
    DelayedRespawnRowAndRunChainFrames 1, 0, Room05V2Chain6_id
    DelayedRespawnRowAndRunChainFrames 3, 0, Room05V2Chain9_id
    End
Room05V2Chain1:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "Job done, Professor Lupin."
    @ "Thank you, Miss Granger."
    ShowRoomDialog 139
    DelayedRespawnRowAndRunChainFrames 3, 0, 0
    DespawnTileObject Room05V2Group0_id, 1
    DelayedRespawnRowAndRunChain 0, Room05V2Group2_id, 0
    @ "Harry, are you all right?"
    @ "W-what? What happened? Where's that - that thing? Who screamed?"
    @ "No one screamed."
    ShowRoomDialog 140
    @ "Hogsmeade, next stop!"
    ShowRoomDialog 141
    ClearQuestStateUpperHalf
    PlayScreenTransitionOut
    Unk2A 5, 255, 255, 255
    SetStoryStage 0
    PlayCutscene 5, 0, Room05V2Chain2_id
    End
Room05V2Chain2:
    SetTileObjectAnimStateWithSpeed 0, 255
    ReturnToOverworld 16, 0
    End
Room05V2Chain3:
    SetStoryStage 3
    ClearOverworldMonstersDisabled
    ReturnToOverworld 6, 0
    End
Room05V2Chain4:
    ArmChainYield 1
    SetStoryStage 2
    ClearOverworldMonstersDisabled
    ReturnToOverworld 5, 0
    End
Room05V2Chain5:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "Here's the chocolate, Professor!"
    @ "Well done, Mr. Weasley."
    ShowRoomDialog 138
    DespawnTileObject Room05V2Group0_id, 1
    DelayedRespawnRowAndRunChain 0, Room05V2Group2_id, 0
    @ "Harry, are you all right?"
    @ "W-what? What happened? Where's that - that thing? Who screamed?"
    @ "No one screamed."
    ShowRoomDialog 140
    @ "Hogsmeade, next stop!"
    ShowRoomDialog 141
    ClearQuestStateUpperHalf
    PlayScreenTransitionOut
    Unk2A 5, 255, 255, 255
    SetStoryStage 0
    PlayCutscene 5, 0, Room05V2Chain2_id
    End
Room05V2Chain6:
    GotoIfQuestStateCompare 6, 0, 12, 0, 0, Room05V2Group3_id, 0
    GotoIfQuestStateCompare 6, 0, 6, 0, 0, Room05V2Group4_id, 0
    End
Room05V2Chain7:
    SetStoryStage 9
    End
Room05V2Chain8:
    SetStoryStage 10
    End
Room05V2Chain9:
    GotoIfQuestStateCompare 6, 3, 7, Room05V2Chain8_id, Room05V2Chain7_id, 0, 0
    End
Room05V2Chain10:
    GotoIfQuestStateCompare 6, 3, 7, 0, 0, Room05V2Group5_id, Room05V2Group6_id
    End
    EndSubBlock Room05V2End

    SubBlock Room05V3, 1, Room05V3Routes, Room05V3Chains, Room05V3End
    OffsetTable Room05V3Groups, 2, 1
    Offsets Room05V3Group0, Room05V3Group1
    EndTable
    Group Room05V3Group0, 7
    Npc 185, 261, sprite=15, facing=2, arg_0f=0
    TriggerZone 199, 271, half_width=29, half_height=89, chain=Room05V3Chain1_id
    Npc 211, 261, sprite=16, facing=0, arg_0f=0
    Npc 187, 281, sprite=34, facing=2, arg_0f=0
    Prop 245, 182, kind=44
    TriggerZone 103, 294, half_width=9, half_height=27, chain=Room05V3Chain3_id
    TriggerZone 440, 295, half_width=9, half_height=33, chain=Room05V3Chain5_id
    Group Room05V3Group1, 1
    Npc 211, 261, sprite=31, facing=4
    OffsetTable Room05V3Routes, 0
    EndTable
    OffsetTable Room05V3Chains, 6, 1
    Offsets Room05V3Chain0, Room05V3Chain1, Room05V3Chain2, Room05V3Chain3, Room05V3Chain4, Room05V3Chain5
    EndTable
Room05V3Chain0:
    SetOverworldMonstersDisabled
    GotoIfQuestStateCompare 246, 0, 0, Room05V3Chain2_id, 0, 0, 0
    End
Room05V3Chain1:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    @ "Here's the chocolate, Professor!"
    @ "Well done, Mr. Weasley."
    ShowRoomDialog 138
    ConsumeRoomItem 76
    ShowItemRemovedMessage 76
    DespawnTileObject Room05V3Group0_id, 2
    DelayedRespawnRowAndRunChain 0, Room05V3Group1_id, 0
    @ "Harry, are you all right?"
    @ "W-what? What happened? Where's that - that thing? Who screamed?"
    @ "No one screamed."
    ShowRoomDialog 140
    @ "Hogsmeade, next stop!"
    ShowRoomDialog 141
    ClearQuestStateUpperHalf
    PlayScreenTransitionOut
    Unk2A 5, 255, 255, 255
    SetStoryStage 0
    PlayCutscene 5, 0, Room05V3Chain4_id
    End
Room05V3Chain2:
    DespawnTileObject Room05V3Group0_id, 1
    End
Room05V3Chain3:
    ArmChainYield 1
    ClearOverworldMonstersDisabled
    SetStoryStage 3
    ReturnToOverworld 6, 0
    End
Room05V3Chain4:
    SetTileObjectAnimStateWithSpeed 0, 255
    ReturnToOverworld 16, 0
    End
Room05V3Chain5:
    ArmChainYield 1
    SetStoryStage 2
    ClearOverworldMonstersDisabled
    ReturnToOverworld 5, 0
    End
    EndSubBlock Room05V3End

    SubBlock Room05V4, 1, Room05V4Routes, Room05V4Chains, Room05V4End
    OffsetTable Room05V4Groups, 2, 1
    Offsets Room05V4Group0, Room05V4Group1
    EndTable
    Group Room05V4Group0, 4
    TriggerZone 104, 292, half_width=9, half_height=33, chain=Room05V4Chain10_id
    TriggerZone 439, 292, half_width=9, half_height=33, chain=Room05V4Chain5_id
    Prop 245, 182, kind=44
    Chest 125, 213, flag_id=12, reward_id=85
    Group Room05V4Group1, 2
    Npc 380, 266, sprite=105, facing=6
    TriggerZone 380, 267, half_width=27, half_height=23, chain=Room05V4Chain6_id
    OffsetTable Room05V4Routes, 1
    Offsets Room05V4Route0
    EndTable
Room05V4Route0:
    Route 2
    Waypoint 364, 265
    Waypoint 391, 263
    OffsetTable Room05V4Chains, 15, 1
    Offsets Room05V4Chain0, Room05V4Chain1, Room05V4Chain2, Room05V4Chain3, Room05V4Chain4, Room05V4Chain5
    Offsets Room05V4Chain6, Room05V4Chain7, Room05V4Chain8, Room05V4Chain9, Room05V4Chain10, Room05V4Chain11
    Offsets Room05V4Chain12, Room05V4Chain13, Room05V4Chain14
    EndTable
Room05V4Chain0:
    GotoIfQuestStateCompare 6, 0, 3, Room05V4Chain14_id, 0, Room05V4Group1_id, 0
    End
Room05V4Chain1:
    SetQuestState 7, 223
    SetStoryStage 3
    ReturnToOverworld 6, 0
    End
Room05V4Chain2:
    End
Room05V4Chain3:
    End
Room05V4Chain4:
    GotoIfQuestStateCompare 250, 3, 1, Room05V4Chain9_id, Room05V4Chain8_id, 0, 0
    End
Room05V4Chain5:
    ArmChainYield 1
    SetStoryStage 0
    ReturnToOverworld 7, 0
    End
Room05V4Chain6:
    DespawnTileObject Room05V4Group1_id, 0
    StartBattle 12, 0, Room05V4Chain7_id
    End
Room05V4Chain7:
    SetQuestState 5, 6
    End
Room05V4Chain8:
    ArmChainYield 1
    SetStoryStage 0
    SetOverworldMonstersDisabled
    ReturnToOverworld 5, 1
    End
Room05V4Chain9:
    ArmChainYield 1
    SetStoryStage 9
    SetOverworldMonstersDisabled
    ReturnToOverworld 5, 1
    End
Room05V4Chain10:
    GotoIfQuestStateCompare 250, 3, 1, Room05V4Chain13_id, Room05V4Chain8_id, 0, 0
    End
Room05V4Chain11:
    End
Room05V4Chain12:
    ArmChainYield 1
    SetStoryStage 10
    SetOverworldMonstersDisabled
    ReturnToOverworld 5, 1
    End
Room05V4Chain13:
    GotoIfQuestStateCompare 250, 0, 2, Room05V4Chain9_id, Room05V4Chain12_id, 0, 0
    End
Room05V4Chain14:
    StartObjectAnimSequence Room05V4Group1_id, 0, 0, 0, Room05V4Route0_id, 0, 0, 0, 0, 0
    End
    EndSubBlock Room05V4End
