#include "types.h"
#include "dialog.h"

// Text ids of the dialog blocks' lines; g_aDialogBlocks points into this table.
const u32 g_adwDialogBlockTextIds[979] = {
    // Block 0
    0x0,  // "There you are, Harry!"
    0x1,  // "Um... Hello..."
    0x2,  // "I am Cornelius Fudge, Harry, the Minister for Magic."
    0x3,  // "Hello, Mr. Fudge. Have you had any luck with catching Sirius Black yet?"
    0x4,  // "What's that?"
    0x5,  // "Sirius Black, the murderer who killed thirteen people with a single curs..."
    0x6,  // "Oh, that Sirius Black - well, no, not yet, but it's only a matter of tim..."
    0x7,  // "All right, thank you."
    // Block 1
    0x8,  // "I thought you'd be in your room by now, Mr. Potter."
    // Block 2
    0x7,  // "All right, thank you."
    // Block 3
    0x1B,  // "I don't think I should be going down into the cellar just yet."
    // Blocks 4, 5
    0xA,  // "Here, Harry. Take these collector's cards. They might help you during a..."
    0xB,  // "Thank you, Minister."
    // Block 6
    0x8,  // "I thought you'd be in your room by now, Mr. Potter."
    // Block 7
    0x1C,  // "There's nothing like a nice glass of Butterbeer!"
    // Block 8
    0x1D,  // "I'm afraid this seat is taken."
    // Block 9
    0x1E,  // "Harry Potter, isn't it?"
    // Block 10
    0x1F,  // "I suppose you'll be attending Hogwarts, am I right?"
    // Block 11
    0x2A,  // "Heading for the cellar? Better watch your step. I hear there are rats do..."
    // Block 12
    0x2B,  // "It's awfully dark down there..."
    // Block 13
    0x2C,  // "I wouldn't go down there if I were you."
    // Block 14
    0x2D,  // "Are you sure you want to go down into the cellar?"
    // Block 15
    0x13,  // "Harry! How are you?"
    0x14,  // "Fine, thanks, Mrs. Weasley."
    0x15,  // "Hello, Harry."
    // Block 16
    0x17,  // "Hi, Harry! So, you managed to make it through the summer?"
    0x18,  // "Just about, Ron. Have you heard from Hermione lately?"
    0x19,  // "I just saw her in Diagon Alley. She was talking about buying a cat..."
    0x1A,  // "Speaking of pets, how's your rat, Scabbers?"
    0x23,  // "He's been a bit off-color ever since I brought him back from Egypt."
    0x24,  // "Why don't you give him a dose of Rat Tonic?"
    0x25,  // "I don't have any Rat Tonic left."
    0x26,  // "Maybe the innkeeper, Tom, has some. Tell you what, I'll go and ask him."
    // Block 17
    0x12,  // "Maybe I should speak to Tom, the innkeeper, before going down into the c..."
    // Block 18
    0x21,  // "Hello!"
    // Block 19
    0x20,  // "Good to see you again."
    // Block 20
    0xC,  // "There's a package on my bed..."
    0xD,  // "There's a card... It's from Hagrid! He remembered my birthday!"
    0xE,  // "It's a book! 'The Monster Book of Monsters'."
    0xF,  // "Uh oh..."
    // Block 21
    0x10,  // "Trust Hagrid to think that a biting book would come in useful!"
    // Blocks 22, 23
    0x11,  // "Thank goodness for that! I think I'll turn in for the night."
    // Block 24
    0x12,  // "Maybe I should speak to Tom, the innkeeper, before going down into the c..."
    // Block 25
    0x2F,  // "Hmm - if I cast Lumos, I'll be able to see better."
    // Block 26
    0x30,  // "If I cast Flipendo I'll be able to push and break certain things..."
    // Block 27
    0x27,  // "Ron Weasley was looking for you, Mr. Potter."
    // Block 28
    0x23,  // "He's been a bit off-color ever since I brought him back from Egypt."
    0x24,  // "Why don't you give him a dose of Rat Tonic?"
    0x25,  // "I don't have any Rat Tonic left."
    0x26,  // "Maybe the innkeeper, Tom, has some. Tell you what, I'll go and ask him."
    // Block 29
    0x28,  // "Excuse me, Tom, I don't suppose you have any Rat Tonic?"
    0x29,  // "Indeed I do, Mr. Potter. If you don't mind finding your own way, there's..."
    0x2E,  // "I'm sure I can find the Rat Tonic for Ron..."
    // Block 30
    0x31,  // "This must be the way down to the cellar."
    // Block 31
    0x32,  // "It's really dusty down here."
    0x33,  // "Where is that bottle hiding?"
    // Block 32
    0x34,  // "Tom really needs to tidy up down here."
    // Block 33
    0x35,  // "This place could do with a spring clean..."
    // Block 34
    0x36,  // "This place is really dark. I'd better cast Lumos so I don't fall over."
    // Block 35
    0x37,  // "There's the Rat Tonic!"
    // Block 36
    0x44,  // "There you are, Harry! Did you manage to get any Rat Tonic?"
    0x45,  // "Yes. There you go."
    0x46,  // "Thanks. This will make you feel better, Scabbers."
    0x47,  // "What's wrong, Harry? You look upset."
    0x48,  // "I overheard your parents talking about Sirius Black. He wants to kill me..."
    0x49,  // "Promise me you won't go looking for trouble, Harry."
    0x4A,  // "I don't go looking for trouble, Ron. Trouble usually finds me..."
    // Block 37
    0x38,  // "Oh! It's had too much Rat Tonic! I'd better get the rest of the Tonic an..."
    // Block 38
    0x39,  // "This place is even dingier than the Cupboard under the Stairs!"
    // Block 39
    0x4B,  // "Be careful down in the cellar, Harry."
    0x4C,  // "I still have to get the Rat Tonic for Ron!"
    // Block 40
    0x4F,  // "Did you find the Rat Tonic, Mr. Potter?"
    0x4D,  // "Not yet. I think I'll have another look."
    // Block 41
    0x3A,  // "...makes no sense not to tell him, Molly. Harry's got a right to know."
    0x3B,  // "Arthur, the truth would terrify him! And Harry will be safe at Hogwarts."
    0x3C,  // "We thought Azkaban prison was safe. If Black can break out of Azkaban, h..."
    // Block 42
    0x3D,  // "I couldn't help hearing. Sorry..."
    0x3E,  // "That's not the way I'd have chosen for you to find out."
    0x3F,  // "No - honestly, it's OK. At least I now know what's going on."
    0x40,  // "Harry, you must be very scared."
    0x41,  // "I'm not. Really. Sirius Black can't be worse than Voldemort, can he?"
    0x42,  // "Listen, I want you to give me your word - swear to me that you won't go..."
    // Blocks 43, 44
    0x50,  // "Harry! You must be more careful. Tom found you lying on the floor uncons..."
    // Block 45
    0x54,  // "Hermione - we were wondering when you'd show up!"
    0x55,  // "It's really good to see you both again. I'd like you to meet my new cat,..."
    0x56,  // "You bought that monster?"
    0x57,  // "He's gorgeous, isn't he?"
    0x58,  // "Squeak! Squeeeeeak!"
    0x59,  // "That beast of yours is scaring Scabbers! Keep it away from him!"
    0x5A,  // "Meoww!"
    // Block 46
    0x5B,  // "Scabbers! Come back!"
    0x5C,  // "Crookshanks! Come back! Oh, it's no use!"
    0x5D,  // "We need to rescue Scabbers!"
    0x5E,  // "I'll go. Crookshanks is my responsibility."
    0x5F,  // "I'll go. He's my rat."
    0x60,  // "I'll help you find them."
    // Block 47
    0x61,  // "Scabbers!"
    // Block 48
    0x62,  // "Scabbers, where are you?"
    // Block 49
    0x7B,  // "They must have gone down here."
    0x7C,  // "Be careful, Ron. It's dangerous down there."
    // Block 50
    0x7D,  // "Got him! It's OK, Scabbers, you're safe now."
    // Block 51
    0x9E,  // "Crookshanks! Oh, where are you?"
    // Block 52
    0x9F,  // "Crookshanks is going to need a bath if he's been running around down her..."
    // Block 53
    0xA0,  // "Where could they be?"
    // Block 54
    0xA1,  // "Come out, Crookshanks!"
    // Block 55
    0x9C,  // "Got you, you naughty cat!"
    0x9D,  // "We'd better go and find Ron."
    // Block 56
    0x82,  // "I found Crookshanks. Did you manage to find Scabbers?"
    0x83,  // "Yes, I did - no thanks to your cat."
    0x84,  // "Bad Crookshanks! Don't run away again!"
    // Block 57
    0x82,  // "I found Crookshanks. Did you manage to find Scabbers?"
    0x83,  // "Yes, I did - no thanks to your cat."
    0x84,  // "Bad Crookshanks! Don't run away again!"
    // Block 58
    0x71,  // "Did you see a cat chase a rat past here?"
    0x72,  // "Yes. They both went down into the cellar."
    // Block 59
    0x73,  // "Did you see a cat chase a rat past here?"
    0x74,  // "They were heading for the cellar."
    // Block 60
    0x75,  // "Did you see a cat chase a rat past here?"
    0x76,  // "I did. They went down into the cellar."
    // Block 61
    0x77,  // "Did you see a cat chase a rat past here?"
    0x78,  // "No. I didn't even know they allowed pets in here."
    // Block 62
    0x79,  // "Did you see a cat chase a rat past here?"
    0x7A,  // "Yes, they were running full-pelt towards the cellar."
    // Block 63
    0x85,  // "Have you seen a cat run past here?"
    0x86,  // "Was that a cat? It was after a rat. They were running towards the cellar..."
    // Block 64
    0x87,  // "Have you seen a cat run past here?"
    0x88,  // "I did indeed. Close on the heels of an unfortunate rat. They were headin..."
    // Block 65
    0x89,  // "Did you see a cat chase a rat past here?"
    0x8A,  // "They went towards the cellar."
    // Block 66
    0x8B,  // "Did you see a cat chase a rat past here?"
    0x8C,  // "I saw them go down into the cellar."
    // Block 67
    0x8D,  // "Did you see a cat chase a rat past here?"
    0x8E,  // "Yes, in the direction of the cellar."
    // Block 68
    0x98,  // "Tom - have you seen my cat chasing Scabbers past here?"
    0x99,  // "Yes, Miss Granger. They were running into the cellar."
    // Block 69
    0x67,  // "Tom - have you seen my rat?"
    0x68,  // "He was heading for the cellar, with a big cat chasing him."
    // Block 70
    0x6B,  // "Ginny - you haven't seen Scabbers, have you?"
    // Block 71
    0x69,  // "Have you seen Scabbers, Percy?"
    // Block 72
    0x6D,  // "Mum, Dad - have you seen Scabbers?"
    // Block 73
    0x71,  // "Did you see a cat chase a rat past here?"
    0x72,  // "Yes. They both went down into the cellar."
    // Block 74
    0x73,  // "Did you see a cat chase a rat past here?"
    0x74,  // "They were heading for the cellar."
    // Block 75
    0x75,  // "Did you see a cat chase a rat past here?"
    0x76,  // "I did. They went down into the cellar."
    // Block 76
    0x77,  // "Did you see a cat chase a rat past here?"
    0x78,  // "No. I didn't even know they allowed pets in here."
    // Block 77
    0xA2,  // "C'mon you lot! We need to leave for King's Cross station right away if w..."
    // Block 78
    0xA3,  // "These stairs are broken!"
    // Block 79
    0xA4,  // "I can fix them with the Reparo Spell."
    // Block 80
    0xA5,  // "I think we should look for another way in."
    // Block 81
    0xA6,  // "This door's locked!"
    // Block 82
    0xA7,  // "I think we should look for another way in."
    // Block 83
    0xA8,  // "I can use the Alohomora Spell to unlock it."
    // Block 84
    0x4E,  // "Did you manage to get any Rat Tonic, Harry?"
    0x4D,  // "Not yet. I think I'll have another look."
    // Block 85
    0xAD,  // "Thanks!"
    // Block 86
    0xAF,  // "We'd better hurry up and find seats."
    // Block 87
    0xB0,  // "I'm going to miss Mum and Dad."
    // Block 88
    0xB1,  // "All my new owl does is sleep!"
    // Block 89
    0xB2,  // "I hope there aren't any leaves on the line..."
    // Block 90
    0xB3,  // "Hello. Nice day for a train ride."
    // Block 91
    0xB4,  // "I hope I've packed everything."
    // Block 92
    0xB5,  // "I predict that Divination class will be a lot of fun."
    // Block 93
    0xB6,  // "One of my school books just growled at me!"
    // Block 94
    0xB7,  // "I wonder who'll be teaching the Care of Magical Creatures class?"
    // Block 95
    0xB8,  // "I hope Professor Snape isn't as nasty as everyone says."
    // Block 96
    0xB9,  // "Train rides make me sleepy. I'll probably sleep all the way to Hogwarts."
    // Block 97
    0xBA,  // "I think I'll try out for the Quidditch team this year."
    // Block 98
    0xBB,  // "Muggle Studies sounds interesting; their peculiar artifacts and funny ha..."
    // Block 99
    0xBC,  // "Mum told me to stay away from the baggage car. I wonder why?"
    // Block 100
    0xBD,  // "I wish I could fly to Hogwarts..."
    // Block 101
    0xBE,  // "I wish I didn't have to take Ancient Runes this term."
    // Block 102
    0xA9,  // "How nice to see you."
    // Block 103
    0xAA,  // "Hello."
    // Block 104
    0xAB,  // "Great to see you."
    // Block 105
    0xAC,  // "Really good to see you."
    // Block 106
    0xE1,  // "Well, look who it is."
    // Block 107
    0x138,  // "We don't speak to Gryffindors."
    // Block 108
    0x139,  // "Who do you think you're talking to?"
    // Block 109
    0xBF,  // "These look like the only empty seats."
    0xC0,  // "Who d'you reckon he is?"
    0xC1,  // "Professor R. J. Lupin. He's the new Defense Against the Dark Arts teache..."
    0xC2,  // "Zzzzzz…"
    // Block 110
    0xAE,  // "I wonder where the buffet car is?"
    // Block 111
    0xE7,  // "What's going on? Why's the train stopped?"
    // Blocks 112, 113, 114
    0xF9,  // "What was that thing? And what's the matter with Harry?"
    0xFA,  // "That was a Dementor. One of the Dementors of Azkaban. For some reason it..."
    0xFB,  // "Can't we do something?"
    0xFC,  // "Mr. Weasley, I'd like you to go and find some chocolate so that we can r..."
    0xFE,  // "What can I do to help, Professor?"
    0xFF,  // "Miss Granger, I'd like you to go and find the conductor and get the trai..."
    // Blocks 115, 116, 117, 118
    0xA2,  // "C'mon you lot! We need to leave for King's Cross station right away if w..."
    // Block 119
    0xA2,  // "C'mon you lot! We need to leave for King's Cross station right away if w..."
    // Block 120
    0xA2,  // "C'mon you lot! We need to leave for King's Cross station right away if w..."
    // Block 121
    0xA2,  // "C'mon you lot! We need to leave for King's Cross station right away if w..."
    // Block 122
    0xA2,  // "C'mon you lot! We need to leave for King's Cross station right away if w..."
    // Block 123
    0xA2,  // "C'mon you lot! We need to leave for King's Cross station right away if w..."
    // Block 124
    0x645,  // "You Receive: \n @1 @2"
    // Blocks 126, 127, 128
    0xD0,  // "Why, do you need a one-way ticket back to the Muggles? I'd gladly pay fo..."
    // Block 129
    0xC3,  // "Have you seen the conductor?"
    0xCE,  // "He was going towards the front of the train, looking very cross, I might..."
    // Blocks 130, 131
    0xD1,  // "That must be the conductor. I recognize his uniform."
    // Block 132
    0xD2,  // "Excuse me..."
    0xD3,  // "Yes, miss?"
    0xD4,  // "Erm... Professor Lupin was wondering if you might get the train moving a..."
    0xD5,  // "Of course it's possible. Tell Professor Lupin we'll be underway very soo..."
    0xD6,  // "OK. Thank you very much."
    // Block 133
    0xD7,  // "Better return to your seat, miss. We'll be at Hogsmeade very shortly."
    // Block 134
    0xE0,  // "Better get back to your seat, son. It won't be long before we reach the..."
    // Block 135
    0x112,  // "Here it is! The buffet car!"
    // Block 136
    0x114,  // "A bar of chocolate, please."
    0x115,  // "There you are, my dear. That'll be one Sickle."
    0x116,  // "Thanks."
    // Block 137
    0x117,  // "I've sold out of chocolate, I'm afraid."
    // Block 138
    0x118,  // "Here's the chocolate, Professor!"
    0x119,  // "Well done, Mr. Weasley."
    // Block 139
    0xD8,  // "Job done, Professor Lupin."
    0xD9,  // "Thank you, Miss Granger."
    // Block 140
    0xDA,  // "Harry, are you all right?"
    0xDB,  // "W-what? What happened? Where's that - that thing? Who screamed?"
    0xDC,  // "No one screamed."
    // Block 141
    0xDF,  // "Hogsmeade, next stop!"
    // Block 142
    0xE0,  // "Better get back to your seat, son. It won't be long before we reach the..."
    // Block 143
    0xE2,  // "Harry, I can't find my toad, Trevor. Can you help me find him?"
    0xE3,  // "Where did you last see him?"
    0xE4,  // "Someone said they saw him near the baggage car - but I don't think we're..."
    0xE5,  // "Don't worry, Neville, we'll find him for you."
    0xE6,  // "Thanks, Harry. I'll wait here for you."
    // Block 144
    0xEB,  // "Uhhh..."
    0xEC,  // "Harry!"
    // Block 145
    0xED,  // "It's trying to get in! We have to bar the door!"
    0xF0,  // "Maybe I can find something to Flipendo?"
    // Block 146
    0xE9,  // "There he is!"
    0xEA,  // "Let's get him and get back to..."
    // Block 147
    0xEB,  // "Uhhh..."
    0xEC,  // "Harry!"
    // Block 148
    0xED,  // "It's trying to get in! We have to bar the door!"
    // Block 149
    0xEE,  // "We can use Flipendo to move objects."
    // Block 150
    0xF0,  // "Maybe I can find something to Flipendo?"
    0xF1,  // "I wonder if there's anything in these trunks we could use?"
    0xF2,  // "Nothing in here."
    // Block 151
    0xF0,  // "Maybe I can find something to Flipendo?"
    // Block 152
    0xF1,  // "I wonder if there's anything in these trunks we could use?"
    // Block 153
    0xF2,  // "Nothing in here."
    // Block 154
    0xF3,  // "This trunk is full of brooms. How could we use these to stop the Demento..."
    // Block 155
    0xF4,  // "That's done it! But, what about the other door?"
    // Block 156
    0xF5,  // "That's stopped it!"
    // Block 157
    0xF6,  // "The Dementor's inside!"
    // Block 158
    0xF7,  // "Oh no! It's broken through!"
    // Block 159
    0xF8,  // "None of us is hiding Sirius Black under our cloaks! Go!"
    // Block 160
    0xF9,  // "What was that thing? And what's the matter with Harry?"
    0xFA,  // "That was a Dementor. One of the Dementors of Azkaban. For some reason it..."
    0xFB,  // "Can't we do something?"
    0xFC,  // "Mr. Weasley, I'd like you to go and find some chocolate so that we can r..."
    // Block 161
    0x102,  // "Have you been to the buffet car?"
    // Block 162
    0x103,  // "Not recently."
    // Block 163
    0x104,  // "Why, was I supposed to?"
    // Block 164
    0x105,  // "I think it's towards the front of the train."
    // Block 165
    0x106,  // "It's towards the front of the train."
    // Block 166
    0x107,  // "Yes, and I stocked up on sweets!"
    // Block 167
    0x108,  // "No, sorry, I haven't."
    // Block 168
    0x109,  // "No. I'm not really hungry…"
    // Block 169
    0x10A,  // "No. I've been snoozing."
    // Block 170
    0x10B,  // "It seemed to be near the front of the train…"
    // Block 171
    0x10C,  // "No, but I think I should… I'm starving!"
    // Block 172
    0x10D,  // "The train has a buffet car? Brilliant!"
    // Block 173
    0x10E,  // "The buffet car is at the front of the train."
    // Block 174
    0x10F,  // "Nope. 'Fraid not."
    // Block 175
    0x110,  // "Even if you do find the buffet car, Weasley, it's not as if you'll be ab..."
    // Block 176
    0x111,  // "Sorry, Ron - I was looking for my toad, Trevor."
    // Block 177
    0x112,  // "Here it is! The buffet car!"
    // Block 178
    0x114,  // "A bar of chocolate, please."
    0x115,  // "There you are, my dear. That'll be one Sickle."
    0x116,  // "Thanks."
    // Block 179
    0x118,  // "Here's the chocolate, Professor!"
    0x119,  // "Well done, Mr. Weasley."
    0x11A,  // "Harry, are you all right?"
    // Block 180
    0x11B,  // "W-what? What happened? Where's that - that thing? Who screamed?"
    0x11C,  // "No one screamed."
    // Block 181
    0x11C,  // "No one screamed."
    // Block 182
    0x11F,  // "Sorry, I can't help you at the moment."
    // Block 183
    0x121,  // "Hey, Potter, better watch out, the Dementors are coming!"
    0x122,  // "Shove off, Malfoy."
    0x123,  // "Leave him, Ron, he's not worth it. Let's get to the Gryffindor common ro..."
    // Block 184
    0x124,  // "Attention, please. I have a couple of announcements to make..."
    0x126,  // "I am pleased to welcome two new teachers to our ranks this year. Profess..."
    0x127,  // "Our second appointment will be filled by Rubeus Hagrid, who will be teac..."
    0x128,  // "I think that's everything of importance. Hermione Granger, please come a..."
    // Block 185
    0x129,  // "I hope she isn't in trouble."
    // Block 186
    0x12A,  // "What did Professor McGonagall want?"
    0x12B,  // "Oh... Umm... Nothing, really. We just talked about my heavy timetable th..."
    0x12C,  // "Off to bed, everyone. You've all had a long day and I want you to be ale..."
    // Block 187
    0x12D,  // "The Gryffindor common room is on the seventh floor. Just like last year."
    // Block 188
    0x12E,  // "I can't find the common room for my house! Do you know where it is?"
    // Block 189
    0x12F,  // "I heard that the Gryffindor common room is on the seventh floor."
    // Block 190
    0x130,  // "I'm so excited! A brand new year at Hogwarts!"
    // Block 191
    0x131,  // "I wonder who the new Defense Against the Dark Arts teacher will be this..."
    // Block 192
    0x132,  // "Hi, Harry! Welcome back!"
    // Block 193
    0x133,  // "The Grand Staircase is up those stairs and to your right..."
    // Block 194
    0x134,  // "I just got sorted into Gryffindor. I think the common room is on the sev..."
    // Block 195
    0x135,  // "Slytherin's definitely the best house."
    // Block 196
    0x136,  // "I don't speak to Gryffindors."
    // Block 197
    0x13A,  // "We'd better get going... It's almost time for Transfiguration class!"
    0x13B,  // "Okay, let's go."
    // Block 198
    0x13C,  // "Attention, class! Today's lesson will concern Animagi."
    0x13D,  // "Animagi are wizards who can transform at will into animals. Like this..."
    // Block 199
    0x13E,  // "What's got into you all today? That's the first time my transformation's..."
    0x13F,  // "Now - I need someone to assist me in a Transfiguration challenge. Any vo..."
    // Block 200
    0x140,  // "Mr. Potter, Miss Granger, I shall enter a maze. You must find your own w..."
    // Block 201
    0x141,  // "Excellent, Mr. Potter. As a reward, you may have this Petrificus Totalus..."
    // Block 202
    0x142,  // "I've forgotten who teaches Transfiguration."
    // Block 203
    0x143,  // "Have you got Transfiguration next?"
    // Block 204
    0x144,  // "Professor McGonagall seems really strict."
    // Block 205
    0x145,  // "I'd hate to make Professor McGonagall angry."
    // Block 206
    0x146,  // "I love Transfiguration; it's my favorite subject."
    // Block 207
    0x147,  // "I prefer Potions to Transfiguration."
    // Block 208
    0x148,  // "I just don't get Transfiguration."
    // Block 209
    0x149,  // "Actually, Professor McGonagall can be really nice."
    // Blocks 210, 211
    0x14B,  // "I think Gryffindor have Transfiguration next."
    // Block 212
    0x14C,  // "Transfiguration class is held on the first floor."
    // Block 213
    0x14D,  // "I can't find the Transfiguration classroom. I heard it was on the first..."
    // Blocks 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229
    0x152,  // "It's time for Care of Magical Creatures class with Hagrid - come on!"
    0x153,  // "I just hope he isn't too nervous..."
    0x154,  // "I'm really looking forward to this. Let's go."
    // Block 230
    0x155,  // "Got a real treat for yeh today! Great lesson comin' up!"
    // Block 231
    0x156,  // "Firs' thing yeh'll want ter do is open yer books -"
    0x157,  // "How do we do that if we don't have a copy of 'The Monster Book of Monste..."
    0x158,  // "Oh, er, well, I…"
    0x159,  // "Oh, surely you have extra copies we could borrow?"
    0x15A,  // "Harry, can I have a word?"
    // Block 232
    0x15B,  // "What's wrong, Hagrid?"
    0x15C,  // "My extra copies o' 'The Monster Book of Monsters'... they escaped!"
    0x15D,  // "I bet Malfoy had something to do with it."
    0x15E,  // "Tha' may be, but I'd really appreciate it if yeh'd go and find 'em fer m..."
    0x15F,  // "Of course we'll find them for you, Hagrid. We'd be glad to help, reward..."
    0x160,  // "Thanks."
    // Block 233
    0x16B,  // "A copy of 'The Monster Book of Monsters' ate my homework!"
    // Block 234
    0x16C,  // "For some reason I'm really worried about Care of Magical Creatures class..."
    // Block 235
    0x16D,  // "I'm really looking forward to Care of Magical Creatures!"
    // Block 236
    0x16E,  // "I care for magical creatures... but they don't seem to care for me."
    // Block 237
    0x16F,  // "This would be a nice day to have a class outside."
    // Block 238
    0x170,  // "The Monster Book of Monsters' is pretty fierce, isn't it?"
    // Block 239
    0x171,  // "Hagrid's a natural to teach Care of Magical Creatures - don't you think?"
    // Block 240
    0x172,  // "Will there be dragons in Care of Magical Creatures class? That would be..."
    // Block 241
    0x173,  // "If I do well in Care of Magical Creatures class, maybe Mum and Dad will..."
    // Block 242
    0x174,  // "If you ask me, magical creatures should be able to take care of themselv..."
    // Block 243
    0x161,  // "These three spellbooks may help you to get through my garden."
    // Block 244
    0x162,  // "The books - there they are!"
    // Block 245
    0x164,  // "There's the first one. Four more to go."
    // Block 246
    0x165,  // "There's number two! Only three more."
    // Block 247
    0x166,  // "Got the third book! Just two more."
    // Block 248
    0x167,  // "That's book number four! One more and I've got them all."
    // Block 249
    0x168,  // "There, that's the last book! We'd better get these back to Hagrid!"
    // Block 250
    0x169,  // "Oh, dear, that ain't all of 'em. Yeh'd best go back and look fer the res..."
    // Block 251
    0x16A,  // "Well done! 'Ave this as a reward fer returning the books!"
    // Block 252
    0x175,  // "What's all that noise coming from Hagrid's garden?"
    // Block 253
    0x176,  // "There appears to be some kind of problem in Hagrid's garden..."
    // Block 254
    0x177,  // "Can't someone find out what's going on in Hagrid's garden?"
    // Block 255
    0x178,  // "Sounds like animals fighting in Hagrid's garden."
    // Block 256
    0x179,  // "Is there some kind of trouble in Hagrid's garden?"
    // Block 257
    0x17A,  // "What's going on in Hagrid's garden?"
    // Block 258
    0x17B,  // "Something's definitely going on in Hagrid's garden."
    // Block 259
    0x17C,  // "Sounds like something's on a rampage in Hagrid's garden!"
    // Block 260
    0x17D,  // "What's making all the noise in Hagrid's garden?"
    // Block 261
    0x17E,  // "I bet I can sever this with my Diffindo Spell!"
    // Block 262
    0x17F,  // "I can use Spongify to make these pads rubbery so we can bounce over this..."
    // Block 263
    0x180,  // "I can cast Glacius to turn the water into ice so that we can cross this."
    // Block 264
    0x181,  // "Righ', then, so... so yeh've got yer books an'... an'... if you'd like t..."
    // Block 265
    0x182,  // "Come on you two. I can't wait to see what Hagrid's going to show us!"
    0x183,  // "Me neither - let's go!"
    // Block 266
    0x184,  // "Everyone gather round! That's it - make sure yeh can see."
    // Block 267
    0x185,  // "This place is going to the dogs. That oaf teaching classes, my father'll..."
    0x186,  // "Shut up, Malfoy."
    0x187,  // "Careful, Potter, there's a Dementor behind you-"
    // Block 268
    0x189,  // "A Hippogriff! Beau'iful, aren' they?"
    0x188,  // "Ooooooooh!"
    0x18A,  // "Now, firs' thing yeh gotta know abou' Hippogriffs is they're proud. Don'..."
    // Block 269
    0x18B,  // "This is very easy. I bet you're not dangerous at all, are you, you ugly..."
    // Block 270
    0x18C,  // "I'm dying! Look at me! It's killed me!"
    0x18D,  // "Yer not dyin'! Someone help me - gotta get him outta here, gotta get him..."
    // Block 271
    0x18E,  // "It was Malfoy's fault. He insulted Buckbeak even though he was warned no..."
    0x18F,  // "Buckbeak looks pretty calm now. I'll try and approach him the way Hagrid..."
    // Block 272
    0x190,  // "Careful, Harry!"
    0x191,  // "We're friends now. You know, I bet I could ride him..."
    // Block 273
    0x192,  // "That's it, Harry!"
    // Block 274
    0x193,  // "Wow! That was great!"
    0x194,  // "Well done, Harry!"
    0x3A4,  // "Buckbeak's Hippogriff Glide can now be accessed from the Mini-Games menu..."
    // Block 275
    0x19F,  // "I really appreciate all yeh've done."
    // Block 276
    0x195,  // "I wonder what's waiting for us at the paddock?"
    // Block 277
    0x196,  // "I hope Hagrid hasn't got anything too dangerous in the paddock."
    // Block 278
    0x197,  // "I've heard that Hagrid's very fond of creatures with sharp teeth."
    // Block 279
    0x198,  // "Magical creatures are really fantastic!"
    // Block 280
    0x199,  // "Care of Magical Creatures is my favorite lesson."
    // Block 281
    0x19A,  // "I don't really care for magical creatures..."
    // Block 282
    0x19B,  // "I've never been to the paddock before."
    // Block 283
    0x19C,  // "I wonder if the magical creature at the paddock's got loads of heads?"
    // Block 284
    0x19D,  // "I hope the magical creature in the paddock isn't invisible."
    // Block 285
    0x19E,  // "I'm not scared of magical creatures. I'm not too fond of dogs though."
    // Block 286
    0x1A0,  // "It's Potions next..."
    0x1A1,  // "I don't know what you're groaning about, Harry, I'm really looking forwa..."
    0x1A2,  // "What?!"
    0x1A3,  // "Just joking - I'm dreading it as much as you."
    0x1A4,  // "I've heard we're learning how to make a Shrinking Solution today. Let's..."
    // Block 287
    0x1A5,  // "I hate Potions."
    // Block 288
    0x1A6,  // "Professor Snape's always so unpleasant."
    // Block 289
    0x136,  // "I don't speak to Gryffindors."
    // Block 290
    0x1A8,  // "Gryffindor always seems to lose house points in Snape's lessons."
    // Block 291
    0x1A9,  // "I wonder why Professor Snape appears to dislike Gryffindors so much?"
    // Block 292
    0x1DF,  // "I much prefer Potions to Transfiguration."
    // Block 293
    0x1AB,  // "I think Snape's the best teacher at Hogwarts."
    // Block 294
    0x1AD,  // "Professor Snape's lessons are so smelly..."
    // Block 295
    0x1AF,  // "Settle down, settle down. Today we shall be making a new potion, a Shrin..."
    // Block 296
    0x1B0,  // "I require a volunteer to gather ingredients for this potion."
    // Block 297
    0x1B1,  // "Weasley, while I am reluctant to assign you a task as complex as finding..."
    0x1B3,  // "I require potion ingredients from the Potions store room. Bring them bac..."
    0x1E6,  // "The potion requires daisy root, Shrivelfig, rat spleen, dead caterpillar..."
    0x1B6,  // "Do not think of this as an opportunity to avoid the lesson, Weasley. Tar..."
    0x1B7,  // "Yes, Professor."
    // Block 298
    0x1B2,  // "Feeling particularly keen today, are we, Potter? Very well..."
    0x1B4,  // "Go to the Potions store room, Potter, retrieve some herbs and then bring..."
    0x1E6,  // "The potion requires daisy root, Shrivelfig, rat spleen, dead caterpillar..."
    0x1B8,  // "Do not think of this as an opportunity to avoid the lesson, Potter."
    0x1B9,  // "Yes, Professor."
    0x1BA,  // "Let's go to the Potions store room, Hermione."
    // Block 299
    0x1BB,  // "I seem to recall that I requested more herbs than this, Potter. Kindly r..."
    // Block 300
    0x1CA,  // "I seem to recall that I requested more ingredients than this, Weasley. D..."
    // Block 301
    0x1BD,  // "These must be the herbs!"
    0x1BE,  // "Right, so where's the chopping table? It shouldn't be too difficult to f..."
    // Block 302
    0x1BF,  // "Here's the chopping table! I just need to spread out the herbs and get t..."
    // Block 303
    0x1C0,  // "Diffindo!"
    0x1C1,  // "It worked! Now, we'd better get all this to Snape right away!"
    // Block 304
    0x1C2,  // "Here's the chopping table!"
    0x1C3,  // "Yes, but where are the herbs? Let's keep looking."
    // Block 305
    0x1C4,  // "We'd better get started, Hermione."
    // Block 306
    0x1C5,  // "These must be the ingredients!"
    0x1C6,  // "Good job, Ron. Now where are the glass vials?"
    // Block 307
    0x1C7,  // "I've found the vials!"
    0x1C8,  // "Be careful with those, Ron. Snape won't be happy if you break them. Let'..."
    // Block 308
    0x1C9,  // "I seem to recall that I requested more ingredients than this, Weasley. D..."
    // Block 309
    0x1CA,  // "I seem to recall that I requested more ingredients than this, Weasley. D..."
    // Block 310
    0x1CB,  // "Quite remarkable, Potter. You appear to have achieved the task without d..."
    // Block 311
    0x1CC,  // "You surprise me, Mr. Weasley. I was expecting you to return empty handed..."
    // Block 312
    0x1CE,  // "Now, mix the herbs and ingredients in the large classroom cauldron."
    // Block 313
    0x1CF,  // "I've found the ingredients!"
    0x1D0,  // "Excellent! Now put the ingredients into the vials - and do be careful, R..."
    // Block 314
    0x1D1,  // "OK, all done. Nothing for Snape to complain about."
    0x1D2,  // "Don't be too sure... Let's get back."
    // Block 315
    0x1D3,  // "Don't think you're leaving just yet. The Shrinking Solution has yet to b..."
    0x1D4,  // "Uh-oh, how are we going to brew the potion?"
    0x1D5,  // "Maybe Hermione knows?"
    0x1D6,  // "It isn't difficult. Simply put the herbs and ingredients into the cauldr..."
    0x1D7,  // "There go the herbs..."
    0x1D8,  // "And now for the ingredients..."
    // Block 316
    0x1D9,  // "It's worked!"
    0x1DA,  // "I suppose you expect a reward... Take this Wingardium Leviosa spellbook...."
    // Block 317
    0x1E1,  // "The ingredients necessary for the Shrinking Solution are: daisy root, de..."
    // Block 318
    0x1E2,  // "There, we have all the ingredients. Now we need to get them back to clas..."
    // Block 319
    0x1B6,  // "Do not think of this as an opportunity to avoid the lesson, Weasley. Tar..."
    0x1B7,  // "Yes, Professor."
    // Block 320
    0x1B8,  // "Do not think of this as an opportunity to avoid the lesson, Potter."
    0x1B9,  // "Yes, Professor."
    // Block 321
    0x1DB,  // "Potions class is in the dungeons off the Entrance Hall."
    // Block 322
    0x1DC,  // "I hate having to go into the dungeons to get to Potions."
    // Block 323
    0x1DD,  // "It's Potions next - down in the dungeons."
    // Block 324
    0x1DE,  // "Potions? It's held down in the dungeons."
    // Block 325
    0x1DF,  // "I much prefer Potions to Transfiguration."
    // Block 326
    0x1E0,  // "Shouldn't you be on your way to the Potions classroom? It's in the dunge..."
    // Block 327
    0x209,  // "The Defense Against the Dark Arts class is on the third floor."
    // Block 328
    0x20A,  // "Defense Against the Dark Arts class is on the third floor. I heard it mi..."
    // Block 329
    0x20B,  // "The staff room's next to the Entrance Hall. I don't think we are allowed..."
    // Block 330
    0x20C,  // "Why do you want to go to the staff room? Isn't it for teachers only?"
    // Block 331
    0x20D,  // "The staff room's next to the Entrance Hall."
    // Block 332
    0x20E,  // "The staff room? Didn't Professor Binns fall asleep in there once?"
    // Block 333
    0x20F,  // "The Defense Against the Dark Arts classroom's on the third floor."
    // Block 334
    0x210,  // "I wonder if the new Defense Against the Dark Arts teacher will be as goo..."
    // Block 335
    0x1E8,  // "It's almost time for Defense Against the Dark Arts class."
    0x1E9,  // "I've just seen a notice on the staff-room door saying that we should all..."
    0x1EA,  // "OK, let's go."
    // Block 336
    0x1EB,  // "I'm really looking forward to Defense Against the Dark Arts!"
    // Block 337
    0x1EC,  // "I wonder what the new teacher's like?"
    // Block 338
    0x1ED,  // "I hope the new Defense Against the Dark Arts teacher is better than that..."
    // Block 339
    0x1EE,  // "How many Defense Against the Dark Arts teachers have we had so far?"
    // Block 340
    0x1EF,  // "I didn't like Professor Quirrell very much. And Professor Lockhart was a..."
    // Block 341
    0x1F0,  // "Anyone know what Professor Lupin did before he came to Hogwarts?"
    // Block 342
    0x1F1,  // "I've never seen inside the staff-room before. I wonder what it's like?"
    // Block 343
    0x1F2,  // "I hope we haven't got Cornish pixies again..."
    // Block 344
    0x1F3,  // "Professor Lupin looks rather shabby, if you ask me."
    // Block 345
    0x1F4,  // "If there weren't any Dark Arts, there'd be no need for this lesson..."
    // Block 346
    0x1F5,  // "Thinking of trying to catch Black single-handed, Potter?"
    // Block 347
    0x1F6,  // "Good afternoon. Today's will be a practical lesson."
    0x1F7,  // "I draw your attention to this wardrobe. There's a Boggart in there. Now,..."
    0x1F8,  // "It's a shape-shifter. It can take the shape of whatever it thinks will f..."
    0x1F9,  // "Well put. The charm that repels a Boggart is simple. It forces the Bogga..."
    // Block 348
    0x1FA,  // "Neville, Lavender, Ron and Parvati, please come forward."
    // Block 349
    0x1FB,  // "Oh! I... erm... OK, I s'pose..."
    // Block 350
    0x1FC,  // "Now, are you ready?"
    0x1FD,  // "Erm... OK, I s'pose..."
    0x1FE,  // "Remember to think of something amusing and cast Riddikulus. I'm going to..."
    // Block 351
    0x200,  // "Now, please return to your common room."
    0x3A3,  // "The Riddikulus Boggart Challenge can now be accessed from the Mini-Games..."
    // Block 352
    0x201,  // "Anything worrying you, Harry?"
    0x202,  // "Yes. Why didn't you let me fight the Boggart?"
    0x203,  // "I assumed that if the Boggart faced you, it would assume the shape of Lo..."
    0x204,  // "I did think of him, at first. But then I remembered those Dementors."
    0x205,  // "The Dementors affect you worse than the others because there are horrors..."
    0x206,  // "Thank you very much, Professor."
    0x207,  // "I'll come and find you for the lessons. Now, I'd advise you to go to you..."
    0x208,  // "Bye, Professor."
    // Block 353
    0x211,  // "I'd advise you to go to your common room."
    // Block 354
    0x213,  // "Meowrr!"
    // Block 355
    0x214,  // "Crookshanks! What is wrong with you?"
    0x215,  // "Just keep that cat away from Scabbers!"
    // Block 356
    0x216,  // "Scabbers, come back!"
    0x217,  // "I'll help you get him, Ron."
    // Block 357
    0x218,  // "Scabbers! There you are!"
    0x219,  // "Let's get back to the common room."
    // Block 358
    0x283,  // "Hagrid! Look at my new Firebolt!"
    // Block 359
    0x284,  // "Yeh've heard!"
    0x285,  // "Hagrid, what is it?"
    0x286,  // "They're going ter put poor Buckbeak on trial fer attackin' Malfoy..."
    0x287,  // "Listen, you can't give up. You just need a good defense. You can call us..."
    // Block 360
    0x289,  // "We can look it up for you in the library. Coming, Hermione?"
    // Block 361
    0x28A,  // "No. I want a quick word with Professor McGonagall."
    // Block 362
    0x28B,  // "Don't worry, we'll work out a defense for Buckbeak. Let's go to the libr..."
    // Block 363
    0x21A,  // "Heard about the portrait of the Fat Lady?"
    // Block 364
    0x21B,  // "There's something going on just outside the Gryffindor common room!"
    // Block 365
    0x21C,  // "Hogsmeade was really good fun."
    // Block 366
    0x21D,  // "What's happened to the Fat Lady?"
    // Block 367
    0x21E,  // "All the portraits seem a little nervous..."
    // Block 368
    0x21F,  // "I wonder why the portraits are so nervous?"
    // Block 369
    0x220,  // "The portraits are looking rather shifty at the moment..."
    // Block 370
    0x221,  // "The portraits are making me nervous..."
    // Block 371
    0x222,  // "The eyes of the portraits are following us more than usual..."
    // Block 372
    0x223,  // "It's come to something when even a portrait's not safe around here..."
    // Block 373
    0x224,  // "Why isn't everyone going into the common room?"
    0x225,  // "Oh, my... haven't you heard, Harry?"
    0x226,  // "Heard what?"
    0x227,  // "Over here!"
    0x228,  // "Oh no..."
    0x229,  // "The Fat Lady's gone and we can't get into the common room..."
    // Block 374
    0x22A,  // "We need to find her! Come on, Ron. Harry, why don't you stay here in cas..."
    // Block 375
    0x22B,  // "OK."
    // Block 376
    0x230,  // "Have at thee, scurvy knave!"
    0x22C,  // "The Fat Lady must be in another portrait..."
    0x22D,  // "Why don't we ask Sir Cadogan? He's bonkers, but he knows all about this..."
    0x22E,  // "OK, we have to start somewhere."
    0x22F,  // "Hello, Sir Cadogan."
    0x232,  // "I don't suppose you happened to see the Fat Lady go by here?"
    0x233,  // "That I did, fair maiden, and in great distress!"
    0x234,  // "Could you help us find her?"
    0x235,  // "That I shall, milady, and verily so!"
    // Block 377
    0x249,  // "How can we find Sir Cadogan?"
    0x24A,  // "Let's ask the portraits. Maybe they saw him go by."
    // Block 378
    0x236,  // "Has Sir Cadogan come this way?"
    // Block 379
    0x231,  // "Maybe we could ask the portraits where the Fat Lady is?"
    // Block 380
    0x236,  // "Has Sir Cadogan come this way?"
    0x237,  // "No, I'm afraid he hasn't."
    // Block 381
    0x236,  // "Has Sir Cadogan come this way?"
    0x238,  // "Sorry, no."
    // Block 382
    0x236,  // "Has Sir Cadogan come this way?"
    0x239,  // "Don't know anyone by that name."
    // Block 383
    0x236,  // "Has Sir Cadogan come this way?"
    0x23A,  // "No, he hasn't."
    // Block 384
    0x236,  // "Has Sir Cadogan come this way?"
    0x23B,  // "I'm afraid not."
    // Block 385
    0x236,  // "Has Sir Cadogan come this way?"
    0x23C,  // "That daft knight? No, I'm afraid not."
    // Block 386
    0x236,  // "Has Sir Cadogan come this way?"
    0x23D,  // "Ah, yes. I believe he's down on the lower levels."
    // Block 387
    0x236,  // "Has Sir Cadogan come this way?"
    0x23E,  // "Yes. Took a dive into the portrait room."
    // Block 388
    0x236,  // "Has Sir Cadogan come this way?"
    0x23F,  // "Indeed. Saw him dash into the Grand Staircase."
    // Block 389
    0x236,  // "Has Sir Cadogan come this way?"
    0x240,  // "He's on the second floor. And would you kindly ask him to stay there?"
    // Block 390
    0x241,  // "The lady is found!"
    // Block 391
    0x242,  // "Hello, are you all right?"
    0x243,  // "Oh, it was horrible... horrible!"
    0x244,  // "What happened?"
    0x245,  // "He's got a dreadful temper!"
    0x246,  // "Who? Who has?"
    0x247,  // "Sirius Black!"
    0x248,  // "We have to warn Harry!"
    0x24B,  // "Come on, then - back to the common room!"
    // Block 392
    0x24F,  // "I think you should return to your common room - it's not safe."
    // Blocks 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407
    0x24C,  // "Harry, it was Sirius Black who slashed the Fat Lady's portrait!"
    0x24D,  // "Do you think Black's still in the castle?"
    0x24E,  // "He might be!"
    // Block 408
    0x250,  // "We should be on our way to Defense Against the Dark Arts class."
    0x251,  // "I wonder if Professor Lupin will even be there? He hasn't looked well la..."
    0x252,  // "That class does seem to take a toll on its teachers. Let's get going."
    // Block 409
    0x253,  // "Sorry we're late - oh, Professor Snape!"
    // Block 410
    0x254,  // "This lesson began ten minutes ago, Potter. Sit down."
    // Block 411
    0x255,  // "Professor Lupin says he's feeling too ill to teach today."
    0x256,  // "I would like you all to go to the library and research the subject of -..."
    // Block 412
    0x258,  // "I've already read a great deal about werewolves... I even know how to im..."
    0x259,  // "Well, good for you, Hermione. I'm sure that'll come in really useful one..."
    0x25A,  // "Let's get going."
    // Block 413
    0x257,  // "And Potter, don't be surprised if I stop by to check on your progress."
    // Block 414
    0x25B,  // "Let's ask Madam Pince where we can find the book we need."
    // Block 415
    0x25C,  // "What can I do for you?"
    0x25D,  // "We were wondering if you have a good book on werewolves?"
    0x25E,  // "I'm afraid that our only werewolf reference book had a tussle with 'The..."
    0x25F,  // "Why don't we find the torn pages? Then I can place them back in the book..."
    0x260,  // "I would appreciate you doing that, Miss Granger."
    0x261,  // "OK, let's get to it."
    // Block 416
    0x262,  // "You've done splendidly, but you don't have all the pages. Hurry and get..."
    // Block 417
    0x263,  // "Excellent, you have all the pages! Would you like to repair the book now..."
    // Block 418
    0x264,  // "Reparo!"
    // Block 419
    0x265,  // "You two go back to class and stall Snape. I'll write up the research and..."
    0x266,  // "OK."
    // Block 420
    0x26E,  // "Here's the first book page. We'd better find the rest."
    // Block 421
    0x270,  // "Here's another book page."
    // Block 422
    0x26F,  // "Great! We've found all the pages! Let's take them back to Madam Pince."
    // Block 423
    0x267,  // "Potter, Weasley... where is your research?"
    // Block 424
    0x268,  // "Here it is, Professor!"
    // Block 425
    0x269,  // "This is... acceptable."
    // Block 426
    0x26A,  // "Hermione, how did you write that up so quickly?"
    0x26B,  // "Umm... like I said, I'd read the book before. See you later..."
    // Block 427
    0x26C,  // "Ever get the feeling there's something funny going on with her?"
    0x26D,  // "More and more... C'mon, let's get back to the common room."
    // Block 428
    0xEB,  // "Uhhh..."
    // Block 429
    0x271,  // "I wonder where Hermione's got to?"
    0x272,  // "She'll miss the Christmas feast in the Great Hall if she doesn't turn up..."
    // Block 430
    0x273,  // "Something wrong?"
    // Block 431
    0x274,  // "Hedwig dropped a parcel on top of that notice board and we don't know ho..."
    0x275,  // "Why don't you just use Wingardium Leviosa?"
    // Block 432
    0x278,  // "Wingardium Leviosa!"
    // Block 433
    0x279,  // "I don't believe it - it's a Firebolt racing broom! There's no card, thou..."
    0x27A,  // "Wait 'til Malfoy sees you on this! He'll be sick as a pig!"
    0x27B,  // "I can't believe this. Who - ?"
    0x27C,  // "I know who it could've been - Lupin!"
    0x27D,  // "I can't see Lupin affording something like this."
    // Block 434
    0x27E,  // "It's a bit odd, isn't it? Maybe we should get Professor McGonagall to ch..."
    0x27F,  // "I'm sure it's all right, Hermione. I can't wait to show Hagrid. Let's go..."
    // Block 435
    0x280,  // "Let's go then!"
    0x281,  // "You aren't going to ride the Firebolt to Hagrid's hut, are you?"
    0x282,  // "If it makes you feel better, I'll carry it."
    // Block 436
    0x283,  // "Hagrid! Look at my new Firebolt!"
    // Block 437
    0x284,  // "Yeh've heard!"
    0x285,  // "Hagrid, what is it?"
    // Block 438
    0x286,  // "They're going ter put poor Buckbeak on trial fer attackin' Malfoy..."
    0x287,  // "Listen, you can't give up. You just need a good defense. You can call us..."
    0x288,  // "I'm sure I've read about a case of Hippogriff-baiting…"
    0x289,  // "We can look it up for you in the library. Coming, Hermione?"
    0x28A,  // "No. I want a quick word with Professor McGonagall."
    0x28B,  // "Don't worry, we'll work out a defense for Buckbeak. Let's go to the libr..."
    // Block 439
    0x28C,  // "We're looking for a book on wizard law, Madam Pince."
    0x28D,  // "Very well; the legal section is on the south side of the library."
    // Block 440
    0x28E,  // "Here's the legal section! It looks like no one's been here in a long tim..."
    0x28F,  // "Let's try and find books that refer to Hippogriff-baiting."
    // Block 441
    0x290,  // "I can't find anything on Hippogriffs!"
    0x291,  // "There're certainly a lot of obscure titles here."
    // Block 442
    0x292,  // "Look, this must be the book Hermione mentioned! It's got a section deali..."
    0x293,  // "Let's have a look!"
    0x294,  // "It doesn't look good."
    0x295,  // "We can't tell Hagrid that!"
    0x296,  // "Let's find Hermione. Maybe she'll be able to make sense of it all."
    // Block 443
    0x298,  // "I need to see Professor McGonagall."
    // Block 444
    0x299,  // "What is it, Miss Granger?"
    0x29A,  // "It's Harry, Professor. He's just received an anonymous gift of a Firebol..."
    0x29B,  // "Hmm - thank you for informing me, Miss Granger. I agree with you and I'l..."
    0x29C,  // "Thank you, Professor."
    // Block 445
    0x29D,  // "Did you find out anything?"
    0x29E,  // "Nothing very positive, I'm afraid."
    0x29F,  // "Oh, poor Hagrid - and poor Buckbeak. Let's go back to the common room."
    // Block 446
    0x297,  // "Is there something else I can help you with?"
    // Block 447
    0x2A0,  // "Is it true about the Firebolt?"
    // Block 448
    0x2A1,  // "I heard somebody got a Firebolt for Christmas!"
    // Block 449
    0x2A2,  // "I'd really like to see a Firebolt close up."
    // Block 450
    0x2A3,  // "I'd love a new broom for Christmas. I still have my sister's old one!"
    // Block 451
    0x2A4,  // "I dream about Firebolts!"
    // Block 452
    0x2A5,  // "Firebolts are the best racing brooms in the world!"
    // Block 453
    0x2A6,  // "I'd love to ride a Firebolt!"
    // Block 454
    0x2A7,  // "If our Quidditch team all had Firebolts, they'd make mincemeat of everyo..."
    // Block 455
    0x2A8,  // "I've heard Firebolts are the fastest brooms ever."
    // Block 456
    0x2A9,  // "I touched a Firebolt once and I didn't wash my hands for two weeks!"
    // Block 457
    0x3BE,  // "Harry. Hurry up!"
    // Block 458
    0x19F,  // "I really appreciate all yeh've done."
    // Block 459
    0x2AA,  // "We should be on our way to the Christmas feast in the Great Hall."
    0x2AB,  // "Absolutely, Harry! I'm starving!"
    0x2AC,  // "I'll see you there. I have - something important to do..."
    // Block 460
    0x2B7,  // "Miss Granger has recently informed me that you have been sent a broomsti..."
    // Block 461
    0x2B8,  // "May I see it? Hmm. And there was no note at all, Potter?"
    0x2B9,  // "No."
    0x2BA,  // "I see. Well, I'm afraid I will have to take this, Potter."
    0x2BB,  // "W-what? Why?"
    0x2BC,  // "It will need to be checked for jinxes. It shouldn't take more than a few..."
    0x2BD,  // "You will have it back if we are sure it is jinx-free. I shall keep you i..."
    // Block 462
    0x2BE,  // "I don't believe it!"
    0x2BF,  // "There's nothing wrong with it!"
    // Block 463
    0x2C0,  // "Hermione! What did you go running to McGonagall for?"
    0x2C1,  // "Because I thought - and Professor McGonagall agrees with me - that that..."
    // Block 464
    0x2C2,  // "Merry Christmas! Sit down, sit down! And now - crackers! Or, to be preci..."
    // Block 465
    0x2C3,  // "That was a lot of fun."
    0x2C4,  // "Yes, it was!"
    0x3A5,  // "Wizard Cracker Pop-it can now be accessed from the Mini-Games menu found..."
    0x2C5,  // "Let's go to the common room and try and take our minds off losing the Fi..."
    // Block 466
    0x2AD,  // "I love the Christmas feast!"
    // Block 467
    0x2AE,  // "I'm going to eat so much at the Christmas Feast they'll have to send me..."
    // Block 468
    0x2AF,  // "I hope there are crackers at the Christmas feast."
    // Block 469
    0x2B0,  // "Great! It's time for the Christmas feast!"
    // Block 470
    0x2B1,  // "We need more holidays - and more feasts!"
    // Block 471
    0x2B2,  // "I've heard we'll be playing a game at this year's Christmas feast."
    // Block 472
    0x2B3,  // "Anyone got any Toothflossing Stringmints for after the Christmas feast?"
    // Block 473
    0x2B4,  // "I don't want to be late for the Christmas feast!"
    // Block 474
    0x2B5,  // "Christmas or Halloween... I don't know which feast I like best."
    // Block 475
    0x137,  // "Shove off, Potter!"
    // Block 476
    0x138,  // "We don't speak to Gryffindors."
    // Block 477
    0x136,  // "I don't speak to Gryffindors."
    // Block 478
    0xAA,  // "Hello."
    // Block 479
    0x1AC,  // "I wish I was still in bed."
    // Block 480
    0x303,  // "Zonko's is definitely the best shop in Hogsmeade."
    // Block 481
    0xAC,  // "Really good to see you."
    // Block 482
    0x358,  // "Good evening, Sirius. How I hoped I would be the one to catch you…"
    // Block 483
    0x2C6,  // "I was wondering, Harry, if you'd like to begin the Anti-Dementor lessons..."
    0x2C7,  // "Of course, Professor."
    0x2C8,  // "Very well, then. Meet me in my office on the third floor."
    // Block 484
    0x2DB,  // "Glad you came, Harry. Are you ready for the lesson?"
    0x2DC,  // "Yes, Professor."
    0x2C9,  // "So... The spell I am going to try and teach you is highly advanced magic..."
    0x2CA,  // "How does it work?"
    0x2CB,  // "It conjures up a Patronus, which is a kind of Anti-Dementor - a guardian..."
    0x2CC,  // "What does a Patronus look like?"
    0x2CD,  // "Each one is unique to the wizard who conjures it."
    0x2CE,  // "And how do you conjure it?"
    0x2CF,  // "With the incantation - expecto patronum! There is a Boggart in this ches..."
    0x2D0,  // "Expecto patronum!"
    // Block 485
    0x2D0,  // "Expecto patronum!"
    // Block 486
    0x2D1,  // "Excellent! Ready for another try?"
    // Block 487
    0x2D2,  // "Well done! Ready to go again?"
    // Block 488
    0x2D3,  // "Impressive! Ready for one last try?"
    // Block 489
    0x2D4,  // "Excellent! Excellent, Harry! That was definitely a start!"
    // Block 490
    0x2D5,  // "A good attempt, Harry. Ready for another go?"
    // Block 491
    0x2D6,  // "Try to concentrate on a single, happy memory, Harry. Ready for another a..."
    // Block 492
    0x2D7,  // "Think of your happiest memory, Harry. Ready for another go?"
    // Block 493
    0x2D8,  // "That was a little better. Ready for another try?"
    // Block 494
    0x2D4,  // "Excellent! Excellent, Harry! That was definitely a start!"
    0x206,  // "Thank you very much, Professor."
    0x2D9,  // "Professor Lupin? If you knew my dad, you must've known Sirius Black as w..."
    0x2DA,  // "I thought I did, Harry. You'd better get off to your common room. It's g..."
    0x208,  // "Bye, Professor."
    // Block 495
    0x2E6,  // "Well, here it is. There doesn't seem to be anything wrong with the Fireb..."
    0x2E7,  // "I can have it back? Seriously?"
    0x2E8,  // "Seriously. And Potter - do try and win, won't you?"
    // Block 496
    0x2DD,  // "Seen Ron around?"
    0x2DE,  // "No, I haven't."
    // Block 497
    0x2DF,  // "LOOK!"
    0x2E1,  // "N-no..."
    0x2E2,  // "LONG, GINGER CAT HAIRS!"
    // Blocks 498, 499
    0x2E4,  // "Let's go to the Quidditch pitch. The walk and the fresh air will clear o..."
    // Block 500
    0x2E5,  // "You haven't heard the last of this, Hermione!"
    // Block 501
    0x2E9,  // "Yes! We won!"
    0x2EA,  // "Good for you, Harry!"
    0x2EB,  // "I've never seen Professor McGonagall so angry! Malfoy's definitely for i..."
    0x2EC,  // "Well done, Harry! Ten Galleons to me! Must find Penelope. Excuse me -"
    // Block 502
    0x2ED,  // "You were fantastic, Harry!"
    // Block 503
    0x2EE,  // "You gave Malfoy one heck of a fright!"
    // Block 504
    0x2EF,  // "I know that you all want to celebrate, but I think we've had quite enoug..."
    // Block 505
    0x2F0,  // "AAARRRGGGHHH! NOOOOOOOOOOOO!"
    // Block 506
    0x2F1,  // "Ron? What's going on?"
    0x2F2,  // "Black! Sirius Black! With a knife!"
    0x2F3,  // "What?"
    0x2F4,  // "Here! Just now! Slashed the curtains! Woke me up!!"
    0x2F5,  // "We'd better get Professor McGonagall!"
    // Block 507
    0x2F6,  // "Don't go without me!"
    // Block 508
    0x2F7,  // "I am delighted that Gryffindor won the match, but this is getting ridicu..."
    0x2F8,  // "Ron had a nightmare, Professor."
    0x2F9,  // "IT WASN'T A NIGHTMARE! SIRIUS BLACK WAS STANDING OVER ME, HOLDING A KNIF..."
    // Block 509
    0x2FA,  // "Professor McGonagall, Sir Cadogan has just informed me that he let a man..."
    0x2FB,  // "But - but the password?"
    0x2FC,  // "Apparently, this man already had them! He read them off a piece of paper..."
    0x2FD,  // "Which abysmally foolish person wrote down the password and left it lying..."
    // Block 510
    0x2FE,  // "I - erm - well, I..."
    0x2FF,  // "I see. From tonight, Sir Cadogan is sacked and the Fat Lady will return...."
    // Block 511
    0x300,  // "I'm still stuffed from the Christmas feast!"
    // Block 512
    0x301,  // "I'm really glad Gryffindor beat Slytherin."
    // Block 513
    0x302,  // "I missed the last trip to Hogsmeade!"
    // Block 514
    0x303,  // "Zonko's is definitely the best shop in Hogsmeade."
    // Block 515
    0x304,  // "When's the next feast going to be, anyway?"
    // Block 516
    0x305,  // "I heard that Sirius Black was seen in Gryffindor Tower!"
    // Block 517
    0x306,  // "Is it true Sirius Black tried to stab Ron Weasley?"
    // Block 518
    0x307,  // "Security's really been stepped up, hasn't it?"
    // Blocks 519, 520, 521, 522, 523, 524, 525, 526
    0x308,  // "I'm exhausted, but I can't sleep... there's too much going on in my head..."
    // Block 527
    0x309,  // "It's a lovely night..."
    // Block 528
    0x30A,  // "There's Crookshanks! But what's that walking alongside him?"
    // Block 529
    0x30B,  // "It's a black dog!"
    // Block 530
    0x30C,  // "It's a note from Hagrid: 'Dear Harry, we lost the trial. Buckbeak's exec..."
    // Block 531
    0x30D,  // "Oh, no! They can't do this! Buckbeak isn't dangerous! I have to find Ron..."
    // Block 532
    0x318,  // "Hagrid sent me a note. They're going to execute Buckbeak!"
    0x319,  // "No! They can't do that!"
    0x31A,  // "We have to go and see Hagrid after dinner and give him our support!"
    // Block 533
    0x31B,  // "Let's go!"
    // Block 534
    0x30E,  // "I've heard they're going to execute Buckbeak!"
    // Block 535
    0x30F,  // "Is it true about Buckbeak?"
    // Block 536
    0x310,  // "Poor Hagrid! He loves that Hippogriff."
    // Block 537
    0x311,  // "I wonder how they'll execute Buckbeak?"
    // Block 538
    0x312,  // "Personally, I'm against the execution of magical creatures."
    // Block 539
    0x313,  // "It's a real shame about Buckbeak."
    // Block 540
    0x314,  // "Poor Buckbeak..."
    // Block 541
    0x315,  // "It's all Malfoy's fault!"
    // Block 542
    0x316,  // "Hippogriffs aren't dangerous unless you provoke them!"
    // Block 543
    0x317,  // "Malfoy provoked Buckbeak!"
    // Blocks 544, 545
    0x31C,  // "There's Hagrid's hut!"
    0x31D,  // "Let's hurry…"
    // Block 546
    0x31E,  // "Isn't there anything anyone can do, Hagrid?"
    0x31F,  // "Dumbledore's tried. He's got no power ter overrule the Committee. I expe..."
    0x320,  // "We'll stay with you, Hagrid…"
    // Block 547
    0x321,  // "Squeak!"
    0x322,  // "It's Scabbers! Scabbers, what are you doing here?"
    // Block 548
    0x323,  // "They're comin' - Macnair, the executioner, and Fudge. Yeh'd best leave n..."
    0x324,  // "We'll be back, Hagrid..."
    // Block 549
    0x325,  // "What was that? It sounded like..."
    0x326,  // "Oh, no!"
    0x327,  // "They did it! I d-don't believe it - they executed Buckbeak!"
    // Block 550
    0x323,  // "They're comin' - Macnair, the executioner, and Fudge. Yeh'd best leave n..."
    // Block 551
    0x329,  // "How could they execute Buckbeak - how could they?"
    0x328,  // "Scabbers, keep still!"
    0x32A,  // "Squeak!"
    0x32B,  // "Ouch! Scabbers bit me!"
    // Block 552
    0x32D,  // "Yeowwl!"
    // Block 553
    0x32C,  // "Crookshanks, no! Come back!"
    // Block 554
    0x32E,  // "The black dog! It's got Ron!"
    // Block 556
    0x32F,  // "It's dragging him towards the Whomping Willow! And where's Crookshanks?"
    // Block 555
    0x330,  // "Help!"
    // Block 557
    0x331,  // "The dog's dragged Ron under the Whomping Willow!"
    0x332,  // "If that dog can get in, we can!"
    // Block 558
    0x333,  // "Crookshanks! How did he know the way in?"
    0x335,  // "We've got to rescue Ron!"
    // Block 559
    0x334,  // "That took care of that - now let's get Ron!"
    // Block 560
    0x336,  // "We have to find Ron! Maybe we should split up…"
    // Block 561
    0x345,  // "Where are we?"
    0x346,  // "I think we're in the Shrieking Shack - the most haunted building in Brit..."
    0x347,  // "Probably a good place for Black to hide. Ron must be here somewhere... w..."
    // Block 562
    0x337,  // "Any luck?"
    0x338,  // "No. You?"
    0x339,  // "I'm afraid not. They must have gone this way."
    // Blocks 563, 564
    0x33A,  // "Well, this isn't helpful! The platform's lifted me up here but it's stuc..."
    0x33B,  // "Let me look around - there might be a switch somewhere."
    0x33C,  // "Wait! I can see a switch over there on that balcony!"
    // Block 565
    0x33D,  // "Thanks, Harry, but you could have hurried it up a bit, don't you think?"
    // Block 566
    0x33E,  // "All these doors are locked. I need to find some way of opening them."
    // Block 567
    0x33F,  // "I bet I can sever these ropes with Diffindo."
    // Block 568
    0x340,  // "Oh, no! It was a trap!"
    // Block 569
    0x341,  // "There's no way to get over this gap. If we can find a way to turn this v..."
    // Block 570
    0x342,  // "All of these doors are locked. I need to find some way of opening them."
    // Block 571
    0x343,  // "Maybe there's a key in one of these barrels."
    // Block 572
    0x348,  // "Ron - are you OK? Where's the dog?"
    0x349,  // "Not a dog. Harry, it's a trap... Black is the dog... he's an Animagus..."
    // Block 573
    0x34B,  // "Where is he, Sirius? Where is Peter Pettigrew?"
    0x34C,  // "Over there..."
    // Block 574
    0x34D,  // "Squeak!"
    0x34E,  // "Ah, there you are, Peter. Ready, Sirius?"
    // Block 575
    0x34F,  // "S-Sirius... R-Remus... My friends... my old friends..."
    0x350,  // "I broke out of Azkaban, not to get at you, Harry, but to seek revenge on..."
    0x351,  // "You don't understand! The Dark Lord was taking over everywhere! He would..."
    0x352,  // "You should have realized. If Voldemort didn't kill you, we would. Goodby..."
    // Block 576
    0x353,  // "NO! You can't kill him. I don't reckon my dad would've wanted his best f..."
    0x354,  // "Very well, Harry. You're the only person who has the right to decide. We..."
    // Block 577
    0x355,  // "You're free, Sirius."
    0x356,  // "Yes, thank you all. Harry, your parents named me your godfather. Once my..."
    0x357,  // "When can I move in?"
    // Block 578
    0x359,  // "Professor Snape! You're making a mistake. Sirius Black isn't here to kil..."
    0x35A,  // "SILENCE! Two more for Azkaban tonight..."
    // Block 579
    0x35B,  // "Professor Snape - it - it wouldn't hurt to hear what they've got to say,..."
    0x35C,  // "Professor Lupin could have killed me many times. If he was helping Black..."
    0x35D,  // "Get out of the way, Potter."
    // Block 580
    0x358,  // "Good evening, Sirius. How I hoped I would be the one to catch you…"
    // Block 581
    0x34A,  // "Expelliarmus!"
    // Block 582
    0x35E,  // "Uhhhhh..."
    0x35F,  // "Oh my - Professor Lupin didn't take his Potion tonight!"
    // Block 583
    0x360,  // "Arrrrrooooooooh!"
    0x361,  // "Leave it to me - GO!"
    // Block 584
    0x367,  // "Hermione, Pettigrew's gone, he transformed!"
    0x368,  // "Do something, Harry! Please!"
    // Block 585
    0x369,  // "Expecto... Expecto patro... No - no - he's innocent…"
    // Block 586
    0x36A,  // "Dad?"
    // Block 587
    0x371,  // "What we need is more time."
    0x372,  // "Miss Granger, three turns should do it. Good luck."
    // Block 588
    0x373,  // "What are we supposed to do?"
    0x374,  // "We're going to use the Time-Turner to go back three hours, rescue Buckbe..."
    // Block 589
    0x3BB,  // "We have to get back to the lake... no matter what!"
    0x3BC,  // "Right... we can't let them take Sirius back to Azkaban!"
    0x378,  // "We have to hurry, Harry."
    0x379,  // "OK. Buckbeak first. We haven't got much time..."
    // Block 590
    0x37B,  // "There's Hagrid! Don't let him see us!"
    // Block 591
    0x37C,  // "It's all righ', Beaky... It's all righ'..."
    // Block 592
    0x37D,  // "Who's that at the door?"
    // Block 593
    0x37E,  // "That must be us! We don't have much time before Macnair, the executioner..."
    // Block 594
    0x37F,  // "Hello, Buckbeak, remember me? We're going to take you for a walk."
    0x380,  // "Let's hurry on to the lake!"
    // Block 595
    0x381,  // "Look, it's us... and Lupin's closing in!"
    // Block 596
    0x383,  // "Well done, Hermione!"
    // Block 597
    0x384,  // "Here comes Lupin! Help, Buckbeak!"
    // Block 598
    0x389,  // "Thanks, Buckbeak!"
    // Block 599
    0x382,  // "I know what to do! Arrrrrooooooooh!"
    // Block 600
    0x38A,  // "We'd better get Buckbeak to a safe place before we go back inside."
    // Block 601
    0x3BB,  // "We have to get back to the lake... no matter what!"
    0x3BC,  // "Right... we can't let them take Sirius back to Azkaban!"
    // Block 602
    0x3BD,  // "The Dementors almost have Sirius! Where are you, Dad? Wait a minute, it..."
    0x3BE,  // "Harry. Hurry up!"
    0x3BF,  // "Wait here, Hermione…"
    // Block 603
    0x3C0,  // "EXPECTO PATRONUM!"
    // Block 604
    0x3C1,  // "What did you do?"
    0x3C2,  // "I just saved our lives! Listen, I'll fly Buckbeak up to the West Tower's..."
    0x3C4,  // "And whoever gets there first can set Sirius free! Let's go!"
    0x3C5,  // "Come on, Buckbeak, we have to get to Sirius!"
    // Block 605
    0x3B2,  // "A pipe must have burst here. Maybe we should split up?"
    // Block 606
    0x3B0,  // "Hermione, I'll go this way. Maybe you could try looking around for a fas..."
    0x3B1,  // "Okay. I'll meet up with you at the tower."
    // Block 607
    0x3B3,  // "I bet I can get through very quickly this way. Why don't you peek around..."
    0x3B4,  // "Okay. I'll meet up with you at the tower."
    // Blocks 608, 609
    0x3B5,  // "Hermione! You got here quickly! We must get to Sirius. The Dementors are..."
    0x3B6,  // "Harry! How did you manage to get here before me? Never mind, the Demento..."
    // Block 610
    0x3B7,  // "Malfoy!"
    0x3B8,  // "What are you doing here, Potter? In a hurry to get somewhere?"
    0x3B9,  // "Stay out of the way, Malfoy."
    // Block 611
    0x3C6,  // "How - how - ?"
    0x3C8,  // "Sirius, the Dementors are coming! You'd better go. Quickly, before they..."
    0x3C9,  // "How can I ever thank-"
    0x3CA,  // "GO!"
    0x3CB,  // "We'll see each other again. You are - truly your father's son, Harry..."
    // Block 612
    0x397,  // "You have a new item. To equip it, press START and then select Status/Equ..."
    // Block 613
    0x398,  // "You are about to enter a magical encounter. Each character and creature..."
    // Block 614
    0x399,  // "I wonder if there's something here that I can't see. Maybe I should try..."
    // Block 615
    0x39A,  // "Press the L or R Buttons to change spells. Press the B Button to cast th..."
    // Block 616
    0x39B,  // "These stairs look damaged. I wonder if the Reparo Spell would help?"
    // Block 617
    0x39C,  // "I bet I could use Flipendo to break those barrels."
    // Block 618
    0x39D,  // "That crate has a Flipendo symbol on it. If I hit it with the spell, it m..."
    // Block 619
    0x3A0,  // "I can always cast Flipendo on that button on the wall to move Flipendo c..."
    // Block 620
    0x39E,  // "Harry, this gate is locked and we don't have a key. I wonder if I should..."
    // Block 621
    0x39F,  // "Now you must choose who you want in your party. Ron or Hermione will joi..."
    // Blocks 622, 623
    0x3A1,  // "You've received some collector's cards! Collect all the cards to unlock..."
    // Block 624
    0x3D9,  // "Locked."
    // Block 625
    0x3DA,  // "I heard a rumor that Fred and George Weasley have a shop on the seventh..."
    // Block 626
    0x3DB,  // "The library? You'll need to go to the second floor."
    // Block 627
    0x3DC,  // "Madam Pince's desk is in the library."
    // Block 628
    0x3DD,  // "Fred and George sell all sorts of useful items in their shop on the seve..."
    // Block 629
    0x3DE,  // "Did you know that Fred and George sell items that you usually can't get..."
    // Block 630
    0x3DF,  // "Looking for a new robe? Fred and George will sell you one - try their sh..."
    // Block 631
    0x3E0,  // "The library's quite large - and it's got upper and lower levels..."
    // Block 632
    0x3E1,  // "I hope I can get to Madam Pince before everyone else does. She's on the..."
    // Block 633
    0x3E2,  // "If you're unwell, go and see Madam Pomfrey whenever you like. She's in t..."
    // Block 634
    0x3E3,  // "Madam Pomfrey's the Hogwarts nurse. She's on the fourth floor if you eve..."
    // Block 635
    0x3E4,  // "I know the hospital wing's on the fourth floor - I just can't remember t..."
    // Block 636
    0x3E5,  // "Have you visited Madam Pomfrey in the hospital wing on the fourth floor?"
    // Block 637
    0x3E6,  // "The hospital wing is on the fourth floor."
    // Block 638
    0x3E7,  // "Did you know that you can visit our shop on the seventh floor? You can b..."
    // Block 639
    0x3E8,  // "Come and join the Wizard Card Collectors' Club. Meetings are held on the..."
    // Block 640
    0x3E9,  // "I heard there are portrait shortcuts on every floor of Hogwarts..."
    // Block 641
    0x3EA,  // "I hate having to walk up and down the stairs all the time. I just use th..."
    // Block 642
    0x3EB,  // "Portraits are a convenient way to get around Hogwarts - once you figure..."
    // Block 643
    0x3EE,  // "There are portraits on the different floors that will help you get aroun..."
    // Block 644
    0x3ED,  // "When I'm running late for class, I use the portrait shortcuts to get whe..."
    // Block 645
    0x3ED,  // "When I'm running late for class, I use the portrait shortcuts to get whe..."
    // Block 646
    0x3D5,  // "Hello! How are you feeling?"
    // Block 647
    0x3D6,  // "You look as if you're injured. Here, let me help you."
    // Block 648
    0x3D7,  // "You look as healthy as can be. Come back if you need any assistance."
    // Block 649
    0x3D8,  // "Oh! You're awake. Someone found you unconscious and brought you in for c..."
    // Block 650
    0x3EF,  // "Welcome back to the Wizard Card Collectors' Club! You can trade cards wi..."
    // Block 651
    0x3F0,  // "I see that you've collected all of the cards in one of the categories. G..."
    // Block 652
    0x3F1,  // "Congratulations, you got all the cards! There's nothing more to unlock h..."
    // Block 653
    0x3CC,  // "@3 has been added to your Inventory."
    // Block 654
    0x3CD,  // "@3 has been removed from your Inventory."
    // Block 655
    0x3CE,  // "You've learned a new spell: @3."
    // Block 656
    0x3CF,  // "You don't have all the cards from the @3 collector's cards category."
    // Block 657
    0x3D0,  // "Congratulations! You collected all the cards from the @3 collector's car..."
    // Block 658
    0x3D1,  // "You've unlocked: @3."
    // Block 659
    0x3D2,  // "All members of your party level up by @3!"
    // Block 660
    0x3A2,  // "You've just gained your first level! You will now have more Stamina Poin..."
    // Block 661
    0x3D3,  // "@3 has been added to your Folio Universitas."
    // Block 662
    0x3D4,  // "Hagrid's copies of 'The Monster Book of Monsters' have been removed from..."
    // Block 663
    0x3A8,  // "You've received the Dunbar Oglethorpe, Devlin Whitehorn, and Cyprian You..."
    // Block 664
    0x3A9,  // "Harry receives Diffindo, Ron receives Spongify, and Hermione receives Gl..."
    // Block 125
    0x648,  // "You Receive: \n @1 Sickles"
    // Block 665
    0x3A6,  // "Tea Leaf Divination can now be accessed from the Mini-Games menu found o..."
};

