#include "types.h"
#include "menu/help.h"

// Help screen page scripts, interpreted by the help engine one 32-bit word at a time (see
// menu/help.h). Each array holds a topic's pages in order; the menus link to the first page.

const u32 g_aHelpFolioUniversitas[] = {
    // page 1/5
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpFolioUniversitas[14]),
    HELP_TITLE(0x40D),  // "Folio Universitas"
    // "The Folio Universitas displays the collector's cards and the Card Combos you have
    //  collected."
    HELP_TEXT(12, 48, 212, 104, 0x5DF),
    // "Each card category is separated into three combinations with three cards each. A rare tenth
    //  card can be collected in each category as well. Collect all ten cards in a category to
    //  unlock the treasure chests in the Wizard Card Collectors' Club."
    HELP_TEXT(12, 88, 212, 104, 0x5E0),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 5),
    HELP_END,

    // page 2/5
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpFolioUniversitas),
    HELP_NEXT_PAGE(&g_aHelpFolioUniversitas[28]),
    HELP_TITLE(0x40D),  // "Folio Universitas"
    // "If a card has not yet been collected, the card slot will be grey. When a card is collected,
    //  the slot for that card will turn from grey to gold. If a card is pulsing, it has been
    //  collected since the Folio was last viewed."
    HELP_TEXT(12, 48, 212, 104, 0x5E1),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(2, 5),
    HELP_END,

    // page 3/5
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpFolioUniversitas[14]),
    HELP_NEXT_PAGE(&g_aHelpFolioUniversitas[42]),
    HELP_TITLE(0x40D),  // "Folio Universitas"
    // "Use the +Control Pad to move the cursor around the combo grid. Each highlighted combo will
    //  display a larger representation of the cards at the bottom of the screen. To see more
    //  information about a highlighted card, press the A Button. A large representation of the card
    //  will be displayed, as well as a brief description. Press any Button to return to the Folio
    //  Universitas screen."
    HELP_TEXT(12, 48, 212, 104, 0x5E2),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(3, 5),
    HELP_END,

    // page 4/5
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpFolioUniversitas[28]),
    HELP_NEXT_PAGE(&g_aHelpFolioUniversitas[56]),
    HELP_TITLE(0x40D),  // "Folio Universitas"
    // "To see detailed information about a Card Combo, press Select. A small window will pop up
    //  with a description of that combo. If you have at least one of the three cards, a check
    //  appears next to the combo. Press any Button to remove the window and show the Folio
    //  Universitas again."
    HELP_TEXT(12, 48, 212, 104, 0x5E3),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(4, 5),
    HELP_END,

    // page 5/5
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpFolioUniversitas[42]),
    HELP_TITLE(0x40D),  // "Folio Universitas"
    HELP_TEXT(12, 48, 212, 104, 0x5E4),  // "To exit back to the Main Menu, press the B Button."
    // "Hint: Look for cards in and around Hogwarts. Collect as many cards as you can to unlock
    //  bonuses and special features. Don't forget to visit the Wizard Card Collectors' Club,
    //  classroom 5B, to unlock special treasure chests."
    HELP_TEXT(12, 80, 212, 104, 0x5E5),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(5, 5),
    HELP_END,
};

const u32 g_aHelpFolioBruti[] = {
    // page 1/5
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpFolioBruti[11]),
    HELP_TITLE(0x8F4),  // "Folio Bruti"
    // "The Folio Bruti shows the names and pictures of beasts encountered during a game. If you
    //  cast Informus on a beast during a magical encounter, the Folio Bruti stores information on
    //  its strengths and weaknesses. Use it to prepare for future encounters."
    HELP_TEXT(12, 48, 212, 104, 0x5B7),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 5),
    HELP_END,

    // page 2/5
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpFolioBruti),
    HELP_NEXT_PAGE(&g_aHelpFolioBruti[25]),
    HELP_TITLE(0x8F4),  // "Folio Bruti"
    // "A grid of squares represents each creature in the game. A tick will appear in the box
    //  corresponding to any creature you have used Informus on. Detailed information about its
    //  strengths and weaknesses can also be found here."
    HELP_TEXT(12, 48, 212, 104, 0x5B8),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(2, 5),
    HELP_END,

    // page 3/5
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpFolioBruti[11]),
    HELP_NEXT_PAGE(&g_aHelpFolioBruti[39]),
    HELP_TITLE(0x8F4),  // "Folio Bruti"
    // "The bars at the bottom of the screen indicate how strong or weak the creature's resistance
    //  is to each of the player's spells. The weaker the creature's resistance to a spell, the
    //  further to the right the indicator on the bar will be."
    HELP_TEXT(12, 48, 212, 104, 0x5BC),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(3, 5),
    HELP_END,

    // page 4/5
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpFolioBruti[25]),
    HELP_NEXT_PAGE(&g_aHelpFolioBruti[53]),
    HELP_TITLE(0x8F4),  // "Folio Bruti"
    // "If you have a magical encounter with a creature but don't cast Informus, a simple dot will
    //  appear in the grid square. No detailed information will be available."
    HELP_TEXT(12, 48, 212, 104, 0x5B9),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(4, 5),
    HELP_END,

    // page 5/5
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpFolioBruti[39]),
    HELP_TITLE(0x8F4),  // "Folio Bruti"
    // "Creatures not yet encountered will appear as a silhouette."
    HELP_TEXT(12, 48, 212, 104, 0x5BA),
    // "Use the +Control Pad to move the cursor around the grid. The creature's image, description
    //  and information will update as the cursor is moved. Press the B Button to exit the Folio
    //  Bruti."
    HELP_TEXT(12, 80, 212, 104, 0x5BB),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(5, 5),
    HELP_END,
};

