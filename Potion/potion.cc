#include "potion.h"


// constructor
Potion::Potion(std::string type) : 
    type {type}
{}


// accessor
std::string Potion::getType() const {
    return type;
}
