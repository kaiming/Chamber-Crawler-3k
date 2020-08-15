#include "wdFactory.h"
#include "../Potion/potion.h"
#include "../Potion/wd.h"

std::shared_ptr<Potion> WDFactory::spawn() {
    return std::make_shared<WD>();
}