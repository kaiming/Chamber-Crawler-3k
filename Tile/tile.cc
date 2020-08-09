#include "tile.h"


// constructor
// NOTE: CAN CHANGE THIS TO TAKE A PAIR IF WE WANT
Tile::Tile(char Type, int x, int y) : 
    type {type},
    coord {std::pair<int, int> {x, y}}
{}

Tile::~Tile() {
    
}

// accessors
char Tile::getType() const {
    return type;
}


std::pair<int, int> Tile::getCoord() const {
    return coord;
}
