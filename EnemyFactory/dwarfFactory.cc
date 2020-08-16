#include "dwarfFactory.h"
#include "../Enemy/enemy.h"

#include "../Enemy/dwarf.h"

std::shared_ptr<Enemy> DwarfFactory::spawn() {
    return std::make_shared<Dwarf>();
}