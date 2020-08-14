#include "walkablefactory.h"
#include "../Tile/tile.h"
#include "../Tile/walkabletile.h"


// WalkableFactory::makeTile(...) makes a WalkableTile with either default fields or specified ones
std::shared_ptr<Tile> WalkableFactory::makeTile(char type, int x, int y, std::shared_ptr<Character> occupant, std::shared_ptr<Potion> potion, std::shared_ptr<Gold> gold, bool exit) {
    return std::make_shared<WalkableTile>(type, x, y, occupant, potion, gold, exit);
}
