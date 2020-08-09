#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <memory>
#include <string>

class Tile;
class WalkableTile;

class Enemy;
class Human;
class Dwarf;
class Elf;
class Orc;
class Merchant;
class Dragon;
class Halfling;
class Potion;

class Player;
class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;

class Potion;
class Gold;
class DragonHoard;

class Board {
    private:
        std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors;
        std::vector<bool> filled;
        std::vector<std::shared_ptr<WalkableTile>> playerSpawns;
        std::vector<std::shared_ptr<WalkableTile>> enemies;
        std::vector<std::shared_ptr<WalkableTile>> dragonHoards;
        std::string race;

        std::shared_ptr<WalkableTile> player;
        std::vector<std::string> potionsUsed;
        std::vector<std::vector<std::shared_ptr<WalkableTile>>> chambers;
        std::shared_ptr<Player> playerPtr;
        int floorNum;
        bool merchantAgro = false;
        bool enemiesFrozen = false;

        std::shared_ptr<WalkableTile> validDest(std::shared_ptr<WalkableTile> package, std::string direction); 
        void assignChambers();
        void tileDFS(std::pair<int, int> coords, int floorNum, std::vector<std::shared_ptr<WalkableTile>>& chamber);
        void changeFloor();

    public:
        Board(
            std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors = {{{}}}, // NOTE: IDK IF THIS IS HOW TO GIVE A 3D VECTOR A DEFAULT VALUE
            std::vector<bool> filled = {},
            std::vector<std::shared_ptr<WalkableTile>> playerSpawns = {},
            std::vector<std::shared_ptr<WalkableTile>> enemies = {},
            std::vector<std::shared_ptr<WalkableTile>> dragonHoards = {},
            std::string race = ""
        );
        
        std::string getRace() const;
        int getFloorNum() const;
        bool toggleFreeze();

        std::string movePlayer(std::string direction);
        std::string attackEnemy(std::string direction);
        std::string moveEnemies();
        std::string usePotion(std::string direction);
        void generateFloor();

        friend class TextDisplay;
};

#endif
