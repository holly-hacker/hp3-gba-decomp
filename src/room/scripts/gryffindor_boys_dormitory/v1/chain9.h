const u8 g_abRoom28V1Chain9[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    // "It's a lovely night..."
    RS_ShowRoomDialog(527),
    RS_SetTileObjectFacing(0, 255, 0),
    // "There's Crookshanks! But what's that walking alongside him?"
    RS_ShowRoomDialog(528),
    RS_DelayedRespawnRowAndRunChain(1, 0, 0),
    RS_SetQuestState(1, 232),
    RS_ReturnToOverworld(10, 3),
    RS_End(),
};
