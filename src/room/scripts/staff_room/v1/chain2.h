const u8 g_abRoom27V1Chain2[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    // "Now, please return to your common room."
    // "The Riddikulus Boggart Challenge can now be accessed from the Mini-Games menu found on the Title Screen."
    RS_ShowRoomDialog(351),
    RS_ArmChainYield(0),
    RS_RespawnRowAndRunChain(0, 4),
    RS_ArmChainYield(1),
    RS_QueueTileObjectMove(0, 255, 0, 0, 1600, 0),
    RS_DelayedRespawnRowAndRunChain(8, 0, 0),
    RS_StartTileObjectScript(127, 7, 1, 0, 255, 0, 0, 5, 255, 255, 255),
    RS_RespawnRowAndRunChain(0, 5),
    // "Anything worrying you, Harry?"
    // "Yes. Why didn't you let me fight the Boggart?"
    // "I assumed that if the Boggart faced you, it would assume the shape of Lord Voldemort."
    // "I did think of him, at first. But then I remembered those Dementors."
    // "The Dementors affect you worse than the others because there are horrors in your past that the others don't have. I can help you resist them with some Anti-Dementor lessons..."
    // "Thank you very much, Professor."
    // "I'll come and find you for the lessons. Now, I'd advise you to go to your common room."
    // "Bye, Professor."
    RS_ShowRoomDialog(352),
    RS_RespawnRowAndRunChain(5, 0),
    RS_SetQuestState(23, 25),
    RS_SetTileObjectAnimStateWithSpeed(0, 255),
    RS_End(),
};