const DialogBlock g_aDialogBlocks[666] = {
    { &g_adwDialogBlockTextIds[0], 8 },  // 0
    { &g_adwDialogBlockTextIds[8], 1 },  // 1
    { &g_adwDialogBlockTextIds[9], 1 },  // 2
    { &g_adwDialogBlockTextIds[10], 1 },  // 3
    { &g_adwDialogBlockTextIds[11], 0 },  // 4
    { &g_adwDialogBlockTextIds[11], 2 },  // 5
    { &g_adwDialogBlockTextIds[13], 1 },  // 6
    { &g_adwDialogBlockTextIds[14], 1 },  // 7
    { &g_adwDialogBlockTextIds[15], 1 },  // 8
    { &g_adwDialogBlockTextIds[16], 1 },  // 9
    { &g_adwDialogBlockTextIds[17], 1 },  // 10
    { &g_adwDialogBlockTextIds[18], 1 },  // 11
    { &g_adwDialogBlockTextIds[19], 1 },  // 12
    { &g_adwDialogBlockTextIds[20], 1 },  // 13
    { &g_adwDialogBlockTextIds[21], 1 },  // 14
    { &g_adwDialogBlockTextIds[22], 3 },  // 15
    { &g_adwDialogBlockTextIds[25], 8 },  // 16
    { &g_adwDialogBlockTextIds[33], 1 },  // 17
    { &g_adwDialogBlockTextIds[34], 1 },  // 18
    { &g_adwDialogBlockTextIds[35], 1 },  // 19
    { &g_adwDialogBlockTextIds[36], 4 },  // 20
    { &g_adwDialogBlockTextIds[40], 1 },  // 21
    { &g_adwDialogBlockTextIds[41], 0 },  // 22
    { &g_adwDialogBlockTextIds[41], 1 },  // 23
    { &g_adwDialogBlockTextIds[42], 1 },  // 24
    { &g_adwDialogBlockTextIds[43], 1 },  // 25
    { &g_adwDialogBlockTextIds[44], 1 },  // 26
    { &g_adwDialogBlockTextIds[45], 1 },  // 27
    { &g_adwDialogBlockTextIds[46], 4 },  // 28
    { &g_adwDialogBlockTextIds[50], 3 },  // 29
    { &g_adwDialogBlockTextIds[53], 1 },  // 30
    { &g_adwDialogBlockTextIds[54], 2 },  // 31
    { &g_adwDialogBlockTextIds[56], 1 },  // 32
    { &g_adwDialogBlockTextIds[57], 1 },  // 33
    { &g_adwDialogBlockTextIds[58], 1 },  // 34
    { &g_adwDialogBlockTextIds[59], 1 },  // 35
    { &g_adwDialogBlockTextIds[60], 7 },  // 36
    { &g_adwDialogBlockTextIds[67], 1 },  // 37
    { &g_adwDialogBlockTextIds[68], 1 },  // 38
    { &g_adwDialogBlockTextIds[69], 2 },  // 39
    { &g_adwDialogBlockTextIds[71], 2 },  // 40
    { &g_adwDialogBlockTextIds[73], 3 },  // 41
    { &g_adwDialogBlockTextIds[76], 6 },  // 42
    { &g_adwDialogBlockTextIds[82], 0 },  // 43
    { &g_adwDialogBlockTextIds[82], 1 },  // 44
    { &g_adwDialogBlockTextIds[83], 7 },  // 45
    { &g_adwDialogBlockTextIds[90], 6 },  // 46
    { &g_adwDialogBlockTextIds[96], 1 },  // 47
    { &g_adwDialogBlockTextIds[97], 1 },  // 48
    { &g_adwDialogBlockTextIds[98], 2 },  // 49
    { &g_adwDialogBlockTextIds[100], 1 },  // 50
    { &g_adwDialogBlockTextIds[101], 1 },  // 51
    { &g_adwDialogBlockTextIds[102], 1 },  // 52
    { &g_adwDialogBlockTextIds[103], 1 },  // 53
    { &g_adwDialogBlockTextIds[104], 1 },  // 54
    { &g_adwDialogBlockTextIds[105], 2 },  // 55
    { &g_adwDialogBlockTextIds[107], 3 },  // 56
    { &g_adwDialogBlockTextIds[110], 3 },  // 57
    { &g_adwDialogBlockTextIds[113], 2 },  // 58
    { &g_adwDialogBlockTextIds[115], 2 },  // 59
    { &g_adwDialogBlockTextIds[117], 2 },  // 60
    { &g_adwDialogBlockTextIds[119], 2 },  // 61
    { &g_adwDialogBlockTextIds[121], 2 },  // 62
    { &g_adwDialogBlockTextIds[123], 2 },  // 63
    { &g_adwDialogBlockTextIds[125], 2 },  // 64
    { &g_adwDialogBlockTextIds[127], 2 },  // 65
    { &g_adwDialogBlockTextIds[129], 2 },  // 66
    { &g_adwDialogBlockTextIds[131], 2 },  // 67
    { &g_adwDialogBlockTextIds[133], 2 },  // 68
    { &g_adwDialogBlockTextIds[135], 2 },  // 69
    { &g_adwDialogBlockTextIds[137], 1 },  // 70
    { &g_adwDialogBlockTextIds[138], 1 },  // 71
    { &g_adwDialogBlockTextIds[139], 1 },  // 72
    { &g_adwDialogBlockTextIds[140], 2 },  // 73
    { &g_adwDialogBlockTextIds[142], 2 },  // 74
    { &g_adwDialogBlockTextIds[144], 2 },  // 75
    { &g_adwDialogBlockTextIds[146], 2 },  // 76
    { &g_adwDialogBlockTextIds[148], 1 },  // 77
    { &g_adwDialogBlockTextIds[149], 1 },  // 78
    { &g_adwDialogBlockTextIds[150], 1 },  // 79
    { &g_adwDialogBlockTextIds[151], 1 },  // 80
    { &g_adwDialogBlockTextIds[152], 1 },  // 81
    { &g_adwDialogBlockTextIds[153], 1 },  // 82
    { &g_adwDialogBlockTextIds[154], 1 },  // 83
    { &g_adwDialogBlockTextIds[155], 2 },  // 84
    { &g_adwDialogBlockTextIds[157], 1 },  // 85
    { &g_adwDialogBlockTextIds[158], 1 },  // 86
    { &g_adwDialogBlockTextIds[159], 1 },  // 87
    { &g_adwDialogBlockTextIds[160], 1 },  // 88
    { &g_adwDialogBlockTextIds[161], 1 },  // 89
    { &g_adwDialogBlockTextIds[162], 1 },  // 90
    { &g_adwDialogBlockTextIds[163], 1 },  // 91
    { &g_adwDialogBlockTextIds[164], 1 },  // 92
    { &g_adwDialogBlockTextIds[165], 1 },  // 93
    { &g_adwDialogBlockTextIds[166], 1 },  // 94
    { &g_adwDialogBlockTextIds[167], 1 },  // 95
    { &g_adwDialogBlockTextIds[168], 1 },  // 96
    { &g_adwDialogBlockTextIds[169], 1 },  // 97
    { &g_adwDialogBlockTextIds[170], 1 },  // 98
    { &g_adwDialogBlockTextIds[171], 1 },  // 99
    { &g_adwDialogBlockTextIds[172], 1 },  // 100
    { &g_adwDialogBlockTextIds[173], 1 },  // 101
    { &g_adwDialogBlockTextIds[174], 1 },  // 102
    { &g_adwDialogBlockTextIds[175], 1 },  // 103
    { &g_adwDialogBlockTextIds[176], 1 },  // 104
    { &g_adwDialogBlockTextIds[177], 1 },  // 105
    { &g_adwDialogBlockTextIds[178], 1 },  // 106
    { &g_adwDialogBlockTextIds[179], 1 },  // 107
    { &g_adwDialogBlockTextIds[180], 1 },  // 108
    { &g_adwDialogBlockTextIds[181], 4 },  // 109
    { &g_adwDialogBlockTextIds[185], 1 },  // 110
    { &g_adwDialogBlockTextIds[186], 1 },  // 111
    { &g_adwDialogBlockTextIds[187], 0 },  // 112
    { &g_adwDialogBlockTextIds[187], 0 },  // 113
    { &g_adwDialogBlockTextIds[187], 6 },  // 114
    { &g_adwDialogBlockTextIds[193], 0 },  // 115
    { &g_adwDialogBlockTextIds[193], 0 },  // 116
    { &g_adwDialogBlockTextIds[193], 0 },  // 117
    { &g_adwDialogBlockTextIds[193], 1 },  // 118
    { &g_adwDialogBlockTextIds[194], 1 },  // 119
    { &g_adwDialogBlockTextIds[195], 1 },  // 120
    { &g_adwDialogBlockTextIds[196], 1 },  // 121
    { &g_adwDialogBlockTextIds[197], 1 },  // 122
    { &g_adwDialogBlockTextIds[198], 1 },  // 123
    { &g_adwDialogBlockTextIds[199], 0 },  // 124
    { &g_adwDialogBlockTextIds[977], 0 },  // 125
    { &g_adwDialogBlockTextIds[200], 0 },  // 126
    { &g_adwDialogBlockTextIds[200], 0 },  // 127
    { &g_adwDialogBlockTextIds[200], 1 },  // 128
    { &g_adwDialogBlockTextIds[201], 2 },  // 129
    { &g_adwDialogBlockTextIds[203], 0 },  // 130
    { &g_adwDialogBlockTextIds[203], 1 },  // 131
    { &g_adwDialogBlockTextIds[204], 5 },  // 132
    { &g_adwDialogBlockTextIds[209], 1 },  // 133
    { &g_adwDialogBlockTextIds[210], 1 },  // 134
    { &g_adwDialogBlockTextIds[211], 1 },  // 135
    { &g_adwDialogBlockTextIds[212], 3 },  // 136
    { &g_adwDialogBlockTextIds[215], 1 },  // 137
    { &g_adwDialogBlockTextIds[216], 2 },  // 138
    { &g_adwDialogBlockTextIds[218], 2 },  // 139
    { &g_adwDialogBlockTextIds[220], 3 },  // 140
    { &g_adwDialogBlockTextIds[223], 1 },  // 141
    { &g_adwDialogBlockTextIds[224], 1 },  // 142
    { &g_adwDialogBlockTextIds[225], 5 },  // 143
    { &g_adwDialogBlockTextIds[230], 2 },  // 144
    { &g_adwDialogBlockTextIds[232], 2 },  // 145
    { &g_adwDialogBlockTextIds[234], 2 },  // 146
    { &g_adwDialogBlockTextIds[236], 2 },  // 147
    { &g_adwDialogBlockTextIds[238], 1 },  // 148
    { &g_adwDialogBlockTextIds[239], 1 },  // 149
    { &g_adwDialogBlockTextIds[240], 3 },  // 150
    { &g_adwDialogBlockTextIds[243], 1 },  // 151
    { &g_adwDialogBlockTextIds[244], 1 },  // 152
    { &g_adwDialogBlockTextIds[245], 1 },  // 153
    { &g_adwDialogBlockTextIds[246], 1 },  // 154
    { &g_adwDialogBlockTextIds[247], 1 },  // 155
    { &g_adwDialogBlockTextIds[248], 1 },  // 156
    { &g_adwDialogBlockTextIds[249], 1 },  // 157
    { &g_adwDialogBlockTextIds[250], 1 },  // 158
    { &g_adwDialogBlockTextIds[251], 1 },  // 159
    { &g_adwDialogBlockTextIds[252], 4 },  // 160
    { &g_adwDialogBlockTextIds[256], 1 },  // 161
    { &g_adwDialogBlockTextIds[257], 1 },  // 162
    { &g_adwDialogBlockTextIds[258], 1 },  // 163
    { &g_adwDialogBlockTextIds[259], 1 },  // 164
    { &g_adwDialogBlockTextIds[260], 1 },  // 165
    { &g_adwDialogBlockTextIds[261], 1 },  // 166
    { &g_adwDialogBlockTextIds[262], 1 },  // 167
    { &g_adwDialogBlockTextIds[263], 1 },  // 168
    { &g_adwDialogBlockTextIds[264], 1 },  // 169
    { &g_adwDialogBlockTextIds[265], 1 },  // 170
    { &g_adwDialogBlockTextIds[266], 1 },  // 171
    { &g_adwDialogBlockTextIds[267], 1 },  // 172
    { &g_adwDialogBlockTextIds[268], 1 },  // 173
    { &g_adwDialogBlockTextIds[269], 1 },  // 174
    { &g_adwDialogBlockTextIds[270], 1 },  // 175
    { &g_adwDialogBlockTextIds[271], 1 },  // 176
    { &g_adwDialogBlockTextIds[272], 1 },  // 177
    { &g_adwDialogBlockTextIds[273], 3 },  // 178
    { &g_adwDialogBlockTextIds[276], 3 },  // 179
    { &g_adwDialogBlockTextIds[279], 2 },  // 180
    { &g_adwDialogBlockTextIds[281], 1 },  // 181
    { &g_adwDialogBlockTextIds[282], 1 },  // 182
    { &g_adwDialogBlockTextIds[283], 3 },  // 183
    { &g_adwDialogBlockTextIds[286], 4 },  // 184
    { &g_adwDialogBlockTextIds[290], 1 },  // 185
    { &g_adwDialogBlockTextIds[291], 3 },  // 186
    { &g_adwDialogBlockTextIds[294], 1 },  // 187
    { &g_adwDialogBlockTextIds[295], 1 },  // 188
    { &g_adwDialogBlockTextIds[296], 1 },  // 189
    { &g_adwDialogBlockTextIds[297], 1 },  // 190
    { &g_adwDialogBlockTextIds[298], 1 },  // 191
    { &g_adwDialogBlockTextIds[299], 1 },  // 192
    { &g_adwDialogBlockTextIds[300], 1 },  // 193
    { &g_adwDialogBlockTextIds[301], 1 },  // 194
    { &g_adwDialogBlockTextIds[302], 1 },  // 195
    { &g_adwDialogBlockTextIds[303], 1 },  // 196
    { &g_adwDialogBlockTextIds[304], 2 },  // 197
    { &g_adwDialogBlockTextIds[306], 2 },  // 198
    { &g_adwDialogBlockTextIds[308], 2 },  // 199
    { &g_adwDialogBlockTextIds[310], 1 },  // 200
    { &g_adwDialogBlockTextIds[311], 1 },  // 201
    { &g_adwDialogBlockTextIds[312], 1 },  // 202
    { &g_adwDialogBlockTextIds[313], 1 },  // 203
    { &g_adwDialogBlockTextIds[314], 1 },  // 204
    { &g_adwDialogBlockTextIds[315], 1 },  // 205
    { &g_adwDialogBlockTextIds[316], 1 },  // 206
    { &g_adwDialogBlockTextIds[317], 1 },  // 207
    { &g_adwDialogBlockTextIds[318], 1 },  // 208
    { &g_adwDialogBlockTextIds[319], 1 },  // 209
    { &g_adwDialogBlockTextIds[320], 0 },  // 210
    { &g_adwDialogBlockTextIds[320], 1 },  // 211
    { &g_adwDialogBlockTextIds[321], 1 },  // 212
    { &g_adwDialogBlockTextIds[322], 1 },  // 213
    { &g_adwDialogBlockTextIds[323], 0 },  // 214
    { &g_adwDialogBlockTextIds[323], 0 },  // 215
    { &g_adwDialogBlockTextIds[323], 0 },  // 216
    { &g_adwDialogBlockTextIds[323], 0 },  // 217
    { &g_adwDialogBlockTextIds[323], 0 },  // 218
    { &g_adwDialogBlockTextIds[323], 0 },  // 219
    { &g_adwDialogBlockTextIds[323], 0 },  // 220
    { &g_adwDialogBlockTextIds[323], 0 },  // 221
    { &g_adwDialogBlockTextIds[323], 0 },  // 222
    { &g_adwDialogBlockTextIds[323], 0 },  // 223
    { &g_adwDialogBlockTextIds[323], 0 },  // 224
    { &g_adwDialogBlockTextIds[323], 0 },  // 225
    { &g_adwDialogBlockTextIds[323], 0 },  // 226
    { &g_adwDialogBlockTextIds[323], 0 },  // 227
    { &g_adwDialogBlockTextIds[323], 0 },  // 228
    { &g_adwDialogBlockTextIds[323], 3 },  // 229
    { &g_adwDialogBlockTextIds[326], 1 },  // 230
    { &g_adwDialogBlockTextIds[327], 5 },  // 231
    { &g_adwDialogBlockTextIds[332], 6 },  // 232
    { &g_adwDialogBlockTextIds[338], 1 },  // 233
    { &g_adwDialogBlockTextIds[339], 1 },  // 234
    { &g_adwDialogBlockTextIds[340], 1 },  // 235
    { &g_adwDialogBlockTextIds[341], 1 },  // 236
    { &g_adwDialogBlockTextIds[342], 1 },  // 237
    { &g_adwDialogBlockTextIds[343], 1 },  // 238
    { &g_adwDialogBlockTextIds[344], 1 },  // 239
    { &g_adwDialogBlockTextIds[345], 1 },  // 240
    { &g_adwDialogBlockTextIds[346], 1 },  // 241
    { &g_adwDialogBlockTextIds[347], 1 },  // 242
    { &g_adwDialogBlockTextIds[348], 1 },  // 243
    { &g_adwDialogBlockTextIds[349], 1 },  // 244
    { &g_adwDialogBlockTextIds[350], 1 },  // 245
    { &g_adwDialogBlockTextIds[351], 1 },  // 246
    { &g_adwDialogBlockTextIds[352], 1 },  // 247
    { &g_adwDialogBlockTextIds[353], 1 },  // 248
    { &g_adwDialogBlockTextIds[354], 1 },  // 249
    { &g_adwDialogBlockTextIds[355], 1 },  // 250
    { &g_adwDialogBlockTextIds[356], 1 },  // 251
    { &g_adwDialogBlockTextIds[357], 1 },  // 252
    { &g_adwDialogBlockTextIds[358], 1 },  // 253
    { &g_adwDialogBlockTextIds[359], 1 },  // 254
    { &g_adwDialogBlockTextIds[360], 1 },  // 255
    { &g_adwDialogBlockTextIds[361], 1 },  // 256
    { &g_adwDialogBlockTextIds[362], 1 },  // 257
    { &g_adwDialogBlockTextIds[363], 1 },  // 258
    { &g_adwDialogBlockTextIds[364], 1 },  // 259
    { &g_adwDialogBlockTextIds[365], 1 },  // 260
    { &g_adwDialogBlockTextIds[366], 1 },  // 261
    { &g_adwDialogBlockTextIds[367], 1 },  // 262
    { &g_adwDialogBlockTextIds[368], 1 },  // 263
    { &g_adwDialogBlockTextIds[369], 1 },  // 264
    { &g_adwDialogBlockTextIds[370], 2 },  // 265
    { &g_adwDialogBlockTextIds[372], 1 },  // 266
    { &g_adwDialogBlockTextIds[373], 3 },  // 267
    { &g_adwDialogBlockTextIds[376], 3 },  // 268
    { &g_adwDialogBlockTextIds[379], 1 },  // 269
    { &g_adwDialogBlockTextIds[380], 2 },  // 270
    { &g_adwDialogBlockTextIds[382], 2 },  // 271
    { &g_adwDialogBlockTextIds[384], 2 },  // 272
    { &g_adwDialogBlockTextIds[386], 1 },  // 273
    { &g_adwDialogBlockTextIds[387], 3 },  // 274
    { &g_adwDialogBlockTextIds[390], 1 },  // 275
    { &g_adwDialogBlockTextIds[391], 1 },  // 276
    { &g_adwDialogBlockTextIds[392], 1 },  // 277
    { &g_adwDialogBlockTextIds[393], 1 },  // 278
    { &g_adwDialogBlockTextIds[394], 1 },  // 279
    { &g_adwDialogBlockTextIds[395], 1 },  // 280
    { &g_adwDialogBlockTextIds[396], 1 },  // 281
    { &g_adwDialogBlockTextIds[397], 1 },  // 282
    { &g_adwDialogBlockTextIds[398], 1 },  // 283
    { &g_adwDialogBlockTextIds[399], 1 },  // 284
    { &g_adwDialogBlockTextIds[400], 1 },  // 285
    { &g_adwDialogBlockTextIds[401], 5 },  // 286
    { &g_adwDialogBlockTextIds[406], 1 },  // 287
    { &g_adwDialogBlockTextIds[407], 1 },  // 288
    { &g_adwDialogBlockTextIds[408], 1 },  // 289
    { &g_adwDialogBlockTextIds[409], 1 },  // 290
    { &g_adwDialogBlockTextIds[410], 1 },  // 291
    { &g_adwDialogBlockTextIds[411], 1 },  // 292
    { &g_adwDialogBlockTextIds[412], 1 },  // 293
    { &g_adwDialogBlockTextIds[413], 1 },  // 294
    { &g_adwDialogBlockTextIds[414], 1 },  // 295
    { &g_adwDialogBlockTextIds[415], 1 },  // 296
    { &g_adwDialogBlockTextIds[416], 5 },  // 297
    { &g_adwDialogBlockTextIds[421], 6 },  // 298
    { &g_adwDialogBlockTextIds[427], 1 },  // 299
    { &g_adwDialogBlockTextIds[428], 1 },  // 300
    { &g_adwDialogBlockTextIds[429], 2 },  // 301
    { &g_adwDialogBlockTextIds[431], 1 },  // 302
    { &g_adwDialogBlockTextIds[432], 2 },  // 303
    { &g_adwDialogBlockTextIds[434], 2 },  // 304
    { &g_adwDialogBlockTextIds[436], 1 },  // 305
    { &g_adwDialogBlockTextIds[437], 2 },  // 306
    { &g_adwDialogBlockTextIds[439], 2 },  // 307
    { &g_adwDialogBlockTextIds[441], 1 },  // 308
    { &g_adwDialogBlockTextIds[442], 1 },  // 309
    { &g_adwDialogBlockTextIds[443], 1 },  // 310
    { &g_adwDialogBlockTextIds[444], 1 },  // 311
    { &g_adwDialogBlockTextIds[445], 1 },  // 312
    { &g_adwDialogBlockTextIds[446], 2 },  // 313
    { &g_adwDialogBlockTextIds[448], 2 },  // 314
    { &g_adwDialogBlockTextIds[450], 6 },  // 315
    { &g_adwDialogBlockTextIds[456], 2 },  // 316
    { &g_adwDialogBlockTextIds[458], 1 },  // 317
    { &g_adwDialogBlockTextIds[459], 1 },  // 318
    { &g_adwDialogBlockTextIds[460], 2 },  // 319
    { &g_adwDialogBlockTextIds[462], 2 },  // 320
    { &g_adwDialogBlockTextIds[464], 1 },  // 321
    { &g_adwDialogBlockTextIds[465], 1 },  // 322
    { &g_adwDialogBlockTextIds[466], 1 },  // 323
    { &g_adwDialogBlockTextIds[467], 1 },  // 324
    { &g_adwDialogBlockTextIds[468], 1 },  // 325
    { &g_adwDialogBlockTextIds[469], 1 },  // 326
    { &g_adwDialogBlockTextIds[470], 1 },  // 327
    { &g_adwDialogBlockTextIds[471], 1 },  // 328
    { &g_adwDialogBlockTextIds[472], 1 },  // 329
    { &g_adwDialogBlockTextIds[473], 1 },  // 330
    { &g_adwDialogBlockTextIds[474], 1 },  // 331
    { &g_adwDialogBlockTextIds[475], 1 },  // 332
    { &g_adwDialogBlockTextIds[476], 1 },  // 333
    { &g_adwDialogBlockTextIds[477], 1 },  // 334
    { &g_adwDialogBlockTextIds[478], 3 },  // 335
    { &g_adwDialogBlockTextIds[481], 1 },  // 336
    { &g_adwDialogBlockTextIds[482], 1 },  // 337
    { &g_adwDialogBlockTextIds[483], 1 },  // 338
    { &g_adwDialogBlockTextIds[484], 1 },  // 339
    { &g_adwDialogBlockTextIds[485], 1 },  // 340
    { &g_adwDialogBlockTextIds[486], 1 },  // 341
    { &g_adwDialogBlockTextIds[487], 1 },  // 342
    { &g_adwDialogBlockTextIds[488], 1 },  // 343
    { &g_adwDialogBlockTextIds[489], 1 },  // 344
    { &g_adwDialogBlockTextIds[490], 1 },  // 345
    { &g_adwDialogBlockTextIds[491], 1 },  // 346
    { &g_adwDialogBlockTextIds[492], 4 },  // 347
    { &g_adwDialogBlockTextIds[496], 1 },  // 348
    { &g_adwDialogBlockTextIds[497], 1 },  // 349
    { &g_adwDialogBlockTextIds[498], 3 },  // 350
    { &g_adwDialogBlockTextIds[501], 2 },  // 351
    { &g_adwDialogBlockTextIds[503], 8 },  // 352
    { &g_adwDialogBlockTextIds[511], 1 },  // 353
    { &g_adwDialogBlockTextIds[512], 1 },  // 354
    { &g_adwDialogBlockTextIds[513], 2 },  // 355
    { &g_adwDialogBlockTextIds[515], 2 },  // 356
    { &g_adwDialogBlockTextIds[517], 2 },  // 357
    { &g_adwDialogBlockTextIds[519], 1 },  // 358
    { &g_adwDialogBlockTextIds[520], 4 },  // 359
    { &g_adwDialogBlockTextIds[524], 1 },  // 360
    { &g_adwDialogBlockTextIds[525], 1 },  // 361
    { &g_adwDialogBlockTextIds[526], 1 },  // 362
    { &g_adwDialogBlockTextIds[527], 1 },  // 363
    { &g_adwDialogBlockTextIds[528], 1 },  // 364
    { &g_adwDialogBlockTextIds[529], 1 },  // 365
    { &g_adwDialogBlockTextIds[530], 1 },  // 366
    { &g_adwDialogBlockTextIds[531], 1 },  // 367
    { &g_adwDialogBlockTextIds[532], 1 },  // 368
    { &g_adwDialogBlockTextIds[533], 1 },  // 369
    { &g_adwDialogBlockTextIds[534], 1 },  // 370
    { &g_adwDialogBlockTextIds[535], 1 },  // 371
    { &g_adwDialogBlockTextIds[536], 1 },  // 372
    { &g_adwDialogBlockTextIds[537], 6 },  // 373
    { &g_adwDialogBlockTextIds[543], 1 },  // 374
    { &g_adwDialogBlockTextIds[544], 1 },  // 375
    { &g_adwDialogBlockTextIds[545], 9 },  // 376
    { &g_adwDialogBlockTextIds[554], 2 },  // 377
    { &g_adwDialogBlockTextIds[556], 1 },  // 378
    { &g_adwDialogBlockTextIds[557], 1 },  // 379
    { &g_adwDialogBlockTextIds[558], 2 },  // 380
    { &g_adwDialogBlockTextIds[560], 2 },  // 381
    { &g_adwDialogBlockTextIds[562], 2 },  // 382
    { &g_adwDialogBlockTextIds[564], 2 },  // 383
    { &g_adwDialogBlockTextIds[566], 2 },  // 384
    { &g_adwDialogBlockTextIds[568], 2 },  // 385
    { &g_adwDialogBlockTextIds[570], 2 },  // 386
    { &g_adwDialogBlockTextIds[572], 2 },  // 387
    { &g_adwDialogBlockTextIds[574], 2 },  // 388
    { &g_adwDialogBlockTextIds[576], 2 },  // 389
    { &g_adwDialogBlockTextIds[578], 1 },  // 390
    { &g_adwDialogBlockTextIds[579], 8 },  // 391
    { &g_adwDialogBlockTextIds[587], 1 },  // 392
    { &g_adwDialogBlockTextIds[588], 0 },  // 393
    { &g_adwDialogBlockTextIds[588], 0 },  // 394
    { &g_adwDialogBlockTextIds[588], 0 },  // 395
    { &g_adwDialogBlockTextIds[588], 0 },  // 396
    { &g_adwDialogBlockTextIds[588], 0 },  // 397
    { &g_adwDialogBlockTextIds[588], 0 },  // 398
    { &g_adwDialogBlockTextIds[588], 0 },  // 399
    { &g_adwDialogBlockTextIds[588], 0 },  // 400
    { &g_adwDialogBlockTextIds[588], 1 },  // 401
    { &g_adwDialogBlockTextIds[588], 3 },  // 402
    { &g_adwDialogBlockTextIds[588], 0 },  // 403
    { &g_adwDialogBlockTextIds[588], 0 },  // 404
    { &g_adwDialogBlockTextIds[588], 0 },  // 405
    { &g_adwDialogBlockTextIds[588], 0 },  // 406
    { &g_adwDialogBlockTextIds[588], 3 },  // 407
    { &g_adwDialogBlockTextIds[591], 3 },  // 408
    { &g_adwDialogBlockTextIds[594], 1 },  // 409
    { &g_adwDialogBlockTextIds[595], 1 },  // 410
    { &g_adwDialogBlockTextIds[596], 2 },  // 411
    { &g_adwDialogBlockTextIds[598], 3 },  // 412
    { &g_adwDialogBlockTextIds[601], 1 },  // 413
    { &g_adwDialogBlockTextIds[602], 1 },  // 414
    { &g_adwDialogBlockTextIds[603], 6 },  // 415
    { &g_adwDialogBlockTextIds[609], 1 },  // 416
    { &g_adwDialogBlockTextIds[610], 1 },  // 417
    { &g_adwDialogBlockTextIds[611], 1 },  // 418
    { &g_adwDialogBlockTextIds[612], 2 },  // 419
    { &g_adwDialogBlockTextIds[614], 1 },  // 420
    { &g_adwDialogBlockTextIds[615], 1 },  // 421
    { &g_adwDialogBlockTextIds[616], 1 },  // 422
    { &g_adwDialogBlockTextIds[617], 1 },  // 423
    { &g_adwDialogBlockTextIds[618], 1 },  // 424
    { &g_adwDialogBlockTextIds[619], 1 },  // 425
    { &g_adwDialogBlockTextIds[620], 2 },  // 426
    { &g_adwDialogBlockTextIds[622], 2 },  // 427
    { &g_adwDialogBlockTextIds[624], 1 },  // 428
    { &g_adwDialogBlockTextIds[625], 2 },  // 429
    { &g_adwDialogBlockTextIds[627], 1 },  // 430
    { &g_adwDialogBlockTextIds[628], 2 },  // 431
    { &g_adwDialogBlockTextIds[630], 1 },  // 432
    { &g_adwDialogBlockTextIds[631], 5 },  // 433
    { &g_adwDialogBlockTextIds[636], 2 },  // 434
    { &g_adwDialogBlockTextIds[638], 3 },  // 435
    { &g_adwDialogBlockTextIds[641], 1 },  // 436
    { &g_adwDialogBlockTextIds[642], 2 },  // 437
    { &g_adwDialogBlockTextIds[644], 6 },  // 438
    { &g_adwDialogBlockTextIds[650], 2 },  // 439
    { &g_adwDialogBlockTextIds[652], 2 },  // 440
    { &g_adwDialogBlockTextIds[654], 2 },  // 441
    { &g_adwDialogBlockTextIds[656], 5 },  // 442
    { &g_adwDialogBlockTextIds[661], 1 },  // 443
    { &g_adwDialogBlockTextIds[662], 4 },  // 444
    { &g_adwDialogBlockTextIds[666], 3 },  // 445
    { &g_adwDialogBlockTextIds[669], 1 },  // 446
    { &g_adwDialogBlockTextIds[670], 1 },  // 447
    { &g_adwDialogBlockTextIds[671], 1 },  // 448
    { &g_adwDialogBlockTextIds[672], 1 },  // 449
    { &g_adwDialogBlockTextIds[673], 1 },  // 450
    { &g_adwDialogBlockTextIds[674], 1 },  // 451
    { &g_adwDialogBlockTextIds[675], 1 },  // 452
    { &g_adwDialogBlockTextIds[676], 1 },  // 453
    { &g_adwDialogBlockTextIds[677], 1 },  // 454
    { &g_adwDialogBlockTextIds[678], 1 },  // 455
    { &g_adwDialogBlockTextIds[679], 1 },  // 456
    { &g_adwDialogBlockTextIds[680], 1 },  // 457
    { &g_adwDialogBlockTextIds[681], 1 },  // 458
    { &g_adwDialogBlockTextIds[682], 3 },  // 459
    { &g_adwDialogBlockTextIds[685], 1 },  // 460
    { &g_adwDialogBlockTextIds[686], 6 },  // 461
    { &g_adwDialogBlockTextIds[692], 2 },  // 462
    { &g_adwDialogBlockTextIds[694], 2 },  // 463
    { &g_adwDialogBlockTextIds[696], 1 },  // 464
    { &g_adwDialogBlockTextIds[697], 4 },  // 465
    { &g_adwDialogBlockTextIds[701], 1 },  // 466
    { &g_adwDialogBlockTextIds[702], 1 },  // 467
    { &g_adwDialogBlockTextIds[703], 1 },  // 468
    { &g_adwDialogBlockTextIds[704], 1 },  // 469
    { &g_adwDialogBlockTextIds[705], 1 },  // 470
    { &g_adwDialogBlockTextIds[706], 1 },  // 471
    { &g_adwDialogBlockTextIds[707], 1 },  // 472
    { &g_adwDialogBlockTextIds[708], 1 },  // 473
    { &g_adwDialogBlockTextIds[709], 1 },  // 474
    { &g_adwDialogBlockTextIds[710], 1 },  // 475
    { &g_adwDialogBlockTextIds[711], 1 },  // 476
    { &g_adwDialogBlockTextIds[712], 1 },  // 477
    { &g_adwDialogBlockTextIds[713], 1 },  // 478
    { &g_adwDialogBlockTextIds[714], 1 },  // 479
    { &g_adwDialogBlockTextIds[715], 1 },  // 480
    { &g_adwDialogBlockTextIds[716], 1 },  // 481
    { &g_adwDialogBlockTextIds[717], 1 },  // 482
    { &g_adwDialogBlockTextIds[718], 3 },  // 483
    { &g_adwDialogBlockTextIds[721], 10 },  // 484
    { &g_adwDialogBlockTextIds[731], 1 },  // 485
    { &g_adwDialogBlockTextIds[732], 1 },  // 486
    { &g_adwDialogBlockTextIds[733], 1 },  // 487
    { &g_adwDialogBlockTextIds[734], 1 },  // 488
    { &g_adwDialogBlockTextIds[735], 1 },  // 489
    { &g_adwDialogBlockTextIds[736], 1 },  // 490
    { &g_adwDialogBlockTextIds[737], 1 },  // 491
    { &g_adwDialogBlockTextIds[738], 1 },  // 492
    { &g_adwDialogBlockTextIds[739], 1 },  // 493
    { &g_adwDialogBlockTextIds[740], 5 },  // 494
    { &g_adwDialogBlockTextIds[745], 3 },  // 495
    { &g_adwDialogBlockTextIds[748], 2 },  // 496
    { &g_adwDialogBlockTextIds[750], 3 },  // 497
    { &g_adwDialogBlockTextIds[753], 0 },  // 498
    { &g_adwDialogBlockTextIds[753], 1 },  // 499
    { &g_adwDialogBlockTextIds[754], 1 },  // 500
    { &g_adwDialogBlockTextIds[755], 4 },  // 501
    { &g_adwDialogBlockTextIds[759], 1 },  // 502
    { &g_adwDialogBlockTextIds[760], 1 },  // 503
    { &g_adwDialogBlockTextIds[761], 1 },  // 504
    { &g_adwDialogBlockTextIds[762], 1 },  // 505
    { &g_adwDialogBlockTextIds[763], 5 },  // 506
    { &g_adwDialogBlockTextIds[768], 1 },  // 507
    { &g_adwDialogBlockTextIds[769], 3 },  // 508
    { &g_adwDialogBlockTextIds[772], 4 },  // 509
    { &g_adwDialogBlockTextIds[776], 2 },  // 510
    { &g_adwDialogBlockTextIds[778], 1 },  // 511
    { &g_adwDialogBlockTextIds[779], 1 },  // 512
    { &g_adwDialogBlockTextIds[780], 1 },  // 513
    { &g_adwDialogBlockTextIds[781], 1 },  // 514
    { &g_adwDialogBlockTextIds[782], 1 },  // 515
    { &g_adwDialogBlockTextIds[783], 1 },  // 516
    { &g_adwDialogBlockTextIds[784], 1 },  // 517
    { &g_adwDialogBlockTextIds[785], 1 },  // 518
    { &g_adwDialogBlockTextIds[786], 0 },  // 519
    { &g_adwDialogBlockTextIds[786], 0 },  // 520
    { &g_adwDialogBlockTextIds[786], 0 },  // 521
    { &g_adwDialogBlockTextIds[786], 0 },  // 522
    { &g_adwDialogBlockTextIds[786], 0 },  // 523
    { &g_adwDialogBlockTextIds[786], 0 },  // 524
    { &g_adwDialogBlockTextIds[786], 0 },  // 525
    { &g_adwDialogBlockTextIds[786], 1 },  // 526
    { &g_adwDialogBlockTextIds[787], 1 },  // 527
    { &g_adwDialogBlockTextIds[788], 1 },  // 528
    { &g_adwDialogBlockTextIds[789], 1 },  // 529
    { &g_adwDialogBlockTextIds[790], 1 },  // 530
    { &g_adwDialogBlockTextIds[791], 1 },  // 531
    { &g_adwDialogBlockTextIds[792], 3 },  // 532
    { &g_adwDialogBlockTextIds[795], 1 },  // 533
    { &g_adwDialogBlockTextIds[796], 1 },  // 534
    { &g_adwDialogBlockTextIds[797], 1 },  // 535
    { &g_adwDialogBlockTextIds[798], 1 },  // 536
    { &g_adwDialogBlockTextIds[799], 1 },  // 537
    { &g_adwDialogBlockTextIds[800], 1 },  // 538
    { &g_adwDialogBlockTextIds[801], 1 },  // 539
    { &g_adwDialogBlockTextIds[802], 1 },  // 540
    { &g_adwDialogBlockTextIds[803], 1 },  // 541
    { &g_adwDialogBlockTextIds[804], 1 },  // 542
    { &g_adwDialogBlockTextIds[805], 1 },  // 543
    { &g_adwDialogBlockTextIds[806], 0 },  // 544
    { &g_adwDialogBlockTextIds[806], 2 },  // 545
    { &g_adwDialogBlockTextIds[808], 3 },  // 546
    { &g_adwDialogBlockTextIds[811], 2 },  // 547
    { &g_adwDialogBlockTextIds[813], 2 },  // 548
    { &g_adwDialogBlockTextIds[815], 3 },  // 549
    { &g_adwDialogBlockTextIds[818], 1 },  // 550
    { &g_adwDialogBlockTextIds[819], 4 },  // 551
    { &g_adwDialogBlockTextIds[823], 1 },  // 552
    { &g_adwDialogBlockTextIds[824], 1 },  // 553
    { &g_adwDialogBlockTextIds[825], 1 },  // 554
    { &g_adwDialogBlockTextIds[827], 1 },  // 555
    { &g_adwDialogBlockTextIds[826], 1 },  // 556
    { &g_adwDialogBlockTextIds[828], 2 },  // 557
    { &g_adwDialogBlockTextIds[830], 2 },  // 558
    { &g_adwDialogBlockTextIds[832], 1 },  // 559
    { &g_adwDialogBlockTextIds[833], 1 },  // 560
    { &g_adwDialogBlockTextIds[834], 3 },  // 561
    { &g_adwDialogBlockTextIds[837], 3 },  // 562
    { &g_adwDialogBlockTextIds[840], 0 },  // 563
    { &g_adwDialogBlockTextIds[840], 3 },  // 564
    { &g_adwDialogBlockTextIds[843], 1 },  // 565
    { &g_adwDialogBlockTextIds[844], 1 },  // 566
    { &g_adwDialogBlockTextIds[845], 1 },  // 567
    { &g_adwDialogBlockTextIds[846], 1 },  // 568
    { &g_adwDialogBlockTextIds[847], 1 },  // 569
    { &g_adwDialogBlockTextIds[848], 1 },  // 570
    { &g_adwDialogBlockTextIds[849], 1 },  // 571
    { &g_adwDialogBlockTextIds[850], 2 },  // 572
    { &g_adwDialogBlockTextIds[852], 2 },  // 573
    { &g_adwDialogBlockTextIds[854], 2 },  // 574
    { &g_adwDialogBlockTextIds[856], 4 },  // 575
    { &g_adwDialogBlockTextIds[860], 2 },  // 576
    { &g_adwDialogBlockTextIds[862], 3 },  // 577
    { &g_adwDialogBlockTextIds[865], 2 },  // 578
    { &g_adwDialogBlockTextIds[867], 3 },  // 579
    { &g_adwDialogBlockTextIds[870], 1 },  // 580
    { &g_adwDialogBlockTextIds[871], 1 },  // 581
    { &g_adwDialogBlockTextIds[872], 2 },  // 582
    { &g_adwDialogBlockTextIds[874], 2 },  // 583
    { &g_adwDialogBlockTextIds[876], 2 },  // 584
    { &g_adwDialogBlockTextIds[878], 1 },  // 585
    { &g_adwDialogBlockTextIds[879], 1 },  // 586
    { &g_adwDialogBlockTextIds[880], 2 },  // 587
    { &g_adwDialogBlockTextIds[882], 2 },  // 588
    { &g_adwDialogBlockTextIds[884], 4 },  // 589
    { &g_adwDialogBlockTextIds[888], 1 },  // 590
    { &g_adwDialogBlockTextIds[889], 1 },  // 591
    { &g_adwDialogBlockTextIds[890], 1 },  // 592
    { &g_adwDialogBlockTextIds[891], 1 },  // 593
    { &g_adwDialogBlockTextIds[892], 2 },  // 594
    { &g_adwDialogBlockTextIds[894], 1 },  // 595
    { &g_adwDialogBlockTextIds[895], 1 },  // 596
    { &g_adwDialogBlockTextIds[896], 1 },  // 597
    { &g_adwDialogBlockTextIds[897], 1 },  // 598
    { &g_adwDialogBlockTextIds[898], 1 },  // 599
    { &g_adwDialogBlockTextIds[899], 1 },  // 600
    { &g_adwDialogBlockTextIds[900], 2 },  // 601
    { &g_adwDialogBlockTextIds[902], 3 },  // 602
    { &g_adwDialogBlockTextIds[905], 1 },  // 603
    { &g_adwDialogBlockTextIds[906], 4 },  // 604
    { &g_adwDialogBlockTextIds[910], 1 },  // 605
    { &g_adwDialogBlockTextIds[911], 2 },  // 606
    { &g_adwDialogBlockTextIds[913], 2 },  // 607
    { &g_adwDialogBlockTextIds[915], 1 },  // 608
    { &g_adwDialogBlockTextIds[915], 1 },  // 609
    { &g_adwDialogBlockTextIds[917], 3 },  // 610
    { &g_adwDialogBlockTextIds[920], 5 },  // 611
    { &g_adwDialogBlockTextIds[925], 1 },  // 612
    { &g_adwDialogBlockTextIds[926], 1 },  // 613
    { &g_adwDialogBlockTextIds[927], 1 },  // 614
    { &g_adwDialogBlockTextIds[928], 1 },  // 615
    { &g_adwDialogBlockTextIds[929], 1 },  // 616
    { &g_adwDialogBlockTextIds[930], 1 },  // 617
    { &g_adwDialogBlockTextIds[931], 1 },  // 618
    { &g_adwDialogBlockTextIds[932], 1 },  // 619
    { &g_adwDialogBlockTextIds[933], 1 },  // 620
    { &g_adwDialogBlockTextIds[934], 1 },  // 621
    { &g_adwDialogBlockTextIds[935], 0 },  // 622
    { &g_adwDialogBlockTextIds[935], 1 },  // 623
    { &g_adwDialogBlockTextIds[936], 1 },  // 624
    { &g_adwDialogBlockTextIds[937], 1 },  // 625
    { &g_adwDialogBlockTextIds[938], 1 },  // 626
    { &g_adwDialogBlockTextIds[939], 1 },  // 627
    { &g_adwDialogBlockTextIds[940], 1 },  // 628
    { &g_adwDialogBlockTextIds[941], 1 },  // 629
    { &g_adwDialogBlockTextIds[942], 1 },  // 630
    { &g_adwDialogBlockTextIds[943], 1 },  // 631
    { &g_adwDialogBlockTextIds[944], 1 },  // 632
    { &g_adwDialogBlockTextIds[945], 1 },  // 633
    { &g_adwDialogBlockTextIds[946], 1 },  // 634
    { &g_adwDialogBlockTextIds[947], 1 },  // 635
    { &g_adwDialogBlockTextIds[948], 1 },  // 636
    { &g_adwDialogBlockTextIds[949], 1 },  // 637
    { &g_adwDialogBlockTextIds[950], 1 },  // 638
    { &g_adwDialogBlockTextIds[951], 1 },  // 639
    { &g_adwDialogBlockTextIds[952], 1 },  // 640
    { &g_adwDialogBlockTextIds[953], 1 },  // 641
    { &g_adwDialogBlockTextIds[954], 1 },  // 642
    { &g_adwDialogBlockTextIds[955], 1 },  // 643
    { &g_adwDialogBlockTextIds[956], 1 },  // 644
    { &g_adwDialogBlockTextIds[957], 1 },  // 645
    { &g_adwDialogBlockTextIds[958], 1 },  // 646
    { &g_adwDialogBlockTextIds[959], 1 },  // 647
    { &g_adwDialogBlockTextIds[960], 1 },  // 648
    { &g_adwDialogBlockTextIds[961], 1 },  // 649
    { &g_adwDialogBlockTextIds[962], 1 },  // 650
    { &g_adwDialogBlockTextIds[963], 1 },  // 651
    { &g_adwDialogBlockTextIds[964], 1 },  // 652
    { &g_adwDialogBlockTextIds[965], 1 },  // 653
    { &g_adwDialogBlockTextIds[966], 1 },  // 654
    { &g_adwDialogBlockTextIds[967], 1 },  // 655
    { &g_adwDialogBlockTextIds[968], 1 },  // 656
    { &g_adwDialogBlockTextIds[969], 1 },  // 657
    { &g_adwDialogBlockTextIds[970], 1 },  // 658
    { &g_adwDialogBlockTextIds[971], 1 },  // 659
    { &g_adwDialogBlockTextIds[972], 1 },  // 660
    { &g_adwDialogBlockTextIds[973], 1 },  // 661
    { &g_adwDialogBlockTextIds[974], 1 },  // 662
    { &g_adwDialogBlockTextIds[975], 1 },  // 663
    { &g_adwDialogBlockTextIds[976], 1 },  // 664
    { &g_adwDialogBlockTextIds[978], 1 },  // 665
};
