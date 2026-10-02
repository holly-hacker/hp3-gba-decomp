    .include "asm/room_blob.inc"

Room29Blob:
    RoomBlob 3
    PlayerEntry 553, 353, 0, 0
    PlayerEntry 203, 165, 1, 4
    PlayerEntry 553, 353, 0, 0
    StageIndex 3
    StageToVariant 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    VariantEntry Room29V0
    VariantEntry Room29V1
    VariantEntry Room29V2

    SubBlock Room29V0, 1, Room29V0Routes, Room29V0Chains, Room29V0End
    OffsetTable Room29V0Groups, 1
    Offsets Room29V0Group0
    EndTable
    Group Room29V0Group0, 3
    Door 546, 392, half_width=25, half_height=11, destination_room=24, exit_param=5
    Door 203, 134, half_width=21, half_height=16, destination_room=28
    Chest 122, 208, flag_id=40, reward_id=121
    OffsetTable Room29V0Routes, 0
    EndTable
    OffsetTable Room29V0Chains, 1
    Offsets Room29V0Chain0
    EndTable
Room29V0Chain0:
    SetDefeatWarpSelector 2
    End
    EndSubBlock Room29V0End

    SubBlock Room29V1, 1, Room29V1Routes, Room29V1Chains, Room29V1End
    OffsetTable Room29V1Groups, 21, 1
    Offsets Room29V1Group0, Room29V1Group1, Room29V1Group2, Room29V1Group3, Room29V1Group4, Room29V1Group5
    Offsets Room29V1Group6, Room29V1Group7, Room29V1Group8, Room29V1Group9, Room29V1Group10, Room29V1Group11
    Offsets Room29V1Group12, Room29V1Group13, Room29V1Group14, Room29V1Group15, Room29V1Group16, Room29V1Group17
    Offsets Room29V1Group18, Room29V1Group19, Room29V1Group20
    EndTable
    Group Room29V1Group0, 1
    TriggerZone 294, 209, half_width=32, half_height=32, rearm_delay=3, trigger_kind=1, require_a_press=1, chain=Room29V1Chain18_id
    Group Room29V1Group1, 8
    Npc 155, 230, sprite=17, facing=4
    TriggerZone 394, 326, half_width=12, half_height=24, chain=Room29V1Chain4_id
    Npc 253, 207, sprite=39, facing=6, arg_0f=0
    Npc 264, 226, sprite=43, facing=6, arg_0f=0
    Npc 287, 239, sprite=47, facing=6, arg_0f=0
    Npc 223, 195, sprite=51, facing=4, arg_0f=0
    Npc 163, 281, sprite=55, facing=0
    Npc 179, 305, sprite=59, facing=0
    Group Room29V1Group2, 1
    Npc 238, 312, sprite=34, facing=7
    Group Room29V1Group3, 2
    Npc 261, 294, sprite=32, facing=4
    Npc 234, 313, sprite=34, facing=0
    Group Room29V1Group4, 3
    Npc 166, 181, sprite=4, facing=4
    Npc 80, 330, sprite=5, facing=2
    TriggerZone 344, 313, half_width=12, half_height=38, chain=Room29V1Chain11_id
    Group Room29V1Group5, 1
    Npc 230, 315, sprite=34, facing=2
    Group Room29V1Group6, 0
    Group Room29V1Group7, 1
    Npc 265, 312, sprite=34, facing=2
    Group Room29V1Group8, 2
    Npc 210, 322, sprite=31, facing=2
    TriggerZone 360, 326, half_width=14, half_height=27, chain=Room29V1Chain19_id
    Group Room29V1Group9, 4
    TriggerZone 344, 314, half_width=10, half_height=40, chain=Room29V1Chain22_id
    Npc 160, 318, sprite=34, facing=2
    Npc 215, 303, sprite=17, facing=2
    Npc 197, 200, sprite=32, facing=4
    Group Room29V1Group10, 9
    Npc 170, 291, sprite=30, facing=4
    Npc 237, 300, sprite=29, facing=4
    Npc 275, 312, sprite=27, facing=6
    Npc 190, 320, sprite=26, facing=2
    Npc 254, 309, sprite=63, facing=6
    Npc 355, 320, sprite=17, facing=6
    Npc 195, 298, sprite=32, facing=4
    Npc 208, 335, sprite=34, facing=0
    Npc 240, 340, sprite=39, facing=0
    Group Room29V1Group11, 1
    TriggerZone 204, 187, half_width=76, half_height=12, chain=Room29V1Chain33_id
    Group Room29V1Group12, 8
    Npc 390, 307, sprite=17, facing=6
    Npc 261, 297, sprite=32, facing=4
    Npc 415, 320, sprite=27, facing=6
    Npc 243, 290, sprite=63, facing=4
    Npc 216, 326, sprite=47, facing=2
    Npc 244, 338, sprite=34, facing=0
    Npc 270, 343, sprite=59, facing=0
    Npc 279, 293, sprite=39, facing=4
    Group Room29V1Group13, 3
    TriggerZone 205, 188, half_width=94, half_height=7, chain=Room29V1Chain40_id
    Npc 86, 286, sprite=32, facing=2
    Npc 108, 295, sprite=34, facing=6
    Group Room29V1Group14, 3
    TriggerZone 333, 308, half_width=11, half_height=56, chain=Room29V1Chain49_id
    Prop 297, 158, kind=68
    Npc 100, 270, sprite=34, facing=2
    Group Room29V1Group15, 1
    Prop 270, 210, kind=67, arg_0e=0
    Group Room29V1Group16, 1
    Npc 315, 250, sprite=32, facing=0
    Group Room29V1Group17, 1
    Npc 168, 275, sprite=34, facing=0
    Group Room29V1Group18, 1
    Prop 255, 304, kind=67, arg_0e=0, arg_13=0
    Group Room29V1Group19, 1
    Npc 368, 322, sprite=32, facing=6
    Group Room29V1Group20, 1
    Npc 195, 170, sprite=32, facing=4
    OffsetTable Room29V1Routes, 67
    Offsets Room29V1Route0, Room29V1Route1, Room29V1Route2, Room29V1Route3, Room29V1Route4, Room29V1Route5
    Offsets Room29V1Route6, Room29V1Route7, Room29V1Route8, Room29V1Route9, Room29V1Route10, Room29V1Route11
    Offsets Room29V1Route12, Room29V1Route13, Room29V1Route14, Room29V1Route15, Room29V1Route16, Room29V1Route17
    Offsets Room29V1Route18, Room29V1Route19, Room29V1Route20, Room29V1Route21, Room29V1Route22, Room29V1Route23
    Offsets Room29V1Route24, Room29V1Route25, Room29V1Route26, Room29V1Route27, Room29V1Route28, Room29V1Route29
    Offsets Room29V1Route30, Room29V1Route31, Room29V1Route32, Room29V1Route33, Room29V1Route34, Room29V1Route35
    Offsets Room29V1Route36, Room29V1Route37, Room29V1Route38, Room29V1Route39, Room29V1Route40, Room29V1Route41
    Offsets Room29V1Route42, Room29V1Route43, Room29V1Route44, Room29V1Route45, Room29V1Route46, Room29V1Route47
    Offsets Room29V1Route48, Room29V1Route49, Room29V1Route50, Room29V1Route51, Room29V1Route52, Room29V1Route53
    Offsets Room29V1Route54, Room29V1Route55, Room29V1Route56, Room29V1Route57, Room29V1Route58, Room29V1Route59
    Offsets Room29V1Route60, Room29V1Route61, Room29V1Route62, Room29V1Route63, Room29V1Route64, Room29V1Route65
    Offsets Room29V1Route66
    EndTable
