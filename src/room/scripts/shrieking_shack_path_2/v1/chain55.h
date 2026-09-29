const u8 g_abRoom45V1Chain55[] = {
    RS_ArmChainYield(1),
    RS_DelayedRespawnRowAndRunChainFrames(1, 0, 0),
    RS_GotoIfStoryStageCompare(0, 30, 0, 0, 2, 0),
    RS_SetBattleDefeatState(10),
    RS_ArmChainYield(0),
    RS_End(),
};
