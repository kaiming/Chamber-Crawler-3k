#include "bdFactory.h"
#include "../Potion/potion.h"
#include "../Potion/bd.h"

std::shared_ptr<Potion> BDFactory::spawn() {
    return std::make_shared<BD>();
}