Room29V1Route0:
    Route 3
    Waypoint 155, 230
    Waypoint 92, 230
    Waypoint 92, 290
Room29V1Route1:
    Route 5
    Waypoint 238, 307
    Waypoint 199, 307
    Waypoint 199, 331
    Waypoint 96, 331
    Waypoint 96, 308, on_arrival_chain=Room29V1Chain6_id
Room29V1Route2:
    Route 4
    Waypoint 96, 303
    Waypoint 96, 327
    Waypoint 230, 328, on_arrival_chain=Room29V1Chain9_id
    Waypoint 230, 317, on_arrival_chain=Room29V1Chain7_id
Room29V1Route3:
    Route 3
    Waypoint 383, 322
    Waypoint 281, 315
    Waypoint 217, 304, on_arrival_chain=Room29V1Chain1_id
Room29V1Route4:
    Route 2
    Waypoint 217, 304
    Waypoint 217, 308
Room29V1Route5:
    Route 5
    Waypoint 217, 310
    Waypoint 165, 310
    Waypoint 165, 220
    Waypoint 198, 220
    Waypoint 198, 168, on_arrival_chain=Room29V1Chain8_id
Room29V1Route6:
    Route 3
    Waypoint 345, 315
    Waypoint 200, 315
    Waypoint 205, 315
Room29V1Route7:
    Route 11
    Waypoint 165, 180
    Waypoint 165, 250
    Waypoint 177, 250
    Waypoint 177, 270
    Waypoint 157, 270
    Waypoint 157, 288
    Waypoint 180, 288
    Waypoint 180, 300
    Waypoint 200, 300
    Waypoint 200, 325, on_arrival_chain=Room29V1Chain12_id
    Waypoint 195, 325
Room29V1Route8:
    Route 2
    Waypoint 80, 325
    Waypoint 155, 325, on_arrival_chain=Room29V1Chain13_id
Room29V1Route9:
    Route 3
    Waypoint 195, 325
    Waypoint 260, 325
    Waypoint 255, 325
Room29V1Route10:
    Route 2
    Waypoint 155, 325
    Waypoint 215, 325, on_arrival_chain=Room29V1Chain14_id
Room29V1Route11:
    Route 11
    Waypoint 255, 325
    Waypoint 270, 325
    Waypoint 270, 300
    Waypoint 195, 300
    Waypoint 195, 325
    Waypoint 230, 325
    Waypoint 230, 345
    Waypoint 285, 345
    Waypoint 285, 315
    Waypoint 440, 315
    Waypoint 480, 315
Room29V1Route12:
    Route 12
    Waypoint 215, 325
    Waypoint 255, 325
    Waypoint 270, 325
    Waypoint 270, 300
    Waypoint 195, 300
    Waypoint 195, 325
    Waypoint 210, 325
    Waypoint 210, 345
    Waypoint 270, 345
    Waypoint 270, 315
    Waypoint 405, 315, on_arrival_chain=Room29V1Chain15_id
    Waypoint 445, 315
Room29V1Route13:
    Route 4
    Waypoint 205, 315
    Waypoint 255, 315
    Waypoint 215, 315, on_arrival_chain=Room29V1Chain16_id
    Waypoint 285, 315
