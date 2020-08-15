#include "rhFactory.h"
#include "../Potion/potion.h"
#include "../Potion/rh.h"

std::shared_ptr<Potion> RHFactory::spawn() {
    return std::make_shared<RH>();
}