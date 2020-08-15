#include "waFactory.h"
#include "../Potion/potion.h"
#include "../Potion/wa.h"

std::shared_ptr<Potion> WAFactory::spawn() {
    return std::make_shared<WA>();
}