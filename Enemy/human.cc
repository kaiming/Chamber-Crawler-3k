#include "human.h"
#include "../Player/shade.h"
#include "../Player/drow.h"
#include "../Player/vampire.h"
#include "../Player/troll.h"
#include "../Player/goblin.h"
#include <cmath>
#include <cstdlib>

Human::Human() : Enemy{140, 20, 20} {

}

std::string Human::getRace() const {
    return "Human";
}

bool Human::getAttacked(Player & p) {
    return p.attack(*this);
}

// Human attacking Shade
bool Human::attack(Shade & s) {
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

// Human attacking Drow
bool Human::attack(Drow & d) {
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

// Human attacking Vampire
bool Human::attack(Vampire & v) {
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

// Human attacking Troll
bool Human::attack(Troll & t) {
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

// Human attacking Goblin
bool Human::attack(Goblin & g) {
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
