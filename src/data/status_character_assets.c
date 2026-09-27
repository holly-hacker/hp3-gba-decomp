#include "types.h"
#include "object.h"
#include "gen/StatusCharacters.h"

// Status/equip screen character rotations, indexed by sub_0803A030.
const ObjectAssetRecord g_aStatusCharacterAssets[3] = {
    { (void *)gStatusCharacter001Tiles, (void *)gStatusCharacter001Frames, (void *)gStatusCharacter001Palette, 0 }, // Harry
    { (void *)gStatusCharacter002Tiles, (void *)gStatusCharacter002Frames, (void *)gStatusCharacter002Palette, 0 }, // Hermione
    { (void *)gStatusCharacter003Tiles, (void *)gStatusCharacter003Frames, (void *)gStatusCharacter003Palette, 0 }, // Ron
};
