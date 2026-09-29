const u8 g_abRoom38V3Chain1[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetQuestState(1, 253),
    RS_QueueTileObjectMove(4, 0, 0, 0, 1200, 0),
    RS_Unk02(4, 0, 4),
    RS_Unk02(4, 1, 4),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(4, 1, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(4, 0, 0, 0, 1, 0, 1, 0, 0, 0),
    RS_End(),
};
