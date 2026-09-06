#include "encounters.h"

// Random-encounter roster: g_dwCurrentGameModeArg1 selects the id,
// g_dwCurrentGameModeArg3 the kind, g_dwCurrentGameModeArg2 the pre-picked variant.
// Room users from g_pRoomTable bEncounterVariant; ids 16/23/24/26 are unreferenced.
// See docs/formats/encounters.md.
const RandomEncounter g_aRandomEncounters[30] = {
    { {  // id 0: room 38 (Leaky Cauldron - Cellar 1)
        { {  // kind 0
            { 255,   4, 255, 255 },  // variant 0: slot1 Rat
            { 255, 255,  43, 255 },  // variant 1: slot2 Red Cap
            { 255,  26, 255, 255 },  // variant 2: slot1 Bat
            { 255, 255,  15, 255 },  // variant 3: slot2 Funnelweb Spider
        }, },
        { {  // kind 1
            { 255,  43, 255, 255 },  // variant 0: slot1 Red Cap
            { 255, 255,   5, 255 },  // variant 1: slot2 Albino Rat
            { 255,  26, 255, 255 },  // variant 2: slot1 Bat
            { 255, 255,  15, 255 },  // variant 3: slot2 Funnelweb Spider
        }, },
        { {  // kind 2
            { 255,   4, 255, 255 },  // variant 0: slot1 Rat
            { 255, 255,   5, 255 },  // variant 1: slot2 Albino Rat
            { 255,  43, 255, 255 },  // variant 2: slot1 Red Cap
            { 255, 255,  15, 255 },  // variant 3: slot2 Funnelweb Spider
        }, },
    }, },
    { {  // id 1: room 39 (Leaky Cauldron - Cellar 2)
        { {  // kind 0
            { 255,   4,   4, 255 },  // variant 0: slot1 Rat, slot2 Rat
            {  43,  43,  43, 255 },  // variant 1: slot0 Red Cap, slot1 Red Cap, slot2 Red Cap
            {  26,  27,  26, 255 },  // variant 2: slot0 Bat, slot1 Fruitbat, slot2 Bat
            { 255,  15,  15, 255 },  // variant 3: slot1 Funnelweb Spider, slot2 Funnelweb Spider
        }, },
        { {  // kind 1
            {  43,  43,  43, 255 },  // variant 0: slot0 Red Cap, slot1 Red Cap, slot2 Red Cap
            {   5,   5,   5, 255 },  // variant 1: slot0 Albino Rat, slot1 Albino Rat, slot2 Albino Rat
            {  27,  26,  27, 255 },  // variant 2: slot0 Fruitbat, slot1 Bat, slot2 Fruitbat
            {  15,  15,  15, 255 },  // variant 3: slot0 Funnelweb Spider, slot1 Funnelweb Spider, slot2 Funnelweb Spider
        }, },
        { {  // kind 2
            { 255,  26,   4, 255 },  // variant 0: slot1 Bat, slot2 Rat
            { 255,  15,  15, 255 },  // variant 1: slot1 Funnelweb Spider, slot2 Funnelweb Spider
            { 255,  26,  26, 255 },  // variant 2: slot1 Bat, slot2 Bat
            { 255, 255,  15, 255 },  // variant 3: slot2 Funnelweb Spider
        }, },
    }, },
    { {  // id 2: room 53 (Diagon Alley Test Map 4)
        { {  // kind 0
            { 255,  54, 255, 255 },  // variant 0: slot1 Whomping Willow
            { 255, 255,  56, 255 },  // variant 1: slot2 River Troll
            { 255,  57, 255, 255 },  // variant 2: slot1 Venemous Tentacula
            {  52,  52,  52, 255 },  // variant 3: slot0 Bullfrog, slot1 Bullfrog, slot2 Bullfrog
        }, },
        { {  // kind 1
            { 255,   0, 255, 255 },  // variant 0: slot1 Ruby Fire Crab
            { 255, 255,   3, 255 },  // variant 1: slot2 Cornish Pixie
            { 255,   4, 255, 255 },  // variant 2: slot1 Rat
            { 255, 255,   7, 255 },  // variant 3: slot2 Clabbert
        }, },
        { {  // kind 2
            { 255, 255, 255, 255 },  // variant 0: (empty)
            { 255, 255, 255, 255 },  // variant 1: (empty)
            { 255, 255, 255, 255 },  // variant 2: (empty)
            { 255, 255, 255, 255 },  // variant 3: (empty)
        }, },
    }, },
    { {  // id 3: room 54 (Diagon Alley Test Map 5)
        { {  // kind 0
            { 255,  68,  68, 255 },  // variant 0: slot1 Native of Fiji. Has a heavily jeweled shell., slot2 Native of Fiji. Has a heavily jeweled shell.
            { 255,  68,  68, 255 },  // variant 1: slot1 Native of Fiji. Has a heavily jeweled shell., slot2 Native of Fiji. Has a heavily jeweled shell.
            { 255,  68,  68, 255 },  // variant 2: slot1 Native of Fiji. Has a heavily jeweled shell., slot2 Native of Fiji. Has a heavily jeweled shell.
            { 255,  68,  68, 255 },  // variant 3: slot1 Native of Fiji. Has a heavily jeweled shell., slot2 Native of Fiji. Has a heavily jeweled shell.
        }, },
        { {  // kind 1
            { 255,  68,  68, 255 },  // variant 0: slot1 Native of Fiji. Has a heavily jeweled shell., slot2 Native of Fiji. Has a heavily jeweled shell.
            { 255,  68,  68, 255 },  // variant 1: slot1 Native of Fiji. Has a heavily jeweled shell., slot2 Native of Fiji. Has a heavily jeweled shell.
            { 255,  68,  68, 255 },  // variant 2: slot1 Native of Fiji. Has a heavily jeweled shell., slot2 Native of Fiji. Has a heavily jeweled shell.
            { 255,  68,  68, 255 },  // variant 3: slot1 Native of Fiji. Has a heavily jeweled shell., slot2 Native of Fiji. Has a heavily jeweled shell.
        }, },
        { {  // kind 2
            { 255,  68,  68, 255 },  // variant 0: slot1 Native of Fiji. Has a heavily jeweled shell., slot2 Native of Fiji. Has a heavily jeweled shell.
            { 255,  68,  68, 255 },  // variant 1: slot1 Native of Fiji. Has a heavily jeweled shell., slot2 Native of Fiji. Has a heavily jeweled shell.
            { 255,  68,  68, 255 },  // variant 2: slot1 Native of Fiji. Has a heavily jeweled shell., slot2 Native of Fiji. Has a heavily jeweled shell.
            { 255,  68,  68, 255 },  // variant 3: slot1 Native of Fiji. Has a heavily jeweled shell., slot2 Native of Fiji. Has a heavily jeweled shell.
        }, },
    }, },
    { {  // id 4: room 5 (Hogwarts Express - Baggage Car), room 6 (Hogwarts Express - Passenger Car), room 7 (Hogwarts Express - Buffet Car)
        { {  // kind 0
            { 255,   5,   5, 255 },  // variant 0: slot1 Albino Rat, slot2 Albino Rat
            { 255,   6, 255, 255 },  // variant 1: slot1 Plague Rat
            { 255,  27,  27, 255 },  // variant 2: slot1 Fruitbat, slot2 Fruitbat
            { 255,  16,  16, 255 },  // variant 3: slot1 Brown Recluse Spider, slot2 Brown Recluse Spider
        }, },
        { {  // kind 1
            { 255,  16, 255, 255 },  // variant 0: slot1 Brown Recluse Spider
            { 255,  16,  16, 255 },  // variant 1: slot1 Brown Recluse Spider, slot2 Brown Recluse Spider
            { 255,   5, 255, 255 },  // variant 2: slot1 Albino Rat
            { 255,   5,   5, 255 },  // variant 3: slot1 Albino Rat, slot2 Albino Rat
        }, },
        { {  // kind 2
            { 255,  16, 255, 255 },  // variant 0: slot1 Brown Recluse Spider
            { 255,  16,  16, 255 },  // variant 1: slot1 Brown Recluse Spider, slot2 Brown Recluse Spider
            { 255,   5, 255, 255 },  // variant 2: slot1 Albino Rat
            { 255,   5,   5, 255 },  // variant 3: slot1 Albino Rat, slot2 Albino Rat
        }, },
    }, },
    { {  // id 5: room 3 (Transfiguration Classroom)
        { {  // kind 0
            { 255,  12,  12, 255 },  // variant 0: slot1 Suit of Armor (Swordsman), slot2 Suit of Armor (Swordsman)
            { 255,  17,  17, 255 },  // variant 1: slot1 Large Spider, slot2 Large Spider
            { 255,  31,  31, 255 },  // variant 2: slot1 Horklump, slot2 Horklump
            { 255,  24,  24, 255 },  // variant 3: slot1 Large Orange Snail, slot2 Large Orange Snail
        }, },
        { {  // kind 1
            { 255,  12,  12, 255 },  // variant 0: slot1 Suit of Armor (Swordsman), slot2 Suit of Armor (Swordsman)
            {  31,  24,  31, 255 },  // variant 1: slot0 Horklump, slot1 Large Orange Snail, slot2 Horklump
            {  12,  17,  12, 255 },  // variant 2: slot0 Suit of Armor (Swordsman), slot1 Large Spider, slot2 Suit of Armor (Swordsman)
            { 255,  17,  17, 255 },  // variant 3: slot1 Large Spider, slot2 Large Spider
        }, },
        { {  // kind 2
            { 255,  12,  12, 255 },  // variant 0: slot1 Suit of Armor (Swordsman), slot2 Suit of Armor (Swordsman)
            {  31,  24,  31, 255 },  // variant 1: slot0 Horklump, slot1 Large Orange Snail, slot2 Horklump
            {  12,  17,  12, 255 },  // variant 2: slot0 Suit of Armor (Swordsman), slot1 Large Spider, slot2 Suit of Armor (Swordsman)
            { 255,  17,  17, 255 },  // variant 3: slot1 Large Spider, slot2 Large Spider
        }, },
    }, },
    { {  // id 6: room 4 (Transfiguration Classroom Maze)
        { {  // kind 0
            {   6,  16,   6, 255 },  // variant 0: slot0 Plague Rat, slot1 Brown Recluse Spider, slot2 Plague Rat
            { 255,   0,   0, 255 },  // variant 1: slot1 Ruby Fire Crab, slot2 Ruby Fire Crab
            { 255,  10,  10, 255 },  // variant 2: slot1 Suit of Armor (Paladin), slot2 Suit of Armor (Paladin)
            { 255,   3,   3, 255 },  // variant 3: slot1 Cornish Pixie, slot2 Cornish Pixie
        }, },
        { {  // kind 1
            { 255,  10,  10, 255 },  // variant 0: slot1 Suit of Armor (Paladin), slot2 Suit of Armor (Paladin)
            { 255,   0,   0, 255 },  // variant 1: slot1 Ruby Fire Crab, slot2 Ruby Fire Crab
            {   3,  16,   3, 255 },  // variant 2: slot0 Cornish Pixie, slot1 Brown Recluse Spider, slot2 Cornish Pixie
            {  16,   6,  16, 255 },  // variant 3: slot0 Brown Recluse Spider, slot1 Plague Rat, slot2 Brown Recluse Spider
        }, },
        { {  // kind 2
            { 255,  10,  10, 255 },  // variant 0: slot1 Suit of Armor (Paladin), slot2 Suit of Armor (Paladin)
            { 255,   3,   3, 255 },  // variant 1: slot1 Cornish Pixie, slot2 Cornish Pixie
            {   0,   6,   0, 255 },  // variant 2: slot0 Ruby Fire Crab, slot1 Plague Rat, slot2 Ruby Fire Crab
            {   6,  16,   6, 255 },  // variant 3: slot0 Plague Rat, slot1 Brown Recluse Spider, slot2 Plague Rat
        }, },
    }, },
    { {  // id 7: room 1 (Potions Classroom)
        { {  // kind 0
            { 255,  13,  13, 255 },  // variant 0: slot1 Suit of Armor (Crusader), slot2 Suit of Armor (Crusader)
            {  25,  25,  25, 255 },  // variant 1: slot0 Flailtail Snail, slot1 Flailtail Snail, slot2 Flailtail Snail
            { 255,  30,  30, 255 },  // variant 2: slot1 Imperial Dragonfly, slot2 Imperial Dragonfly
            {   2,   2,   2, 255 },  // variant 3: slot0 Sapphire Fire Crab, slot1 Sapphire Fire Crab, slot2 Sapphire Fire Crab
        }, },
        { {  // kind 1
            { 255,  13,  13, 255 },  // variant 0: slot1 Suit of Armor (Crusader), slot2 Suit of Armor (Crusader)
            {  25,  25,  25, 255 },  // variant 1: slot0 Flailtail Snail, slot1 Flailtail Snail, slot2 Flailtail Snail
            { 255,  30,  30, 255 },  // variant 2: slot1 Imperial Dragonfly, slot2 Imperial Dragonfly
            {   2,   2,   2, 255 },  // variant 3: slot0 Sapphire Fire Crab, slot1 Sapphire Fire Crab, slot2 Sapphire Fire Crab
        }, },
        { {  // kind 2
            { 255,  13,  13, 255 },  // variant 0: slot1 Suit of Armor (Crusader), slot2 Suit of Armor (Crusader)
            {  25,  25,  25, 255 },  // variant 1: slot0 Flailtail Snail, slot1 Flailtail Snail, slot2 Flailtail Snail
            { 255,  30,  30, 255 },  // variant 2: slot1 Imperial Dragonfly, slot2 Imperial Dragonfly
            {   2,   2,   2, 255 },  // variant 3: slot0 Sapphire Fire Crab, slot1 Sapphire Fire Crab, slot2 Sapphire Fire Crab
        }, },
    }, },
    { {  // id 8: room 2 (Potions Classroom Maze)
        { {  // kind 0
            { 255,  28,  28, 255 },  // variant 0: slot1 Mortis Bat, slot2 Mortis Bat
            { 255,  45,  45, 255 },  // variant 1: slot1 Salamander, slot2 Salamander
            {  28,  38,  28, 255 },  // variant 2: slot0 Mortis Bat, slot1 Doxy, slot2 Mortis Bat
            {  45,  45,  45, 255 },  // variant 3: slot0 Salamander, slot1 Salamander, slot2 Salamander
        }, },
        { {  // kind 1
            {  19,  19,  19, 255 },  // variant 0: slot0 Giant Spider, slot1 Giant Spider, slot2 Giant Spider
            {  38,  38,  38, 255 },  // variant 1: slot0 Doxy, slot1 Doxy, slot2 Doxy
            {  38,  45,  38, 255 },  // variant 2: slot0 Doxy, slot1 Salamander, slot2 Doxy
            {  28,  19,  28, 255 },  // variant 3: slot0 Mortis Bat, slot1 Giant Spider, slot2 Mortis Bat
        }, },
        { {  // kind 2
            {  19,  19,  19, 255 },  // variant 0: slot0 Giant Spider, slot1 Giant Spider, slot2 Giant Spider
            {  38,  38,  38, 255 },  // variant 1: slot0 Doxy, slot1 Doxy, slot2 Doxy
            {  38,  45,  38, 255 },  // variant 2: slot0 Doxy, slot1 Salamander, slot2 Doxy
            {  28,  19,  28, 255 },  // variant 3: slot0 Mortis Bat, slot1 Giant Spider, slot2 Mortis Bat
        }, },
    }, },
    { {  // id 9: room 34 (Library)
        { {  // kind 0
            {  11,  23,  11, 255 },  // variant 0: slot0 Suit of Armor (Squire), slot1 Snail, slot2 Suit of Armor (Squire)
            { 255,   7,   7, 255 },  // variant 1: slot1 Clabbert, slot2 Clabbert
            {   1,   1,   1, 255 },  // variant 2: slot0 Emerald Fire Crab, slot1 Emerald Fire Crab, slot2 Emerald Fire Crab
            { 255,  23,  23, 255 },  // variant 3: slot1 Snail, slot2 Snail
        }, },
        { {  // kind 1
            {   7,   1,   7, 255 },  // variant 0: slot0 Clabbert, slot1 Emerald Fire Crab, slot2 Clabbert
            { 255,  11,  11, 255 },  // variant 1: slot1 Suit of Armor (Squire), slot2 Suit of Armor (Squire)
            {  23,   7,  23, 255 },  // variant 2: slot0 Snail, slot1 Clabbert, slot2 Snail
            {  11,  23,  11, 255 },  // variant 3: slot0 Suit of Armor (Squire), slot1 Snail, slot2 Suit of Armor (Squire)
        }, },
        { {  // kind 2
            {   7,   1,   7, 255 },  // variant 0: slot0 Clabbert, slot1 Emerald Fire Crab, slot2 Clabbert
            { 255,  11,  11, 255 },  // variant 1: slot1 Suit of Armor (Squire), slot2 Suit of Armor (Squire)
            {  23,   7,  23, 255 },  // variant 2: slot0 Snail, slot1 Clabbert, slot2 Snail
            {  11,  23,  11, 255 },  // variant 3: slot0 Suit of Armor (Squire), slot1 Snail, slot2 Suit of Armor (Squire)
        }, },
    }, },
    { {  // id 10: room 35 (Library)
        { {  // kind 0
            {  46,  31,  46, 255 },  // variant 0: slot0 Amazonian Salamander, slot1 Horklump, slot2 Amazonian Salamander
            { 255,   9,   9, 255 },  // variant 1: slot1 Suit of Armor (Cavalier), slot2 Suit of Armor (Cavalier)
            {  31,  24,  31, 255 },  // variant 2: slot0 Horklump, slot1 Large Orange Snail, slot2 Horklump
            { 255,  24,  24, 255 },  // variant 3: slot1 Large Orange Snail, slot2 Large Orange Snail
        }, },
        { {  // kind 1
            { 255,  31,  31, 255 },  // variant 0: slot1 Horklump, slot2 Horklump
            {  24,   9,  24, 255 },  // variant 1: slot0 Large Orange Snail, slot1 Suit of Armor (Cavalier), slot2 Large Orange Snail
            { 255,  46,  46, 255 },  // variant 2: slot1 Amazonian Salamander, slot2 Amazonian Salamander
            {   9,  46,   9, 255 },  // variant 3: slot0 Suit of Armor (Cavalier), slot1 Amazonian Salamander, slot2 Suit of Armor (Cavalier)
        }, },
        { {  // kind 2
            {  46,  31,  46, 255 },  // variant 0: slot0 Amazonian Salamander, slot1 Horklump, slot2 Amazonian Salamander
            { 255,   9,   9, 255 },  // variant 1: slot1 Suit of Armor (Cavalier), slot2 Suit of Armor (Cavalier)
            {  31,  24,  31, 255 },  // variant 2: slot0 Horklump, slot1 Large Orange Snail, slot2 Horklump
            { 255,  24,  24, 255 },  // variant 3: slot1 Large Orange Snail, slot2 Large Orange Snail
        }, },
    }, },
    { {  // id 11: room 0 (Defense Against the Dark Arts Classroom)
        { {  // kind 0
            { 255,  40,  40, 255 },  // variant 0: slot1 Hinkypunk, slot2 Hinkypunk
            { 255,   8,   8, 255 },  // variant 1: slot1 Suit of Armor (Footman), slot2 Suit of Armor (Footman)
            {  42,  51,  42, 255 },  // variant 2: slot0 Grindylow, slot1 Wide-mouth Toad, slot2 Grindylow
            {  51,  51,  51, 255 },  // variant 3: slot0 Wide-mouth Toad, slot1 Wide-mouth Toad, slot2 Wide-mouth Toad
        }, },
        { {  // kind 1
            {  51,  40,  51, 255 },  // variant 0: slot0 Wide-mouth Toad, slot1 Hinkypunk, slot2 Wide-mouth Toad
            {   8,  42,   8, 255 },  // variant 1: slot0 Suit of Armor (Footman), slot1 Grindylow, slot2 Suit of Armor (Footman)
            { 255,  42,  42, 255 },  // variant 2: slot1 Grindylow, slot2 Grindylow
            {  40,  51,  40, 255 },  // variant 3: slot0 Hinkypunk, slot1 Wide-mouth Toad, slot2 Hinkypunk
        }, },
        { {  // kind 2
            {  51,  40,  51, 255 },  // variant 0: slot0 Wide-mouth Toad, slot1 Hinkypunk, slot2 Wide-mouth Toad
            {   8,  42,   8, 255 },  // variant 1: slot0 Suit of Armor (Footman), slot1 Grindylow, slot2 Suit of Armor (Footman)
            { 255,  42,  42, 255 },  // variant 2: slot1 Grindylow, slot2 Grindylow
            {  40,  51,  40, 255 },  // variant 3: slot0 Hinkypunk, slot1 Wide-mouth Toad, slot2 Hinkypunk
        }, },
    }, },
    { {  // id 12: room 27 (Staff Room)
        { {  // kind 0
            { 255,   2,   2, 255 },  // variant 0: slot1 Sapphire Fire Crab, slot2 Sapphire Fire Crab
            {  18,  18,  18, 255 },  // variant 1: slot0 Redback Spider, slot1 Redback Spider, slot2 Redback Spider
            {  18,   2,  18, 255 },  // variant 2: slot0 Redback Spider, slot1 Sapphire Fire Crab, slot2 Redback Spider
            {  35,  35,  35, 255 },  // variant 3: slot0 Tarantula Hawk Wasp, slot1 Tarantula Hawk Wasp, slot2 Tarantula Hawk Wasp
        }, },
        { {  // kind 1
            {  18,   2,  18, 255 },  // variant 0: slot0 Redback Spider, slot1 Sapphire Fire Crab, slot2 Redback Spider
            {  35,  35,  35, 255 },  // variant 1: slot0 Tarantula Hawk Wasp, slot1 Tarantula Hawk Wasp, slot2 Tarantula Hawk Wasp
            { 255,   2,   2, 255 },  // variant 2: slot1 Sapphire Fire Crab, slot2 Sapphire Fire Crab
            {  18,  18,  18, 255 },  // variant 3: slot0 Redback Spider, slot1 Redback Spider, slot2 Redback Spider
        }, },
        { {  // kind 2
            {  18,   2,  18, 255 },  // variant 0: slot0 Redback Spider, slot1 Sapphire Fire Crab, slot2 Redback Spider
            {  35,  35,  35, 255 },  // variant 1: slot0 Tarantula Hawk Wasp, slot1 Tarantula Hawk Wasp, slot2 Tarantula Hawk Wasp
            { 255,   2,   2, 255 },  // variant 2: slot1 Sapphire Fire Crab, slot2 Sapphire Fire Crab
            {  18,  18,  18, 255 },  // variant 3: slot0 Redback Spider, slot1 Redback Spider, slot2 Redback Spider
        }, },
    }, },
    { {  // id 13: room 17 (Great Hall)
        { {  // kind 0
            {   2,  19,   2, 255 },  // variant 0: slot0 Sapphire Fire Crab, slot1 Giant Spider, slot2 Sapphire Fire Crab
            { 255,  45,  45, 255 },  // variant 1: slot1 Salamander, slot2 Salamander
            {  45,   2,  45, 255 },  // variant 2: slot0 Salamander, slot1 Sapphire Fire Crab, slot2 Salamander
            { 255,  19,  19, 255 },  // variant 3: slot1 Giant Spider, slot2 Giant Spider
        }, },
        { {  // kind 1
            {   2,  19,   2, 255 },  // variant 0: slot0 Sapphire Fire Crab, slot1 Giant Spider, slot2 Sapphire Fire Crab
            { 255,  45,  45, 255 },  // variant 1: slot1 Salamander, slot2 Salamander
            {  45,   2,  45, 255 },  // variant 2: slot0 Salamander, slot1 Sapphire Fire Crab, slot2 Salamander
            { 255,  19,  19, 255 },  // variant 3: slot1 Giant Spider, slot2 Giant Spider
        }, },
        { {  // kind 2
            {   2,  19,   2, 255 },  // variant 0: slot0 Sapphire Fire Crab, slot1 Giant Spider, slot2 Sapphire Fire Crab
            { 255,  45,  45, 255 },  // variant 1: slot1 Salamander, slot2 Salamander
            {  45,   2,  45, 255 },  // variant 2: slot0 Salamander, slot1 Sapphire Fire Crab, slot2 Salamander
            { 255,  19,  19, 255 },  // variant 3: slot1 Giant Spider, slot2 Giant Spider
        }, },
    }, },
    { {  // id 14: room 12 (Hagrid's Garden Maze)
        { {  // kind 0
            { 255,  41,  41, 255 },  // variant 0: slot1 Gytrash, slot2 Gytrash
            {  29,  22,  29, 255 },  // variant 1: slot0 Dragonfly, slot1 Flobberworm, slot2 Dragonfly
            {  22,  41,  22, 255 },  // variant 2: slot0 Flobberworm, slot1 Gytrash, slot2 Flobberworm
            { 255,  29,  29, 255 },  // variant 3: slot1 Dragonfly, slot2 Dragonfly
        }, },
        { {  // kind 1
            {  41,  41,  41, 255 },  // variant 0: slot0 Gytrash, slot1 Gytrash, slot2 Gytrash
            {  29,  22,  29, 255 },  // variant 1: slot0 Dragonfly, slot1 Flobberworm, slot2 Dragonfly
            {  22,  41,  22, 255 },  // variant 2: slot0 Flobberworm, slot1 Gytrash, slot2 Flobberworm
            {  29,  29,  29, 255 },  // variant 3: slot0 Dragonfly, slot1 Dragonfly, slot2 Dragonfly
        }, },
        { {  // kind 2
            {  41,  41,  41, 255 },  // variant 0: slot0 Gytrash, slot1 Gytrash, slot2 Gytrash
            {  29,  22,  29, 255 },  // variant 1: slot0 Dragonfly, slot1 Flobberworm, slot2 Dragonfly
            {  22,  41,  22, 255 },  // variant 2: slot0 Flobberworm, slot1 Gytrash, slot2 Flobberworm
            {  29,  29,  29, 255 },  // variant 3: slot0 Dragonfly, slot1 Dragonfly, slot2 Dragonfly
        }, },
    }, },
    { {  // id 15: room 8 (Hogwarts Grounds - Castle Doors), room 9 (Hogwarts Grounds - Boathouse), room 10 (Hogwarts Grounds - Greenhouses), room 11 (Hagrid's Hut)
        { {  // kind 0
            {  34,  34,  34, 255 },  // variant 0: slot0 Wasp, slot1 Wasp, slot2 Wasp
            {  29,   0,  29, 255 },  // variant 1: slot0 Dragonfly, slot1 Ruby Fire Crab, slot2 Dragonfly
            { 255,  41, 255, 255 },  // variant 2: slot1 Gytrash
            { 255,  29,  29, 255 },  // variant 3: slot1 Dragonfly, slot2 Dragonfly
        }, },
        { {  // kind 1
            {  41,  41,  41, 255 },  // variant 0: slot0 Gytrash, slot1 Gytrash, slot2 Gytrash
            {   0,  41,   0, 255 },  // variant 1: slot0 Ruby Fire Crab, slot1 Gytrash, slot2 Ruby Fire Crab
            { 255,  29,  29, 255 },  // variant 2: slot1 Dragonfly, slot2 Dragonfly
            {  34,   0,  34, 255 },  // variant 3: slot0 Wasp, slot1 Ruby Fire Crab, slot2 Wasp
        }, },
        { {  // kind 2
            {  41,  41,  41, 255 },  // variant 0: slot0 Gytrash, slot1 Gytrash, slot2 Gytrash
            {   0,  41,   0, 255 },  // variant 1: slot0 Ruby Fire Crab, slot1 Gytrash, slot2 Ruby Fire Crab
            { 255,  29,  29, 255 },  // variant 2: slot1 Dragonfly, slot2 Dragonfly
            {  34,   0,  34, 255 },  // variant 3: slot0 Wasp, slot1 Ruby Fire Crab, slot2 Wasp
        }, },
    }, },
    { {  // id 16: no room references
        { {  // kind 0
            { 255,  36, 255, 255 },  // variant 0: slot1 Bowtruckle
            { 255,  46, 255, 255 },  // variant 1: slot1 Amazonian Salamander
            { 255,  33, 255, 255 },  // variant 2: slot1 Spitting Snake
            { 255,   2, 255, 255 },  // variant 3: slot1 Sapphire Fire Crab
        }, },
        { {  // kind 1
            { 255,  36, 255, 255 },  // variant 0: slot1 Bowtruckle
            { 255,  46, 255, 255 },  // variant 1: slot1 Amazonian Salamander
            { 255,  33, 255, 255 },  // variant 2: slot1 Spitting Snake
            { 255,   2, 255, 255 },  // variant 3: slot1 Sapphire Fire Crab
        }, },
        { {  // kind 2
            { 255,  36, 255, 255 },  // variant 0: slot1 Bowtruckle
            { 255,  46, 255, 255 },  // variant 1: slot1 Amazonian Salamander
            { 255,  33, 255, 255 },  // variant 2: slot1 Spitting Snake
            { 255,   2, 255, 255 },  // variant 3: slot1 Sapphire Fire Crab
        }, },
    }, },
    { {  // id 17: room 25 (Rooftop)
        { {  // kind 0
            { 255,  14,  14, 255 },  // variant 0: slot1 Suit of Armor (Knight), slot2 Suit of Armor (Knight)
            { 255,  12,  12, 255 },  // variant 1: slot1 Suit of Armor (Swordsman), slot2 Suit of Armor (Swordsman)
            { 255,  39,  39, 255 },  // variant 2: slot1 Doxy Queen, slot2 Doxy Queen
            { 255,  44,  44, 255 },  // variant 3: slot1 Armored Red Cap, slot2 Armored Red Cap
        }, },
        { {  // kind 1
            { 255,  14,  14, 255 },  // variant 0: slot1 Suit of Armor (Knight), slot2 Suit of Armor (Knight)
            { 255,  12,  12, 255 },  // variant 1: slot1 Suit of Armor (Swordsman), slot2 Suit of Armor (Swordsman)
            { 255,  39,  39, 255 },  // variant 2: slot1 Doxy Queen, slot2 Doxy Queen
            { 255,  44,  44, 255 },  // variant 3: slot1 Armored Red Cap, slot2 Armored Red Cap
        }, },
        { {  // kind 2
            { 255,  14,  14, 255 },  // variant 0: slot1 Suit of Armor (Knight), slot2 Suit of Armor (Knight)
            { 255,  12,  12, 255 },  // variant 1: slot1 Suit of Armor (Swordsman), slot2 Suit of Armor (Swordsman)
            { 255,  39,  39, 255 },  // variant 2: slot1 Doxy Queen, slot2 Doxy Queen
            { 255,  44,  44, 255 },  // variant 3: slot1 Armored Red Cap, slot2 Armored Red Cap
        }, },
    }, },
    { {  // id 18: room 15 (Hogwarts Grounds - Whomping Willow)
        { {  // kind 0
            {  34,  34,  34, 255 },  // variant 0: slot0 Wasp, slot1 Wasp, slot2 Wasp
            {  50,  50,  50, 255 },  // variant 1: slot0 Tree Frog, slot1 Tree Frog, slot2 Tree Frog
            { 255,  41,  41, 255 },  // variant 2: slot1 Gytrash, slot2 Gytrash
            { 255,  36,  36, 255 },  // variant 3: slot1 Bowtruckle, slot2 Bowtruckle
        }, },
        { {  // kind 1
            { 255,  36,  36, 255 },  // variant 0: slot1 Bowtruckle, slot2 Bowtruckle
            { 255,  50,  50, 255 },  // variant 1: slot1 Tree Frog, slot2 Tree Frog
            { 255,  32,  32, 255 },  // variant 2: slot1 Snake, slot2 Snake
            { 255,  36,  36, 255 },  // variant 3: slot1 Bowtruckle, slot2 Bowtruckle
        }, },
        { {  // kind 2
            { 255,  36,  36, 255 },  // variant 0: slot1 Bowtruckle, slot2 Bowtruckle
            { 255,  50,  50, 255 },  // variant 1: slot1 Tree Frog, slot2 Tree Frog
            { 255,  32,  32, 255 },  // variant 2: slot1 Snake, slot2 Snake
            { 255,  36,  36, 255 },  // variant 3: slot1 Bowtruckle, slot2 Bowtruckle
        }, },
    }, },
    { {  // id 19: room 13 (Hogwarts Grounds - Lake)
        { {  // kind 0
            { 255,  52,  52, 255 },  // variant 0: slot1 Bullfrog, slot2 Bullfrog
            { 255,  40,  40, 255 },  // variant 1: slot1 Hinkypunk, slot2 Hinkypunk
            {  52,  25,  52, 255 },  // variant 2: slot0 Bullfrog, slot1 Flailtail Snail, slot2 Bullfrog
            { 255,  25,  25, 255 },  // variant 3: slot1 Flailtail Snail, slot2 Flailtail Snail
        }, },
        { {  // kind 1
            { 255,  52,  52, 255 },  // variant 0: slot1 Bullfrog, slot2 Bullfrog
            { 255,  40,  40, 255 },  // variant 1: slot1 Hinkypunk, slot2 Hinkypunk
            {  52,  25,  52, 255 },  // variant 2: slot0 Bullfrog, slot1 Flailtail Snail, slot2 Bullfrog
            { 255,  25,  25, 255 },  // variant 3: slot1 Flailtail Snail, slot2 Flailtail Snail
        }, },
        { {  // kind 2
            { 255,  52,  52, 255 },  // variant 0: slot1 Bullfrog, slot2 Bullfrog
            { 255,  40,  40, 255 },  // variant 1: slot1 Hinkypunk, slot2 Hinkypunk
            {  52,  25,  52, 255 },  // variant 2: slot0 Bullfrog, slot1 Flailtail Snail, slot2 Bullfrog
            { 255,  25,  25, 255 },  // variant 3: slot1 Flailtail Snail, slot2 Flailtail Snail
        }, },
    }, },
    { {  // id 20: room 14 (Path to Hagrid's Hut)
        { {  // kind 0
            { 255,  37,  37, 255 },  // variant 0: slot1 Oaken Bowtruckle, slot2 Oaken Bowtruckle
            { 255,  47,  47, 255 },  // variant 1: slot1 Peruvian Salamander, slot2 Peruvian Salamander
            {  33,  21,  33, 255 },  // variant 2: slot0 Spitting Snake, slot1 Whitetail Spider, slot2 Spitting Snake
            { 255,  52,  52, 255 },  // variant 3: slot1 Bullfrog, slot2 Bullfrog
        }, },
        { {  // kind 1
            { 255,  37,  37, 255 },  // variant 0: slot1 Oaken Bowtruckle, slot2 Oaken Bowtruckle
            {  47,  21,  47, 255 },  // variant 1: slot0 Peruvian Salamander, slot1 Whitetail Spider, slot2 Peruvian Salamander
            { 255,  33,  33, 255 },  // variant 2: slot1 Spitting Snake, slot2 Spitting Snake
            { 255,  52,  52, 255 },  // variant 3: slot1 Bullfrog, slot2 Bullfrog
        }, },
        { {  // kind 2
            {  21,  37,  21, 255 },  // variant 0: slot0 Whitetail Spider, slot1 Oaken Bowtruckle, slot2 Whitetail Spider
            { 255,  47,  47, 255 },  // variant 1: slot1 Peruvian Salamander, slot2 Peruvian Salamander
            {  33,  21,  33, 255 },  // variant 2: slot0 Spitting Snake, slot1 Whitetail Spider, slot2 Spitting Snake
            { 255,  52,  52, 255 },  // variant 3: slot1 Bullfrog, slot2 Bullfrog
        }, },
    }, },
    { {  // id 21: room 43 (Shrieking Shack Interior), room 44 (Shrieking Shack Path), room 46 (Shrieking Shack - Path 3), room 47 (Shrieking Shack - Path 4), room 48 (Shrieking Shack - Path 5), room 49 (Shrieking Shack - Path 6)
        { {  // kind 0
            { 255,  48,  48, 255 },  // variant 0: slot1 Charmed Skeleton, slot2 Charmed Skeleton
            { 255,  49,  49, 255 },  // variant 1: slot1 Jinxed Skeleton, slot2 Jinxed Skeleton
            { 255,  20,  20, 255 },  // variant 2: slot1 Cocoon Spider, slot2 Cocoon Spider
            { 255,  14,  14, 255 },  // variant 3: slot1 Suit of Armor (Knight), slot2 Suit of Armor (Knight)
        }, },
        { {  // kind 1
            { 255,  48,  48, 255 },  // variant 0: slot1 Charmed Skeleton, slot2 Charmed Skeleton
            {  49,  48,  49, 255 },  // variant 1: slot0 Jinxed Skeleton, slot1 Charmed Skeleton, slot2 Jinxed Skeleton
            { 255,  20,  20, 255 },  // variant 2: slot1 Cocoon Spider, slot2 Cocoon Spider
            { 255,  14,  14, 255 },  // variant 3: slot1 Suit of Armor (Knight), slot2 Suit of Armor (Knight)
        }, },
        { {  // kind 2
            { 255,  48,  48, 255 },  // variant 0: slot1 Charmed Skeleton, slot2 Charmed Skeleton
            {  49,  48,  49, 255 },  // variant 1: slot0 Jinxed Skeleton, slot1 Charmed Skeleton, slot2 Jinxed Skeleton
            { 255,  20,  20, 255 },  // variant 2: slot1 Cocoon Spider, slot2 Cocoon Spider
            { 255,  14,  14, 255 },  // variant 3: slot1 Suit of Armor (Knight), slot2 Suit of Armor (Knight)
        }, },
    }, },
    { {  // id 22: room 45 (Shrieking Shack - Path 2)
        { {  // kind 0
            { 255,  48, 255, 255 },  // variant 0: slot1 Charmed Skeleton
            { 255,  49, 255, 255 },  // variant 1: slot1 Jinxed Skeleton
            { 255,  20, 255, 255 },  // variant 2: slot1 Cocoon Spider
            { 255,  14, 255, 255 },  // variant 3: slot1 Suit of Armor (Knight)
        }, },
        { {  // kind 1
            { 255,  48, 255, 255 },  // variant 0: slot1 Charmed Skeleton
            { 255,  49, 255, 255 },  // variant 1: slot1 Jinxed Skeleton
            { 255,  20, 255, 255 },  // variant 2: slot1 Cocoon Spider
            { 255,  14, 255, 255 },  // variant 3: slot1 Suit of Armor (Knight)
        }, },
        { {  // kind 2
            { 255,  48, 255, 255 },  // variant 0: slot1 Charmed Skeleton
            { 255,  49, 255, 255 },  // variant 1: slot1 Jinxed Skeleton
            { 255,  20, 255, 255 },  // variant 2: slot1 Cocoon Spider
            { 255,  14, 255, 255 },  // variant 3: slot1 Suit of Armor (Knight)
        }, },
    }, },
    { {  // id 23: no room references
        { {  // kind 0
            { 255,  48, 255, 255 },  // variant 0: slot1 Charmed Skeleton
            { 255,  49, 255, 255 },  // variant 1: slot1 Jinxed Skeleton
            { 255,  21, 255, 255 },  // variant 2: slot1 Whitetail Spider
            { 255,  14, 255, 255 },  // variant 3: slot1 Suit of Armor (Knight)
        }, },
        { {  // kind 1
            { 255,  48, 255, 255 },  // variant 0: slot1 Charmed Skeleton
            { 255,  49, 255, 255 },  // variant 1: slot1 Jinxed Skeleton
            { 255,  21, 255, 255 },  // variant 2: slot1 Whitetail Spider
            { 255,  14, 255, 255 },  // variant 3: slot1 Suit of Armor (Knight)
        }, },
        { {  // kind 2
            { 255,  48, 255, 255 },  // variant 0: slot1 Charmed Skeleton
            { 255,  49, 255, 255 },  // variant 1: slot1 Jinxed Skeleton
            { 255,  21, 255, 255 },  // variant 2: slot1 Whitetail Spider
            { 255,  14, 255, 255 },  // variant 3: slot1 Suit of Armor (Knight)
        }, },
    }, },
    { {  // id 24: no room references
        { {  // kind 0
            { 255,  48, 255, 255 },  // variant 0: slot1 Charmed Skeleton
            { 255,  49, 255, 255 },  // variant 1: slot1 Jinxed Skeleton
            { 255,  21, 255, 255 },  // variant 2: slot1 Whitetail Spider
            { 255,  14, 255, 255 },  // variant 3: slot1 Suit of Armor (Knight)
        }, },
        { {  // kind 1
            { 255,  48, 255, 255 },  // variant 0: slot1 Charmed Skeleton
            { 255,  49, 255, 255 },  // variant 1: slot1 Jinxed Skeleton
            { 255,  21, 255, 255 },  // variant 2: slot1 Whitetail Spider
            { 255,  14, 255, 255 },  // variant 3: slot1 Suit of Armor (Knight)
        }, },
        { {  // kind 2
            { 255,  48, 255, 255 },  // variant 0: slot1 Charmed Skeleton
            { 255,  49, 255, 255 },  // variant 1: slot1 Jinxed Skeleton
            { 255,  21, 255, 255 },  // variant 2: slot1 Whitetail Spider
            { 255,  14, 255, 255 },  // variant 3: slot1 Suit of Armor (Knight)
        }, },
    }, },
    { {  // id 25: room 22 (Fifth Floor), room 23 (Sixth Floor)
        { {  // kind 0
            { 255,   8,   8, 255 },  // variant 0: slot1 Suit of Armor (Footman), slot2 Suit of Armor (Footman)
            {   8,   0,   8, 255 },  // variant 1: slot0 Suit of Armor (Footman), slot1 Ruby Fire Crab, slot2 Suit of Armor (Footman)
            {  10,  10,  10, 255 },  // variant 2: slot0 Suit of Armor (Paladin), slot1 Suit of Armor (Paladin), slot2 Suit of Armor (Paladin)
            {   0,  10,   0, 255 },  // variant 3: slot0 Ruby Fire Crab, slot1 Suit of Armor (Paladin), slot2 Ruby Fire Crab
        }, },
        { {  // kind 1
            { 255,   8,   8, 255 },  // variant 0: slot1 Suit of Armor (Footman), slot2 Suit of Armor (Footman)
            {   8,   0,   8, 255 },  // variant 1: slot0 Suit of Armor (Footman), slot1 Ruby Fire Crab, slot2 Suit of Armor (Footman)
            {  10,  10,  10, 255 },  // variant 2: slot0 Suit of Armor (Paladin), slot1 Suit of Armor (Paladin), slot2 Suit of Armor (Paladin)
            {   0,  10,   0, 255 },  // variant 3: slot0 Ruby Fire Crab, slot1 Suit of Armor (Paladin), slot2 Ruby Fire Crab
        }, },
        { {  // kind 2
            { 255,   8,   8, 255 },  // variant 0: slot1 Suit of Armor (Footman), slot2 Suit of Armor (Footman)
            {   8,   0,   8, 255 },  // variant 1: slot0 Suit of Armor (Footman), slot1 Ruby Fire Crab, slot2 Suit of Armor (Footman)
            {  10,  10,  10, 255 },  // variant 2: slot0 Suit of Armor (Paladin), slot1 Suit of Armor (Paladin), slot2 Suit of Armor (Paladin)
            {   0,  10,   0, 255 },  // variant 3: slot0 Ruby Fire Crab, slot1 Suit of Armor (Paladin), slot2 Ruby Fire Crab
        }, },
    }, },
    { {  // id 26: no room references
        { {  // kind 0
            { 255,  48, 255, 255 },  // variant 0: slot1 Charmed Skeleton
            { 255,  49, 255, 255 },  // variant 1: slot1 Jinxed Skeleton
            { 255,  20, 255, 255 },  // variant 2: slot1 Cocoon Spider
            { 255,  14, 255, 255 },  // variant 3: slot1 Suit of Armor (Knight)
        }, },
        { {  // kind 1
            { 255,  48, 255, 255 },  // variant 0: slot1 Charmed Skeleton
            { 255,  49, 255, 255 },  // variant 1: slot1 Jinxed Skeleton
            { 255,  20, 255, 255 },  // variant 2: slot1 Cocoon Spider
            { 255,  14, 255, 255 },  // variant 3: slot1 Suit of Armor (Knight)
        }, },
        { {  // kind 2
            { 255,  48, 255, 255 },  // variant 0: slot1 Charmed Skeleton
            { 255,  49, 255, 255 },  // variant 1: slot1 Jinxed Skeleton
            { 255,  20, 255, 255 },  // variant 2: slot1 Cocoon Spider
            { 255,  14, 255, 255 },  // variant 3: slot1 Suit of Armor (Knight)
        }, },
    }, },
    { {  // id 27: room 50 (Diagon Alley Test Map1)
        { {  // kind 0
            {  61,  22, 255, 255 },  // variant 0: slot0 Draco, slot1 Flobberworm
            {  59, 255,  23, 255 },  // variant 1: slot0 Giant Rat, slot2 Snail
            {  60,  26, 255, 255 },  // variant 2: slot0 Crabbe, slot1 Bat
            { 255,  62,  29, 255 },  // variant 3: slot1 Goyle, slot2 Dragonfly
        }, },
        { {  // kind 1
            { 255, 255, 255, 255 },  // variant 0: (empty)
            { 255, 255, 255, 255 },  // variant 1: (empty)
            { 255, 255, 255, 255 },  // variant 2: (empty)
            { 255, 255, 255, 255 },  // variant 3: (empty)
        }, },
        { {  // kind 2
            { 255, 255, 255, 255 },  // variant 0: (empty)
            { 255, 255, 255, 255 },  // variant 1: (empty)
            { 255, 255, 255, 255 },  // variant 2: (empty)
            { 255, 255, 255, 255 },  // variant 3: (empty)
        }, },
    }, },
    { {  // id 28: room 51 (Diagon Alley Test Map 2)
        { {  // kind 0
            { 255,  48,  29, 255 },  // variant 0: slot1 Charmed Skeleton, slot2 Dragonfly
            { 255,  48,  29, 255 },  // variant 1: slot1 Charmed Skeleton, slot2 Dragonfly
            { 255,  48,  29, 255 },  // variant 2: slot1 Charmed Skeleton, slot2 Dragonfly
            { 255,  48,  29, 255 },  // variant 3: slot1 Charmed Skeleton, slot2 Dragonfly
        }, },
        { {  // kind 1
            { 255,  48,  29, 255 },  // variant 0: slot1 Charmed Skeleton, slot2 Dragonfly
            { 255,  48,  29, 255 },  // variant 1: slot1 Charmed Skeleton, slot2 Dragonfly
            { 255,  48,  29, 255 },  // variant 2: slot1 Charmed Skeleton, slot2 Dragonfly
            { 255,  48,  29, 255 },  // variant 3: slot1 Charmed Skeleton, slot2 Dragonfly
        }, },
        { {  // kind 2
            { 255,  48,  29, 255 },  // variant 0: slot1 Charmed Skeleton, slot2 Dragonfly
            { 255,  48,  29, 255 },  // variant 1: slot1 Charmed Skeleton, slot2 Dragonfly
            { 255,  48,  29, 255 },  // variant 2: slot1 Charmed Skeleton, slot2 Dragonfly
            { 255,  48,  29, 255 },  // variant 3: slot1 Charmed Skeleton, slot2 Dragonfly
        }, },
    }, },
    { {  // id 29: room 52 (Diagon Alley Test Map 3)
        { {  // kind 0
            { 255,  38, 255, 255 },  // variant 0: slot1 Doxy
            {  40, 255, 255, 255 },  // variant 1: slot0 Hinkypunk
            { 255,  41, 255, 255 },  // variant 2: slot1 Gytrash
            { 255, 255,  42, 255 },  // variant 3: slot2 Grindylow
        }, },
        { {  // kind 1
            { 255, 255, 255, 255 },  // variant 0: (empty)
            { 255, 255, 255, 255 },  // variant 1: (empty)
            { 255, 255, 255, 255 },  // variant 2: (empty)
            { 255, 255, 255, 255 },  // variant 3: (empty)
        }, },
        { {  // kind 2
            { 255, 255, 255, 255 },  // variant 0: (empty)
            { 255, 255, 255, 255 },  // variant 1: (empty)
            { 255, 255, 255, 255 },  // variant 2: (empty)
            { 255, 255, 255, 255 },  // variant 3: (empty)
        }, },
    }, },
};
