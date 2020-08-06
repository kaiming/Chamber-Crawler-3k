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
        std::vector<std::vector<std::shared_ptr<Tile>>> floor;
        std::vector<std::vector<std::shared_ptr<WalkableTile>>> chambers;
        std::shared_ptr<WalkableTile> player;
        std::vector<std::shared_ptr<WalkableTile>> enemies;
        std::vector<std::shared_ptr<WalkableTile>> dragons;

        std::vector<std::string> potionsUsed;
        int floorNum;
        bool merchantAgro;

        std::shared_ptr<WalkableTile> validDest(std::shared_ptr<WalkableTile> package, std::string direction); 
        void generateItem(); // need to fill in inputs

    public:
        Board(std::vector<std::vector<std::shared_ptr<Tile>>> floor, bool filled);
        
        int getFloorNum();
        void setFloorNum(int num); // maybe not needed
        void setFloor (std::vector<std::vector<std::shared_ptr<Tile>>> floor) : floor{floor}

        void movePlayer(std::string direction);
        void attackEnemey(std::string direction);
        void moveEnemies();
        void usePotion(std::string direction);
        void generateFloor();

}

#endif
