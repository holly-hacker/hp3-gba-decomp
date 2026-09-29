const u8 g_abRoom12V1Chain22[] = {
    RS_ArmChainYield(1),
    RS_ClearTileObjectFlagBit(0, 255, 9),
    RS_ClearTileObjectFlagBit(0, 255, 4),
    RS_CancelObjectAnimSequence(0, 255),
    RS_ArmChainYield(0),
    RS_RemovePartyFollower(6),
    RS_RemovePartyFollower(7),
    RS_ArmChainYield(1),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 0, 0, 6, 0, 0, 0),
    RS_StartObjectAnimSequence(1, 34, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_End(),
};
