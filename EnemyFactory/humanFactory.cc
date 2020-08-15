#include "humanFactory.h"
#include "../Enemy/enemy.h"
#include "../Enemy/human.h"

std::shared_ptr<Enemy> HumanFactory::spawn() {
    return std::make_shared<Human>();
}