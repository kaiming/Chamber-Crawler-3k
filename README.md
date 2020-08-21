# ChamberCrawler3000

Welcome to ChamberCrawler3000, an exciting rendition of the classic Rougue single-player game.


Created by: Kaiming Qiu, Allen Lu


Definitions -------------------------------------------------------------------------------


Definition 1: A character is a person/animal/thing in the game of CC3k. This can be either the player character (PC), who is controlled by the player of the game, or non-playable characters, who are strictly enemies in CC3k.


Definition 2: An item is something the player character can pick up or use. In CC3k, this is either gold or potions. Potions offer potentially positive and negative effects to the player character.


Definition 3: A chamber is an individual room in the game of CC3k. Chambers are connected by pas- sages.


Definition 4: A floor in CC3k is a predefined configuration of 5 chambers with connecting passageways. Figure 1 depicts an empty floor. Note that the configuration is the same for every floor in a game of CC3k.


Definition 5: Health Points (HP) is the representation of a character’s health (both enemies and the player character). When a character’s HP reaches 0, they are slain. For an enemy this means that they are removed from the floor and a tidy sum of gold is given to the player character. When the player character has 0 HP then the current game ends.


Definition 6: Attack (Atk) is the representation of a character’s strength. This is how hard a character can hit another character. In CC3k conflict is solely between the player character and non-playable characters.


Definition 7 : Defense (Def ) is the representation of a character’s toughness. This is how hard a character can be hit by another character.


Definition 8: A cell is either a wall, floor tile, doorway, or passage.


Definition 9: Something being spawned means that the particular something (an enemy, gold, etc) should
be generated and placed on the board.


Definition 10: A 1 block radius denotes the 8 cells adjacent to the character or item. If the character is near an edge or a corner, there are fewer adjacent cells.


-----------------------------------------------------------------------------------------


Player Characters -----------------------------------------------------------------------


Shade: HP - 125 | ATK - 25 | DEF - 25 | Special - None

Drow: HP - 150 | ATK - 25 | DEF- 15 | Special - All potions have their effects magnified by 1.5

Vampire: HP - 50 | ATK - 25 | DEF - 25 | Special - Gains 5 HP every successful attack, has not HP cap

Troll: HP - 120 | ATK - 25 | DEF - 15 | Special - Regains 5 HP every turn, capped at 120

Goblin: HP - 110 | ATK  15 | DEF - 20 | Special - Steals 5 gold from every slain enemy


-----------------------------------------------------------------------------------------


Enemy Characters ------------------------------------------------------------------------




