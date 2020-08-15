#include "baFactory.h"
#include "../Potion/potion.h"
#include "../Potion/ba.h"

std::shared_ptr<Potion> BAFactory::spawn() {
    return std::make_shared<BA>();
}

BAFactory::~BAFactory() {

}