const u32 g_aHelpTradeCards[] = {
    // page 1/4
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpTradeCards[14]),
    HELP_TITLE(0x8C8),  // "Trade Cards"
    // "Trade collector's cards with your friends. To trade cards, both players must have a Harry
    //  Potter and the Prisoner of Azkaban game and connect their games together via the Game Boy(R)
    //  Advance Game Link(R) cable."
    HELP_TEXT(12, 48, 212, 104, 0x8D2),
    // "During the game, each player needs to access the Main Menu by pressing START. Select
    //  Connectivity and then Trade Cards."
    HELP_TEXT(12, 104, 212, 104, 0x8D3),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 4),
    HELP_END,

    // page 2/4
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpTradeCards),
    HELP_NEXT_PAGE(&g_aHelpTradeCards[28]),
    HELP_TITLE(0x8C8),  // "Trade Cards"
    // "The screen is divided in half. The left side of the screen displays your selection and the
    //  right side what your friend is selecting. Select Choose Card to pick a card from your Folio
    //  Universitas. Whatever card the other player has selected appears on the right side of the
    //  screen. You can change your selection by choosing Choose Card again and picking another
    //  card."
    HELP_TEXT(12, 48, 212, 104, 0x8D4),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(2, 4),
    HELP_END,

    // page 3/4
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpTradeCards[14]),
    HELP_NEXT_PAGE(&g_aHelpTradeCards[45]),
    HELP_TITLE(0x8C8),  // "Trade Cards"
    // "Once each person has chosen their cards, select Trade Cards to initiate a trade. Once the
    //  trade is complete, you can trade more cards or Exit back out to the Main Menu."
    HELP_TEXT(12, 48, 212, 104, 0x8D5),
    // "Hints: Trade cards to complete your collection, especially if you're only missing a few
    //  cards in a category. Your friends might have the card you need."
    HELP_TEXT(12, 96, 212, 104, 0x8D6),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(3, 4),
    HELP_END,

    // page 4/4
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpTradeCards[28]),
    HELP_TITLE(0x8C8),  // "Trade Cards"
    // "It's possible to just give a card to another player. If a player's portion of the screen is
    //  blank when selecting Trade Cards, it means that player isn't trading anything. It's a great
    //  way to help out your friends if they're struggling or starting a new card collection."
    HELP_TEXT(12, 48, 212, 104, 0x8D7),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(4, 4),
    HELP_END,
};

const u32 g_aHelpMagicalEncounters[] = {
    // page 1/17
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[11]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "Harry, Ron and Hermione duel with creatures in magical encounters gaining experience, items
    //  and Sickles. On the adventure map, you'll see magical clouds. Touching one will start a
    //  magical encounter."
    HELP_TEXT(12, 48, 212, 104, 0x5C7),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 17),
    HELP_END,

    // page 2/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpMagicalEncounters),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[25]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "Casting Informus on a creature allows the player to see that creature on the adventure map
    //  before entering a magical encounter with it. If the creature is with others, then the player
    //  will still see a magical cloud until all creatures have had Informus cast on them."
    HELP_TEXT(12, 48, 212, 104, 0x5DE),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(2, 17),
    HELP_END,

    // page 3/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[11]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[39]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "Several options are available. Use the +Control Pad to select different icons and press the
    //  A Button."
    HELP_TEXT(12, 48, 212, 104, 0x5C8),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(3, 17),
    HELP_END,

    // page 4/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[25]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[53]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "Selecting the Spell icon shows the current spells for a character. Harry, Ron and Hermione
    //  have slightly different sets of spells. Select a spell and choose the creature or party
    //  member you want to use it on."
    HELP_TEXT(12, 48, 212, 104, 0x5C9),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(4, 17),
    HELP_END,

    // page 5/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[39]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[67]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "You'll require Magic Points (MP) to use many of the spells. When selecting a spell, a
    //  number followed by MP appears, along with its name. If the spell is cast, that number of MP
    //  is deducted. You can't cast a spell if you don't have enough MP."
    HELP_TEXT(12, 48, 212, 104, 0x5DD),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(5, 17),
    HELP_END,

    // page 6/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[53]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[81]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "Selecting Special Moves brings up options unique to each character: Harry uses Card Combos,
    //  Ron uses Stink Pellets or Wizard Crackers, and Hermione lectures."
    HELP_TEXT(12, 48, 212, 104, 0x5CA),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(6, 17),
    HELP_END,

    // page 7/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[67]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[98]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "Selecting Items allows you to use potions in your Inventory to replenish Stamina Points,
    //  Magic Points, and reverse the effects of poison and paralysis."
    HELP_TEXT(12, 48, 212, 104, 0x5CB),
    // "Attempt to escape an encounter by selecting Flee. This doesn't always work, so be careful.
    //  (You might lose a turn!)"
    HELP_TEXT(12, 96, 212, 104, 0x5CC),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(7, 17),
    HELP_END,

    // page 8/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[81]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[112]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "Selecting Folio Bruti displays the same Folio Bruti available from the Main Menu. Use it,
    //  and the Informus Spell, to effectively plan your encounters."
    HELP_TEXT(12, 48, 212, 104, 0x5CD),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(8, 17),
    HELP_END,

    // page 9/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[98]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[126]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "The heads at the top of the screen show your party members, the creatures in the encounter
    //  and whose turn it is. Current Level, Magic Points (MP) and Stamina Points (SP) are shown
    //  next to the portraits of the characters. For creatures, only Stamina Points and Current
    //  Level are shown."
    HELP_TEXT(12, 48, 212, 104, 0x5CE),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(9, 17),
    HELP_END,

    // page 10/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[112]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[140]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "You can only enter commands for a character when they are selected. The highlighted head at
    //  the top of the screen shows whose turn it is. The action stops while you enter commands and
    //  select spells. Each character can execute only one command per turn and each creature can
    //  only attack once per turn."
    HELP_TEXT(12, 48, 212, 104, 0x5CF),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(10, 17),
    HELP_END,

    // page 11/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[126]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[154]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "Successfully winning an encounter displays the Results screen. Every encounter awards
    //  Experience Points (EXP) to each member of the party. In addition, creatures often leave
    //  behind varying quantities of Sickles and items (such as potions)."
    HELP_TEXT(12, 48, 212, 104, 0x5D0),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(11, 17),
    HELP_END,

    // page 12/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[140]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[168]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "At the beginning of a game, your spell selection will be limited. Learn new spells and
    //  spell levels by successfully winning magical encounters and leveling up. The more magical
    //  encounters Harry, Ron and Hermione win, the stronger they will become and the more effective
    //  their spells will be."
    HELP_TEXT(12, 48, 212, 104, 0x5D1),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(12, 17),
    HELP_END,

    // page 13/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[154]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[182]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "The following list explains what each spell does. As spells get more powerful, experiment
    //  with them to see if you can target more than one creature."
    HELP_TEXT(12, 48, 212, 104, 0x5D2),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(13, 17),
    HELP_END,

    // page 14/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[168]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[202]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "Flipendo - Knock-back Jinx. Can be used on an opponent."
    HELP_TEXT(12, 48, 212, 104, 0x5D3),
    // "Fumos - Defensive spell used in magical encounters."
    HELP_TEXT(12, 80, 212, 104, 0x5D4),
    HELP_TEXT(12, 112, 212, 104, 0x5D5),  // "Incendio - Fire-making charm."
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(14, 17),
    HELP_END,

    // page 15/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[182]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[222]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "Informus - Cast upon a creature to learn about its strengths and weaknesses."
    HELP_TEXT(12, 48, 212, 104, 0x5D6),
    HELP_TEXT(12, 80, 212, 104, 0x5D7),  // "Petrificus Totalus - Total body bind spell."
    HELP_TEXT(12, 112, 212, 104, 0x5D8),  // "Spongify - Turns target soft, rubbery and bouncy."
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(15, 17),
    HELP_END,

    // page 16/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[202]),
    HELP_NEXT_PAGE(&g_aHelpMagicalEncounters[242]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    HELP_TEXT(12, 48, 212, 104, 0x5D9),  // "Verdimillious - Fires a jet of green sparks."
    HELP_TEXT(12, 80, 212, 104, 0x5DA),  // "Wingardium Leviosa - Levitates small objects."
    HELP_TEXT(12, 112, 212, 104, 0x5DB),  // "Glacius - A freezing cold blast."
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(16, 17),
    HELP_END,

    // page 17/17
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpMagicalEncounters[222]),
    HELP_TITLE(0x5B4),  // "Magical Encounters"
    // "Diffindo - A severing charm. Can be used on plants."
    HELP_TEXT(12, 48, 212, 104, 0x5DC),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(17, 17),
    HELP_END,
};