Room29V1Route14:
    Route 5
    Waypoint 217, 304
    Waypoint 167, 304
    Waypoint 167, 208
    Waypoint 189, 208
    Waypoint 190, 181
Room29V1Route15:
    Route 2
    Waypoint 217, 322
    Waypoint 305, 322, on_arrival_chain=Room29V1Chain20_id
Room29V1Route16:
    Route 2
    Waypoint 160, 318
    Waypoint 205, 318
Room29V1Route17:
    Route 3
    Waypoint 310, 320
    Waypoint 265, 320, on_arrival_chain=Room29V1Chain23_id
    Waypoint 260, 315, on_arrival_chain=Room29V1Chain23_id
Room29V1Route18:
    Route 2
    Waypoint 215, 303
    Waypoint 245, 303
Room29V1Route19:
    Route 2
    Waypoint 260, 315
    Waypoint 233, 315
Room29V1Route20:
    Route 2
    Waypoint 255, 303
    Waypoint 332, 303, on_arrival_chain=Room29V1Chain24_id
Room29V1Route21:
    Route 2
    Waypoint 197, 200
    Waypoint 197, 245, on_arrival_chain=Room29V1Chain25_id
Room29V1Route22:
    Route 2
    Waypoint 205, 318
    Waypoint 205, 309
Room29V1Route23:
    Route 2
    Waypoint 233, 315
    Waypoint 223, 298
Room29V1Route24:
    Route 2
    Waypoint 223, 298
    Waypoint 223, 303, on_arrival_chain=Room29V1Chain27_id
Room29V1Route25:
    Route 2
    Waypoint 190, 320
    Waypoint 203, 320, on_arrival_chain=Room29V1Chain28_id
Room29V1Route26:
    Route 2
    Waypoint 275, 312
    Waypoint 350, 312, on_arrival_chain=Room29V1Chain29_id
Room29V1Route27:
    Route 2
    Waypoint 355, 320
    Waypoint 280, 320, on_arrival_chain=Room29V1Chain30_id
Room29V1Route28:
    Route 3
    Waypoint 193, 305
    Waypoint 160, 305
    Waypoint 160, 200
Room29V1Route29:
    Route 2
    Waypoint 280, 315
    Waypoint 370, 315
Room29V1Route30:
    Route 5
    Waypoint 243, 300
    Waypoint 285, 300
    Waypoint 285, 240
    Waypoint 260, 240
    Waypoint 260, 200
Room29V1Route31:
    Route 4
    Waypoint 208, 335
    Waypoint 180, 335
    Waypoint 145, 335
    Waypoint 145, 392, on_arrival_chain=Room29V1Chain54_id
Room29V1Route32:
    Route 3
    Waypoint 230, 340
    Waypoint 170, 340
    Waypoint 170, 190, on_arrival_chain=Room29V1Chain31_id
Room29V1Route33:
    Route 2
    Waypoint 390, 307
    Waypoint 290, 308, on_arrival_chain=Room29V1Chain34_id
Room29V1Route34:
    Route 3
    Waypoint 170, 210
    Waypoint 170, 298
    Waypoint 218, 298
Room29V1Route35:
    Route 2
    Waypoint 415, 320
    Waypoint 300, 320, on_arrival_chain=Room29V1Chain35_id
Room29V1Route36:
    Route 2
    Waypoint 243, 290
    Waypoint 243, 300, on_arrival_chain=Room29V1Chain36_id
Room29V1Route37:
    Route 6
    Waypoint 261, 300
    Waypoint 216, 300
    Waypoint 175, 300
    Waypoint 175, 221
    Waypoint 201, 220
    Waypoint 202, 159
Room29V1Route38:
    Route 4
    Waypoint 244, 338
    Waypoint 200, 338
    Waypoint 145, 338
    Waypoint 145, 392, on_arrival_chain=Room29V1Chain58_id
Room29V1Route39:
    Route 2
    Waypoint 300, 307
    Waypoint 370, 307
Room29V1Route40:
    Route 5
    Waypoint 293, 293
    Waypoint 293, 230
    Waypoint 250, 230
    Waypoint 250, 182
    Waypoint 230, 182
Room29V1Route41:
    Route 4
    Waypoint 170, 195
    Waypoint 170, 235
    Waypoint 100, 235
    Waypoint 100, 265, on_arrival_chain=Room29V1Chain41_id
Room29V1Route42:
    Route 2
    Waypoint 108, 295
    Waypoint 100, 295
Room29V1Route43:
    Route 3
    Waypoint 86, 286
    Waypoint 100, 286
    Waypoint 100, 295
Room29V1Route44:
    Route 2
    Waypoint 100, 265
    Waypoint 100, 295, on_arrival_chain=Room29V1Chain42_id
Room29V1Route45:
    Route 4
    Waypoint 300, 300
    Waypoint 300, 240
    Waypoint 276, 229
    Waypoint 280, 220, on_arrival_chain=Room29V1Chain45_id
Room29V1Route46:
    Route 2
    Waypoint 295, 240
    Waypoint 295, 323
Room29V1Route47:
    Route 3
    Waypoint 100, 270
    Waypoint 100, 323
    Waypoint 295, 323, on_arrival_chain=Room29V1Chain47_id
Room29V1Route48:
    Route 2
    Waypoint 280, 220
    Waypoint 295, 240, on_arrival_chain=Room29V1Chain48_id
Room29V1Route49:
    Route 3
    Waypoint 315, 250
    Waypoint 295, 250
    Waypoint 295, 323
