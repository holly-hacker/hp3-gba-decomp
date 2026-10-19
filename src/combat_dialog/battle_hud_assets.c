#include "actor.h"
#include "combat_dialog.h"
#include "gen/graphics/battle.h"

// Portrait shown beside a battle message about a party member, by FighterType.
const ActorAssetRecord g_aPartyFaceAssets[4] = {
    { (void *)gBattleFace001Tiles, (void *)gBattleFace001Frames, (void *)gBattleFace001Palette, 0 }, // 0
    { (void *)gBattleFace002Tiles, (void *)gBattleFace002Frames, (void *)gBattleFace002Palette, 0 }, // 1
    { (void *)gBattleFace003Tiles, (void *)gBattleFace003Frames, (void *)gBattleFace003Palette, 0 }, // 2
    { (void *)gBattleFace004Tiles, (void *)gBattleFace004Frames, (void *)gBattleFace004Palette, 0 }, // 3
};

// Portrait shown beside a battle message about a monster, by monster id. Repeated
// entries share one sprite.
const ActorAssetRecord g_aMonsterFaceAssets[68] = {
    { (void *)gBattleFace005Tiles, (void *)gBattleFace005Frames, (void *)gBattleFace005Palette, 0 }, // 0
    { (void *)gBattleFace006Tiles, (void *)gBattleFace006Frames, (void *)gBattleFace006Palette, 0 }, // 1
    { (void *)gBattleFace007Tiles, (void *)gBattleFace007Frames, (void *)gBattleFace007Palette, 0 }, // 2
    { (void *)gBattleFace008Tiles, (void *)gBattleFace008Frames, (void *)gBattleFace008Palette, 0 }, // 3
    { (void *)gBattleFace009Tiles, (void *)gBattleFace009Frames, (void *)gBattleFace009Palette, 0 }, // 4
    { (void *)gBattleFace010Tiles, (void *)gBattleFace010Frames, (void *)gBattleFace010Palette, 0 }, // 5
    { (void *)gBattleFace011Tiles, (void *)gBattleFace011Frames, (void *)gBattleFace011Palette, 0 }, // 6
    { (void *)gBattleFace012Tiles, (void *)gBattleFace012Frames, (void *)gBattleFace012Palette, 0 }, // 7
    { (void *)gBattleFace013Tiles, (void *)gBattleFace013Frames, (void *)gBattleFace013Palette, 0 }, // 8
    { (void *)gBattleFace014Tiles, (void *)gBattleFace014Frames, (void *)gBattleFace014Palette, 0 }, // 9
    { (void *)gBattleFace015Tiles, (void *)gBattleFace015Frames, (void *)gBattleFace015Palette, 0 }, // 10
    { (void *)gBattleFace016Tiles, (void *)gBattleFace016Frames, (void *)gBattleFace016Palette, 0 }, // 11
    { (void *)gBattleFace017Tiles, (void *)gBattleFace017Frames, (void *)gBattleFace017Palette, 0 }, // 12
    { (void *)gBattleFace018Tiles, (void *)gBattleFace018Frames, (void *)gBattleFace018Palette, 0 }, // 13
    { (void *)gBattleFace019Tiles, (void *)gBattleFace019Frames, (void *)gBattleFace019Palette, 0 }, // 14
    { (void *)gBattleFace020Tiles, (void *)gBattleFace020Frames, (void *)gBattleFace020Palette, 0 }, // 15
    { (void *)gBattleFace021Tiles, (void *)gBattleFace021Frames, (void *)gBattleFace021Palette, 0 }, // 16
    { (void *)gBattleFace022Tiles, (void *)gBattleFace022Frames, (void *)gBattleFace022Palette, 0 }, // 17
    { (void *)gBattleFace023Tiles, (void *)gBattleFace023Frames, (void *)gBattleFace023Palette, 0 }, // 18
    { (void *)gBattleFace024Tiles, (void *)gBattleFace024Frames, (void *)gBattleFace024Palette, 0 }, // 19
    { (void *)gBattleFace025Tiles, (void *)gBattleFace025Frames, (void *)gBattleFace025Palette, 0 }, // 20
    { (void *)gBattleFace026Tiles, (void *)gBattleFace026Frames, (void *)gBattleFace026Palette, 0 }, // 21
    { (void *)gBattleFace027Tiles, (void *)gBattleFace027Frames, (void *)gBattleFace027Palette, 0 }, // 22
    { (void *)gBattleFace028Tiles, (void *)gBattleFace028Frames, (void *)gBattleFace028Palette, 0 }, // 23
    { (void *)gBattleFace029Tiles, (void *)gBattleFace029Frames, (void *)gBattleFace029Palette, 0 }, // 24
    { (void *)gBattleFace030Tiles, (void *)gBattleFace030Frames, (void *)gBattleFace030Palette, 0 }, // 25
    { (void *)gBattleFace031Tiles, (void *)gBattleFace031Frames, (void *)gBattleFace031Palette, 0 }, // 26
    { (void *)gBattleFace032Tiles, (void *)gBattleFace032Frames, (void *)gBattleFace032Palette, 0 }, // 27
    { (void *)gBattleFace033Tiles, (void *)gBattleFace033Frames, (void *)gBattleFace033Palette, 0 }, // 28
    { (void *)gBattleFace034Tiles, (void *)gBattleFace034Frames, (void *)gBattleFace034Palette, 0 }, // 29
    { (void *)gBattleFace035Tiles, (void *)gBattleFace035Frames, (void *)gBattleFace035Palette, 0 }, // 30
    { (void *)gBattleFace036Tiles, (void *)gBattleFace036Frames, (void *)gBattleFace036Palette, 0 }, // 31
    { (void *)gBattleFace037Tiles, (void *)gBattleFace037Frames, (void *)gBattleFace037Palette, 0 }, // 32
    { (void *)gBattleFace038Tiles, (void *)gBattleFace038Frames, (void *)gBattleFace038Palette, 0 }, // 33
    { (void *)gBattleFace039Tiles, (void *)gBattleFace039Frames, (void *)gBattleFace039Palette, 0 }, // 34
    { (void *)gBattleFace040Tiles, (void *)gBattleFace040Frames, (void *)gBattleFace040Palette, 0 }, // 35
    { (void *)gBattleFace041Tiles, (void *)gBattleFace041Frames, (void *)gBattleFace041Palette, 0 }, // 36
    { (void *)gBattleFace042Tiles, (void *)gBattleFace042Frames, (void *)gBattleFace042Palette, 0 }, // 37
    { (void *)gBattleFace043Tiles, (void *)gBattleFace043Frames, (void *)gBattleFace043Palette, 0 }, // 38
    { (void *)gBattleFace044Tiles, (void *)gBattleFace044Frames, (void *)gBattleFace044Palette, 0 }, // 39
    { (void *)gBattleFace045Tiles, (void *)gBattleFace045Frames, (void *)gBattleFace045Palette, 0 }, // 40
    { (void *)gBattleFace046Tiles, (void *)gBattleFace046Frames, (void *)gBattleFace046Palette, 0 }, // 41
    { (void *)gBattleFace047Tiles, (void *)gBattleFace047Frames, (void *)gBattleFace047Palette, 0 }, // 42
    { (void *)gBattleFace048Tiles, (void *)gBattleFace048Frames, (void *)gBattleFace048Palette, 0 }, // 43
    { (void *)gBattleFace049Tiles, (void *)gBattleFace049Frames, (void *)gBattleFace049Palette, 0 }, // 44
    { (void *)gBattleFace050Tiles, (void *)gBattleFace050Frames, (void *)gBattleFace050Palette, 0 }, // 45
    { (void *)gBattleFace051Tiles, (void *)gBattleFace051Frames, (void *)gBattleFace051Palette, 0 }, // 46
    { (void *)gBattleFace052Tiles, (void *)gBattleFace052Frames, (void *)gBattleFace052Palette, 0 }, // 47
    { (void *)gBattleFace053Tiles, (void *)gBattleFace053Frames, (void *)gBattleFace053Palette, 0 }, // 48
    { (void *)gBattleFace054Tiles, (void *)gBattleFace054Frames, (void *)gBattleFace054Palette, 0 }, // 49
    { (void *)gBattleFace055Tiles, (void *)gBattleFace055Frames, (void *)gBattleFace055Palette, 0 }, // 50
    { (void *)gBattleFace056Tiles, (void *)gBattleFace056Frames, (void *)gBattleFace056Palette, 0 }, // 51
    { (void *)gBattleFace057Tiles, (void *)gBattleFace057Frames, (void *)gBattleFace057Palette, 0 }, // 52
    { (void *)gBattleFace058Tiles, (void *)gBattleFace058Frames, (void *)gBattleFace058Palette, 0 }, // 53
    { (void *)gBattleFace059Tiles, (void *)gBattleFace059Frames, (void *)gBattleFace059Palette, 0 }, // 54
    { (void *)gBattleFace060Tiles, (void *)gBattleFace060Frames, (void *)gBattleFace060Palette, 0 }, // 55
    { (void *)gBattleFace061Tiles, (void *)gBattleFace061Frames, (void *)gBattleFace061Palette, 0 }, // 56
    { (void *)gBattleFace062Tiles, (void *)gBattleFace062Frames, (void *)gBattleFace062Palette, 0 }, // 57
    { (void *)gBattleFace063Tiles, (void *)gBattleFace063Frames, (void *)gBattleFace063Palette, 0 }, // 58
    { (void *)gBattleFace064Tiles, (void *)gBattleFace064Frames, (void *)gBattleFace064Palette, 0 }, // 59
    { (void *)gBattleFace065Tiles, (void *)gBattleFace065Frames, (void *)gBattleFace065Palette, 0 }, // 60
    { (void *)gBattleFace066Tiles, (void *)gBattleFace066Frames, (void *)gBattleFace066Palette, 0 }, // 61
    { (void *)gBattleFace067Tiles, (void *)gBattleFace067Frames, (void *)gBattleFace067Palette, 0 }, // 62
    { (void *)gBattleFace068Tiles, (void *)gBattleFace068Frames, (void *)gBattleFace068Palette, 0 }, // 63
    { (void *)gBattleFace069Tiles, (void *)gBattleFace069Frames, (void *)gBattleFace069Palette, 0 }, // 64
    { (void *)gBattleFace070Tiles, (void *)gBattleFace070Frames, (void *)gBattleFace070Palette, 0 }, // 65
    { (void *)gBattleFace063Tiles, (void *)gBattleFace063Frames, (void *)gBattleFace063Palette, 0 }, // 66
    { (void *)gBattleFace063Tiles, (void *)gBattleFace063Frames, (void *)gBattleFace063Palette, 0 }, // 67
};

