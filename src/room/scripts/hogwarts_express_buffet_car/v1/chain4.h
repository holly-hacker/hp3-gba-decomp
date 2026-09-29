const u8 g_abRoom07V1Chain4[] = {
    RS_ArmChainYield(1),
    // "Excuse me..."
    // "Yes, miss?"
    // "Erm... Professor Lupin was wondering if you might get the train moving again - if that's possible?"
    // "Of course it's possible. Tell Professor Lupin we'll be underway very soon."
    // "OK. Thank you very much."
    RS_ShowRoomDialog(132),
    RS_DelayedRespawnRowAndRunChain(0, 4, 0),
    RS_SetQuestState(1, 246),
    RS_DespawnTileObject(3, 2),
    RS_End(),
};
