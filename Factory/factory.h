#ifndef __FACTORY_H__
#define __FACTORY_H__
#include <memory>
#include <vector>

class Tile;
class Character;
class Potion;
class Gold;

class Factory {
  public:
    // makeTile creates a specific type of tile for the floor
    virtual std::shared_ptr<Tile> makeTile(char type, int x, int y, std::shared_ptr<Character> occupant = nullptr, std::shared_ptr<Potion> potion = nullptr, std::vector<std::shared_ptr<Gold>> goldStash = {}, bool exit = false) = 0;
}; 

#endif