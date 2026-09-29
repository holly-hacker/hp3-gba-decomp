const u8 g_abRoom01V1Chain27[] = {
    RS_ArmChainYield(1),
    RS_StartTileObjectScript(305, 214, 0, 0, 255, 0, 0, 0, 255, 255, 255),
    // "You surprise me, Mr. Weasley. I was expecting you to return empty handed."
    RS_ShowRoomDialog(311),
    RS_DelayedRespawnRowAndRunChainFrames(1, 0, 0),
    RS_RespawnRowAndRunChain(13, 0),
    RS_InvokeChainIfEnabled(0, 32),
    RS_End(),
};