const u32 g_aHelpEquipItems[] = {
    // page 1/4
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpEquipItems[11]),
    HELP_TITLE(0x5B3),  // "Equip Items"
    // "Throughout the game, you'll be able to find and purchase various items - such as hats,
    //  robes, gloves, shoes and belts. These can be worn by Harry, Ron or Hermione to improve their
    //  statistics and give them an advantage during magical encounters. In order to take advantage
    //  of an item, you'll need to equip it."
    HELP_TEXT(12, 48, 212, 104, 0x5BD),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 4),
    HELP_END,

    // page 2/4
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpEquipItems),
    HELP_NEXT_PAGE(&g_aHelpEquipItems[28]),
    HELP_TITLE(0x5B3),  // "Equip Items"
    // "Press START to bring up the Main Menu and select Status/Equip. Choose the member of your
    //  party that you want to equip."
    HELP_TEXT(12, 48, 212, 104, 0x5BE),
    // "On the Status/Equip screen, the character is surrounded by six boxes. Move the cursor to
    //  the item you want to equip or change and press the A Button."
    HELP_TEXT(12, 96, 212, 104, 0x5BF),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(2, 4),
    HELP_END,

    // page 3/4
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpEquipItems[11]),
    HELP_NEXT_PAGE(&g_aHelpEquipItems[42]),
    HELP_TITLE(0x5B3),  // "Equip Items"
    // "A list of items appears. Use the +Control Pad to select the item you want to equip. As you
    //  move the cursor, you can see how the statistics will change once equipped. Press the A
    //  Button to equip an item. If you want to remove an item and have nothing equipped, select the
    //  yellow Remove Arrow and press the A Button."
    HELP_TEXT(12, 48, 212, 104, 0x5C0),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(3, 4),
    HELP_END,

    // page 4/4
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpEquipItems[28]),
    HELP_TITLE(0x5B3),  // "Equip Items"
    // "Remember, some items can only be worn by certain party members. Look for special items in
    //  and around Hogwarts and don't forget to visit Fred and George's shop."
    HELP_TEXT(12, 48, 212, 104, 0x5C1),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(4, 4),
    HELP_END,
};

const u32 g_aHelpUsingItems[] = {
    // page 1/4
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpUsingItems[14]),
    HELP_TITLE(0x5B5),  // "Using Items"
    // "During the course of the game, you will find, purchase and acquire items - such as potions
    //  and potion ingredients."
    HELP_TEXT(12, 48, 212, 104, 0x5C2),
    // "Press START to bring up the Main Menu and then select Items. Select All to see all of the
    //  items you have at once, or select Potions or Miscellaneous to see only those types of items.
    //  Pressing the A Button brings up the appropriate list."
    HELP_TEXT(12, 88, 212, 104, 0x5C3),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 4),
    HELP_END,

    // page 2/4
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpUsingItems),
    HELP_NEXT_PAGE(&g_aHelpUsingItems[28]),
    HELP_TITLE(0x5B5),  // "Using Items"
    // "An item is displayed with a small icon, its name and the amount you are carrying. Use the
    //  +Control Pad to move up and down through the item list and press the A Button to use one. If
    //  there is more than one person in the party, you'll need to choose who benefits from the
    //  item."
    HELP_TEXT(12, 48, 212, 104, 0x5C4),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(2, 4),
    HELP_END,

    // page 3/4
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpUsingItems[14]),
    HELP_NEXT_PAGE(&g_aHelpUsingItems[42]),
    HELP_TITLE(0x5B5),  // "Using Items"
    // "Some items can only be used at certain times. If you receive a message telling you that you
    //  can't use a particular item, try using it at a different point in the game."
    HELP_TEXT(12, 48, 212, 104, 0x5C5),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(3, 4),
    HELP_END,

    // page 4/4
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpUsingItems[28]),
    HELP_TITLE(0x5B5),  // "Using Items"
    // "Potions are valuable. You can replenish Stamina and Magic Points with them so keep plenty
    //  on hand. Potions can be found, bought or acquired by defeating creatures in magical
    //  encounters."
    HELP_TEXT(12, 48, 212, 104, 0x5C6),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(4, 4),
    HELP_END,
};

