const u8 g_abRoom43V1Chain7[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_ArmChainYield(1),
    // "S-Sirius... R-Remus... My friends... my old friends..."
    // "I broke out of Azkaban, not to get at you, Harry, but to seek revenge on Pettigrew. It was Pettigrew who betrayed your parents, and made it look like I had betrayed them."
    // "You don't understand! The Dark Lord was taking over everywhere! He would have killed me!"
    // "You should have realized. If Voldemort didn't kill you, we would. Goodbye, Peter."
    RS_ShowRoomDialog(575),
    RS_StartTileObjectScript(115, 105, 0, 0, 255, 0, 0, 2, 255, 255, 255),
    RS_SetTileObjectFacing(7, 0, 4),
    RS_QueueTileObjectMove(0, 255, 0, 0, 400, 0),
    // "NO! You can't kill him. I don't reckon my dad would've wanted his best friends to become killers. He can go to Azkaban."
    // "Very well, Harry. You're the only person who has the right to decide. We'll take him back to Hogwarts."
    RS_ShowRoomDialog(576),
    RS_RespawnRowAndRunChain(5, 0),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(3, 0, 0, 0, 5, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 7, 0, 1, 0, 0, 0),
    RS_End(),
};
