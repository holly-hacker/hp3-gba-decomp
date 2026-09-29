const u8 g_abRoom29V1Chain1[] = {
    RS_ArmChainYield(1),
    RS_SetQuestState(1, 1),
    RS_SetQuestState(0, 129),
    RS_QueueTileObjectMove(2, 0, 0, 0, 1500, 0),
    RS_RemovePartyFollower(6),
    RS_RespawnRowAndRunChain(3, 0),
    // "Attention, please. I have a couple of announcements to make..."
    // "I am pleased to welcome two new teachers to our ranks this year. Professor Lupin, who has consented to fill the post of Defense Against the Dark Arts teacher."
    // "Our second appointment will be filled by Rubeus Hagrid, who will be teaching Care of Magical Creatures in addition to his game keeping duties."
    // "I think that's everything of importance. Hermione Granger, please come and speak to me immediately."
    RS_ShowRoomDialog(184),
    RS_ArmChainYield(0),
    RS_StartObjectAnimSequence(2, 0, 0, 0, 0, 0, 1, 0, 0, 0),
    RS_StartObjectAnimSequence(3, 0, 0, 0, 1, 0, 1, 0, 0, 0),
    RS_End(),
};
