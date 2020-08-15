#include "baFactory.h"
#include "../Potion/potion.h"
#include "../Potion/ba.h"

std::shared_ptr<Potion> BAFactory::spawnEnemy() {
    return std::make_shared<BA>();
}