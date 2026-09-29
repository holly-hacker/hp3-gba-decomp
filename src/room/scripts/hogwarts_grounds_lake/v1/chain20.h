const u8 g_abRoom13V1Chain20[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_StartTileObjectScript(270, 215, 2, 0, 255, 0, 0, 0, 255, 255, 255),
    RS_SetTileObjectFacing(0, 255, 0),
    // "Here comes Lupin! Help, Buckbeak!"
    RS_ShowRoomDialog(597),
    RS_InvokeChainIfEnabled(0, 19),
    RS_End(),
};
