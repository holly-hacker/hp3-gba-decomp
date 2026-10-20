#include "actor.h"
#include "combat.h"
#include "gen/graphics/overworld.h"
#include "hero.h"

const ActorAssetRecord g_aFieldSpellIconAssets[8] = {
    { (void *)gFieldSpellIconFlipendoTiles, (void *)gFieldSpellIconFlipendoFrames, (void *)gFieldSpellIconFlipendoPalette, 0 },
    { (void *)gFieldSpellIconLumosTiles, (void *)gFieldSpellIconLumosFrames, (void *)gFieldSpellIconLumosPalette, 0 },
    { (void *)gFieldSpellIconReparoTiles, (void *)gFieldSpellIconReparoFrames, (void *)gFieldSpellIconReparoPalette, 0 },
    { (void *)gFieldSpellIconAlohomoraTiles, (void *)gFieldSpellIconAlohomoraFrames, (void *)gFieldSpellIconAlohomoraPalette, 0 },
    { (void *)gFieldSpellIconGlaciusTiles, (void *)gFieldSpellIconGlaciusFrames, (void *)gFieldSpellIconGlaciusPalette, 0 },
    { (void *)gFieldSpellIconSpongifyTiles, (void *)gFieldSpellIconSpongifyFrames, (void *)gFieldSpellIconSpongifyPalette, 0 },
    { (void *)gFieldSpellIconDiffindoTiles, (void *)gFieldSpellIconDiffindoFrames, (void *)gFieldSpellIconDiffindoPalette, 0 },
    { (void *)gFieldSpellIconWingardiumLeviosaTiles, (void *)gFieldSpellIconWingardiumLeviosaFrames, (void *)gFieldSpellIconWingardiumLeviosaPalette, 0 },
};

const FieldSpellEntry g_aFieldSpells[FIELD_SPELL_COUNT] = {
    { FieldSpellFlipendo,  Harry,    0 },
    { FieldSpellLumos,     Harry,    0 },
    { FieldSpellDiffindo,  Harry,    5 },
    { FieldSpellFlipendo,  Hermione, 0 },
    { FieldSpellReparo,    Hermione, 0 },
    { FieldSpellGlacius,   Hermione, 6 },
    { FieldSpellFlipendo,  Ron,      0 },
    { FieldSpellAlohomora, Ron,      0 },
    { FieldSpellSpongify,  Ron,      5 },
};
