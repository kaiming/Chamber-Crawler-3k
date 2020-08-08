#include "nonwalkablefactory.h"
#include "../Tile/tile.h"


// makeTile creates a tile that players and enemies are not able to walk on
std::shared_ptr<Tile> NonWalkableFactory::makeTile(char type, int x, int y, std::shared_ptr<Character> occupant, std::shared_ptr<Potion> potion, std::vector<std::shared_ptr<Gold>> goldStash, bool exit) {
    return std::make_shared<Tile>(type, x, y);
}
