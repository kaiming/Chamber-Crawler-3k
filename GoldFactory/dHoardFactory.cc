#include "dHoardFactory.h"
#include "../Gold/dragonhoard.h"

DHoardFactory::DHoardFactory() : GFactory("Dragon Hoard", 6) {
    
}

std::shared_ptr<Gold> DHoardFactory::spawn() {
    return std::make_shared<DragonHoard>();
}