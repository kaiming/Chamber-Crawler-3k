#include "dragonhoard.h"

/*
   std::shared_ptr<Dragon> dragon;
*/

DragonHoard::DragonHoard() : Gold{"Dragon Hoard", 6}, dragon{std::make_shared<Dragon>} {

}

std::shared_ptr<Dragon> DragonHoard::getDragon() {
    return dragon;
}

std::shared_ptr<WalkableTile> DragonHoard::getDragonTile() {
    return dragonTile;
}

void setDragonTile(std::shared_ptr<WalkableTile> tile) {
    dragonTile = tile;
}

