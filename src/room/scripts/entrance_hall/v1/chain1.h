const u8 g_abRoom16V1Chain1[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_ResetPartyLeaderSelection(),
    RS_SetQuestState(2, 224),
    RS_DespawnTileObject(2, 3),
    RS_DespawnTileObject(2, 4),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 9, 0, 1, 0, 0, 0),
    RS_End(),
};
