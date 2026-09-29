const u8 g_abRoom34V1Chain15[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_GrantPartyExperience(10, 65535),
    // "Here's the legal section! It looks like no one's been here in a long time..."
    // "Let's try and find books that refer to Hippogriff-baiting."
    RS_ShowRoomDialog(440),
    RS_RespawnRowAndRunChain(15, 0),
    RS_DespawnRoomRowObjects(10),
    RS_SetQuestState(4, 230),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
