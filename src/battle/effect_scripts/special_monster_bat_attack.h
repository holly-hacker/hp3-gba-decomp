// Bat/Fruitbat/Mortis Bat's special attack animation; no status effect.
const u8 g_abSpecialMonsterBatAttackScript[] = {
    BS_SnapToCaster(0),
    BS_MoveBy(20, -21),
    BS_SetObjectAnim(16, 0),
    BS_SetOamPriority(0),
    BS_SetVelocity(5, 2),
    BS_WaitFrames(1),
    BS_ShowObject(),
    BS_GotoIfLocalAEqual(5, 38),
    BS_SpawnEffect(16),
  BS_Label(38),
    BS_WaitForCounter(),
    BS_End(),
};
