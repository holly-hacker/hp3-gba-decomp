const u8 g_abRoom39V1Chain18[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_ArmChainYield(1),
    RS_StartTileObjectScript(183, 140, 0, 6, 0, 0, 0, 0, 255, 255, 255),
    RS_NoOpAlt(0xffffff0a),
    // "I found Crookshanks. Did you manage to find Scabbers?"
    // "Yes, I did - no thanks to your cat."
    // "Bad Crookshanks! Don't run away again!"
    RS_ShowRoomDialog(56),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_SetStoryStage(8),
    RS_End(),
};