Room29V1Route50:
    Route 3
    Waypoint 308, 307
    Waypoint 300, 307
    Waypoint 300, 300, on_arrival_chain=Room29V1Chain44_id
Room29V1Route51:
    Route 2
    Waypoint 295, 323
    Waypoint 360, 323, on_arrival_chain=Room29V1Chain56_id
Room29V1Route52:
    Route 4
    Waypoint 92, 290
    Waypoint 92, 326
    Waypoint 120, 326, on_arrival_chain=Room29V1Chain52_id
    Waypoint 180, 326
Room29V1Route53:
    Route 3
    Waypoint 163, 305
    Waypoint 163, 320
    Waypoint 163, 392
Room29V1Route54:
    Route 4
    Waypoint 253, 239
    Waypoint 253, 195
    Waypoint 205, 195
    Waypoint 205, 160
Room29V1Route55:
    Route 3
    Waypoint 168, 275
    Waypoint 168, 195
    Waypoint 175, 195, on_arrival_chain=Room29V1Chain50_id
Room29V1Route56:
    Route 2
    Waypoint 175, 195
    Waypoint 198, 195
Room29V1Route57:
    Route 2
    Waypoint 198, 170
    Waypoint 198, 195
Room29V1Route58:
    Route 2
    Waypoint 308, 322
    Waypoint 368, 322, on_arrival_chain=Room29V1Chain53_id
Room29V1Route59:
    Route 2
    Waypoint 340, 322
    Waypoint 368, 322
Room29V1Route60:
    Route 2
    Waypoint 360, 322
    Waypoint 330, 322
Room29V1Route61:
    Route 4
    Waypoint 190, 320
    Waypoint 190, 350
    Waypoint 155, 350
    Waypoint 155, 392, on_arrival_chain=Room29V1Chain55_id
Room29V1Route62:
    Route 2
    Waypoint 198, 170
    Waypoint 198, 195, on_arrival_chain=Room29V1Chain57_id
Room29V1Route63:
    Route 3
    Waypoint 198, 195
    Waypoint 198, 225
    Waypoint 160, 225, on_arrival_chain=Room29V1Chain51_id
Room29V1Route64:
    Route 3
    Waypoint 270, 343
    Waypoint 155, 343
    Waypoint 155, 392, on_arrival_chain=Room29V1Chain59_id
Room29V1Route65:
    Route 4
    Waypoint 190, 245
    Waypoint 167, 245
    Waypoint 167, 299
    Waypoint 196, 299, on_arrival_chain=Room29V1Chain62_id
Room29V1Route66:
    Route 4
    Waypoint 252, 324
    Waypoint 158, 323
    Waypoint 158, 197
    Waypoint 194, 196, on_arrival_chain=Room29V1Chain38_id
    OffsetTable Room29V1Chains, 63, 1
    Offsets Room29V1Chain0, Room29V1Chain1, Room29V1Chain2, Room29V1Chain3, Room29V1Chain4, Room29V1Chain5
    Offsets Room29V1Chain6, Room29V1Chain7, Room29V1Chain8, Room29V1Chain9, Room29V1Chain10, Room29V1Chain11
    Offsets Room29V1Chain12, Room29V1Chain13, Room29V1Chain14, Room29V1Chain15, Room29V1Chain16, Room29V1Chain17
    Offsets Room29V1Chain18, Room29V1Chain19, Room29V1Chain20, Room29V1Chain21, Room29V1Chain22, Room29V1Chain23
    Offsets Room29V1Chain24, Room29V1Chain25, Room29V1Chain26, Room29V1Chain27, Room29V1Chain28, Room29V1Chain29
    Offsets Room29V1Chain30, Room29V1Chain31, Room29V1Chain32, Room29V1Chain33, Room29V1Chain34, Room29V1Chain35
    Offsets Room29V1Chain36, Room29V1Chain37, Room29V1Chain38, Room29V1Chain39, Room29V1Chain40, Room29V1Chain41
    Offsets Room29V1Chain42, Room29V1Chain43, Room29V1Chain44, Room29V1Chain45, Room29V1Chain46, Room29V1Chain47
    Offsets Room29V1Chain48, Room29V1Chain49, Room29V1Chain50, Room29V1Chain51, Room29V1Chain52, Room29V1Chain53
    Offsets Room29V1Chain54, Room29V1Chain55, Room29V1Chain56, Room29V1Chain57, Room29V1Chain58, Room29V1Chain59
    Offsets Room29V1Chain60, Room29V1Chain61, Room29V1Chain62
    EndTable
Room29V1Chain0:
    GotoIfStoryStageCompare 0, 0, Room29V1Chain2_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 6, Room29V1Chain10_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 14, Room29V1Chain43_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 18, Room29V1Chain21_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 19, Room29V1Chain37_id, 0, 0, 0
    GotoIfStoryStageCompare 0, 21, Room29V1Chain39_id, 0, 0, 0
    End
Room29V1Chain1:
    ArmChainYield 1
    SetQuestState 1, 1
    SetQuestState 0, 129
    QueueTileObjectMove Room29V1Group1_id, 0, 0, 0, 1500, 0
    RemovePartyFollower 6
    RespawnRowAndRunChain Room29V1Group2_id, 0
    @ "Attention, please. I have a couple of announcements to make..."
    @ "I am pleased to welcome two new teachers to our ranks this year. Professor Lupin, who has consented to fill the post of Defense Against the Dark Arts teacher."
    @ "Our second appointment will be filled by Rubeus Hagrid, who will be teaching Care of Magical Creatures in addition to his game keeping duties."
    @ "I think that's everything of importance. Hermione Granger, please come and speak to me immediately."
    ShowRoomDialog 184
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group1_id, 0, 0, 0, Room29V1Route0_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group2_id, 0, 0, 0, Room29V1Route1_id, 0, 1, 0, 0, 0
    End
