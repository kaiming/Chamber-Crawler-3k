#include "orcFactory.h"
#include "../Enemy/enemy.h"
#include "../Enemy/orc.h"

std::shared_ptr<Enemy> OrcFactory::spawn() {
    return std::make_shared<Orc>();
}