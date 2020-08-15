#include "wdFactory.h"
#include "../Potion/potion.h"
#include "../Potion/wd.h"

std::shared_ptr<Potion> WDFactory::spawnEnemy() {
    return std::make_shared<WD>();
}