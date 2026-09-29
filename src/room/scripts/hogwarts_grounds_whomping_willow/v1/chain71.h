const u8 g_abRoom15V1Chain71[] = {
    RS_ArmChainYield(1),
    RS_Unk02(29, 0, 3),
    RS_Unk02(29, 1, 3),
    // "Help!"
    RS_ShowRoomDialog(555),
    RS_SetTileObjectSpecialFlag(29, 1, 1),
    RS_ArmChainYield(0),
    RS_PlayTileObjectAnimation(29, 1, 22),
    RS_StartObjectAnimSequence(29, 0, 0, 0, 66, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(29, 1, 0, 0, 66, 0, 1, 0, 0, 0),
    RS_SetTileObjectFacing(0, 255, 2),
    RS_End(),
};
