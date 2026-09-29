const u8 g_abRoom11V1Chain22[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChainFrames(5, 0, 0),
    RS_GotoIfQuestStateCompare(230, 0, 1, 26, 0, 0, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(14, 0, 0, 0, 12, 0, 0, 0, 0, 0),
    RS_End(),
};
