#include "elfFactory.h"
#include "../Enemy/enemy.h"
#include "../Enemy/elf.h"

std::shared_ptr<Enemy> ElfFactory::spawnEnemy() {
    return std::make_shared<Elf>();
}