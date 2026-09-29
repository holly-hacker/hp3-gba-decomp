const u8 g_abRoom34V1Chain13[] = {
    RS_ArmChainYield(1),
    // "We're looking for a book on wizard law, Madam Pince."
    // "Very well; the legal section is on the south side of the library."
    RS_ShowRoomDialog(439),
    RS_RespawnRowAndRunChain(10, 0),
    RS_SetQuestState(3, 230),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
