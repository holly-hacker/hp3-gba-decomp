const u8 g_abRoom15V1Chain11[] = {
    RS_ArmChainYield(1),
    RS_CancelObjectAnimSequence(0, 255),
    RS_ConsumeRoomItem(78),
    RS_ConsumeRoomItem(78),
    RS_ConsumeRoomItem(78),
    RS_ConsumeRoomItem(78),
    RS_ConsumeRoomItem(78),
    // "Hagrid's copies of 'The Monster Book of Monsters' have been removed from your Inventory."
    RS_ShowRoomDialog(662),
    // "Well done! 'Ave this as a reward fer returning the books!"
    RS_ShowRoomDialog(251),
    RS_GrantPartyExperience(5, 65535),
    RS_GrantRoomReward(10, 0),
    RS_ShowRewardPickupMessage(10),
    RS_InvokeChainIfEnabled(0, 10),
    RS_End(),
};
