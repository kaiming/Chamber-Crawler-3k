#include "dragonhoard.h"

/*
   std::shared_ptr<Dragon> dragon;
*/

DragonGold::DragonGold() : Gold{"Dragon Hoard", "6"}, dragon{std::make_shared<Dragon>} {

}

std::shared_ptr DragonGold::getDragon() {
    return dragon;
}
