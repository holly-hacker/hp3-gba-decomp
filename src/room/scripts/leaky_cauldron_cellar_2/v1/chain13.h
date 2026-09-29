const u8 g_abRoom39V1Chain13[] = {
    RS_ArmChainYield(1),
    RS_StartTileObjectScript(399, 155, 0, 0, 255, 0, 0, 2, 255, 255, 255),
    RS_DelayedRespawnRowAndRunChainFrames(0, 0, 47),
    // "Got you, you naughty cat!"
    // "We'd better go and find Ron."
    RS_ShowRoomDialog(55),
    RS_DespawnTileObject(17, 5),
    RS_DespawnTileObject(0, 3),
    RS_SetQuestState(1, 242),
    RS_SetQuestState(54, 25),
    RS_DelayedRespawnRowAndRunChain(0, 6, 0),
    RS_DelayedRespawnRowAndRunChain(0, 10, 0),
    RS_End(),
};
