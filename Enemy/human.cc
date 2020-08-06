#include "human.h"


bool Human::getattacked(Player & p) {
    p.attack(*this);
}

// Human attacking Shade
void Human::attack(Shade & s) {

}

// Human attacking Drow
void Human::attack(Drow & d) {

}

// Human attacking Vampire
void Human::attack(Vampire & v) {

}

// Human attacking Troll
void Human::attack(Troll & t) {

}

// Human attacking Goblin
void Human::attack(Goblin & g) {

}