const u32 g_aHelpWizardCrackerPopIt[] = {
    // page 1/3
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpWizardCrackerPopIt[14]),
    HELP_TITLE(0xA4A),  // "Wizard Cracker Pop-it"
    // "The object of the game is to pop as many Wizard Crackers as you can and get the highest
    //  score."
    HELP_TEXT(12, 48, 212, 104, 0x5E6),
    // "Use the +Control Pad to move the wand over the Wizard Crackers. When two or more of a color
    //  are next to each other, press the A Button and all the matching Wizard Crackers will pop."
    HELP_TEXT(12, 88, 212, 104, 0x5E7),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 3),
    HELP_END,

    // page 2/3
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpWizardCrackerPopIt),
    HELP_NEXT_PAGE(&g_aHelpWizardCrackerPopIt[28]),
    HELP_TITLE(0xA4A),  // "Wizard Cracker Pop-it"
    // "Different difficulty levels increase the number of colors for the Wizard Crackers. Easy =
    //  three colors, Medium = four colors, Hard = five colors."
    HELP_TEXT(12, 48, 212, 104, 0x5E8),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(2, 3),
    HELP_END,

    // page 3/3
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpWizardCrackerPopIt[14]),
    HELP_TITLE(0xA4A),  // "Wizard Cracker Pop-it"
    // "Hint: The more Wizard Crackers you can pop at the same time, the higher the score. Receive
    //  a point bonus for the least amount of Wizard Crackers remaining."
    HELP_TEXT(12, 48, 212, 104, 0x5E9),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(3, 3),
    HELP_END,
};

const u32 g_aHelpHippogriffGlide[] = {
    // page 1/1
    HELP_HEADER(HelpPageText),
    HELP_TITLE(0xA4B),  // "Buckbeak's Hippogriff Glide"
    // "The object of the game is to fly through as many groups of gold bats as you can in the time
    //  allotted."
    HELP_TEXT(12, 48, 212, 104, 0x5ED),
    // "Use the +Control Pad to move Buckbeak left and right. Press and hold the A Button to fly
    //  higher. Capture the gold bats by flying through them to gain points. Try to get the high
    //  score."
    HELP_TEXT(12, 88, 212, 104, 0x5EE),
    HELP_PAGE_NUMBER(1, 1),
    HELP_END,
};

const u32 g_aHelpRiddikulus[] = {
    // page 1/4
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpRiddikulus[14]),
    HELP_TITLE(0xA4C),  // "Riddikulus Boggart Challenge"
    // "The object of the game is to survive as many encounters with the Boggart as possible."
    HELP_TEXT(12, 48, 212, 104, 0x5F0),
    // "There are four students on the screen. Each student corresponds to a direction on the
    //  +Control Pad. The Boggart will appear in the center of the screen in one of its various
    //  forms and begin moving towards one of the students."
    HELP_TEXT(12, 80, 212, 104, 0x5F1),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 4),
    HELP_END,

    // page 2/4
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpRiddikulus),
    HELP_NEXT_PAGE(&g_aHelpRiddikulus[28]),
    HELP_TITLE(0xA4C),  // "Riddikulus Boggart Challenge"
    // "To cast the Riddikulus Charm and get rid of the Boggart, press the +Control Pad in the
    //  direction you want the student to cast. For example, to make the student at the top of the
    //  screen cast the Riddikulus Charm, press Down on the +Control Pad."
    HELP_TEXT(12, 48, 212, 104, 0x5F2),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(2, 4),
    HELP_END,

    // page 3/4
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpRiddikulus[14]),
    HELP_NEXT_PAGE(&g_aHelpRiddikulus[45]),
    HELP_TITLE(0xA4C),  // "Riddikulus Boggart Challenge"
    // "The Boggart will move more quickly when it reappears after each successful Riddikulus
    //  cast."
    HELP_TEXT(12, 48, 212, 104, 0x5F3),
    // "If you make a mistake three times, the game is over."
    HELP_TEXT(12, 88, 212, 104, 0x5F4),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(3, 4),
    HELP_END,

    // page 4/4
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpRiddikulus[28]),
    HELP_TITLE(0xA4C),  // "Riddikulus Boggart Challenge"
    // "Hint: Keep calm, especially during later rounds. Noting the direction the Boggart is facing
    //  before it moves will give you an advantage."
    HELP_TEXT(12, 48, 212, 104, 0x5F5),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(4, 4),
    HELP_END,
};

const u32 g_aHelpTeaLeafDivination[] = {
    // page 1/2
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpTeaLeafDivination[14]),
    HELP_TITLE(0xA4D),  // "Tea Leaf Divination"
    HELP_TEXT(12, 48, 212, 104, 0x5EA),  // "Read the tea leaves and get a mysterious fortune."
    // "Repeatedly press the A Button to stir the tea and the leaves. The faster you press, the
    //  faster the tea is stirred. When you're ready for a fortune, press the B Button. The tea
    //  drains from the cup and your fortune appears."
    HELP_TEXT(12, 80, 212, 104, 0x5EB),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 2),
    HELP_END,

    // page 2/2
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpTeaLeafDivination),
    HELP_TITLE(0xA4D),  // "Tea Leaf Divination"
    // "What secrets do the tea leaves hold? Check every time you play for clues."
    HELP_TEXT(12, 48, 212, 104, 0x5EC),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(2, 2),
    HELP_END,
};

