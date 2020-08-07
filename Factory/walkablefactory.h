#ifndef __WALKABLEFACTORY_H__
#define __WALKABLEFACTORY_H__
#include "factory.h"

class WalkableFactory : public Factory {
  public:
    // makeTile creates a new walkable tile, whether it is populated or not depends on if there is a given generation or the default is used
    // if default is used then makeTile will create an empty tile and the pointers/vectors being passed will be nullptr/empty and exit is false by default
    std::shared_ptr<Tile> makeTile(char type, int x, int y, std::shared_ptr<Character> occupant = nullptr, std::shared_ptr<Potion> potion = nullptr, std::vector<std::shared_ptr<Gold>> goldStash = {}, bool exit = false) override;
};

#endif