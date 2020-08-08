#include "dragonhoard.h"
#include "../Tile/walkabletile.h"
#include "../Enemy/dragon.h"

/*
   std::shared_ptr<Dragon> dragon;
*/

DragonHoard::DragonHoard() : Gold{"Dragon Hoard", 6}, dragon{std::make_shared<Dragon>()} {

}

std::shared_ptr<Dragon> DragonHoard::getDragon() const {
    return dragon;
}

std::shared_ptr<WalkableTile> DragonHoard::getDragonTile() const {
    return dragonTile;
}

void DragonHoard::setDragonTile(std::shared_ptr<WalkableTile> tile) {
    dragonTile = tile;
}