const u32 g_aHelpDementors[] = {
    // page 1/2
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpDementors[11]),
    HELP_TITLE(0x91F),  // "The Dementors are surrounding Harry!"
    // "There are four Dementors on the screen. As one of them begins to move towards Harry, press
    //  the +Control Pad in the direction he should cast his spell. For example, if the Dementor at
    //  the top of the screen is moving towards Harry, press Up on the +Control Pad to make him cast
    //  a spell upwards, towards the Dementor."
    HELP_TEXT(12, 56, 212, 104, 0x920),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 2),
    HELP_END,

    // page 2/2
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpDementors),
    HELP_TITLE(0x91F),  // "The Dementors are surrounding Harry!"
    // "Each time you successfully cast a spell, the next Dementor moves more quickly."
    HELP_TEXT(12, 48, 212, 104, 0x921),
    // "If you make a mistake three times, the game is over."
    HELP_TEXT(12, 80, 212, 104, 0x922),
    HELP_TEXT(12, 104, 212, 104, 0x923),  // "Hint: Keep calm, especially during later rounds."
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(2, 2),
    HELP_END,
};

const u32 g_aHelpCardComboGlossary[] = {
    // page 1/11
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpCardComboGlossary[11]),
    HELP_TITLE(0x687),  // "Card Combo Glossary"
    // "By gathering collector's cards throughout the adventure, Harry can use them during magical
    //  encounters. Here's a list of all the Card Combos Harry can use if he has the correct cards."
    HELP_TEXT(12, 48, 212, 104, 0x688),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 11),
    HELP_END,

    // page 2/11
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpCardComboGlossary),
    HELP_NEXT_PAGE(&g_aHelpCardComboGlossary[31]),
    HELP_TITLE(0x687),  // "Card Combo Glossary"
    HELP_TEXT(12, 48, 212, 104, 0x689),  // "Jinx Card Combo"
    // "Horklump Spores: Horklump spores appear and blast opponent with pollen."
    HELP_TEXT(12, 64, 212, 104, 0x68A),
    // "Tempest: Causes a gust of wind to blow one opponent off-screen."
    HELP_TEXT(12, 104, 212, 104, 0x68B),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(2, 11),
    HELP_END,

    // page 3/11
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpCardComboGlossary[11]),
    HELP_NEXT_PAGE(&g_aHelpCardComboGlossary[48]),
    HELP_TITLE(0x687),  // "Card Combo Glossary"
    HELP_TEXT(12, 48, 212, 104, 0x689),  // "Jinx Card Combo"
    // "Cracker: Causes Wizard Crackers to go off and give heavy damage to all opponents and some
    //  damage to player's party."
    HELP_TEXT(12, 64, 212, 104, 0x68C),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(3, 11),
    HELP_END,

    // page 4/11
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpCardComboGlossary[31]),
    HELP_NEXT_PAGE(&g_aHelpCardComboGlossary[68]),
    HELP_TITLE(0x687),  // "Card Combo Glossary"
    HELP_TEXT(12, 48, 212, 104, 0x68D),  // "Defense/Protection Card Combo"
    // "Poison Antidote: Removes any poison affecting a party member."
    HELP_TEXT(12, 64, 212, 104, 0x68E),
    // "Remove Jinx: Removes any jinx affecting a party member."
    HELP_TEXT(12, 96, 212, 104, 0x68F),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(4, 11),
    HELP_END,

    // page 5/11
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpCardComboGlossary[48]),
    HELP_NEXT_PAGE(&g_aHelpCardComboGlossary[85]),
    HELP_TITLE(0x687),  // "Card Combo Glossary"
    HELP_TEXT(12, 48, 212, 104, 0x68D),  // "Defense/Protection Card Combo"
    // "Poison Immunity: Gives all party members immunity to poison for one magical encounter."
    HELP_TEXT(12, 64, 212, 104, 0x690),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(5, 11),
    HELP_END,

    // page 6/11
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpCardComboGlossary[68]),
    HELP_NEXT_PAGE(&g_aHelpCardComboGlossary[105]),
    HELP_TITLE(0x687),  // "Card Combo Glossary"
    HELP_TEXT(12, 48, 212, 104, 0x691),  // "General Card Combo"
    // "Revive: Revive an unconscious member of your party."
    HELP_TEXT(12, 64, 212, 104, 0x692),
    // "Girding All: Increases all party members' physical defense."
    HELP_TEXT(12, 96, 212, 104, 0x693),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(6, 11),
    HELP_END,

    // page 7/11
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpCardComboGlossary[85]),
    HELP_NEXT_PAGE(&g_aHelpCardComboGlossary[122]),
    HELP_TITLE(0x687),  // "Card Combo Glossary"
    HELP_TEXT(12, 48, 212, 104, 0x691),  // "General Card Combo"
    // "Reparifors: Cancels any magical ailments affecting the party."
    HELP_TEXT(12, 64, 212, 104, 0x694),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(7, 11),
    HELP_END,

    // page 8/11
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpCardComboGlossary[105]),
    HELP_NEXT_PAGE(&g_aHelpCardComboGlossary[142]),
    HELP_TITLE(0x687),  // "Card Combo Glossary"
    HELP_TEXT(12, 48, 212, 104, 0x695),  // "Hogwarts/Instruction Cards"
    // "Replenish MP: Sets a party member's Magic Points (MP) to maximum."
    HELP_TEXT(12, 64, 212, 104, 0x696),
    // "Replenish SP: Sets all party members' Stamina Points (SP) to maximum."
    HELP_TEXT(12, 96, 212, 104, 0x697),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(8, 11),
    HELP_END,

    // page 9/11
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpCardComboGlossary[122]),
    HELP_NEXT_PAGE(&g_aHelpCardComboGlossary[159]),
    HELP_TITLE(0x687),  // "Card Combo Glossary"
    HELP_TEXT(12, 48, 212, 104, 0x695),  // "Hogwarts/Instruction Cards"
    // "Extra EXP: Gain bonus Experience (EXP) Points after successfully completing a magical
    //  encounter."
    HELP_TEXT(12, 64, 212, 104, 0x698),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(9, 11),
    HELP_END,

    // page 10/11
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpCardComboGlossary[142]),
    HELP_NEXT_PAGE(&g_aHelpCardComboGlossary[179]),
    HELP_TITLE(0x687),  // "Card Combo Glossary"
    HELP_TEXT(12, 48, 212, 104, 0x699),  // "Quidditch Card Combo"
    // "Bludgers: Causes Bludgers to rain down on opponent for low damage."
    HELP_TEXT(12, 64, 212, 104, 0x69A),
    // "Snitch: Snitch flies around opponent's head, distracting them. Opponent loses a turn."
    HELP_TEXT(12, 96, 212, 104, 0x69B),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(10, 11),
    HELP_END,

    // page 11/11
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpCardComboGlossary[159]),
    HELP_TITLE(0x687),  // "Card Combo Glossary"
    HELP_TEXT(12, 48, 212, 104, 0x699),  // "Quidditch Card Combo"
    // "Sonorous Charm: Creates a magnified roar that disrupts all in its path."
    HELP_TEXT(12, 64, 212, 104, 0x69C),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(11, 11),
    HELP_END,
};

