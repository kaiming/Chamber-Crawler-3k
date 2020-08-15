#include "orcFactory.h"
#include "../Enemy/orc.h"

std::shared_ptr<Enemy> OrcFactory::spawnEnemy() {
    return std::make_shared<Orc>;
}