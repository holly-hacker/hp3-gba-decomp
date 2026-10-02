    .include "asm/room_blob.inc"

Room14Blob:
    RoomBlob 1
    PlayerEntry 810, 769, 0, 0
    StageIndex 2
    StageToVariantAll 1
    VariantEntry Room14V0
    VariantEntry Room14V1

    SubBlock Room14V0, 1, Room14V0Routes, Room14V0Chains, Room14V0End
    OffsetTable Room14V0Groups, 1
    Offsets Room14V0Group0
    EndTable
    Group Room14V0Group0, 4
    Door 115, 828, half_width=56, half_height=13, destination_room=15, exit_param=9
    Chest 901, 441, flag_id=90, reward_id=95
    Chest 488, 582, flag_id=91, reward_id=131
    Chest 480, 277, flag_id=92, reward_id=112
    OffsetTable Room14V0Routes, 0
    EndTable
    OffsetTable Room14V0Chains, 1
    Offsets Room14V0Chain0
    EndTable
Room14V0Chain0:
    ClearOverworldMonstersDisabled
    SetBattleDefeatState 2
    End
    EndSubBlock Room14V0End

    SubBlock Room14V1, 1, Room14V1Routes, Room14V1Chains, Room14V1End
    OffsetTable Room14V1Groups, 2, 1
    Offsets Room14V1Group0, Room14V1Group1
    EndTable
    Group Room14V1Group0, 22
    TileAnimation 622, 438, anim_id=33
    Prop 745, 629, kind=51
    Prop 775, 625, kind=51
    Prop 803, 622, kind=51
    Prop 710, 632, kind=51
    Prop 680, 637, kind=51
    Prop 650, 633, kind=51
    Prop 615, 636, kind=51
    Prop 584, 637, kind=51
    Prop 545, 638, kind=51
    Prop 504, 636, kind=51
    Prop 825, 617, kind=51
    TriggerZone 655, 460, half_width=15, half_height=16, trigger_kind=3, chain=Room14V1Chain1_id
    Prop 664, 620, kind=51
    Prop 726, 616, kind=51, arg_13=0
    Prop 760, 610, kind=51
    Prop 790, 607, kind=51
    Prop 629, 623, kind=51
    Prop 599, 624, kind=51
    Prop 564, 626, kind=51
    Prop 482, 638, kind=51
    Prop 525, 639, kind=51
    Group Room14V1Group1, 2
    TriggerZone 156, 601, half_width=117, half_height=9, chain=Room14V1Chain2_id
    TriggerZone 125, 801, half_width=69, half_height=10, chain=Room14V1Chain3_id
    OffsetTable Room14V1Routes, 0
    EndTable
    OffsetTable Room14V1Chains, 4, 1
    Offsets Room14V1Chain0, Room14V1Chain1, Room14V1Chain2, Room14V1Chain3
    EndTable
Room14V1Chain0:
    DelayedRespawnRowAndRunChain 2, 0, 0
    SetBattleDefeatState 17
    RespawnRowAndRunChain Room14V1Group1_id, 0
    End
Room14V1Chain1:
    SetTileObjectAnimState Room14V1Group0_id, 0
    PlaySoundById 32
    End
Room14V1Chain2:
    @ "We have to get back to the lake... no matter what!"
    @ "Right... we can't let them take Sirius back to Azkaban!"
    @ "We have to hurry, Harry."
    @ "OK. Buckbeak first. We haven't got much time..."
    ShowRoomDialog 589
    End
Room14V1Chain3:
    SetQuestState 1, QUEST_ALT_PRESENTATION
    End
    EndSubBlock Room14V1End
