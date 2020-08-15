#include "dHoardFactory.h"
#include "../Gold/dragonhoard.h"

std::shared_ptr<Gold> DHoardFactory::spawnGold() {
    return std::make_shared<DragonHoard>();
}