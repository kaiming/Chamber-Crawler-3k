#include <cmath>
#include <cstdlib>
#include "shade.h"
// add in relative paths later
#include "human.h"
#include "dwarf.h"
#include "elf.h"
#include "orc.h"
#include "merchant.h"
#include "dragon.h"
#include "halfling.h"
#include "potion.h"


// constructor
Shade::Shade() :
    Player {125, 25, 25, 0},
    maxHP {125}
{}


// visitor methods
bool Shade::getAttacked(Enemy& e) {
    return e.attack(*this);
}


bool Shade::attack(Human& h) {    
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + h.getDef()) * this->atk);

    // Set new defender HP
    h.setHP(h.getHP() - damage);

    // Check if defender died
    if (h.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}


bool Shade::attack(Dwarf& d) {
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + d.getDef()) * this->getAtk());

    // Set new defender HP
    d.setHP(d.getHP() - damage);

    // Check if defender died
    if (d.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}


bool Shade::attack(Elf& e) {
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + e.getDef()) * this->getAtk());

    // Set new defender HP
    e.setHP(e.getHP() - damage);

    // Check if defender died
    if (e.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}


bool Shade::attack(Orc& o) {
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + o.getDef()) * this->getAtk());

    // Set new defender HP
    o.setHP(o.getHP() - damage);

    // Check if defender died
    if (o.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}


bool Shade::attack(Merchant& m) {
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + m.getDef()) * this->getAtk());

    // Set new defender HP
    m.setHP(m.getHP() - damage);

    // Check if defender died
    if (m.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}


bool Shade::attack(Dragon& drag) {
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + drag.getDef()) * this->getAtk());

    // Set new defender HP
    drag.setHP(drag.getHP() - damage);

    // Check if defender died
    if (drag.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}


bool Shade::attack(Halfling& half) {
    // Determine attack success/fail
    if (std::rand() % 2 == 0) {
        // Attack failed
        return false;
    } // Else, attack proceeds
    
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + half.getDef()) * this->getAtk());

    // Set new defender HP
    half.setHP(half.getHP() - damage);

    // Check if defender died
    if (half.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}