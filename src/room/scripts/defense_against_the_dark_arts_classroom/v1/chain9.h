const u8 g_abRoom00V1Chain9[] = {
    RS_ArmChainYield(1),
    RS_SetTileObjectFacing(2, 0, 2),
    // "Professor Lupin says he's feeling too ill to teach today."
    // "I would like you all to go to the library and research the subject of - werewolves. Now, run along."
    RS_ShowRoomDialog(411),
    RS_SetQuestState(27, 25),
    RS_DespawnRoomRowObjects(7),
    RS_DelayedRespawnRowAndRunChain(0, 5, 0),
    RS_InvokeChainIfEnabled(0, 3),
    RS_End(),
};
