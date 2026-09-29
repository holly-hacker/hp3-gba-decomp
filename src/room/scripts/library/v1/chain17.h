const u8 g_abRoom34V1Chain17[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_DespawnRoomRowObjects(11),
    RS_DespawnRoomRowObjects(12),
    RS_RespawnRowAndRunChain(17, 0),
    // "Look, this must be the book Hermione mentioned! It's got a section dealing with the Committee for the Disposal of Dangerous Creatures!"
    // "Let's have a look!"
    // "It doesn't look good."
    // "We can't tell Hagrid that!"
    // "Let's find Hermione. Maybe she'll be able to make sense of it all."
    RS_ShowRoomDialog(442),
    RS_SetQuestState(33, 25),
    RS_SetQuestState(1, 230),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
