#include "encounters.h"

// Scripted-fight enemy roster: g_dwCurrentGameModeArg1 selects the row
// when g_dwCurrentGameModeArg3 == 0xFF. Trigger rooms from quest-stage-0
// room scripts (opcode StartBattle); all quest stages 0-34 were scanned.
// See docs/formats/encounters.md.
const u8 g_aScriptedEncounters[15][4] = {
    { 255,  58, 255, 255 },  // fight 0: slot1 'The Monster Book of Monsters'; room 41 (Leaky Cauldron - Harry's Room)
    { 255,  59, 255, 255 },  // fight 1: slot1 Giant Rat; room 38 (Leaky Cauldron - Cellar 1)
    { 255,  54, 255, 255 },  // fight 2: slot1 Whomping Willow; room 15 (Hogwarts Grounds - Whomping Willow)
    { 255,  63, 255, 255 },  // fight 3: slot1 Lupin Werewolf; room 13 (Hogwarts Grounds - Lake)
    {  60,  62, 255, 255 },  // fight 4: slot0 Crabbe, slot1 Goyle; room 4 (Transfiguration Classroom Maze)
    { 255,  61, 255, 255 },  // fight 5: slot1 Draco; room 25 (Rooftop)
    { 255,  66, 255, 255 },  // fight 6: slot1 'The Monster Book of Monsters'; room 12 (Hagrid's Garden Maze)
    { 255,  57, 255, 255 },  // fight 7: slot1 Venemous Tentacula; room 12 (Hagrid's Garden Maze)
    { 255,  55, 255, 255 },  // fight 8: slot1 Forest Troll; room 44 (Shrieking Shack Path)
    { 255,  56, 255, 255 },  // fight 9: slot1 River Troll; room 2 (Potions Classroom Maze)
    { 255,  67, 255, 255 },  // fight 10: slot1 'The Monster Book of Monsters'; room 35 (Library)
    { 255,  49, 255, 255 },  // fight 11: slot1 Jinxed Skeleton; room 45 (Shrieking Shack - Path 2)
    {  64, 255,  65, 255 },  // fight 12: slot0 Snake, slot2 Brown Recluse Spider; room 5 (Hogwarts Express - Baggage Car, quest stage 2)
    { 255,  65, 255, 255 },  // fight 13: slot1 Brown Recluse Spider; room 6 (Hogwarts Express - Passenger Car, quest stage 3)
    { 255,  66, 255, 255 },  // fight 14: slot1 'The Monster Book of Monsters'; no trigger in any quest stage 0-34
};
