#include "dragonhoard.h"

DragonGold::DragonGold() : dragon{std::make_shared<Dragon>} {

}

std::shared_ptr DragonGold::getDragon() {
    return dragon;
}
