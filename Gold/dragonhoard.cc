#include "dragonhoard.h"

/*
   std::shared_ptr<Dragon> dragon;
*/

DragonHoard::DragonHoard() : Gold{"Dragon Hoard", 6}, dragon{std::make_shared<Dragon>} {

}

std::shared_ptr DragonHoard::getDragon() {
    return dragon;
}
