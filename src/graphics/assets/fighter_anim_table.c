#include "types.h"
#include "battle/battle.h"
#include "gen/graphics/battle.h"

// One row of ten sprite records per FighterType. SetPlayerObjectAnim selects
// a record by animation state; record 0 is the live sprite, 6 and 7 hold the
// windup flash palettes, and 8 is the fainted sprite.
const FighterAnimRow g_aFighterAnimTable[4] = {
    { { // Harry
        { (void *)gFighter001Tiles, (void *)gFighter001Frames, (void *)gFighter001Palette, 0 },
        { (void *)gFighter002Tiles, (void *)gFighter002Frames, (void *)gFighter002Palette, 0 },
        { (void *)gFighter003Tiles, (void *)gFighter003Frames, (void *)gFighter003Palette, 0 },
        { (void *)gFighter004Tiles, (void *)gFighter004Frames, (void *)gFighter004Palette, 0 },
        { (void *)gFighter005Tiles, (void *)gFighter005Frames, (void *)gFighter005Palette, 0 },
        { (void *)gFighter005Tiles, (void *)gFighter005Frames, (void *)gFighter005Palette, 0 },
        { (void *)gFighter006Tiles, (void *)gFighter006Frames, (void *)gFighter006Palette, 0 },
        { (void *)gFighter007Tiles, (void *)gFighter007Frames, (void *)gFighter007Palette, 0 },
        { (void *)gFighter008Tiles, (void *)gFighter008Frames, (void *)gFighter008Palette, 0 },
        { (void *)gFighter009Tiles, (void *)gFighter009Frames, (void *)gFighter009Palette, 0 },
    } },
    { { // Hermione
        { (void *)gFighter010Tiles, (void *)gFighter010Frames, (void *)gFighter010Palette, 0 },
        { (void *)gFighter011Tiles, (void *)gFighter011Frames, (void *)gFighter011Palette, 0 },
        { (void *)gFighter012Tiles, (void *)gFighter012Frames, (void *)gFighter012Palette, 0 },
        { (void *)gFighter013Tiles, (void *)gFighter013Frames, (void *)gFighter013Palette, 0 },
        { (void *)gFighter014Tiles, (void *)gFighter014Frames, (void *)gFighter014Palette, 0 },
        { (void *)gFighter014Tiles, (void *)gFighter014Frames, (void *)gFighter014Palette, 0 },
        { (void *)gFighter015Tiles, (void *)gFighter015Frames, (void *)gFighter015Palette, 0 },
        { (void *)gFighter016Tiles, (void *)gFighter016Frames, (void *)gFighter016Palette, 0 },
        { (void *)gFighter017Tiles, (void *)gFighter017Frames, (void *)gFighter017Palette, 0 },
        { (void *)gFighter009Tiles, (void *)gFighter009Frames, (void *)gFighter009Palette, 0 },
    } },
    { { // Ron
        { (void *)gFighter018Tiles, (void *)gFighter018Frames, (void *)gFighter018Palette, 0 },
        { (void *)gFighter019Tiles, (void *)gFighter019Frames, (void *)gFighter019Palette, 0 },
        { (void *)gFighter020Tiles, (void *)gFighter020Frames, (void *)gFighter020Palette, 0 },
        { (void *)gFighter021Tiles, (void *)gFighter021Frames, (void *)gFighter021Palette, 0 },
        { (void *)gFighter022Tiles, (void *)gFighter022Frames, (void *)gFighter022Palette, 0 },
        { (void *)gFighter022Tiles, (void *)gFighter022Frames, (void *)gFighter022Palette, 0 },
        { (void *)gFighter023Tiles, (void *)gFighter023Frames, (void *)gFighter023Palette, 0 },
        { (void *)gFighter024Tiles, (void *)gFighter024Frames, (void *)gFighter024Palette, 0 },
        { (void *)gFighter025Tiles, (void *)gFighter025Frames, (void *)gFighter025Palette, 0 },
        { (void *)gFighter026Tiles, (void *)gFighter026Frames, (void *)gFighter026Palette, 0 },
    } },
    { { // Buckbeak
        { (void *)gFighter027Tiles, (void *)gFighter027Frames, (void *)gFighter027Palette, 0 },
        { (void *)gFighter028Tiles, (void *)gFighter028Frames, (void *)gFighter028Palette, 0 },
        { (void *)gFighter020Tiles, (void *)gFighter020Frames, (void *)gFighter020Palette, 0 },
        { (void *)gFighter021Tiles, (void *)gFighter021Frames, (void *)gFighter021Palette, 0 },
        { (void *)gFighter029Tiles, (void *)gFighter029Frames, (void *)gFighter029Palette, 0 },
        { (void *)gFighter029Tiles, (void *)gFighter029Frames, (void *)gFighter029Palette, 0 },
        { (void *)gFighter027Tiles, (void *)gFighter027Frames, (void *)gFighter030Palette, 0 },
        { (void *)gFighter027Tiles, (void *)gFighter027Frames, (void *)gFighter030Palette, 0 },
        { (void *)gFighter031Tiles, (void *)gFighter031Frames, (void *)gFighter031Palette, 0 },
        { (void *)gFighter026Tiles, (void *)gFighter026Frames, (void *)gFighter026Palette, 0 },
    } },
};
