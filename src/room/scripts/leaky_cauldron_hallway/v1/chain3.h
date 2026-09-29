const u8 g_abRoom40V1Chain3[] = {
    RS_CancelObjectAnimSequence(0, 255),
    RS_SetQuestState(1, 26),
    RS_SetQuestState(1, 231),
    RS_ArmChainYield(1),
    RS_StartTileObjectScript(366, 232, 0, 0, 255, 0, 0, 0, 255, 255, 255),
    // "Here, Harry. Take these collector's cards. They might help you during a magical encounter."
    // "Thank you, Minister."
    RS_ShowRoomDialog(5),
    RS_GrantRoomReward(123, 0),
    RS_GrantRoomReward(124, 0),
    RS_GrantRoomReward(125, 0),
    // "You've received the Dunbar Oglethorpe, Devlin Whitehorn, and Cyprian Youdle collector's cards."
    RS_ShowRoomDialog(663),
    // "You've received some collector's cards! Collect all the cards to unlock secrets and items in the Wizard Card Collectors' Club in classroom 5B. Collecting certain groups of cards will allow Harry to use Card Combos during magical encounters. To view your card collection, choose Folios and then Folio Universitas."
    RS_ShowRoomDialog(623),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_End(),
};