const u32 g_aHelpPotionsGlossary[] = {
    // page 1/7
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpPotionsGlossary[11]),
    HELP_TITLE(0x69D),  // "Potions Glossary"
    // "Potions are very useful during Harry's adventures. They can be found in many places in and
    //  around Hogwarts. Sometimes, creatures may drop them after being defeated in a magical
    //  encounter. Potions can also be purchased from Fred and George's shop. You can use potions
    //  any time. Access them from the Main Menu after pressing START."
    HELP_TEXT(12, 48, 212, 104, 0x69E),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 7),
    HELP_END,

    // page 2/7
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpPotionsGlossary),
    HELP_NEXT_PAGE(&g_aHelpPotionsGlossary[26]),
    HELP_TITLE(0x69D),  // "Potions Glossary"
    // "Wiggenweld: Replenishes some Stamina Points (SP). Harry, Ron and Hermione need to stay
    //  healthy during their adventures. Use the Wiggenweld Potion when a player's Stamina Points
    //  (SP) get low."
    HELP_TEXT(40, 48, 174, 104, 0x69F),
    HELP_SPRITE(16, 0x18, 0x38),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(2, 7),
    HELP_END,

    // page 3/7
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpPotionsGlossary[11]),
    HELP_NEXT_PAGE(&g_aHelpPotionsGlossary[41]),
    HELP_TITLE(0x69D),  // "Potions Glossary"
    // "Grand Wiggenweld: Replenishes many Stamina Points (SP). You might want to save Grand
    //  Wiggenweld Potions for difficult portions of your adventure."
    HELP_TEXT(40, 48, 174, 104, 0x6A0),
    HELP_SPRITE(17, 0x18, 0x38),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(3, 7),
    HELP_END,

    // page 4/7
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpPotionsGlossary[26]),
    HELP_NEXT_PAGE(&g_aHelpPotionsGlossary[56]),
    HELP_TITLE(0x69D),  // "Potions Glossary"
    // "Antidote to Common Poisons: Removes all poison effects. Poisons slowly lower Stamina Points
    //  (SP), so if you or one of your party are poisoned, use the antidote... quickly."
    HELP_TEXT(40, 48, 174, 104, 0x6A1),
    HELP_SPRITE(20, 0x18, 0x38),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(4, 7),
    HELP_END,

    // page 5/7
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpPotionsGlossary[41]),
    HELP_NEXT_PAGE(&g_aHelpPotionsGlossary[71]),
    HELP_TITLE(0x69D),  // "Potions Glossary"
    // "Pepperup: Replenishes some Magic Points (MP). Harry, Ron and Hermione need Magic Points
    //  (MP) to cast many of their spells. Use the Pepperup Potion when a player's Magic Points (MP)
    //  get low."
    HELP_TEXT(40, 48, 174, 104, 0x6A2),
    HELP_SPRITE(18, 0x18, 0x38),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(5, 7),
    HELP_END,

    // page 6/7
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpPotionsGlossary[56]),
    HELP_NEXT_PAGE(&g_aHelpPotionsGlossary[86]),
    HELP_TITLE(0x69D),  // "Potions Glossary"
    // "Grand Pepperup: Replenishes many Magic Points (MP). You might want to save Grand Pepperup
    //  Potion for difficult portions of the adventure."
    HELP_TEXT(40, 48, 174, 104, 0x6A3),
    HELP_SPRITE(19, 0x18, 0x38),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(6, 7),
    HELP_END,

    // page 7/7
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpPotionsGlossary[71]),
    HELP_TITLE(0x69D),  // "Potions Glossary"
    // "Anti-Paralysis: Removes the effects of paralysis during a magical encounter. Some creatures
    //  have the ability to temporarily paralyze Harry, Ron or Hermione. Use this potion to get
    //  moving again."
    HELP_TEXT(40, 48, 174, 104, 0x6A5),
    HELP_SPRITE(21, 0x18, 0x38),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(7, 7),
    HELP_END,
};

