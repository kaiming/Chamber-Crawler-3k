#include "gold.h"

/*
    std::string type;
    int size;
*/

Gold::Gold(std::string type, int size) : type{type}, size{size} {

}

Gold::~Gold () {

}

int Gold::getSize() const {
    return size;
}

std::string Gold::getType() const {
    return type;
}