Room29V1Chain2:
    ResetPartyLeaderSelection
    GotoIfQuestStateCompare 1, 0, 0, 0, 0, Room29V1Group1_id, 0
    End
Room29V1Chain3:
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group1_id, 2, 0, 0, Room29V1Route54_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group1_id, 3, 0, 0, Room29V1Route54_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group1_id, 4, 0, 0, Room29V1Route54_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group1_id, 5, 0, 0, Room29V1Route54_id, 2, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group1_id, 6, 0, 0, Room29V1Route53_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group1_id, 7, 0, 0, Room29V1Route53_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group2_id, 0, 0, 0, Room29V1Route53_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group1_id, 0, 0, 0, Room29V1Route52_id, 0, 1, 0, 0, 0
    End
Room29V1Chain4:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ResetPartyLeaderSelection
    ArmChainYield 0
    InvokeChainIfEnabled 0, Room29V1Chain5_id
    End
Room29V1Chain5:
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route3_id, 0, 1, 0, 0, 0
    End
Room29V1Chain6:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    QueueTileObjectMove 0, 255, 0, 0, 600, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "I hope she isn't in trouble."
    ShowRoomDialog 185
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group2_id, 0, 0, 0, Room29V1Route2_id, 0, 1, 0, 0, 0
    End
Room29V1Chain7:
    ArmChainYield 1
    @ "What did Professor McGonagall want?"
    @ "Oh... Umm... Nothing, really. We just talked about my heavy timetable this year. She offered to help."
    @ "Off to bed, everyone. You've all had a long day and I want you to be alert and ready for my Transfiguration class in the morning!"
    ShowRoomDialog 186
    InvokeChainIfEnabled 0, Room29V1Chain3_id
    End
Room29V1Chain8:
    ArmChainYield 1
    DespawnRoomRowObjects Room29V1Group1_id
    DespawnRoomRowObjects Room29V1Group2_id
    PlayCutscene 1, 0, Room29V1Chain17_id
    End
Room29V1Chain9:
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route4_id, 0, 1, 0, 0, 0
    End
Room29V1Chain10:
    ArmChainYield 1
    GotoIfQuestStateCompare 245, 0, 0, 0, 0, Room29V1Group4_id, 0
    GotoIfQuestStateCompare 245, 0, 2, 0, 0, Room29V1Group8_id, 0
    End
Room29V1Chain11:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetQuestState 1, 245
    Unk02 Room29V1Group4_id, 0, 2
    PlaySoundById 52
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route6_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group4_id, 0, 0, 0, Room29V1Route7_id, 0, 1, 20, 0, 0
    End
Room29V1Chain12:
    StartObjectAnimSequence Room29V1Group4_id, 1, 0, 0, Room29V1Route8_id, 0, 1, 0, 0, 0
    End
Room29V1Chain13:
    ArmChainYield 1
    @ "Meowrr!"
    ShowRoomDialog 354
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group4_id, 0, 0, 0, Room29V1Route9_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group4_id, 1, 0, 0, Room29V1Route10_id, 0, 1, 0, 0, 0
    End
Room29V1Chain14:
    ArmChainYield 1
    PlaySoundById 52
    @ "Crookshanks! What is wrong with you?"
    @ "Just keep that cat away from Scabbers!"
    ShowRoomDialog 355
    Unk02 Room29V1Group4_id, 0, 4
    Unk02 Room29V1Group4_id, 1, 4
    QueueTileObjectMove Room29V1Group4_id, 0, 0, 0, 1700, 0
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group4_id, 0, 0, 0, Room29V1Route11_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group4_id, 1, 0, 0, Room29V1Route12_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route13_id, 0, 1, 0, 0, 0
    End
Room29V1Chain15:
    ArmChainYield 1
    RemovePartyFollower 6
    RespawnRowAndRunChain Room29V1Group7_id, 0
    QueueTileObjectMove 0, 255, 0, 0, 1700, 0
    DespawnRoomRowObjects Room29V1Group4_id
    @ "Scabbers, come back!"
    @ "I'll help you get him, Ron."
    ShowRoomDialog 356
    SetQuestState QUEST_OBJ_FIND_SCABBERS_COMMON_ROOM, QUEST_OBJECTIVE_INDEX
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room29V1Chain16:
    End
Room29V1Chain17:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    RemovePartyFollower 7
    RespawnRowAndRunChain Room29V1Group20_id, 0
    RespawnRowAndRunChain Room29V1Group17_id, 0
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group17_id, 0, 0, 0, Room29V1Route55_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route57_id, 0, 1, 0, 0, 0
    End
Room29V1Chain18:
    @ "Did you know that you can visit our shop on the seventh floor? You can buy items from George and me at very reasonable prices..."
    ShowRoomDialog 638
    End
Room29V1Chain19:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group8_id, 0, 0, 0, Room29V1Route15_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route60_id, 0, 1, 0, 0, 0
    End
