const u8 g_abRoom39V1Chain19[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_ArmChainYield(1),
    // "Scabbers, where are you?"
    RS_ShowRoomDialog(48),
    RS_StartTileObjectScript(89, 100, 0, 0, 255, 0, 0, 2, 255, 255, 255),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_ArmChainYield(0),
    RS_End(),
};
