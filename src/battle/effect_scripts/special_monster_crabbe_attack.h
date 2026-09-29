// Crabbe's special attack animation; no status effect.
const u8 g_abSpecialMonsterCrabbeAttackScript[] = {
    BS_TeleportToSlotPosition(2),
    BS_WaitFrames(1),
    BS_SetObjectAnim(54, 0),
    BS_WaitFrames(1),
    BS_ShowObject(),
    BS_WaitForCounter(),
    BS_AdvanceAttackOutcome(),
    BS_End(),
};
