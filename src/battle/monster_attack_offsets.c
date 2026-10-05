#include "types.h"
#include "battle/battle.h"

// The monster's own {x, y} extent, subtracted from the target slot anchor
// when it moves in to attack; indexed by roster index.
const u8 g_aMonsterAttackOffset_candidate[69][2] = {
    { 32, 32 },  // 0: Ruby Fire Crab
    { 32, 32 },  // 1: Emerald Fire Crab
    { 32, 32 },  // 2: Sapphire Fire Crab
    { 32, 32 },  // 3: Cornish Pixie
    { 24, 32 },  // 4: Rat
    { 24, 32 },  // 5: Albino Rat
    { 24, 32 },  // 6: Plague Rat
    { 48, 32 },  // 7: Clabbert
    { 52, 32 },  // 8: Suit of Armor (Footman)
    { 52, 32 },  // 9: Suit of Armor (Cavalier)
    { 52, 32 },  // 10: Suit of Armor (Paladin)
    { 52, 32 },  // 11: Suit of Armor (Squire)
    { 52, 32 },  // 12: Suit of Armor (Swordsman)
    { 52, 32 },  // 13: Suit of Armor (Crusader)
    { 52, 32 },  // 14: Suit of Armor (Knight)
    { 32, 32 },  // 15: Funnelweb Spider
    { 32, 32 },  // 16: Brown Recluse Spider
    { 32, 32 },  // 17: Large Spider
    { 32, 32 },  // 18: Redback Spider
    { 48, 24 },  // 19: Giant Spider
    { 48, 24 },  // 20: Cocoon Spider
    { 48, 24 },  // 21: Whitetail Spider
    { 32, 32 },  // 22: Flobberworm
    { 32, 32 },  // 23: Snail
    { 32, 32 },  // 24: Large Orange Snail
    { 32, 32 },  // 25: Flailtail Snail
    { 32, 32 },  // 26: Bat
    { 32, 32 },  // 27: Fruitbat
    { 32, 32 },  // 28: Mortis Bat
    { 32, 32 },  // 29: Dragonfly
    { 32, 32 },  // 30: Imperial Dragonfly
    { 24, 16 },  // 31: Horklump
    { 32, 32 },  // 32: Snake
    { 32, 32 },  // 33: Spitting Snake
    { 16, 24 },  // 34: Wasp
    { 32, 32 },  // 35: Tarantula Hawk Wasp
    { 16, 16 },  // 36: Bowtruckle
    { 16, 16 },  // 37: Oaken Bowtruckle
    { 24, 0 },  // 38: Doxy
    { 24, 0 },  // 39: Doxy Queen
    { 32, 32 },  // 40: Hinkypunk
    { 48, 32 },  // 41: Gytrash
    { 32, 32 },  // 42: Grindylow
    { 32, 32 },  // 43: Red Cap
    { 32, 32 },  // 44: Armored Red Cap
    { 32, 32 },  // 45: Salamander
    { 32, 32 },  // 46: Amazonian Salamander
    { 32, 32 },  // 47: Peruvian Salamander
    { 32, 32 },  // 48: Charmed Skeleton
    { 32, 32 },  // 49: Jinxed Skeleton
    { 64, 32 },  // 50: Tree Frog
    { 64, 32 },  // 51: Wide-mouth Toad
    { 64, 32 },  // 52: Bullfrog
    { 32, 32 },  // 53: Flesh-eating Slug (not in game, needs to be in file for coders - no need to translate)
    { 32, 32 },  // 54: Whomping Willow
    { 32, 32 },  // 55: Forest Troll
    { 32, 32 },  // 56: River Troll
    { 32, 32 },  // 57: Venemous Tentacula
    { 32, 32 },  // 58: 'The Monster Book of Monsters'
    { 72, 24 },  // 59: Giant Rat
    { 32, 32 },  // 60: Crabbe
    { 32, 32 },  // 61: Draco
    { 32, 32 },  // 62: Goyle
    { 32, 16 },  // 63: Lupin Werewolf
    { 32, 32 },  // 64: Snake
    { 32, 32 },  // 65: Brown Recluse Spider
    { 32, 32 },  // 66: 'The Monster Book of Monsters'
    { 32, 32 },  // 67: 'The Monster Book of Monsters'
    { 32, 32 },  // 68: Native of Fiji. Has a heavily jeweled shell.
};
