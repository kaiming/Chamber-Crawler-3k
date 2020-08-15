#include "dHoardFactory.h"
#include "../Gold/dragonhoard.h"

std::shared_ptr<Gold> DHoardFactory::spawn() {
    return std::make_shared<DragonHoard>();
}