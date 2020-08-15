#include "dragon.h"
#include "../Player/shade.h"
#include "../Player/drow.h"
#include "../Player/vampire.h"
#include "../Player/troll.h"
#include "../Player/goblin.h"
#include <cmath>
#include <cstdlib>

/*
    bool isAlive;
*/

Dragon::Dragon() : Enemy{150, 20, 20}, isAlive{true} {

}

bool Dragon::getState() const {
    return isAlive;
}

void Dragon::setState(bool state) {
    isAlive = state;
}

std::string Dragon::getRace() const {
    return "Dragon";
}

bool Dragon::getAttacked(Player & p) {
    
    bool Killed = p.attack(*this);

    // Check if Dragon is dead
    if (Killed) {
        isAlive = false;
    }

    return Killed;
}

// Dragon attacking Shade
bool Dragon::attack(Shade & s) {
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
        s.setHP(0);
        return true;
    }

    // Defender alive otherwise
    return false;

}

// Dragon attacking Drow
bool Dragon::attack(Drow & d) {
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
        d.setHP(0);
        return true;
    }

    // Defender alive otherwise
    return false;
}

// Dragon attacking Vampire
bool Dragon::attack(Vampire & v) {
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
        v.setHP(0);
        return true;
    }

    // Defender alive otherwise
    return false;
}

// Dragon attacking Troll
bool Dragon::attack(Troll & t) {
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
        t.setHP(0);
        return true;
    }

    // Defender alive otherwise
    return false;
}

// Dragon attacking Goblin
bool Dragon::attack(Goblin & g) {
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
        g.setHP(0);
        return true;
    }

    // Defender alive otherwise
    return false;
}
