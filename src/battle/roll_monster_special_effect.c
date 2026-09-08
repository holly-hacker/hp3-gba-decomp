#include "types.h"
#include "battle.h"
#include "mt19937.h"

// Rolls a monster's MonsterTable special effect: 100% fires unconditionally,
// anything lower fires only on a hit. Success runs the effect script, then
// stamps Informus as a harmless animation placeholder.
void RollMonsterSpecialEffect(s32 monsterIndex, s32 targetFighterIndex, s32 damage)
{
    // Split base load: folding it into the row address emits ldr after the scale.
    const MonsterTableRow *table = MonsterTable;
    const MonsterTableRow *monster = &table[monsterIndex];
    // u16: ROM narrows the roll before comparing against the u8 chance.
    u16 roll;

    if (monster->bSpecialChance == 100 || (roll = Mt19937RandMax(99)) < monster->bSpecialChance)
    {
        // Casts + u16 damage reproduce the ROM's outgoing-arg zero-extends.
        TriggerBattleEffect(monster->bSpecialId,
            (u8)(g_pFightState->pFighters[g_pFightState->bActiveFighterIndex].bSlotParam + 3),
            g_pFightState->pFighters[targetFighterIndex].bSlotParam,
            g_pFightState->bActiveFighterIndex, (u8)targetFighterIndex, damage);
        g_pFightState->pFighters[g_pFightState->bActiveFighterIndex].bSpellId = Informus;
    }
}
