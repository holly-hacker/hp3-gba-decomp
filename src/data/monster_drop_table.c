#include "types.h"
#include "constants/items.h"

typedef struct {
    u16 chance;
    u16 itemId;
} MonsterDropSlot;

typedef struct {
    MonsterDropSlot slot[2];
} MonsterDropEntry;

// Monster drop table, following the standard monster order (see data/monsters/monsters.json).
// See docs/memory-map/battle.md.
const MonsterDropEntry g_pMonsterDropTable[69] = {
    { { { 30, ITEM_GRAND_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Ruby Fire Crab
    { { { 30, ITEM_GRAND_PEPPERUP_POTION }, { 10, ITEM_GRAND_PEPPERUP_POTION } } },    // Emerald Fire Crab
    { { { 30, ITEM_GRAND_PEPPERUP_POTION }, { 10, ITEM_GRAND_PEPPERUP_POTION } } },    // Sapphire Fire Crab
    { { { 20, ITEM_BEADS }, { 20, ITEM_WIGGENWELD_POTION } } },    // Cornish Pixie
    { { { 20, ITEM_SNEAKERS }, { 20, ITEM_WIGGENWELD_POTION } } },    // Rat
    { { { 20, ITEM_CAP }, { 20, ITEM_PEPPERUP_POTION } } },    // Albino Rat
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Plague Rat
    { { { 30, ITEM_GRAND_PEPPERUP_POTION }, { 10, ITEM_WIGGENWELD_POTION } } },    // Clabbert
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_WIGGENWELD_POTION } } },    // Suit of Armor (Footman)
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Suit of Armor (Cavalier)
    { { { 30, ITEM_ANTI_PARALYSIS_POTION }, { 10, ITEM_GRAND_PEPPERUP_POTION } } },    // Suit of Armor (Paladin)
    { { { 20, ITEM_QUIDDITCH_HELMET }, { 20, ITEM_PEPPERUP_POTION } } },    // Suit of Armor (Squire)
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_ANTI_PARALYSIS_POTION } } },    // Suit of Armor (Swordsman)
    { { { 30, ITEM_GRAND_PEPPERUP_POTION }, { 10, ITEM_ANTI_PARALYSIS_POTION } } },    // Suit of Armor (Crusader)
    { { { 30, ITEM_ANTI_PARALYSIS_POTION }, { 10, ITEM_GRAND_PEPPERUP_POTION } } },    // Suit of Armor (Knight)
    { { { 25, ITEM_BRACELET }, { 25, ITEM_WIGGENWELD_POTION } } },    // Funnelweb Spider
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Brown Recluse Spider
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Large Spider
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Redback Spider
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Giant Spider
    { { { 30, ITEM_GRAND_PEPPERUP_POTION }, { 10, ITEM_ANTIDOTE_TO_COMMON_POISONS } } },    // Cocoon Spider
    { { { 30, ITEM_GRAND_PEPPERUP_POTION }, { 10, ITEM_ANTIDOTE_TO_COMMON_POISONS } } },    // Whitetail Spider
    { { { 30, ITEM_GRAND_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Flobberworm
    { { { 20, ITEM_SWEDISH_SHORTSNOUT_DRAGON_HIDE_GLOVES }, { 20, ITEM_WIGGENWELD_POTION } } },    // Snail
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Large Orange Snail
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_GRAND_PEPPERUP_POTION } } },    // Flailtail Snail
    { { { 20, ITEM_MITTENS }, { 20, ITEM_PEPPERUP_POTION } } },    // Bat
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Fruitbat
    { { { 30, ITEM_GRAND_WIGGENWELD_POTION }, { 10, ITEM_GRAND_PEPPERUP_POTION } } },    // Mortis Bat
    { { { 20, ITEM_LEATHER_BOOTS }, { 20, ITEM_WIGGENWELD_POTION } } },    // Dragonfly
    { { { 30, ITEM_GRAND_PEPPERUP_POTION }, { 10, ITEM_WIGGENWELD_POTION } } },    // Imperial Dragonfly
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Horklump
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Snake
    { { { 30, ITEM_ANTIDOTE_TO_COMMON_POISONS }, { 10, ITEM_GRAND_PEPPERUP_POTION } } },    // Spitting Snake
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Wasp
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Tarantula Hawk Wasp
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Bowtruckle
    { { { 30, ITEM_GRAND_PEPPERUP_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Oaken Bowtruckle
    { { { 20, ITEM_ROPE }, { 20, ITEM_GRAND_WIGGENWELD_POTION } } },    // Doxy
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Doxy Queen
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Hinkypunk
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Gytrash
    { { { 30, ITEM_GRAND_PEPPERUP_POTION }, { 10, ITEM_GRAND_PEPPERUP_POTION } } },    // Grindylow
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_GRAND_PEPPERUP_POTION } } },    // Red Cap
    { { { 20, ITEM_GRAND_PEPPERUP_POTION }, { 20, ITEM_GRAND_PEPPERUP_POTION } } },    // Armored Red Cap
    { { { 20, ITEM_HEAD_BAND }, { 20, ITEM_PEPPERUP_POTION } } },    // Salamander
    { { { 30, ITEM_GRAND_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Amazonian Salamander
    { { { 20, ITEM_GRAND_PEPPERUP_POTION }, { 20, ITEM_GRAND_PEPPERUP_POTION } } },    // Peruvian Salamander
    { { { 20, ITEM_CHINESE_FIREBALL_DRAGON_HIDE_CLOAK }, { 20, ITEM_GRAND_PEPPERUP_POTION } } },    // Charmed Skeleton
    { { { 30, ITEM_ANTI_PARALYSIS_POTION }, { 10, ITEM_GRAND_PEPPERUP_POTION } } },    // Jinxed Skeleton
    { { { 30, ITEM_WIGGENWELD_POTION }, { 10, ITEM_PEPPERUP_POTION } } },    // Tree Frog
    { { { 30, ITEM_ANTIDOTE_TO_COMMON_POISONS }, { 10, ITEM_GRAND_WIGGENWELD_POTION } } },    // Wide-mouth Toad
    { { { 20, ITEM_REMEMBRALL }, { 20, ITEM_ANTIDOTE_TO_COMMON_POISONS } } },    // Bullfrog
    { { { 50, ITEM_WIGGENWELD_POTION }, { 50, ITEM_ANTI_PARALYSIS_POTION } } },    // Flesh-eating Slug (not in game, needs to be in file for coders -- no need to translate)
    { { { 100, ITEM_CHINESE_FIREBALL_DRAGON_HIDE_CAP }, { 0, ITEM_PEPPERUP_POTION } } },    // Whomping Willow
    { { { 100, ITEM_CHINESE_FIREBALL_DRAGON_HIDE_GLOVES }, { 0, ITEM_PEPPERUP_POTION } } },    // Forest Troll
    { { { 100, ITEM_DEAD_CATERPILLAR }, { 0, ITEM_PEPPERUP_POTION } } },    // River Troll
    { { { 100, ITEM_POTIONS_GLOVES }, { 0, ITEM_PEPPERUP_POTION } } },    // Venemous Tentacula
    { { { 100, ITEM_SCHOOL_ROBE }, { 0, ITEM_PEPPERUP_POTION } } },    // 'The Monster Book of Monsters'
    { { { 100, ITEM_ORDINARY_BELT }, { 0, ITEM_PEPPERUP_POTION } } },    // Giant Rat
    { { { 100, ITEM_QUIDDITCH_BOOTS }, { 0, ITEM_WIGGENWELD_POTION } } },    // Crabbe
    { { { 100, 130 }, { 0, ITEM_PEPPERUP_POTION } } },    // Draco
    { { { 100, ITEM_BLACK_POINTED_HAT }, { 0, ITEM_PEPPERUP_POTION } } },    // Goyle
    { { { 100, ITEM_HUNGARIAN_HORNTAIL_DRAGON_HIDE_BOOTS }, { 0, ITEM_PEPPERUP_POTION } } },    // Lupin Werewolf
    { { { 100, 102 }, { 0, ITEM_PEPPERUP_POTION } } },    // Snake
    { { { 100, 112 }, { 0, ITEM_PEPPERUP_POTION } } },    // Brown Recluse Spider
    { { { 100, ITEM_THE_MONSTER_BOOK_OF_MONSTERS }, { 0, ITEM_GRAND_WIGGENWELD_POTION } } },    // 'The Monster Book of Monsters'
    { { { 100, ITEM_SWEDISH_SHORTSNOUT_DRAGON_HIDE_GLOVES }, { 0, ITEM_PEPPERUP_POTION } } },    // 'The Monster Book of Monsters'
    { { { 100, ITEM_THE_MONSTER_BOOK_OF_MONSTERS }, { 0, ITEM_PEPPERUP_POTION } } },    // roster 68 (name unresolved in monsters.json)
};
