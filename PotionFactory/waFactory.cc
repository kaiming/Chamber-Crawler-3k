#include "waFactory.h"
#include "../Potion/potion.h"
#include "../Potion/wa.h"

std::shared_ptr<Potion> WAFactory::spawnEnemy() {
    return std::make_shared<WA>;
}