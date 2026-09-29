#include "types.h"
#include "battle/battle.h"
#include "gen/MonsterBattleSprites.h"
#include "gen/MonsterOverworldSprites.h"
#include "gen/MonsterPalettes.h"
#include "gen/BattleIcons.h"
#include "gen/AllyHeads.h"
#include "gen/BattleHudItems.h"

// Monster sprite records and the battle overlay records after them; see
// docs/formats/folio_bruti.md ("Monster graphics table"). Content is
// identical between the US and JP ROMs apart from addresses.

const MonsterGfxRow g_pMonsterGraphicsTable[69] = {
    { // 0: Ruby Fire Crab
        { (void *)gMonsterBattle001Tiles, (void *)gMonsterBattle001Frames, (void *)gMonsterBattle001Palette, 0 },
        { (void *)gMonsterOverworld001Tiles, (void *)gMonsterOverworld001Frames, (void *)gMonsterOverworld001Palette, 0 },
    },
    { // 1: Emerald Fire Crab
        { (void *)gMonsterBattle001Tiles, (void *)gMonsterBattle001Frames, (void *)gMonsterPalette001Palette, 0 },
        { (void *)gMonsterOverworld001Tiles, (void *)gMonsterOverworld001Frames, (void *)gMonsterPalette001Palette, 0 },
    },
    { // 2: Sapphire Fire Crab
        { (void *)gMonsterBattle001Tiles, (void *)gMonsterBattle001Frames, (void *)gMonsterPalette002Palette, 0 },
        { (void *)gMonsterOverworld001Tiles, (void *)gMonsterOverworld001Frames, (void *)gMonsterPalette002Palette, 0 },
    },
    { // 3: Cornish Pixie
        { (void *)gMonsterBattle002Tiles, (void *)gMonsterBattle002Frames, (void *)gMonsterBattle002Palette, 0 },
        { (void *)gMonsterOverworld002Tiles, (void *)gMonsterOverworld002Frames, (void *)gMonsterOverworld002Palette, 0 },
    },
    { // 4: Rat
        { (void *)gMonsterBattle003Tiles, (void *)gMonsterBattle003Frames, (void *)gMonsterPalette003Palette, 0 },
        { (void *)gMonsterOverworld003Tiles, (void *)gMonsterOverworld003Frames, (void *)gMonsterPalette003Palette, 0 },
    },
    { // 5: Albino Rat
        { (void *)gMonsterBattle003Tiles, (void *)gMonsterBattle003Frames, (void *)gMonsterPalette004Palette, 0 },
        { (void *)gMonsterOverworld003Tiles, (void *)gMonsterOverworld003Frames, (void *)gMonsterPalette004Palette, 0 },
    },
    { // 6: Plague Rat
        { (void *)gMonsterBattle003Tiles, (void *)gMonsterBattle003Frames, (void *)gMonsterPalette005Palette, 0 },
        { (void *)gMonsterOverworld003Tiles, (void *)gMonsterOverworld003Frames, (void *)gMonsterPalette005Palette, 0 },
    },
    { // 7: Clabbert
        { (void *)gMonsterBattle004Tiles, (void *)gMonsterBattle004Frames, (void *)gMonsterBattle004Palette, 0 },
        { (void *)gMonsterOverworld004Tiles, (void *)gMonsterOverworld004Frames, (void *)gMonsterOverworld004Palette, 0 },
    },
    { // 8: Suit of Armor (Footman)
        { (void *)gMonsterBattle005Tiles, (void *)gMonsterBattle005Frames, (void *)gMonsterPalette006Palette, 0 },
        { (void *)gMonsterOverworld005Tiles, (void *)gMonsterOverworld005Frames, (void *)gMonsterPalette006Palette, 0 },
    },
    { // 9: Suit of Armor (Cavalier)
        { (void *)gMonsterBattle005Tiles, (void *)gMonsterBattle005Frames, (void *)gMonsterPalette007Palette, 0 },
        { (void *)gMonsterOverworld005Tiles, (void *)gMonsterOverworld005Frames, (void *)gMonsterPalette007Palette, 0 },
    },
    { // 10: Suit of Armor (Paladin)
        { (void *)gMonsterBattle006Tiles, (void *)gMonsterBattle006Frames, (void *)gMonsterPalette008Palette, 0 },
        { (void *)gMonsterOverworld006Tiles, (void *)gMonsterOverworld006Frames, (void *)gMonsterPalette008Palette, 0 },
    },
    { // 11: Suit of Armor (Squire)
        { (void *)gMonsterBattle006Tiles, (void *)gMonsterBattle006Frames, (void *)gMonsterPalette009Palette, 0 },
        { (void *)gMonsterOverworld006Tiles, (void *)gMonsterOverworld006Frames, (void *)gMonsterPalette009Palette, 0 },
    },
    { // 12: Suit of Armor (Swordsman)
        { (void *)gMonsterBattle005Tiles, (void *)gMonsterBattle005Frames, (void *)gMonsterPalette010Palette, 0 },
        { (void *)gMonsterOverworld005Tiles, (void *)gMonsterOverworld005Frames, (void *)gMonsterPalette010Palette, 0 },
    },
    { // 13: Suit of Armor (Crusader)
        { (void *)gMonsterBattle006Tiles, (void *)gMonsterBattle006Frames, (void *)gMonsterPalette011Palette, 0 },
        { (void *)gMonsterOverworld006Tiles, (void *)gMonsterOverworld006Frames, (void *)gMonsterPalette011Palette, 0 },
    },
    { // 14: Suit of Armor (Knight)
        { (void *)gMonsterBattle006Tiles, (void *)gMonsterBattle006Frames, (void *)gMonsterPalette012Palette, 0 },
        { (void *)gMonsterOverworld006Tiles, (void *)gMonsterOverworld006Frames, (void *)gMonsterPalette012Palette, 0 },
    },
    { // 15: Funnelweb Spider
        { (void *)gMonsterBattle007Tiles, (void *)gMonsterBattle007Frames, (void *)gMonsterBattle007Palette, 0 },
        { (void *)gMonsterOverworld007Tiles, (void *)gMonsterOverworld007Frames, (void *)gMonsterOverworld007Palette, 0 },
    },
    { // 16: Brown Recluse Spider
        { (void *)gMonsterBattle007Tiles, (void *)gMonsterBattle007Frames, (void *)gMonsterPalette013Palette, 0 },
        { (void *)gMonsterOverworld007Tiles, (void *)gMonsterOverworld007Frames, (void *)gMonsterPalette013Palette, 0 },
    },
    { // 17: Large Spider
        { (void *)gMonsterBattle007Tiles, (void *)gMonsterBattle007Frames, (void *)gMonsterPalette014Palette, 0 },
        { (void *)gMonsterOverworld007Tiles, (void *)gMonsterOverworld007Frames, (void *)gMonsterPalette014Palette, 0 },
    },
    { // 18: Redback Spider
        { (void *)gMonsterBattle007Tiles, (void *)gMonsterBattle007Frames, (void *)gMonsterPalette015Palette, 0 },
        { (void *)gMonsterOverworld007Tiles, (void *)gMonsterOverworld007Frames, (void *)gMonsterPalette015Palette, 0 },
    },
    { // 19: Giant Spider
        { (void *)gMonsterBattle008Tiles, (void *)gMonsterBattle008Frames, (void *)gMonsterBattle008Palette, 0 },
        { (void *)gMonsterOverworld008Tiles, (void *)gMonsterOverworld008Frames, (void *)gMonsterOverworld008Palette, 0 },
    },
    { // 20: Cocoon Spider
        { (void *)gMonsterBattle008Tiles, (void *)gMonsterBattle008Frames, (void *)gMonsterPalette016Palette, 0 },
        { (void *)gMonsterOverworld008Tiles, (void *)gMonsterOverworld008Frames, (void *)gMonsterPalette016Palette, 0 },
    },
    { // 21: Whitetail Spider
        { (void *)gMonsterBattle008Tiles, (void *)gMonsterBattle008Frames, (void *)gMonsterPalette017Palette, 0 },
        { (void *)gMonsterOverworld008Tiles, (void *)gMonsterOverworld008Frames, (void *)gMonsterPalette017Palette, 0 },
    },
    { // 22: Flobberworm
        { (void *)gMonsterBattle009Tiles, (void *)gMonsterBattle009Frames, (void *)gMonsterBattle009Palette, 0 },
        { (void *)gMonsterOverworld009Tiles, (void *)gMonsterOverworld009Frames, (void *)gMonsterOverworld009Palette, 0 },
    },
    { // 23: Snail
        { (void *)gMonsterBattle010Tiles, (void *)gMonsterBattle010Frames, (void *)gMonsterPalette018Palette, 0 },
        { (void *)gMonsterOverworld010Tiles, (void *)gMonsterOverworld010Frames, (void *)gMonsterPalette018Palette, 0 },
    },
    { // 24: Large Orange Snail
        { (void *)gMonsterBattle010Tiles, (void *)gMonsterBattle010Frames, (void *)gMonsterPalette019Palette, 0 },
        { (void *)gMonsterOverworld010Tiles, (void *)gMonsterOverworld010Frames, (void *)gMonsterPalette019Palette, 0 },
    },
    { // 25: Flailtail Snail
        { (void *)gMonsterBattle010Tiles, (void *)gMonsterBattle010Frames, (void *)gMonsterPalette020Palette, 0 },
        { (void *)gMonsterOverworld010Tiles, (void *)gMonsterOverworld010Frames, (void *)gMonsterPalette020Palette, 0 },
    },
    { // 26: Bat
        { (void *)gMonsterBattle011Tiles, (void *)gMonsterBattle011Frames, (void *)gMonsterBattle011Palette, 0 },
        { (void *)gMonsterOverworld011Tiles, (void *)gMonsterOverworld011Frames, (void *)gMonsterOverworld011Palette, 0 },
    },
    { // 27: Fruitbat
        { (void *)gMonsterBattle011Tiles, (void *)gMonsterBattle011Frames, (void *)gMonsterPalette021Palette, 0 },
        { (void *)gMonsterOverworld011Tiles, (void *)gMonsterOverworld011Frames, (void *)gMonsterPalette021Palette, 0 },
    },
    { // 28: Mortis Bat
        { (void *)gMonsterBattle011Tiles, (void *)gMonsterBattle011Frames, (void *)gMonsterPalette022Palette, 0 },
        { (void *)gMonsterOverworld011Tiles, (void *)gMonsterOverworld011Frames, (void *)gMonsterPalette022Palette, 0 },
    },
    { // 29: Dragonfly
        { (void *)gMonsterBattle012Tiles, (void *)gMonsterBattle012Frames, (void *)gMonsterBattle012Palette, 0 },
        { (void *)gMonsterOverworld012Tiles, (void *)gMonsterOverworld012Frames, (void *)gMonsterOverworld012Palette, 0 },
    },
    { // 30: Imperial Dragonfly
        { (void *)gMonsterBattle012Tiles, (void *)gMonsterBattle012Frames, (void *)gMonsterPalette023Palette, 0 },
        { (void *)gMonsterOverworld012Tiles, (void *)gMonsterOverworld012Frames, (void *)gMonsterPalette023Palette, 0 },
    },
    { // 31: Horklump
        { (void *)gMonsterBattle013Tiles, (void *)gMonsterBattle013Frames, (void *)gMonsterBattle013Palette, 0 },
        { (void *)gMonsterOverworld013Tiles, (void *)gMonsterOverworld013Frames, (void *)gMonsterOverworld013Palette, 0 },
    },
    { // 32: Snake
        { (void *)gMonsterBattle014Tiles, (void *)gMonsterBattle014Frames, (void *)gMonsterPalette024Palette, 0 },
        { (void *)gMonsterOverworld014Tiles, (void *)gMonsterOverworld014Frames, (void *)gMonsterPalette024Palette, 0 },
    },
    { // 33: Spitting Snake
        { (void *)gMonsterBattle014Tiles, (void *)gMonsterBattle014Frames, (void *)gMonsterPalette025Palette, 0 },
        { (void *)gMonsterOverworld014Tiles, (void *)gMonsterOverworld014Frames, (void *)gMonsterPalette025Palette, 0 },
    },
    { // 34: Wasp
        { (void *)gMonsterBattle015Tiles, (void *)gMonsterBattle015Frames, (void *)gMonsterPalette026Palette, 0 },
        { (void *)gMonsterOverworld015Tiles, (void *)gMonsterOverworld015Frames, (void *)gMonsterPalette026Palette, 0 },
    },
    { // 35: Tarantula Hawk Wasp
        { (void *)gMonsterBattle015Tiles, (void *)gMonsterBattle015Frames, (void *)gMonsterPalette027Palette, 0 },
        { (void *)gMonsterOverworld015Tiles, (void *)gMonsterOverworld015Frames, (void *)gMonsterPalette027Palette, 0 },
    },
    { // 36: Bowtruckle
        { (void *)gMonsterBattle016Tiles, (void *)gMonsterBattle016Frames, (void *)gMonsterPalette028Palette, 0 },
        { (void *)gMonsterOverworld016Tiles, (void *)gMonsterOverworld016Frames, (void *)gMonsterPalette028Palette, 0 },
    },
    { // 37: Oaken Bowtruckle
        { (void *)gMonsterBattle016Tiles, (void *)gMonsterBattle016Frames, (void *)gMonsterPalette029Palette, 0 },
        { (void *)gMonsterOverworld016Tiles, (void *)gMonsterOverworld016Frames, (void *)gMonsterPalette029Palette, 0 },
    },
    { // 38: Doxy
        { (void *)gMonsterBattle017Tiles, (void *)gMonsterBattle017Frames, (void *)gMonsterPalette030Palette, 0 },
        { (void *)gMonsterOverworld017Tiles, (void *)gMonsterOverworld017Frames, (void *)gMonsterPalette030Palette, 0 },
    },
    { // 39: Doxy Queen
        { (void *)gMonsterBattle017Tiles, (void *)gMonsterBattle017Frames, (void *)gMonsterPalette031Palette, 0 },
        { (void *)gMonsterOverworld017Tiles, (void *)gMonsterOverworld017Frames, (void *)gMonsterPalette031Palette, 0 },
    },
    { // 40: Hinkypunk
        { (void *)gMonsterBattle018Tiles, (void *)gMonsterBattle018Frames, (void *)gMonsterBattle018Palette, 0 },
        { (void *)gMonsterOverworld018Tiles, (void *)gMonsterOverworld018Frames, (void *)gMonsterOverworld018Palette, 0 },
    },
    { // 41: Gytrash
        { (void *)gMonsterBattle019Tiles, (void *)gMonsterBattle019Frames, (void *)gMonsterBattle019Palette, 0 },
        { (void *)gMonsterOverworld019Tiles, (void *)gMonsterOverworld019Frames, (void *)gMonsterOverworld019Palette, 0 },
    },
    { // 42: Grindylow
        { (void *)gMonsterBattle020Tiles, (void *)gMonsterBattle020Frames, (void *)gMonsterBattle020Palette, 0 },
        { (void *)gMonsterOverworld020Tiles, (void *)gMonsterOverworld020Frames, (void *)gMonsterOverworld020Palette, 0 },
    },
    { // 43: Red Cap
        { (void *)gMonsterBattle021Tiles, (void *)gMonsterBattle021Frames, (void *)gMonsterBattle021Palette, 0 },
        { (void *)gMonsterOverworld021Tiles, (void *)gMonsterOverworld021Frames, (void *)gMonsterOverworld021Palette, 0 },
    },
    { // 44: Armored Red Cap
        { (void *)gMonsterBattle022Tiles, (void *)gMonsterBattle022Frames, (void *)gMonsterBattle022Palette, 0 },
        { (void *)gMonsterOverworld022Tiles, (void *)gMonsterOverworld022Frames, (void *)gMonsterOverworld022Palette, 0 },
    },
    { // 45: Salamander
        { (void *)gMonsterBattle023Tiles, (void *)gMonsterBattle023Frames, (void *)gMonsterPalette032Palette, 0 },
        { (void *)gMonsterOverworld023Tiles, (void *)gMonsterOverworld023Frames, (void *)gMonsterPalette033Palette, 0 },
    },
    { // 46: Amazonian Salamander
        { (void *)gMonsterBattle023Tiles, (void *)gMonsterBattle023Frames, (void *)gMonsterPalette033Palette, 0 },
        { (void *)gMonsterOverworld023Tiles, (void *)gMonsterOverworld023Frames, (void *)gMonsterPalette032Palette, 0 },
    },
    { // 47: Peruvian Salamander
        { (void *)gMonsterBattle023Tiles, (void *)gMonsterBattle023Frames, (void *)gMonsterPalette034Palette, 0 },
        { (void *)gMonsterOverworld023Tiles, (void *)gMonsterOverworld023Frames, (void *)gMonsterPalette034Palette, 0 },
    },
    { // 48: Charmed Skeleton
        { (void *)gMonsterBattle024Tiles, (void *)gMonsterBattle024Frames, (void *)gMonsterPalette035Palette, 0 },
        { (void *)gMonsterOverworld024Tiles, (void *)gMonsterOverworld024Frames, (void *)gMonsterPalette035Palette, 0 },
    },
    { // 49: Jinxed Skeleton
        { (void *)gMonsterBattle024Tiles, (void *)gMonsterBattle024Frames, (void *)gMonsterPalette036Palette, 0 },
        { (void *)gMonsterOverworld024Tiles, (void *)gMonsterOverworld024Frames, (void *)gMonsterPalette036Palette, 0 },
    },
    { // 50: Tree Frog
        { (void *)gMonsterBattle025Tiles, (void *)gMonsterBattle025Frames, (void *)gMonsterPalette037Palette, 0 },
        { (void *)gMonsterOverworld025Tiles, (void *)gMonsterOverworld025Frames, (void *)gMonsterPalette037Palette, 0 },
    },
    { // 51: Wide-mouth Toad
        { (void *)gMonsterBattle025Tiles, (void *)gMonsterBattle025Frames, (void *)gMonsterPalette038Palette, 0 },
        { (void *)gMonsterOverworld025Tiles, (void *)gMonsterOverworld025Frames, (void *)gMonsterPalette038Palette, 0 },
    },
    { // 52: Bullfrog
        { (void *)gMonsterBattle025Tiles, (void *)gMonsterBattle025Frames, (void *)gMonsterPalette039Palette, 0 },
        { (void *)gMonsterOverworld025Tiles, (void *)gMonsterOverworld025Frames, (void *)gMonsterPalette039Palette, 0 },
    },
    { // 53: Flesh-eating Slug (not in game, needs to be in file for coders - no need to translate)
        { (void *)gMonsterBattle003Tiles, (void *)gMonsterBattle003Frames, (void *)gMonsterBattle026Palette, 0 },
        { (void *)gMonsterOverworld010Tiles, (void *)gMonsterOverworld010Frames, (void *)gMonsterPalette018Palette, 0 },
    },
    { // 54: Whomping Willow
        { (void *)gMonsterBattle027Tiles, (void *)gMonsterBattle027Frames, (void *)gMonsterBattle027Palette, 0 },
        { (void *)gMonsterOverworld003Tiles, (void *)gMonsterOverworld003Frames, (void *)gMonsterPalette004Palette, 0 },
    },
    { // 55: Forest Troll
        { (void *)gMonsterBattle028Tiles, (void *)gMonsterBattle028Frames, (void *)gMonsterBattle028Palette, 0 },
        { (void *)gMonsterOverworld026Tiles, (void *)gMonsterOverworld026Frames, (void *)gMonsterOverworld026Palette, 0 },
    },
    { // 56: River Troll
        { (void *)gMonsterBattle029Tiles, (void *)gMonsterBattle029Frames, (void *)gMonsterBattle029Palette, 0 },
        { (void *)gMonsterOverworld027Tiles, (void *)gMonsterOverworld027Frames, (void *)gMonsterOverworld027Palette, 0 },
    },
    { // 57: Venemous Tentacula
        { (void *)gMonsterBattle030Tiles, (void *)gMonsterBattle030Frames, (void *)gMonsterBattle030Palette, 0 },
        { (void *)gMonsterOverworld028Tiles, (void *)gMonsterOverworld028Frames, (void *)gMonsterOverworld028Palette, 0 },
    },
    { // 58: 'The Monster Book of Monsters'
        { (void *)gMonsterBattle031Tiles, (void *)gMonsterBattle031Frames, (void *)gMonsterBattle031Palette, 0 },
        { (void *)gMonsterOverworld004Tiles, (void *)gMonsterOverworld004Frames, (void *)gMonsterOverworld004Palette, 0 },
    },
    { // 59: Giant Rat
        { (void *)gMonsterBattle032Tiles, (void *)gMonsterBattle032Frames, (void *)gMonsterBattle032Palette, 0 },
        { (void *)gMonsterOverworld003Tiles, (void *)gMonsterOverworld003Frames, (void *)gMonsterOverworld029Palette, 0 },
    },
    { // 60: Crabbe
        { (void *)gMonsterBattle033Tiles, (void *)gMonsterBattle033Frames, (void *)gMonsterBattle033Palette, 0 },
        { (void *)gMonsterOverworld003Tiles, (void *)gMonsterOverworld003Frames, (void *)gMonsterOverworld029Palette, 0 },
    },
    { // 61: Draco
        { (void *)gMonsterBattle034Tiles, (void *)gMonsterBattle034Frames, (void *)gMonsterBattle034Palette, 0 },
        { (void *)gMonsterOverworld003Tiles, (void *)gMonsterOverworld003Frames, (void *)gMonsterOverworld029Palette, 0 },
    },
    { // 62: Goyle
        { (void *)gMonsterBattle035Tiles, (void *)gMonsterBattle035Frames, (void *)gMonsterBattle035Palette, 0 },
        { (void *)gMonsterOverworld003Tiles, (void *)gMonsterOverworld003Frames, (void *)gMonsterOverworld029Palette, 0 },
    },
    { // 63: Lupin Werewolf
        { (void *)gMonsterBattle036Tiles, (void *)gMonsterBattle036Frames, (void *)gMonsterBattle036Palette, 0 },
        { (void *)gMonsterOverworld003Tiles, (void *)gMonsterOverworld003Frames, (void *)gMonsterPalette040Palette, 0 },
    },
    { // 64: Snake
        { (void *)gMonsterBattle014Tiles, (void *)gMonsterBattle014Frames, (void *)gMonsterPalette024Palette, 0 },
        { (void *)gMonsterOverworld014Tiles, (void *)gMonsterOverworld014Frames, (void *)gMonsterPalette024Palette, 0 },
    },
    { // 65: Brown Recluse Spider
        { (void *)gMonsterBattle007Tiles, (void *)gMonsterBattle007Frames, (void *)gMonsterPalette013Palette, 0 },
        { (void *)gMonsterOverworld007Tiles, (void *)gMonsterOverworld007Frames, (void *)gMonsterPalette013Palette, 0 },
    },
    { // 66: 'The Monster Book of Monsters'
        { (void *)gMonsterBattle031Tiles, (void *)gMonsterBattle031Frames, (void *)gMonsterBattle031Palette, 0 },
        { (void *)gMonsterOverworld004Tiles, (void *)gMonsterOverworld004Frames, (void *)gMonsterOverworld004Palette, 0 },
    },
    { // 67: 'The Monster Book of Monsters'
        { (void *)gMonsterBattle031Tiles, (void *)gMonsterBattle031Frames, (void *)gMonsterBattle031Palette, 0 },
        { (void *)gMonsterOverworld004Tiles, (void *)gMonsterOverworld004Frames, (void *)gMonsterOverworld004Palette, 0 },
    },
    { // 68: Native of Fiji. Has a heavily jeweled shell.
        { (void *)gMonsterBattle031Tiles, (void *)gMonsterBattle031Frames, (void *)gMonsterBattle031Palette, 0 },
        { (void *)gMonsterOverworld004Tiles, (void *)gMonsterOverworld004Frames, (void *)gMonsterOverworld004Palette, 0 },
    },
};

