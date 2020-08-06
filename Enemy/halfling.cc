#include "halfling.h"
#include "shade.h"
#include "drow.h"
#include "vampire.h"
#include "troll.h"
#include "goblin.h"
#include <cmath>
#include <cstdlib>

Halfling::Halfling() : Character{100, 15, 20} {

}

bool Halfling::getAttacked(Player & p) {
    return p.attack(*this);
}

// Halfling attacking Shade
bool Halfling::attack(Shade & s) {
    // Determine attack success/fail
    if (std::rand() % 2 == 0) {
        // Attack failed
        return false;
    } // Else, attack proceeds
    
    // Calculate damage dealt
    double damage = std::ceil(100/(100 + s.getDef()) * this->getAtk());

    // Set new defender HP
    s.setHP(s.getHP() - damage);

    // Check if defender died
    if (s.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;

}

// Halfling attacking Drow
bool Halfling::attack(Drow & d) {
    // Determine attack success/fail
    if (std::rand() % 2 == 0) {
        // Attack failed
        return false;
    } // Else, attack proceeds
    
    // Calculate damage dealt
    double damage = std::ceil(100/(100 + d.getDef()) * this->getAtk());

    // Set new defender HP
    d.setHP(d.getHP() - damage);

    // Check if defender died
    if (d.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}

// Halfling attacking Vampire
bool Halfling::attack(Vampire & v) {
    // Determine attack success/fail
    if (std::rand() % 2 == 0) {
        // Attack failed
        return false;
    } // Else, attack proceeds
    
    // Calculate damage dealt
    double damage = std::ceil(100/(100 + v.getDef()) * this->getAtk());

    // Set new defender HP
    v.setHP(v.getHP() - damage);

    // Check if defender died
    if (v.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}

// Halfling attacking Troll
bool Halfling::attack(Troll & t) {
    // Determine attack success/fail
    if (std::rand() % 2 == 0) {
        // Attack failed
        return false;
    } // Else, attack proceeds
    
    // Calculate damage dealt
    double damage = std::ceil(100/(100 + t.getDef()) * this->getAtk());

    // Set new defender HP
    t.setHP(t.getHP() - damage);

    // Check if defender died
    if (t.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}

// Halfling attacking Goblin
bool Halfling::attack(Goblin & g) {
    // Determine attack success/fail
    if (std::rand() % 2 == 0) {
        // Attack failed
        return false;
    } // Else, attack proceeds
    
    // Calculate damage dealt
    double damage = std::ceil(100/(100 + g.getDef()) * this->getAtk());

    // Set new defender HP
    g.setHP(g.getHP() - damage);

    // Check if defender died
    if (g.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}
