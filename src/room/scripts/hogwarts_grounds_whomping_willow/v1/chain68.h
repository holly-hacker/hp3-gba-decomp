const u8 g_abRoom15V1Chain68[] = {
    RS_ArmChainYield(1),
    // "Crookshanks, no! Come back!"
    RS_ShowRoomDialog(553),
    RS_SetTileObjectFacing(20, 0, 2),
    RS_PlayMusicModuleAndFlagIfChain1(12),
    RS_DespawnRoomRowObjects(19),
    RS_RespawnRowAndRunChain(21, 0),
    RS_StartTileObjectScript(540, 132, 3, 21, 0, 0, 0, 0, 255, 255, 255),
    RS_InvokeChainIfEnabled(0, 70),
    RS_End(),
};