const u32 g_aHelpItemsGlossary[] = {
    // page 1/6
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpItemsGlossary[11]),
    HELP_TITLE(0x6A6),  // "Items Glossary"
    // "Items are found in and around Hogwarts and are used at different points in Harry's
    //  adventures. To see the items Harry is currently carrying, select Items from the Main Menu by
    //  pressing START."
    HELP_TEXT(12, 48, 212, 104, 0x6A7),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 6),
    HELP_END,

    // page 2/6
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpItemsGlossary),
    HELP_NEXT_PAGE(&g_aHelpItemsGlossary[30]),
    HELP_TITLE(0x6A6),  // "Items Glossary"
    // "Rat Tonic: Ron asks Harry to retrieve this for Scabbers."
    HELP_TEXT(40, 48, 174, 80, 0x6A8),
    HELP_TEXT(40, 80, 174, 80, 0x6AA),  // "Firebolt: The fastest racing broom on the market."
    HELP_SPRITE(1, 0x18, 0x38),
    HELP_SPRITE(2, 0x18, 0x58),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(2, 6),
    HELP_END,

    // page 3/6
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpItemsGlossary[11]),
    HELP_NEXT_PAGE(&g_aHelpItemsGlossary[45]),
    HELP_TITLE(0x6A6),  // "Items Glossary"
    // "Chocolate Frogs: A chocolate treat for wizards and witches of all ages. Each package
    //  includes a collector's card."
    HELP_TEXT(40, 48, 174, 80, 0x6B0),
    HELP_SPRITE(7, 0x18, 0x38),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(3, 6),
    HELP_END,

    // page 4/6
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpItemsGlossary[30]),
    HELP_NEXT_PAGE(&g_aHelpItemsGlossary[68]),
    HELP_TITLE(0x6A6),  // "Items Glossary"
    HELP_TEXT(40, 48, 174, 80, 0x6B2),  // "Shrivelfig: A potion ingredient."
    HELP_TEXT(40, 80, 174, 80, 0x6B3),  // "Daisy Roots: A potion ingredient."
    HELP_TEXT(40, 112, 174, 80, 0x6B4),  // "Rat Spleen: A potion ingredient."
    HELP_SPRITE(10, 0x18, 0x38),
    HELP_SPRITE(11, 0x18, 0x58),
    HELP_SPRITE(12, 0x18, 0x78),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(4, 6),
    HELP_END,

    // page 5/6
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpItemsGlossary[45]),
    HELP_NEXT_PAGE(&g_aHelpItemsGlossary[87]),
    HELP_TITLE(0x6A6),  // "Items Glossary"
    HELP_TEXT(40, 48, 174, 80, 0x6B5),  // "Leech Juice: A potion ingredient."
    HELP_TEXT(40, 80, 174, 80, 0x6B8),  // "Dead Caterpillar: A potion ingredient."
    HELP_SPRITE(13, 0x18, 0x38),
    HELP_SPRITE(9, 0x18, 0x58),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(5, 6),
    HELP_END,

    // page 6/6
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpItemsGlossary[68]),
    HELP_TITLE(0x6A6),  // "Items Glossary"
    // "Book Pages: Pages of a book scattered around the library."
    HELP_TEXT(40, 48, 174, 80, 0x6B6),
    HELP_SPRITE(15, 0x18, 0x38),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(6, 6),
    HELP_END,
};

const u32 g_aHelpSpecialMovesGlossary[] = {
    // page 1/5
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpSpecialMovesGlossary[11]),
    HELP_TITLE(0x6B9),  // "Special Moves Glossary"
    // "Harry, Ron and Hermione each have Special Moves they can use during magical encounters.
    //  Harry uses his collector's cards in Card Combos to affect creatures. See the special
    //  glossary section on Card Combos for a detailed description of these effects. Hermione and
    //  Ron can execute one Special Move per magical encounter."
    HELP_TEXT(12, 48, 212, 104, 0x6BA),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 5),
    HELP_END,

    // page 2/5
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpSpecialMovesGlossary),
    HELP_NEXT_PAGE(&g_aHelpSpecialMovesGlossary[31]),
    HELP_TITLE(0x6B9),  // "Special Moves Glossary"
    HELP_TEXT(12, 48, 212, 104, 0x6BB),  // "Ron throws items at creatures."
    // "Stink Pellet: Ron throws a Stink Pellet at a creature causing a small amount of damage and
    //  stunning it for one turn."
    HELP_TEXT(12, 64, 212, 104, 0x6BC),
    // "Wizard Cracker: Ron throws a Wizard Cracker at a creature, causing more damage than a Stink
    //  Pellet and obtaining an item."
    HELP_TEXT(12, 96, 212, 104, 0x6BD),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(2, 5),
    HELP_END,

    // page 3/5
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpSpecialMovesGlossary[11]),
    HELP_NEXT_PAGE(&g_aHelpSpecialMovesGlossary[48]),
    HELP_TITLE(0x6B9),  // "Special Moves Glossary"
    HELP_TEXT(12, 48, 212, 104, 0x6BB),  // "Ron throws items at creatures."
    // "Stink Pellet 2: Ron throws a potent Stink Pellet, stunning all creatures for one turn."
    HELP_TEXT(12, 64, 212, 104, 0x6BE),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(3, 5),
    HELP_END,

    // page 4/5
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpSpecialMovesGlossary[31]),
    HELP_NEXT_PAGE(&g_aHelpSpecialMovesGlossary[68]),
    HELP_TITLE(0x6B9),  // "Special Moves Glossary"
    // "Hermione uses her intellect to give quick lectures to a party member."
    HELP_TEXT(12, 48, 212, 104, 0x6BF),
    // "Be More Careful: Increases a party member's physical defense for the rest of the magical
    //  encounter."
    HELP_TEXT(12, 72, 212, 104, 0x6C0),
    // "Proper Wand Technique: Increases the effectiveness of spells for one party member."
    HELP_TEXT(12, 104, 212, 104, 0x6C2),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(4, 5),
    HELP_END,

    // page 5/5
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpSpecialMovesGlossary[48]),
    HELP_TITLE(0x6B9),  // "Special Moves Glossary"
    // "Hermione uses her intellect to give quick lectures to a party member."
    HELP_TEXT(12, 48, 212, 104, 0x6BF),
    // "Good Study Habits: Gain bonus Experience (EXP) Points after successfully completing a
    //  magical encounter."
    HELP_TEXT(12, 72, 212, 104, 0x6C1),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(5, 5),
    HELP_END,
};

