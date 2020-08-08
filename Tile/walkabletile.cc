#include <utility>
#include "walkabletile.h"
#include "../Character/character.h"
#include "../Potion/potion.h"
#include "../Gold/gold.h"


// constructor
WalkableTile::WalkableTile(char type, int x, int y, std::shared_ptr<Character> occupant, std::shared_ptr<Potion> potion, std::vector<std::shared_ptr<Gold>> goldStash, bool exit) :
    Tile {type, x, y},
    occupant {occupant},
    potion {potion},
    goldStash {goldStash},
    exit {exit},
    roomNum {-1}
{}


// accessors and mutators
std::shared_ptr<Character> WalkableTile::getOccupant() const {
    return occupant;
}


void WalkableTile::setOccupant(const std::shared_ptr<Character> character) {
    occupant = character;
}


std::shared_ptr<Potion> WalkableTile::getPotion() const {
    return potion;
}


void WalkableTile::setPotion(const std::shared_ptr<Potion> potion) {
    this->potion = potion;
}


std::vector<std::shared_ptr<Gold>> WalkableTile::getGold() const {
    return goldStash;
}


void WalkableTile::setGold(const std::shared_ptr<Gold> g) {
    // push new gold to stash
    goldStash.push_back(g);
}


bool WalkableTile::isExit() const {
    return exit;
}


void WalkableTile::setExit(const bool exit) {
    this->exit = exit;
}


int WalkableTile::getRoom() const {
    return roomNum;
}


void WalkableTile::setRoom(const int r) {
    roomNum = r;
}


// swaps the location of character at the current WalkableTile to the destination WalkableTile
std::shared_ptr<WalkableTile> WalkableTile::move(std::shared_ptr<WalkableTile> destination) {
    // move the occupant to destination
    std::swap(occupant, destination->occupant);

    // return destination tile
    return destination;
}