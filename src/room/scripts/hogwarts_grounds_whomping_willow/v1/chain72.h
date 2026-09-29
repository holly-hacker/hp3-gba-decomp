const u8 g_abRoom15V1Chain72[] = {
    RS_ArmChainYield(1),
    RS_DespawnRoomRowObjects(29),
    RS_Unk02(0, 255, 1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "The dog's dragged Ron under the Whomping Willow!"
    // "If that dog can get in, we can!"
    RS_ShowRoomDialog(557),
    RS_SetQuestState(1, 129),
    RS_SetQuestState(46, 25),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
