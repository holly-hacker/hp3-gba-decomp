const u8 g_abRoom17V1Chain7[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_ArmChainYield(1),
    // "That was a lot of fun."
    // "Yes, it was!"
    // "Wizard Cracker Pop-it can now be accessed from the Mini-Games menu found on the Title Screen."
    // "Let's go to the common room and try and take our minds off losing the Firebolt¸"
    RS_ShowRoomDialog(465),
    RS_QueueTileObjectMove(2, 15, 0, 0, 2000, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(2, 15, 0, 0, 4, 0, 1, 0, 0, 0),
    RS_End(),
};
