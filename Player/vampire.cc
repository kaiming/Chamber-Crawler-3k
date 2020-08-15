#include <cmath>
#include <cstdlib>
#include "vampire.h"
#include "../Enemy/human.h"
#include "../Enemy/dwarf.h"
#include "../Enemy/elf.h"
#include "../Enemy/orc.h"
#include "../Enemy/merchant.h"
#include "../Enemy/dragon.h"
#include "../Enemy/halfling.h"
#include "../Potion/potion.h"


// constructor
Vampire::Vampire() :
    Player {50, -1, 25, 25}
{}


// visitor methods
bool Vampire::getAttacked(Enemy& e) {
    return e.attack(*this);
}


bool Vampire::attack(Human& h) {    
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + h.getDef()) * this->getAtk());

    // Set new defender HP
    h.setHP(h.getHP() - damage);

    // gains 5 health every successful attack
    this->setHP(this->getHP() + 5);

    // Check if defender died
    if (h.getHP() <= 0) {
        h.setHP(0);
        return true;
    }

    // Defender alive otherwise
    return false;
}


bool Vampire::attack(Dwarf& d) {
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + d.getDef()) * this->getAtk());

    // Set new defender HP
    d.setHP(d.getHP() - damage);

    // alergic to Dwarfs so lose 5 health every successful attack
    this->setHP(this->getHP() - 5);

    // Check if defender died
    if (d.getHP() <= 0) {
        d.setHP(0);
        return true;
    }

    // Defender alive otherwise
    return false;
}


bool Vampire::attack(Elf& e) {
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + e.getDef()) * this->getAtk());

    // Set new defender HP
    e.setHP(e.getHP() - damage);

    // gains 5 health every successful attack
    this->setHP(this->getHP() + 5);

    // Check if defender died
    if (e.getHP() <= 0) {
        e.setHP(0);
        return true;
    }

    // Defender alive otherwise
    return false;
}


bool Vampire::attack(Orc& o) {
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + o.getDef()) * this->getAtk());

    // Set new defender HP
    o.setHP(o.getHP() - damage);

    // Check if defender died
    if (o.getHP() <= 0) {
        o.setHP(0);
        return true;
    }

    // Defender alive otherwise
    return false;
}


bool Vampire::attack(Merchant& m) {
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + m.getDef()) * this->getAtk());

    // Set new defender HP
    m.setHP(m.getHP() - damage);

    // gains 5 health every successful attack
    this->setHP(this->getHP() + 5);

    // Check if defender died
    if (m.getHP() <= 0) {
        m.setHP(0);
        return true;
    }

    // Defender alive otherwise
    return false;
}


bool Vampire::attack(Dragon& drag) {
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + drag.getDef()) * this->getAtk());

    // Set new defender HP
    drag.setHP(drag.getHP() - damage);

    // gains 5 health every successful attack
    this->setHP(this->getHP() + 5);

    // Check if defender died
    if (drag.getHP() <= 0) {
        drag.setHP(0);
        return true;
    }

    // Defender alive otherwise
    return false;
}


bool Vampire::attack(Halfling& half) {
    // Determine attack success/fail
    if (std::rand() % 2 == 0) {
        // Attack failed
        return false;
    } // Else, attack proceeds

    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + half.getDef()) * this->getAtk());

    // Set new defender HP
    half.setHP(half.getHP() - damage);

    // gains 5 health every successful attack
    this->setHP(this->getHP() + 5);

    // Check if defender died
    if (half.getHP() <= 0) {
        half.setHP(0);
        return true;
    }

    // Defender alive otherwise
    return false;
}


// Vampire::getRace() returns Drow as a string
std::string Vampire::getRace() const {
    return "Vampire";
}
