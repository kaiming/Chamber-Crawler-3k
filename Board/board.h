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
        std::vector<std::vector<std::shared_ptr<WalkableTile>>> chambers;
        std::shared_ptr<WalkableTile> player;
        std::vector<std::shared_ptr<WalkableTile>> enemies;
        std::vector<std::shared_ptr<WalkableTile>> dragonHoards;
        std::vector<std::string> potionsUsed;

        std::shared_ptr<Player> playerPtr;
        int floorNum;
        bool merchantAgro;

        std::shared_ptr<WalkableTile> validDest(std::shared_ptr<WalkableTile> package, std::string direction); 
        void assignChambers();
        void tileDFS(std::pair<int, int> coords, int floorNum, std::vector<std::shared_ptr<WalkableTile>>& chamber);

    public:
        Board(std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors, 
            bool filled, 
            std::shared_ptr<WalkableTile> player,
            std::vector<std::shared_ptr<WalkableTile>> enemies,
            std::vector<std::shared_ptr<WalkableTile>> dragonHoards
            std::string race
        );
        
        int getFloorNum() const;

        int movePlayer(std::string direction);
        void attackEnemey(std::string direction);
        bool moveEnemies();
        void usePotion(std::string direction);
        void generateFloor();

};

#endif