const u32 g_aHelpOwlCareKit[] = {
    // page 1/6
    HELP_HEADER(HelpPageText),
    HELP_NEXT_PAGE(&g_aHelpOwlCareKit[11]),
    HELP_TITLE(0x3F6),  // "Owl Care Kit"
    // "In order to begin, you must choose a pet owl. First, choose an owl name and then select an
    //  owl type. There are three types to choose from: White, Brown and Grey."
    HELP_TEXT(12, 48, 212, 104, 0x914),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(1, 6),
    HELP_END,

    // page 2/6
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(g_aHelpOwlCareKit),
    HELP_NEXT_PAGE(&g_aHelpOwlCareKit[25]),
    HELP_TITLE(0x3F6),  // "Owl Care Kit"
    // "The three status bars in the upper left corner of the screen depict your owl's wellbeing:
    //  Mind, Body and Spirit. Try to keep the bars as full as possible. To do this, there are
    //  several options available to care for your owl. At the bottom of the screen are a number of
    //  icons that represent actions:"
    HELP_TEXT(12, 48, 212, 104, 0x915),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(2, 6),
    HELP_END,

    // page 3/6
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpOwlCareKit[11]),
    HELP_NEXT_PAGE(&g_aHelpOwlCareKit[45]),
    HELP_TITLE(0x3F6),  // "Owl Care Kit"
    // "There are several options available to care for your owl."
    HELP_TEXT(12, 48, 212, 104, 0x916),
    HELP_TEXT(12, 80, 212, 104, 0x917),  // "Feed - feeds your owl."
    HELP_TEXT(12, 104, 212, 104, 0x918),  // "Clean - cleans the owl's cage of residue."
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(3, 6),
    HELP_END,

    // page 4/6
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpOwlCareKit[25]),
    HELP_NEXT_PAGE(&g_aHelpOwlCareKit[68]),
    HELP_TITLE(0x3F6),  // "Owl Care Kit"
    // "Pet - pats your owl on the head in an affectionate way."
    HELP_TEXT(12, 48, 212, 104, 0x919),
    HELP_TEXT(12, 72, 212, 104, 0x91A),  // "Groom - cleans and grooms your pet owl."
    HELP_TEXT(12, 96, 212, 104, 0x91C),  // "Teach - increases your owl's intelligence."
    HELP_TEXT(12, 120, 212, 104, 0x91B),  // "Exercise - maintains your owl's health."
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(4, 6),
    HELP_END,

    // page 5/6
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpOwlCareKit[45]),
    HELP_NEXT_PAGE(&g_aHelpOwlCareKit[82]),
    HELP_TITLE(0x3F6),  // "Owl Care Kit"
    // "Mail - sends your owl off to fetch an item. (Check back in a few minutes to see if it
    //  returns with anything useful.)"
    HELP_TEXT(12, 48, 212, 104, 0x91D),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_SPRITE(0, 0xB4, 0x93),
    HELP_PAGE_NUMBER(5, 6),
    HELP_END,

    // page 6/6
    HELP_HEADER(HelpPageText),
    HELP_PREV_PAGE(&g_aHelpOwlCareKit[68]),
    HELP_TITLE(0x3F6),  // "Owl Care Kit"
    // "Upload - this takes you to the Connectivity screen where you'll be able to take part in owl
    //  races. Hook up your Game Boy(R) Advance to a Nintendo GameCube(TM) via a Nintendo
    //  GameCube(TM) Game Boy(R) Advance Cable. Follow the instructions included in the Nintendo
    //  GameCube(TM) version of Harry Potter and the Prisoner of Azkaban to participate in Owl
    //  Races."
    HELP_TEXT(12, 48, 212, 104, 0x91E),
    HELP_SPRITE(0, 0x3C, 0x93),
    HELP_PAGE_NUMBER(6, 6),
    HELP_END,
};

const u32 g_aHelpMenuFolios[] = {
    HELP_HEADER(HelpPageMenu),
    HELP_MENU_LINK(0x5B6, g_aHelpFolioUniversitas),  // "About the Folio Universitas"
    HELP_MENU_LINK(0x5B2, g_aHelpFolioBruti),  // "About the Folio Bruti"
    HELP_END,
};

const u32 g_aHelpMenuCollectorCards[] = {
    HELP_HEADER(HelpPageMenu),
    HELP_MENU_LINK(0x687, g_aHelpCardComboGlossary),  // "Card Combo Glossary"
    HELP_MENU_LINK(0x8C8, g_aHelpTradeCards),  // "Trade Cards"
    HELP_END,
};

const u32 g_aHelpMenuItems[] = {
    HELP_HEADER(HelpPageMenu),
    HELP_MENU_LINK(0x5B3, g_aHelpEquipItems),  // "Equip Items"
    HELP_MENU_LINK(0x5B5, g_aHelpUsingItems),  // "Using Items"
    HELP_MENU_LINK(0x69D, g_aHelpPotionsGlossary),  // "Potions Glossary"
    HELP_MENU_LINK(0x6A6, g_aHelpItemsGlossary),  // "Items Glossary"
    HELP_END,
};

const u32 g_aHelpMenuMiniGames[] = {
    HELP_HEADER(HelpPageMenu),
    HELP_MENU_LINK_IF(0xA4A, g_aHelpWizardCrackerPopIt, IsHelpTopicUnlocked),  // "Wizard Cracker Pop-it"
    HELP_MENU_LINK_IF(0xA4B, g_aHelpHippogriffGlide, IsHelpTopicUnlocked),  // "Buckbeak's Hippogriff Glide"
    HELP_MENU_LINK_IF(0xA4C, g_aHelpRiddikulus, IsHelpTopicUnlocked),  // "Riddikulus Boggart Challenge"
    HELP_MENU_LINK_IF(0xA4D, g_aHelpTeaLeafDivination, IsHelpTopicUnlocked),  // "Tea Leaf Divination"
    HELP_MENU_LINK_IF(0xA4E, g_aHelpDementors, IsHelpTopicUnlocked),  // "Dementor Challenge"
    HELP_MENU_LINK_IF(0x3F6, g_aHelpOwlCareKit, IsHelpTopicUnlocked),  // "Owl Care Kit"
    HELP_END,
};

const u32 g_aHelpMenuMain[] = {
    HELP_HEADER(HelpPageMenu),
    HELP_MENU_LINK(0x3F2, g_aHelpMenuFolios),  // "About the Folios"
    HELP_MENU_LINK(0x3F3, g_aHelpMenuCollectorCards),  // "About Collector's Cards"
    HELP_MENU_LINK(0x3F4, g_aHelpMenuItems),  // "About Items"
    HELP_MENU_LINK(0x3F5, g_aHelpMenuMiniGames),  // "About Mini-Games"
    HELP_MENU_LINK(0x5B4, g_aHelpMagicalEncounters),  // "Magical Encounters"
    HELP_MENU_LINK(0x6B9, g_aHelpSpecialMovesGlossary),  // "Special Moves Glossary"
    HELP_END,
};