Room29V1Chain20:
    ArmChainYield 1
    @ "Harry, it was Sirius Black who slashed the Fat Lady's portrait!"
    @ "Do you think Black's still in the castle?"
    @ "He might be!"
    ShowRoomDialog 407
    RespawnRowAndRunChain Room29V1Group19_id, 0
    RemovePartyFollower 7
    @ "We should be on our way to Defense Against the Dark Arts class."
    @ "I wonder if Professor Lupin will even be there? He hasn't looked well lately."
    @ "That class does seem to take a toll on its teachers. Let's get going."
    ShowRoomDialog 408
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group8_id, 0, 0, 0, Room29V1Route58_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route59_id, 0, 1, 0, 0, 0
    End
Room29V1Chain21:
    GotoIfQuestStateCompare 230, 0, 1, 0, 0, Room29V1Group9_id, 0
    End
Room29V1Chain22:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    SetOverworldMonstersDisabled
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route17_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group9_id, 2, 0, 0, Room29V1Route18_id, 0, 1, 0, 0, 0
    End
Room29V1Chain23:
    ArmChainYield 1
    RespawnRowAndRunChain Room29V1Group18_id, 0
    @ "Well, here it is. There doesn't seem to be anything wrong with the Firebolt at all."
    @ "I can have it back? Seriously?"
    @ "Seriously. And Potter - do try and win, won't you?"
    ShowRoomDialog 495
    DespawnRoomRowObjects Room29V1Group18_id
    GrantRoomReward 67, 0
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group9_id, 2, 0, 0, Room29V1Route20_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route19_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group9_id, 1, 0, 0, Room29V1Route16_id, 0, 1, 0, 0, 0
    QueueTileObjectMove Room29V1Group9_id, 1, 0, 0, 800, 0
    End
Room29V1Chain24:
    ArmChainYield 1
    DespawnTileObject Room29V1Group9_id, 2
    @ "Seen Ron around?"
    @ "No, I haven't."
    ShowRoomDialog 496
    Unk02 Room29V1Group9_id, 3, 2
    SetTileObjectFacing Room29V1Group9_id, 1, 0
    ArmChainYield 0
    QueueTileObjectMove Room29V1Group9_id, 3, 0, 0, 800, 0
    StartObjectAnimSequence Room29V1Group9_id, 3, 0, 0, Room29V1Route21_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route23_id, 0, 1, 0, 0, 0
    End
Room29V1Chain25:
    ArmChainYield 1
    @ "LOOK!"
    @ "N-no..."
    @ "LONG, GINGER CAT HAIRS!"
    ShowRoomDialog 497
    @ "Let's go to the Quidditch pitch. The walk and the fresh air will clear our heads..."
    ShowRoomDialog 499
    ArmChainYield 0
    QueueTileObjectMove 0, 255, 0, 0, 1400, 0
    StartObjectAnimSequence Room29V1Group9_id, 3, 0, 0, Room29V1Route65_id, 0, 1, 0, 0, 0
    End
Room29V1Chain26:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    DespawnRoomRowObjects Room29V1Group9_id
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route24_id, 0, 1, 0, 0, 0
    End
Room29V1Chain27:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "Yes! We won!"
    @ "Good for you, Harry!"
    @ "I've never seen Professor McGonagall so angry! Malfoy's definitely for it!"
    @ "Well done, Harry! Ten Galleons to me! Must find Penelope. Excuse me -"
    ShowRoomDialog 501
    Unk02 Room29V1Group10_id, 2, 2
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group10_id, 2, 0, 0, Room29V1Route26_id, 0, 1, 0, 0, 0
    End
Room29V1Chain28:
    ArmChainYield 1
    @ "You were fantastic, Harry!"
    ShowRoomDialog 502
    @ "You gave Malfoy one heck of a fright!"
    ShowRoomDialog 503
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group10_id, 5, 0, 0, Room29V1Route27_id, 0, 1, 0, 0, 0
    End
Room29V1Chain29:
    DespawnTileObject Room29V1Group10_id, 2
    StartObjectAnimSequence Room29V1Group10_id, 3, 0, 0, Room29V1Route25_id, 0, 1, 0, 0, 0
    End
Room29V1Chain30:
    ArmChainYield 1
    @ "I know that you all want to celebrate, but I think we've had quite enough excitement for one day. Off to your dormitories, please!"
    ShowRoomDialog 504
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group10_id, 5, 0, 0, Room29V1Route29_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group10_id, 3, 0, 0, Room29V1Route61_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group10_id, 7, 0, 0, Room29V1Route31_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group10_id, 1, 0, 0, Room29V1Route30_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group10_id, 0, 0, 0, Room29V1Route28_id, 2, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group10_id, 4, 0, 0, Room29V1Route30_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group10_id, 6, 0, 0, Room29V1Route28_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group10_id, 8, 0, 0, Room29V1Route32_id, 0, 1, 0, 0, 0
    End
Room29V1Chain31:
    ArmChainYield 1
    DespawnTileObject Room29V1Group10_id, 5
    DespawnTileObject Room29V1Group10_id, 4
    DespawnTileObject Room29V1Group10_id, 6
    DespawnTileObject Room29V1Group10_id, 1
    DespawnTileObject Room29V1Group10_id, 0
    DespawnTileObject Room29V1Group10_id, 8
    SetQuestState 2, 230
    SetQuestState 1, QUEST_ALT_PRESENTATION
    SetQuestState QUEST_OBJ_GO_TO_BOYS_DORMITORY, QUEST_OBJECTIVE_INDEX
    SetStoryStage 19
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room29V1Chain32:
    RespawnRowAndRunChain Room29V1Group12_id, 0
    RespawnRowAndRunChain Room29V1Group11_id, 0
    End
