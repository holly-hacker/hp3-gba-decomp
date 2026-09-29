// Draco's special attack animation; no status effect.
const u8 g_abSpecialMonsterDracoAttackScript[] = {
    BS_TeleportToSlotPosition(0),
    BS_WaitFrames(1),
    BS_SetObjectAnim(56, 0),
    BS_WaitFrames(1),
    BS_ShowObject(),
    BS_AdvanceAttackOutcome(),
    BS_AdvanceAttackOutcome(),
    BS_WaitForCounter(),
    BS_AdvanceAttackOutcome(),
    BS_AdvanceAttackOutcome(),
    BS_AdvanceAttackOutcome(),
    BS_End(),
};
