const u8 g_abRoom43V1Chain5[] = {
    RS_ArmChainYield(1),
    RS_SetTileObjectFacing(4, 1, 0),
    RS_Unk02(4, 1, 1),
    // "Where is he, Sirius? Where is Peter Pettigrew?"
    // "Over there..."
    RS_ShowRoomDialog(573),
    RS_QueueTileObjectMove(2, 2, 0, 0, 1200, 0),
    RS_StartTileObjectScript(214, 111, 0, 4, 1, 0, 0, 6, 255, 255, 255),
    RS_SetTileObjectFacing(4, 1, 6),
    // "Squeak!"
    // "Ah, there you are, Peter. Ready, Sirius?"
    RS_ShowRoomDialog(574),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(4, 0, 0, 0, 3, 0, 1, 0, 0, 0),
    RS_End(),
};
