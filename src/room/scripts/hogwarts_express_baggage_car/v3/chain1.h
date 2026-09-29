const u8 g_abRoom05V3Chain1[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "Here's the chocolate, Professor!"
    // "Well done, Mr. Weasley."
    RS_ShowRoomDialog(138),
    RS_ConsumeRoomItem(76),
    RS_ShowItemRemovedMessage(76),
    RS_DespawnTileObject(1, 2),
    RS_DelayedRespawnRowAndRunChain(0, 2, 0),
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
    RS_PlayCutscene(5, 0, 5),
    RS_End(),
};