// Battle menu icons; see SetBattleMenuIconState.
const ActorAssetRecord g_aBattleMenuIconAssets[61] = {
    { (void *)gActionIcon001Tiles, (void *)gActionIcon001Frames, (void *)gActionIcon001Palette, 0 }, // 0
    { (void *)gActionIcon002Tiles, (void *)gActionIcon002Frames, (void *)gActionIcon002Palette, 0 }, // 1
    { (void *)gActionIcon003Tiles, (void *)gActionIcon003Frames, (void *)gActionIcon003Palette, 0 }, // 2
    { (void *)gActionIcon004Tiles, (void *)gActionIcon004Frames, (void *)gActionIcon004Palette, 0 }, // 3
    { (void *)gActionIcon005Tiles, (void *)gActionIcon005Frames, (void *)gActionIcon005Palette, 0 }, // 4
    { (void *)gActionIcon006Tiles, (void *)gActionIcon006Frames, (void *)gActionIcon006Palette, 0 }, // 5
    { (void *)gActionIcon007Tiles, (void *)gActionIcon007Frames, (void *)gActionIcon007Palette, 0 }, // 6
    { (void *)gActionIcon008Tiles, (void *)gActionIcon008Frames, (void *)gActionIcon008Palette, 0 }, // 7
    { (void *)gActionIcon009Tiles, (void *)gActionIcon009Frames, (void *)gActionIcon009Palette, 0 }, // 8
    { (void *)gActionIcon010Tiles, (void *)gActionIcon010Frames, (void *)gActionIcon010Palette, 0 }, // 9
    { (void *)gActionIcon003Tiles, (void *)gActionIcon003Frames, (void *)gActionIcon003Palette, 0 }, // 10
    { (void *)gActionIcon011Tiles, (void *)gActionIcon011Frames, (void *)gActionIcon011Palette, 0 }, // 11
    { (void *)gActionIcon012Tiles, (void *)gActionIcon012Frames, (void *)gActionIcon012Palette, 0 }, // 12
    { (void *)gActionIcon013Tiles, (void *)gActionIcon013Frames, (void *)gActionIcon013Palette, 0 }, // 13
    { (void *)gActionIcon014Tiles, (void *)gActionIcon014Frames, (void *)gActionIcon014Palette, 0 }, // 14
    { (void *)gActionIcon015Tiles, (void *)gActionIcon015Frames, (void *)gActionIcon015Palette, 0 }, // 15
    { (void *)gActionIcon016Tiles, (void *)gActionIcon016Frames, (void *)gActionIcon016Palette, 0 }, // 16
    { (void *)gActionIcon017Tiles, (void *)gActionIcon017Frames, (void *)gActionIcon017Palette, 0 }, // 17
    { (void *)gActionIcon018Tiles, (void *)gActionIcon018Frames, (void *)gActionIcon018Palette, 0 }, // 18
    { (void *)gActionIcon019Tiles, (void *)gActionIcon019Frames, (void *)gActionIcon019Palette, 0 }, // 19
    { (void *)gActionIcon020Tiles, (void *)gActionIcon020Frames, (void *)gActionIcon020Palette, 0 }, // 20
    { (void *)gActionIcon021Tiles, (void *)gActionIcon021Frames, (void *)gActionIcon021Palette, 0 }, // 21
    { (void *)gActionIcon022Tiles, (void *)gActionIcon022Frames, (void *)gActionIcon022Palette, 0 }, // 22
    { (void *)gActionIcon023Tiles, (void *)gActionIcon023Frames, (void *)gActionIcon023Palette, 0 }, // 23
    { (void *)gActionIcon024Tiles, (void *)gActionIcon024Frames, (void *)gActionIcon024Palette, 0 }, // 24
    { (void *)gActionIcon025Tiles, (void *)gActionIcon025Frames, (void *)gActionIcon025Palette, 0 }, // 25
    { (void *)gActionIcon026Tiles, (void *)gActionIcon026Frames, (void *)gActionIcon026Palette, 0 }, // 26
    { (void *)gActionIcon027Tiles, (void *)gActionIcon027Frames, (void *)gActionIcon027Palette, 0 }, // 27
    { (void *)gActionIcon028Tiles, (void *)gActionIcon028Frames, (void *)gActionIcon028Palette, 0 }, // 28
    { (void *)gActionIcon029Tiles, (void *)gActionIcon029Frames, (void *)gActionIcon029Palette, 0 }, // 29
    { (void *)gActionIcon030Tiles, (void *)gActionIcon030Frames, (void *)gActionIcon030Palette, 0 }, // 30
    { (void *)gActionIcon031Tiles, (void *)gActionIcon031Frames, (void *)gActionIcon031Palette, 0 }, // 31
    { (void *)gActionIcon032Tiles, (void *)gActionIcon032Frames, (void *)gActionIcon032Palette, 0 }, // 32
    { (void *)gActionIcon033Tiles, (void *)gActionIcon033Frames, (void *)gActionIcon033Palette, 0 }, // 33
    { (void *)gActionIcon003Tiles, (void *)gActionIcon003Frames, (void *)gActionIcon003Palette, 0 }, // 34
    { (void *)gActionIcon003Tiles, (void *)gActionIcon003Frames, (void *)gActionIcon003Palette, 0 }, // 35
    { (void *)gActionIcon003Tiles, (void *)gActionIcon003Frames, (void *)gActionIcon003Palette, 0 }, // 36
    { (void *)gActionIcon034Tiles, (void *)gActionIcon034Frames, (void *)gActionIcon034Palette, 0 }, // 37
    { (void *)gActionIcon035Tiles, (void *)gActionIcon035Frames, (void *)gActionIcon035Palette, 0 }, // 38
    { (void *)gActionIcon036Tiles, (void *)gActionIcon036Frames, (void *)gActionIcon036Palette, 0 }, // 39
    { (void *)gActionIcon012Tiles, (void *)gActionIcon012Frames, (void *)gActionIcon012Palette, 0 }, // 40
    { (void *)gActionIcon012Tiles, (void *)gActionIcon012Frames, (void *)gActionIcon012Palette, 0 }, // 41
    { (void *)gActionIcon012Tiles, (void *)gActionIcon012Frames, (void *)gActionIcon012Palette, 0 }, // 42
    { (void *)gActionIcon037Tiles, (void *)gActionIcon037Frames, (void *)gActionIcon037Palette, 0 }, // 43
    { (void *)gActionIcon038Tiles, (void *)gActionIcon038Frames, (void *)gActionIcon038Palette, 0 }, // 44
    { (void *)gActionIcon039Tiles, (void *)gActionIcon039Frames, (void *)gActionIcon039Palette, 0 }, // 45
    { (void *)gActionIcon014Tiles, (void *)gActionIcon014Frames, (void *)gActionIcon014Palette, 0 }, // 46
    { (void *)gActionIcon014Tiles, (void *)gActionIcon014Frames, (void *)gActionIcon014Palette, 0 }, // 47
    { (void *)gActionIcon014Tiles, (void *)gActionIcon014Frames, (void *)gActionIcon014Palette, 0 }, // 48
    { (void *)gActionIcon015Tiles, (void *)gActionIcon015Frames, (void *)gActionIcon015Palette, 0 }, // 49
    { (void *)gActionIcon015Tiles, (void *)gActionIcon015Frames, (void *)gActionIcon015Palette, 0 }, // 50
    { (void *)gActionIcon015Tiles, (void *)gActionIcon015Frames, (void *)gActionIcon015Palette, 0 }, // 51
    { (void *)gActionIcon016Tiles, (void *)gActionIcon016Frames, (void *)gActionIcon016Palette, 0 }, // 52
    { (void *)gActionIcon040Tiles, (void *)gActionIcon040Frames, (void *)gActionIcon040Palette, 0 }, // 53
    { (void *)gActionIcon016Tiles, (void *)gActionIcon016Frames, (void *)gActionIcon016Palette, 0 }, // 54
    { (void *)gActionIcon041Tiles, (void *)gActionIcon041Frames, (void *)gActionIcon041Palette, 0 }, // 55
    { (void *)gActionIcon042Tiles, (void *)gActionIcon042Frames, (void *)gActionIcon042Palette, 0 }, // 56
    { (void *)gActionIcon042Tiles, (void *)gActionIcon042Frames, (void *)gActionIcon042Palette, 0 }, // 57
    { (void *)gActionIcon018Tiles, (void *)gActionIcon018Frames, (void *)gActionIcon018Palette, 0 }, // 58
    { (void *)gActionIcon018Tiles, (void *)gActionIcon018Frames, (void *)gActionIcon018Palette, 0 }, // 59
    { (void *)gActionIcon018Tiles, (void *)gActionIcon018Frames, (void *)gActionIcon018Palette, 0 }, // 60
};
