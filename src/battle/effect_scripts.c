#include "types.h"
#include "battle/effect_script.h"
#include "battle/script_opcodes.h"

#include "effect_scripts/special_monster_fire_crab_attack.h"
#include "effect_scripts/effect1.h"
#include "effect_scripts/spell_flipendo_uno.h"
#include "effect_scripts/spell_flipendo_duo.h"
#include "effect_scripts/special_monster_pixie_attack.h"
#include "effect_scripts/special_harry_tempest_jinx.h"
#include "effect_scripts/effect6.h"
#include "effect_scripts/effect7.h"
#include "effect_scripts/effect8.h"
#include "effect_scripts/effect9.h"
#include "effect_scripts/special_harry_cracker_jinx.h"
#include "effect_scripts/spell_fumos_uno.h"
#include "effect_scripts/effect12.h"
#include "effect_scripts/special_monster_flobberworm_attack.h"
#include "effect_scripts/special_harry_extra_exp.h"
#include "effect_scripts/special_harry_horklump_spores.h"
#include "effect_scripts/special_monster_bat_attack.h"
#include "effect_scripts/special_monster_dragonfly_attack.h"
#include "effect_scripts/special_harry_poison_immunity.h"
#include "effect_scripts/spell_verdimillious_uno.h"
#include "effect_scripts/spell_verdimillious_duo.h"
#include "effect_scripts/spell_flipendo_tria.h"
#include "effect_scripts/spell_diffindo.h"
#include "effect_scripts/spell_incendio_uno.h"
#include "effect_scripts/spell_incendio_duo.h"
#include "effect_scripts/spell_incendio_tria.h"
#include "effect_scripts/spell_verdimillious_tria.h"
#include "effect_scripts/special_monster_poison_bite.h"
#include "effect_scripts/spell_wingardium_leviosa.h"
#include "effect_scripts/spell_spongify.h"
#include "effect_scripts/spell_glacius_uno.h"
#include "effect_scripts/spell_glacius_duo.h"
#include "effect_scripts/spell_fumos_duo.h"
#include "effect_scripts/spell_petrificus_totalus_uno.h"
#include "effect_scripts/spell_petrificus_totalus_duo.h"
#include "effect_scripts/special_harry_girding_all.h"
#include "effect_scripts/effect36.h"
#include "effect_scripts/special_harry_revive.h"
#include "effect_scripts/spell_informus.h"
#include "effect_scripts/special_harry_sonorous_charm.h"
#include "effect_scripts/special_harry_replenish_sp.h"
#include "effect_scripts/special_harry_bludgers.h"
#include "effect_scripts/special_harry_poison_antidote.h"
#include "effect_scripts/special_harry_ultimate_mp.h"
#include "effect_scripts/special_ron_stink_pellet.h"
#include "effect_scripts/special_ron_stink_pellet2.h"
#include "effect_scripts/special_ron_wizard_cracker.h"
#include "effect_scripts/special_harry_snitch.h"
#include "effect_scripts/special_harry_replenish_mp.h"
#include "effect_scripts/special_hermione_be_more_careful.h"
#include "effect_scripts/special_hermione_good_study_habits.h"
#include "effect_scripts/special_hermione_proper_wand_technique.h"
#include "effect_scripts/special_harry_remove_jinx.h"
#include "effect_scripts/special_harry_reparifors.h"
#include "effect_scripts/special_monster_crabbe_attack.h"
#include "effect_scripts/special_monster_goyle_attack.h"
#include "effect_scripts/special_monster_draco_attack.h"
#include "effect_scripts/special_monster_hinkypunk_paralyze.h"
#include "effect_scripts/special_monster_salamander_attack.h"
#include "effect_scripts/special_monster_skeleton_paralyze.h"
#include "effect_scripts/special_monster_paralyzing_blow.h"
#include "effect_scripts/special_monster_whomping_willow_attack.h"
#include "effect_scripts/effect62.h"
#include "effect_scripts/effect63.h"
#include "effect_scripts/effect64.h"

const u8 *const g_apEffectScripts[65] = {
    g_abSpecialMonsterFireCrabAttackScript,
    g_abEffect1Script,
    g_abSpellFlipendoUnoScript,
    g_abSpellFlipendoDuoScript,
    g_abSpecialMonsterPixieAttackScript,
    g_abSpecialHarryTempestJinxScript,
    g_abEffect6Script,
    g_abEffect7Script,
    g_abEffect8Script,
    g_abEffect9Script,
    g_abSpecialHarryCrackerJinxScript,
    g_abSpellFumosUnoScript,
    g_abEffect12Script,
    g_abSpecialMonsterFlobberwormAttackScript,
    g_abSpecialHarryExtraExpScript,
    g_abSpecialHarryHorklumpSporesScript,
    g_abSpecialMonsterBatAttackScript,
    g_abSpecialMonsterDragonflyAttackScript,
    g_abSpecialHarryPoisonImmunityScript,
    g_abSpellVerdimilliousUnoScript,
    g_abSpellVerdimilliousDuoScript,
    g_abSpellFlipendoTriaScript,
    g_abSpellDiffindoScript,
    g_abSpellIncendioUnoScript,
    g_abSpellIncendioDuoScript,
    g_abSpellIncendioTriaScript,
    g_abSpellVerdimilliousTriaScript,
    g_abSpecialMonsterPoisonBiteScript,
    g_abSpellWingardiumLeviosaScript,
    g_abSpellSpongifyScript,
    g_abSpellGlaciusUnoScript,
    g_abSpellGlaciusDuoScript,
    g_abSpellFumosDuoScript,
    g_abSpellPetrificusTotalusUnoScript,
    g_abSpellPetrificusTotalusDuoScript,
    g_abSpecialHarryGirdingAllScript,
    g_abEffect36Script,
    g_abSpecialHarryReviveScript,
    g_abSpellInformusScript,
    g_abSpecialHarrySonorousCharmScript,
    g_abSpecialHarryReplenishSpScript,
    g_abSpecialHarryBludgersScript,
    g_abSpecialHarryPoisonAntidoteScript,
    g_abSpecialHarryUltimateMpScript,
    g_abSpecialRonStinkPelletScript,
    g_abSpecialRonStinkPellet2Script,
    g_abSpecialRonWizardCrackerScript,
    g_abSpecialHarrySnitchScript,
    g_abSpecialHarryReplenishMpScript,
    g_abSpecialHermioneBeMoreCarefulScript,
    g_abSpecialHermioneGoodStudyHabitsScript,
    g_abSpecialHermioneProperWandTechniqueScript,
    g_abSpecialHarryRemoveJinxScript,
    g_abSpecialHarryRepariforsScript,
    g_abSpecialMonsterCrabbeAttackScript,
    g_abSpecialMonsterGoyleAttackScript,
    g_abSpecialMonsterDracoAttackScript,
    g_abSpecialMonsterHinkypunkParalyzeScript,
    g_abSpecialMonsterSalamanderAttackScript,
    g_abSpecialMonsterSkeletonParalyzeScript,
    g_abSpecialMonsterParalyzingBlowScript,
    g_abSpecialMonsterWhompingWillowAttackScript,
    g_abEffect62Script,
    g_abEffect63Script,
    g_abEffect64Script,
};
