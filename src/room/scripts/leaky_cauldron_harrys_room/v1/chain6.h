const u8 g_abRoom41V1Chain6[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_StartTileObjectScript(103, 182, 0, 0, 255, 0, 0, 0, 255, 255, 255),
    // "There's a package on my bed..."
    // "There's a card... It's from Hagrid! He remembered my birthday!"
    // "It's a book! 'The Monster Book of Monsters'."
    // "Uh oh..."
    RS_ShowRoomDialog(20),
    RS_DespawnTileObject(2, 1),
    // "You are about to enter a magical encounter. Each character and creature takes a turn to perform an action, however, they can only perform one action per turn. Your characters have Stamina Points and Magic Points. Stamina Points (SP) indicate how healthy your character is and Magic Points (MP) allow a character to cast spells. Each spell uses a different number of points. Click on the Help icon in the Magical Encounter Menu for more information."
    RS_ShowRoomDialog(613),
    RS_PlayTileObjectAnimation(2, 0, 11),
    RS_SetQuestState(1, 5),
    RS_SetQuestState(2, 244),
    RS_DespawnTileObject(2, 0),
    RS_StartBattle(0, 0, 6),
    RS_End(),
};
