#include "gold.h"

/*
    std::string type;
    int size;
*/

Gold::Gold(std::string type, int size) : type{type}, size{size} {

}

int getSize() {
    return size;
}

std::string getType() {
    return type;
}