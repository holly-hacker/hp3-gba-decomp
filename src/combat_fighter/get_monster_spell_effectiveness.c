#include "types.h"
#include "combat_fighter.h"

// Petrificus Totalus and Spongify always work fully; any other row reads 0.
s32 GetMonsterSpellEffectiveness(s32 monsterIndex, s32 spell)
{
    switch (spell)
    {
    case FolioSpellFlipendo:
        return MonsterTable[monsterIndex].abEffectiveness[0];
    case FolioSpellVerdimillious:
        return MonsterTable[monsterIndex].abEffectiveness[2];
    case FolioSpellIncendio:
        return MonsterTable[monsterIndex].abEffectiveness[1];
    case FolioSpellWingardiumLeviosa:
        return MonsterTable[monsterIndex].abEffectiveness[3];
    case FolioSpellPetrificusTotalus:
    case FolioSpellSpongify:
        return 100;
    case FolioSpellDiffindo:
        return MonsterTable[monsterIndex].abEffectiveness[5];
    case FolioSpellGlacius:
        return MonsterTable[monsterIndex].abEffectiveness[4];
    default:
        return 0;
    }
}