Room29V1Chain33:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route34_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group12_id, 0, 0, 0, Room29V1Route33_id, 0, 1, 0, 0, 0
    End
Room29V1Chain34:
    ArmChainYield 1
    @ "I am delighted that Gryffindor won the match, but this is getting ridiculous!"
    @ "Ron had a nightmare, Professor."
    @ "IT WASN'T A NIGHTMARE! SIRIUS BLACK WAS STANDING OVER ME, HOLDING A KNIFE!"
    ShowRoomDialog 508
    Unk02 Room29V1Group12_id, 2, 3
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group12_id, 2, 0, 0, Room29V1Route35_id, 0, 1, 0, 0, 0
    QueueTileObjectMove Room29V1Group12_id, 0, 0, 0, 1000, 0
    End
Room29V1Chain35:
    ArmChainYield 1
    @ "Professor McGonagall, Sir Cadogan has just informed me that he let a man into Gryffindor Tower!"
    @ "But - but the password?"
    @ "Apparently, this man already had them! He read them off a piece of paper!"
    @ "Which abysmally foolish person wrote down the password and left it lying around?"
    ShowRoomDialog 509
    ArmChainYield 0
    QueueTileObjectMove Room29V1Group12_id, 3, 0, 0, 1000, 0
    StartObjectAnimSequence Room29V1Group12_id, 3, 0, 0, Room29V1Route36_id, 0, 1, 0, 0, 0
    End
Room29V1Chain36:
    ArmChainYield 1
    @ "I - erm - well, I..."
    @ "I see. From tonight, Sir Cadogan is sacked and the Fat Lady will return. Security will be increased. Everyone, please be more careful. Now, back to bed."
    ShowRoomDialog 510
    QueueTileObjectMove 0, 255, 0, 0, 1000, 0
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group12_id, 7, 0, 0, Room29V1Route40_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group12_id, 0, 0, 0, Room29V1Route39_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group12_id, 1, 0, 0, Room29V1Route37_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group12_id, 3, 0, 0, Room29V1Route66_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group12_id, 4, 0, 0, Room29V1Route66_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group12_id, 6, 0, 0, Room29V1Route64_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group12_id, 5, 0, 0, Room29V1Route38_id, 1, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group12_id, 2, 0, 0, Room29V1Route39_id, 0, 1, 0, 0, 0
    End
Room29V1Chain37:
    GotoIfQuestStateCompare 231, 0, 2, Room29V1Chain32_id, 0, 0, 0
    End
Room29V1Chain38:
    ArmChainYield 1
    DespawnRoomRowObjects Room29V1Group11_id
    DespawnTileObject Room29V1Group12_id, 7
    DespawnTileObject Room29V1Group12_id, 4
    DespawnTileObject Room29V1Group12_id, 0
    DespawnTileObject Room29V1Group12_id, 3
    DespawnTileObject Room29V1Group12_id, 2
    DespawnTileObject Room29V1Group12_id, 1
    SetQuestState 2, 231
    SetQuestState QUEST_OBJ_GO_TO_BOYS_DORMITORY, QUEST_OBJECTIVE_INDEX
    SetStoryStage 20
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room29V1Chain39:
    GotoIfQuestStateCompare 233, 0, 0, Room29V1Chain61_id, 0, Room29V1Group13_id, 0
    End
Room29V1Chain40:
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route41_id, 0, 1, 0, 0, 0
    End
Room29V1Chain41:
    ArmChainYield 1
    @ "Hagrid sent me a note. They're going to execute Buckbeak!"
    @ "No! They can't do that!"
    @ "We have to go and see Hagrid after dinner and give him our support!"
    ShowRoomDialog 532
    PlayCutscene 0, 0, Room29V1Chain60_id
    End
Room29V1Chain42:
    ArmChainYield 1
    DespawnRoomRowObjects Room29V1Group13_id
    RecruitPartyFollower 7
    RecruitPartyFollower 6
    SetQuestState QUEST_OBJ_GO_TO_HAGRIDS_HUT_SECOND, QUEST_OBJECTIVE_INDEX
    SetQuestState 1, 233
    SetQuestState 1, QUEST_ALT_PRESENTATION
    ClearOverworldMonstersDisabled
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room29V1Chain43:
    GotoIfQuestStateCompare 245, 0, 0, 0, 0, Room29V1Group14_id, 0
    End
Room29V1Chain44:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route45_id, 0, 1, 0, 0, 0
    End
Room29V1Chain45:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 2, 0, 0
    QueueTileObjectMove Room29V1Group14_id, 2, 0, 0, 1400, 0
    @ "Something wrong?"
    ShowRoomDialog 430
    DespawnTileObject Room29V1Group14_id, 1
    DespawnTileObject Room29V1Group14_id, 0
    RespawnRowAndRunChain Room29V1Group16_id, 0
    RespawnRowAndRunChain Room29V1Group15_id, 0
    RemovePartyFollower 7
    @ "Hedwig dropped a parcel on top of that notice board and we don't know how to get to it."
    @ "Why don't you just use Wingardium Leviosa?"
    ShowRoomDialog 431
    @ "Wingardium Leviosa!"
    ShowRoomDialog 432
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route48_id, 0, 1, 0, 0, 0
    End