const ObjectAssetRecord g_MonsterShadowGfxRow = { (void *)gBattleIcon001Tiles, (void *)gBattleIcon001Frames, (void *)gBattleIcon001Palette, 0 };

// Indexed by bRosterIndex.
const ObjectAssetRecord g_aEnemyTurnOrderIconAssets[69] = {
    { (void *)gBattleIcon002Tiles, (void *)gBattleIcon002Frames, (void *)gMonsterBattle001Palette, 0 }, // 0: Ruby Fire Crab
    { (void *)gBattleIcon002Tiles, (void *)gBattleIcon002Frames, (void *)gMonsterPalette001Palette, 0 }, // 1: Emerald Fire Crab
    { (void *)gBattleIcon002Tiles, (void *)gBattleIcon002Frames, (void *)gMonsterPalette002Palette, 0 }, // 2: Sapphire Fire Crab
    { (void *)gBattleIcon003Tiles, (void *)gBattleIcon003Frames, (void *)gMonsterBattle002Palette, 0 }, // 3: Cornish Pixie
    { (void *)gBattleIcon004Tiles, (void *)gBattleIcon004Frames, (void *)gMonsterPalette003Palette, 0 }, // 4: Rat
    { (void *)gBattleIcon004Tiles, (void *)gBattleIcon004Frames, (void *)gMonsterPalette004Palette, 0 }, // 5: Albino Rat
    { (void *)gBattleIcon004Tiles, (void *)gBattleIcon004Frames, (void *)gMonsterPalette005Palette, 0 }, // 6: Plague Rat
    { (void *)gBattleIcon005Tiles, (void *)gBattleIcon005Frames, (void *)gMonsterBattle004Palette, 0 }, // 7: Clabbert
    { (void *)gBattleIcon006Tiles, (void *)gBattleIcon006Frames, (void *)gMonsterPalette006Palette, 0 }, // 8: Suit of Armor (Footman)
    { (void *)gBattleIcon006Tiles, (void *)gBattleIcon006Frames, (void *)gMonsterPalette007Palette, 0 }, // 9: Suit of Armor (Cavalier)
    { (void *)gBattleIcon007Tiles, (void *)gBattleIcon007Frames, (void *)gMonsterPalette008Palette, 0 }, // 10: Suit of Armor (Paladin)
    { (void *)gBattleIcon007Tiles, (void *)gBattleIcon007Frames, (void *)gMonsterPalette009Palette, 0 }, // 11: Suit of Armor (Squire)
    { (void *)gBattleIcon006Tiles, (void *)gBattleIcon006Frames, (void *)gMonsterPalette010Palette, 0 }, // 12: Suit of Armor (Swordsman)
    { (void *)gBattleIcon007Tiles, (void *)gBattleIcon007Frames, (void *)gMonsterPalette011Palette, 0 }, // 13: Suit of Armor (Crusader)
    { (void *)gBattleIcon007Tiles, (void *)gBattleIcon007Frames, (void *)gMonsterPalette012Palette, 0 }, // 14: Suit of Armor (Knight)
    { (void *)gBattleIcon008Tiles, (void *)gBattleIcon008Frames, (void *)gBattleIcon008Palette, 0 }, // 15: Funnelweb Spider
    { (void *)gBattleIcon008Tiles, (void *)gBattleIcon008Frames, (void *)gMonsterPalette013Palette, 0 }, // 16: Brown Recluse Spider
    { (void *)gBattleIcon008Tiles, (void *)gBattleIcon008Frames, (void *)gMonsterPalette014Palette, 0 }, // 17: Large Spider
    { (void *)gBattleIcon008Tiles, (void *)gBattleIcon008Frames, (void *)gMonsterPalette015Palette, 0 }, // 18: Redback Spider
    { (void *)gBattleIcon009Tiles, (void *)gBattleIcon009Frames, (void *)gMonsterBattle008Palette, 0 }, // 19: Giant Spider
    { (void *)gBattleIcon009Tiles, (void *)gBattleIcon009Frames, (void *)gMonsterPalette016Palette, 0 }, // 20: Cocoon Spider
    { (void *)gBattleIcon009Tiles, (void *)gBattleIcon009Frames, (void *)gMonsterPalette017Palette, 0 }, // 21: Whitetail Spider
    { (void *)gBattleIcon010Tiles, (void *)gBattleIcon010Frames, (void *)gMonsterBattle009Palette, 0 }, // 22: Flobberworm
    { (void *)gBattleIcon011Tiles, (void *)gBattleIcon011Frames, (void *)gMonsterPalette018Palette, 0 }, // 23: Snail
    { (void *)gBattleIcon011Tiles, (void *)gBattleIcon011Frames, (void *)gMonsterPalette019Palette, 0 }, // 24: Large Orange Snail
    { (void *)gBattleIcon011Tiles, (void *)gBattleIcon011Frames, (void *)gMonsterPalette020Palette, 0 }, // 25: Flailtail Snail
    { (void *)gBattleIcon012Tiles, (void *)gBattleIcon012Frames, (void *)gBattleIcon012Palette, 0 }, // 26: Bat
    { (void *)gBattleIcon012Tiles, (void *)gBattleIcon012Frames, (void *)gMonsterPalette021Palette, 0 }, // 27: Fruitbat
    { (void *)gBattleIcon012Tiles, (void *)gBattleIcon012Frames, (void *)gMonsterPalette022Palette, 0 }, // 28: Mortis Bat
    { (void *)gBattleIcon013Tiles, (void *)gBattleIcon013Frames, (void *)gBattleIcon013Palette, 0 }, // 29: Dragonfly
    { (void *)gBattleIcon013Tiles, (void *)gBattleIcon013Frames, (void *)gMonsterPalette023Palette, 0 }, // 30: Imperial Dragonfly
    { (void *)gBattleIcon014Tiles, (void *)gBattleIcon014Frames, (void *)gBattleIcon014Palette, 0 }, // 31: Horklump
    { (void *)gBattleIcon015Tiles, (void *)gBattleIcon015Frames, (void *)gMonsterPalette024Palette, 0 }, // 32: Snake
    { (void *)gBattleIcon015Tiles, (void *)gBattleIcon015Frames, (void *)gMonsterPalette025Palette, 0 }, // 33: Spitting Snake
    { (void *)gBattleIcon016Tiles, (void *)gBattleIcon016Frames, (void *)gMonsterPalette026Palette, 0 }, // 34: Wasp
    { (void *)gBattleIcon016Tiles, (void *)gBattleIcon016Frames, (void *)gMonsterPalette027Palette, 0 }, // 35: Tarantula Hawk Wasp
    { (void *)gBattleIcon017Tiles, (void *)gBattleIcon017Frames, (void *)gMonsterPalette028Palette, 0 }, // 36: Bowtruckle
    { (void *)gBattleIcon017Tiles, (void *)gBattleIcon017Frames, (void *)gMonsterPalette029Palette, 0 }, // 37: Oaken Bowtruckle
    { (void *)gBattleIcon018Tiles, (void *)gBattleIcon018Frames, (void *)gMonsterPalette030Palette, 0 }, // 38: Doxy
    { (void *)gBattleIcon018Tiles, (void *)gBattleIcon018Frames, (void *)gMonsterPalette031Palette, 0 }, // 39: Doxy Queen
    { (void *)gBattleIcon019Tiles, (void *)gBattleIcon019Frames, (void *)gMonsterBattle018Palette, 0 }, // 40: Hinkypunk
    { (void *)gBattleIcon020Tiles, (void *)gBattleIcon020Frames, (void *)gMonsterBattle019Palette, 0 }, // 41: Gytrash
    { (void *)gBattleIcon021Tiles, (void *)gBattleIcon021Frames, (void *)gMonsterBattle020Palette, 0 }, // 42: Grindylow
    { (void *)gBattleIcon022Tiles, (void *)gBattleIcon022Frames, (void *)gMonsterBattle021Palette, 0 }, // 43: Red Cap
    { (void *)gBattleIcon023Tiles, (void *)gBattleIcon023Frames, (void *)gMonsterBattle022Palette, 0 }, // 44: Armored Red Cap
    { (void *)gBattleIcon024Tiles, (void *)gBattleIcon024Frames, (void *)gMonsterPalette032Palette, 0 }, // 45: Salamander
    { (void *)gBattleIcon024Tiles, (void *)gBattleIcon024Frames, (void *)gMonsterPalette034Palette, 0 }, // 46: Amazonian Salamander
    { (void *)gBattleIcon024Tiles, (void *)gBattleIcon024Frames, (void *)gMonsterPalette034Palette, 0 }, // 47: Peruvian Salamander
    { (void *)gBattleIcon025Tiles, (void *)gBattleIcon025Frames, (void *)gMonsterPalette035Palette, 0 }, // 48: Charmed Skeleton
    { (void *)gBattleIcon025Tiles, (void *)gBattleIcon025Frames, (void *)gMonsterPalette036Palette, 0 }, // 49: Jinxed Skeleton
    { (void *)gBattleIcon026Tiles, (void *)gBattleIcon026Frames, (void *)gMonsterPalette037Palette, 0 }, // 50: Tree Frog
    { (void *)gBattleIcon026Tiles, (void *)gBattleIcon026Frames, (void *)gMonsterPalette038Palette, 0 }, // 51: Wide-mouth Toad
    { (void *)gBattleIcon026Tiles, (void *)gBattleIcon026Frames, (void *)gMonsterPalette039Palette, 0 }, // 52: Bullfrog
    { (void *)gBattleIcon011Tiles, (void *)gBattleIcon011Frames, (void *)gMonsterPalette018Palette, 0 }, // 53: Flesh-eating Slug (not in game, needs to be in file for coders - no need to translate)
    { (void *)gBattleIcon027Tiles, (void *)gBattleIcon027Frames, (void *)gBattleIcon027Palette, 0 }, // 54: Whomping Willow
    { (void *)gBattleIcon028Tiles, (void *)gBattleIcon028Frames, (void *)gMonsterBattle028Palette, 0 }, // 55: Forest Troll
    { (void *)gBattleIcon029Tiles, (void *)gBattleIcon029Frames, (void *)gMonsterBattle029Palette, 0 }, // 56: River Troll
    { (void *)gBattleIcon030Tiles, (void *)gBattleIcon030Frames, (void *)gMonsterBattle030Palette, 0 }, // 57: Venemous Tentacula
    { (void *)gBattleIcon031Tiles, (void *)gBattleIcon031Frames, (void *)gMonsterBattle031Palette, 0 }, // 58: 'The Monster Book of Monsters'
    { (void *)gBattleIcon032Tiles, (void *)gBattleIcon032Frames, (void *)gMonsterBattle032Palette, 0 }, // 59: Giant Rat
    { (void *)gBattleIcon033Tiles, (void *)gBattleIcon033Frames, (void *)gMonsterBattle033Palette, 0 }, // 60: Crabbe
    { (void *)gBattleIcon034Tiles, (void *)gBattleIcon034Frames, (void *)gMonsterBattle034Palette, 0 }, // 61: Draco
    { (void *)gBattleIcon035Tiles, (void *)gBattleIcon035Frames, (void *)gMonsterBattle035Palette, 0 }, // 62: Goyle
    { (void *)gBattleIcon036Tiles, (void *)gBattleIcon036Frames, (void *)gMonsterBattle036Palette, 0 }, // 63: Lupin Werewolf
    { (void *)gBattleIcon015Tiles, (void *)gBattleIcon015Frames, (void *)gMonsterPalette024Palette, 0 }, // 64: Snake
    { (void *)gBattleIcon008Tiles, (void *)gBattleIcon008Frames, (void *)gMonsterPalette013Palette, 0 }, // 65: Brown Recluse Spider
    { (void *)gBattleIcon031Tiles, (void *)gBattleIcon031Frames, (void *)gMonsterBattle031Palette, 0 }, // 66: 'The Monster Book of Monsters'
    { (void *)gBattleIcon031Tiles, (void *)gBattleIcon031Frames, (void *)gMonsterBattle031Palette, 0 }, // 67: 'The Monster Book of Monsters'
    { (void *)gBattleIcon031Tiles, (void *)gBattleIcon031Frames, (void *)gMonsterBattle031Palette, 0 }, // 68: Native of Fiji. Has a heavily jeweled shell.
};

// Indexed by FighterType: Harry, Hermione, Ron, Buckbeak.
const ObjectAssetRecord g_aAllyTurnOrderIconAssets[4] = {
    { (void *)gAllyHead001Tiles, (void *)gAllyHead001Frames, (void *)gBattleIcon037Palette, 0 },
    { (void *)gAllyHead002Tiles, (void *)gAllyHead002Frames, (void *)gBattleIcon037Palette, 0 },
    { (void *)gAllyHead003Tiles, (void *)gAllyHead003Frames, (void *)gBattleIcon038Palette, 0 },
    { (void *)gBattleIcon039Tiles, (void *)gBattleIcon039Frames, (void *)gBattleIcon039Palette, 0 },
};

const ObjectAssetRecord g_TurnOrderIconContainerAsset = { (void *)gBattleHudItem001Tiles, (void *)gBattleHudItem001Frames, (void *)gBattleHudItem001Palette, 0 };
