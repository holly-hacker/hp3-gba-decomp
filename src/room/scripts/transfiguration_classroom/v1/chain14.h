const u8 g_abRoom03V1Chain14[] = {
    RS_ArmChainYield(1),
    RS_DespawnRoomRowObjects(8),
    // "It's time for Care of Magical Creatures class with Hagrid - come on!"
    // "I just hope he isn't too nervous..."
    // "I'm really looking forward to this. Let's go."
    RS_ShowRoomDialog(229),
    RS_ClearQuestStateUpperHalf(),
    RS_SetQuestState(17, 25),
    RS_RespawnRowAndRunChain(10, 0),
    RS_SetStoryStage(2),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
