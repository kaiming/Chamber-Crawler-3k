#include "walkablefactory.h"
#include "tile.h"
#include "walkabletile.h"


// WalkableFactory::makeTile(...) makes a WalkableTile with either default fields or specified ones
std::shared_ptr<Tile> WalkableFactory::makeTile(char type, int x, int y, std::shared_ptr<Character> occupant, std::shared_ptr<Potion> potion, std::vector<std::shared_ptr<Gold>> goldStash, bool exit) {
    return std::make_shared<WalkableTile>(type, x, y, occupant, potion, goldStash, exit);
}
