const u8 g_abRoom01V1Chain24[] = {
    RS_ArmChainYield(1),
    RS_StartTileObjectScript(305, 214, 0, 0, 255, 0, 0, 0, 255, 255, 255),
    RS_DelayedRespawnRowAndRunChainFrames(1, 0, 0),
    // "I seem to recall that I requested more herbs than this, Potter. Kindly return to the store room and collect the remaining herbs."
    RS_ShowRoomDialog(299),
    RS_ArmChainYield(0),
    RS_InvokeChainIfEnabled(0, 37),
    RS_End(),
};
