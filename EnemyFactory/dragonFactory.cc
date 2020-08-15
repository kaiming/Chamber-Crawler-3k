#include "dragonFactory.h"
#include "../Enemy/enemy.h"
#include "../Enemy/dragon.h"

std::shared_ptr<Enemy> DragonFactory::spawn() {
    return std::make_shared<Dragon>();
}