Room29V1Chain46:
    ArmChainYield 1
    @ "Let's go then!"
    @ "You aren't going to ride the Firebolt to Hagrid's hut, are you?"
    @ "If it makes you feel better, I'll carry it."
    ShowRoomDialog 435
    Unk02 Room29V1Group14_id, 2, 2
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group14_id, 2, 0, 0, Room29V1Route47_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group16_id, 0, 0, 0, Room29V1Route49_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route46_id, 0, 1, 0, 0, 0
    End
Room29V1Chain47:
    ArmChainYield 1
    QueueTileObjectMove 0, 255, 0, 0, 2000, 0
    RecruitPartyFollower 7
    DespawnRoomRowObjects Room29V1Group16_id
    RecruitPartyFollower 6
    DespawnTileObject Room29V1Group14_id, 2
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route51_id, 0, 1, 0, 0, 0
    End
Room29V1Chain48:
    ArmChainYield 1
    DelayedRespawnRowAndRunChain 1, 0, 0
    SetTileObjectFacing 0, 255, 7
    QueueTileObjectMove 0, 255, 0, 0, 2000, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    @ "I don't believe it - it's a Firebolt racing broom! There's no card, though. I wonder who sent it?"
    @ "Wait 'til Malfoy sees you on this! He'll be sick as a pig!"
    @ "I can't believe this. Who - ?"
    @ "I know who it could've been - Lupin!"
    @ "I can't see Lupin affording something like this."
    ShowRoomDialog 433
    QueueTileObjectMove Room29V1Group14_id, 2, 0, 0, 2000, 0
    DelayedRespawnRowAndRunChain 1, 0, 0
    DespawnRoomRowObjects Room29V1Group15_id
    @ "It's a bit odd, isn't it? Maybe we should get Professor McGonagall to check it out?"
    @ "I'm sure it's all right, Hermione. I can't wait to show Hagrid. Let's go find him!"
    ShowRoomDialog 434
    InvokeChainIfEnabled 0, Room29V1Chain46_id
    End
Room29V1Chain49:
    ArmChainYield 1
    CancelObjectAnimSequence 0, 255
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route50_id, 0, 1, 0, 0, 0
    End
Room29V1Chain50:
    ArmChainYield 1
    @ "We'd better get going... It's almost time for Transfiguration class!"
    @ "Okay, let's go."
    ShowRoomDialog 197
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group17_id, 0, 0, 0, Room29V1Route56_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group20_id, 0, 0, 0, Room29V1Route62_id, 0, 1, 0, 0, 0
    End
Room29V1Chain51:
    ArmChainYield 1
    SetQuestState QUEST_OBJ_GO_TO_TRANSFIGURATION, QUEST_OBJECTIVE_INDEX
    SetStoryStage 1
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room29V1Chain52:
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route5_id, 0, 1, 0, 0, 0
    End
Room29V1Chain53:
    ArmChainYield 1
    RecruitPartyFollower 5
    DespawnRoomRowObjects Room29V1Group8_id
    RecruitPartyFollower 7
    DespawnRoomRowObjects Room29V1Group19_id
    SetQuestState QUEST_OBJ_GO_TO_DADA, QUEST_OBJECTIVE_INDEX
    SetStoryStage 7
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room29V1Chain54:
    DespawnTileObject Room29V1Group10_id, 7
    End
Room29V1Chain55:
    DespawnTileObject Room29V1Group10_id, 3
    End
Room29V1Chain56:
    ArmChainYield 1
    SetQuestState 1, 245
    SetQuestState QUEST_OBJ_GO_TO_HAGRIDS_HUT_FIRST, QUEST_OBJECTIVE_INDEX
    SetQuestState 2, 230
    GrantRoomReward 67, 0
    ClearOverworldMonstersDisabled
    SetStoryStage 15
    SetTileObjectAnimStateWithSpeed 0, 255
    End
Room29V1Chain57:
    ArmChainYield 1
    RecruitPartyFollower 7
    DespawnRoomRowObjects Room29V1Group20_id
    RecruitPartyFollower 6
    DespawnRoomRowObjects Room29V1Group17_id
    ArmChainYield 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route63_id, 0, 1, 0, 0, 0
    End
Room29V1Chain58:
    DespawnTileObject Room29V1Group12_id, 5
    End
Room29V1Chain59:
    DespawnTileObject Room29V1Group12_id, 6
    End
Room29V1Chain60:
    ArmChainYield 1
    @ "Let's go!"
    ShowRoomDialog 533
    ArmChainYield 0
    StartObjectAnimSequence Room29V1Group13_id, 1, 0, 0, Room29V1Route43_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence Room29V1Group13_id, 2, 0, 0, Room29V1Route42_id, 0, 1, 0, 0, 0
    StartObjectAnimSequence 0, 255, 0, 0, Room29V1Route44_id, 0, 1, 0, 0, 0
    End
Room29V1Chain61:
    SetQuestState 0, QUEST_ALT_PRESENTATION
    End
Room29V1Chain62:
    ArmChainYield 1
    @ "You haven't heard the last of this, Hermione!"
    ShowRoomDialog 500
    PlayCutscene 0, Room29V1Group10_id, Room29V1Chain26_id
    End
    EndSubBlock Room29V1End

    SubBlock Room29V2, 1, Room29V2Routes, Room29V2Chains, Room29V2End
    OffsetTable Room29V2Groups, 1, 1
    Offsets Room29V2Group0
    EndTable
    Group Room29V2Group0, 0
    OffsetTable Room29V2Routes, 0
    EndTable
    OffsetTable Room29V2Chains, 1, 1
    Offsets Room29V2Chain0
    EndTable
Room29V2Chain0:
    End
    EndSubBlock Room29V2End
