const u8 g_abRoom13V1Chain8[] = {
    RS_ArmChainYield(1),
    // "Expecto... Expecto patro... No - no - he's innocent¸"
    RS_ShowRoomDialog(585),
    RS_RespawnRowAndRunChain(12, 0),
    RS_RemovePartyFollower(6),
    RS_PlaySoundById(161),
    RS_ClearQuestStateUpperHalf(),
    RS_UnlockMinigame(4),
    RS_StartMinigame(4, 2, 1, 0, 10),
    RS_End(),
};
