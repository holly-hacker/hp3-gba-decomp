const u8 g_abRoom01V1Chain21[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_DelayedRespawnRowAndRunChainFrames(5, 0, 0),
    RS_GotoIfQuestStateCompare(231, 4, 4, 26, 28, 0, 0),
    RS_End(),
};
