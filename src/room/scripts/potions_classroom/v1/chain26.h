const u8 g_abRoom01V1Chain26[] = {
    RS_ArmChainYield(1),
    RS_StartTileObjectScript(305, 214, 0, 0, 255, 0, 0, 0, 255, 255, 255),
    // "Quite remarkable, Potter. You appear to have achieved the task without drawing too much attention to yourself."
    RS_ShowRoomDialog(310),
    RS_DelayedRespawnRowAndRunChainFrames(1, 0, 0),
    RS_RespawnRowAndRunChain(14, 0),
    RS_InvokeChainIfEnabled(0, 32),
    RS_End(),
};
