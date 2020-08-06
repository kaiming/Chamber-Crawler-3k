#include "character.h"

// constructor
// NOTE: MIGHT NEED TO DO EXTRA CHECKS BUT WE"LL LEAVE IT LIKE THIS FOR NOW
Character::Character(double HP, double atk, double def) :
    HP {HP},
    atk {atk},
    def {def}
{}


// destructor (does nothing)
Character::~Character() {}


// accessors and mutators
double Character::getHP() const {
    return HP;
}


double Character::getAtk() const {
    return atk;
}


double Character::getDef() const {
    return def;
}

// mutators are currently implemented to take an updated value
// NOTE: WE CAN UPDATE THIS IF WE WANT TO CHANGE
void Character::setHP(const double HP) {
    this->HP = HP;
}


void Character::setAtk(const double atk) {
    if (atk >= 0) this->atk = atk;
}


void Character::setDef(const double def) {
    if (def >= 0) this->def = def;
}