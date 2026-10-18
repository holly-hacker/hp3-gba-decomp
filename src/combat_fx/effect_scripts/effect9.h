const u8 g_abEffect9Script[] = {
    BS_TeleportToSlotPosition(0),
    BS_SetActorAnim(9, 0),
    BS_WaitFrames(1),
    BS_SetOamPriority(2),
    BS_ShowActor(),
    BS_WaitFrames(18),
    BS_AdvanceAttackOutcome(),
    BS_End(),
};
