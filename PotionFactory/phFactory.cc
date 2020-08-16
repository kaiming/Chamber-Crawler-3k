#include "phFactory.h"
#include "../Potion/potion.h"
#include "../Potion/ph.h"

std::shared_ptr<Potion> PHFactory::spawn() {
    return std::make_shared<PH>();
}