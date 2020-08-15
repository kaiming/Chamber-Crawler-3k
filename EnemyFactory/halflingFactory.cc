#include "halflingFactory.h"
#include "../Enemy/enemy.h"
#include "../Enemy/halfling.h"

std::shared_ptr<Enemy> HalflingFactory::spawn() {
    return std::make_shared<Halfling>();
}