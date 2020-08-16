#include "elfFactory.h"
#include "../Enemy/enemy.h"
#include "../Enemy/elf.h"

std::shared_ptr<Enemy> ElfFactory::spawn() {
    return std::make_shared<Elf>();
}