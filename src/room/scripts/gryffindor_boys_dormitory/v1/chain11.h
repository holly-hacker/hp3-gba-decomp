const u8 g_abRoom28V1Chain11[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetQuestState(1, 26),
    RS_SetTileObjectAnimState(0, 1),
    // "AAARRRGGGHHH! NOOOOOOOOOOOO!"
    RS_ShowRoomDialog(505),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_QueueTileObjectMove(6, 1, 0, 0, 2000, 0),
    RS_End(),
};
