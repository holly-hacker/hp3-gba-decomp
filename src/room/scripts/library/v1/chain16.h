const u8 g_abRoom34V1Chain16[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_RespawnRowAndRunChain(11, 0),
    RS_DespawnRoomRowObjects(15),
    // "I can't find anything on Hippogriffs!"
    // "There're certainly a lot of obscure titles here."
    RS_ShowRoomDialog(441),
    RS_SetQuestState(5, 230),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
