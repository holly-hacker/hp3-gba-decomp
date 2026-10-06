#include "types.h"
#include "menu/folio_bruti.h"

// The monster sprite's scale on the Folio Bruti detail panel, 16.16 fixed point: most monsters are drawn
// at full size, a few at 0.5 or 0.85 to fit.
const u32 g_adwFolioBrutiMonsterScale[69] = {
    0x10000,  // 0: Ruby Fire Crab
    0x10000,  // 1: Emerald Fire Crab
    0x10000,  // 2: Sapphire Fire Crab
    0x10000,  // 3: Cornish Pixie
    0x10000,  // 4: Rat
    0x10000,  // 5: Albino Rat
    0x10000,  // 6: Plague Rat
    0x10000,  // 7: Clabbert
    0x10000,  // 8: Suit of Armor (Footman)
    0x10000,  // 9: Suit of Armor (Cavalier)
    0x10000,  // 10: Suit of Armor (Paladin)
    0x10000,  // 11: Suit of Armor (Squire)
    0x10000,  // 12: Suit of Armor (Swordsman)
    0x10000,  // 13: Suit of Armor (Crusader)
    0x10000,  // 14: Suit of Armor (Knight)
    0x10000,  // 15: Funnelweb Spider
    0x10000,  // 16: Brown Recluse Spider
    0x10000,  // 17: Large Spider
    0x10000,  // 18: Redback Spider
    0x10000,  // 19: Giant Spider
    0x10000,  // 20: Cocoon Spider
    0x10000,  // 21: Whitetail Spider
    0x10000,  // 22: Flobberworm
    0x10000,  // 23: Snail
    0x10000,  // 24: Large Orange Snail
    0x10000,  // 25: Flailtail Snail
    0x10000,  // 26: Bat
    0x10000,  // 27: Fruitbat
    0x10000,  // 28: Mortis Bat
    0x10000,  // 29: Dragonfly
    0x10000,  // 30: Imperial Dragonfly
    0x10000,  // 31: Horklump
    0x10000,  // 32: Snake
    0x10000,  // 33: Spitting Snake
    0x10000,  // 34: Wasp
    0x10000,  // 35: Tarantula Hawk Wasp
    0x10000,  // 36: Bowtruckle
    0x10000,  // 37: Oaken Bowtruckle
    0x10000,  // 38: Doxy
    0x10000,  // 39: Doxy Queen
    0x10000,  // 40: Hinkypunk
    0x10000,  // 41: Gytrash
    0x10000,  // 42: Grindylow
    0x10000,  // 43: Red Cap
    0x10000,  // 44: Armored Red Cap
    0x10000,  // 45: Salamander
    0x10000,  // 46: Amazonian Salamander
    0x10000,  // 47: Peruvian Salamander
    0x10000,  // 48: Charmed Skeleton
    0x10000,  // 49: Jinxed Skeleton
    0x10000,  // 50: Tree Frog
    0x10000,  // 51: Wide-mouth Toad
    0x10000,  // 52: Bullfrog
    0x10000,  // 53: Flesh-eating Slug (not in game, needs to be in file for coders - no need to translate)
    0x8000,  // 54: Whomping Willow
    0xD999,  // 55: Forest Troll
    0xD999,  // 56: River Troll
    0x10000,  // 57: Venemous Tentacula
    0x10000,  // 58: 'The Monster Book of Monsters'
    0x10000,  // 59: Giant Rat
    0x10000,  // 60: Crabbe
    0x10000,  // 61: Draco
    0x10000,  // 62: Goyle
    0x10000,  // 63: Lupin Werewolf
    0x10000,  // 64: Snake
    0x10000,  // 65: Brown Recluse Spider
    0x10000,  // 66: 'The Monster Book of Monsters'
    0x10000,  // 67: 'The Monster Book of Monsters'
    0x10000,  // 68: Native of Fiji. Has a heavily jeweled shell.
};
