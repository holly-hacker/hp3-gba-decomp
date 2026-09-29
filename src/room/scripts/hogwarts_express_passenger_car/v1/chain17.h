const u8 g_abRoom06V1Chain17[] = {
    // "Excuse me..."
    // "Yes, miss?"
    // "Erm... Professor Lupin was wondering if you might get the train moving again - if that's possible?"
    // "Of course it's possible. Tell Professor Lupin we'll be underway very soon."
    // "OK. Thank you very much."
    RS_ShowRoomDialog(132),
    RS_SetQuestState(1, 246),
    RS_DelayedRespawnRowAndRunChain(0, 12, 0),
    RS_SetBattleDefeatState(1),
    RS_SetQuestState(11, 6),
    RS_SetQuestState(56, 25),
    RS_End(),
};
