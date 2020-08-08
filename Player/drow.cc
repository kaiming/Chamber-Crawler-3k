#include <cmath>
#include <cstdlib>
#include "drow.h"
#include "../Enemy/human.h"
#include "../Enemy/dwarf.h"
#include "../Enemy/elf.h"
#include "../Enemy/orc.h"
#include "../Enemy/merchant.h"
#include "../Enemy/dragon.h"
#include "../Enemy/halfling.h"
#include "../Potion/potion.h"


// constructor
Drow::Drow() :
    Player {150, 150, 25, 15}
{}


// visitor methods
bool Drow::getAttacked(Enemy& e) {
    return e.attack(*this);
}


bool Drow::attack(Human& h) {    
    // Calculate damage dealt
    double damage = std::ceil(100 / (100 + h.getDef()) * this->getAtk());

    // Set new defender HP
    h.setHP(h.getHP() - damage);

    // Check if defender died
    if (h.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}


bool Drow::attack(Dwarf& d) {
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


bool Drow::attack(Elf& e) {
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


bool Drow::attack(Orc& o) {
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


bool Drow::attack(Merchant& m) {
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


bool Drow::attack(Dragon& drag) {
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


bool Drow::attack(Halfling& half) {
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


// Drow::usePotion(p) amplifies the effets of each potion to the Drow by 1.5 times
void Drow::usePotion(std::shared_ptr<Potion> p) {
    p->applyEffects(*this, 1.5);
}


// Drow::getRace() returns Drow as a string
std::string Drow::getRace() const {
    return "Drow";
}
