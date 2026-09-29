const u8 g_abRoom15V1Chain7[] = {
    RS_ArmChainYield(1),
    RS_QueueTileObjectMove(0, 255, 0, 0, 500, 0),
    // "What's wrong, Hagrid?"
    // "My extra copies o' 'The Monster Book of Monsters'... they escaped!"
    // "I bet Malfoy had something to do with it."
    // "Tha' may be, but I'd really appreciate it if yeh'd go and find 'em fer me. Five books in all - there'd be a reward in it fer yeh."
    // "Of course we'll find them for you, Hagrid. We'd be glad to help, reward or not."
    // "Thanks."
    RS_ShowRoomDialog(232),
    // "These three spellbooks may help you to get through my garden."
    RS_ShowRoomDialog(243),
    RS_GrantPartySpell(6),
    RS_GrantPartySpell(7),
    RS_GrantPartySpell(5),
    // "Harry receives Diffindo, Ron receives Spongify, and Hermione receives Glacius!"
    RS_ShowRoomDialog(664),
    RS_ClearOverworldMonstersDisabled(),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(0, 255, 0, 0, 10, 0, 1, 0, 0, 0),
    RS_End(),
};
