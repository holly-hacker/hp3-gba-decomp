const u8 g_abRoom42V3Chain1[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetQuestState(1, 249),
    RS_ArmChainYield(1),
    RS_QueueTileObjectMove(2, 3, 0, 0, 1350, 0),
    // "...makes no sense not to tell him, Molly. Harry's got a right to know."
    // "Arthur, the truth would terrify him! And Harry will be safe at Hogwarts."
    // "We thought Azkaban prison was safe. If Black can break out of Azkaban, he can break into Hogwarts. He's deranged, Molly, and he thinks murdering Harry will bring You-Know-Who back to power."
    RS_ShowRoomDialog(41),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1500, 0),
    RS_DelayedRespawnRowAndRunChainFrames(1, 0, 15),
    RS_End(),
};
