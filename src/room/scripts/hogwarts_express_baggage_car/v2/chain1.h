const u8 g_abRoom05V2Chain1[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "Job done, Professor Lupin."
    // "Thank you, Miss Granger."
    RS_ShowRoomDialog(139),
    RS_DelayedRespawnRowAndRunChainFrames(3, 0, 0),
    RS_DespawnTileObject(1, 1),
    RS_DelayedRespawnRowAndRunChain(0, 3, 0),
    // "Harry, are you all right?"
    // "W-what? What happened? Where's that - that thing? Who screamed?"
    // "No one screamed."
    RS_ShowRoomDialog(140),
    // "Hogsmeade, next stop!"
    RS_ShowRoomDialog(141),
    RS_ClearQuestStateUpperHalf(),
    RS_PlayScreenTransitionOut(),
    RS_Unk2A(5, 255, 255, 255),
    RS_SetStoryStage(0),
    RS_PlayCutscene(5, 0, 3),
    RS_End(),
};
