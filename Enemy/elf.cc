#include "elf.h"
#include <cmath>
#include <cstdlib>

Elf::Elf() : Character{140, 30, 10} {

}

bool Elf::getAttacked(Player & p) {
    return p.attack(*this);
}

// Elf attacking Shade
bool Elf::attack(Shade & s) {
    // SPECIAL EFFECT: gets two attacks 
    for (int i = 0; i < 2; i++) {
        // Determine attack success/fail
        if (std::rand() % 2 == 0) {
            // Attack failed
            continue;
        } // Else, attack proceeds
        
        // Calculate damage dealt
        double damage = std::ceil(100/(100 + s.getDef()) * this->getAtk());

        // Set new defender HP
        s.setHP(s.getHP() - damage);
    }

    // Check if defender died
    if (s.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;

}

// Elf attacking Drow
bool Elf::attack(Drow & d) {
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

// Elf attacking Vampire
bool Elf::attack(Vampire & v) {
    // SPECIAL EFFECT: gets two attacks
    for (int i = 0; i < 2; i++) {
        // Determine attack success/fail
        if (std::rand() % 2 == 0) {
            // Attack failed
            continue;
        } // Else, attack proceeds
        
        // Calculate damage dealt
        double damage = std::ceil(100/(100 + v.getDef()) * this->getAtk());

        // Set new defender HP
        v.setHP(v.getHP() - damage);
    }

    // Check if defender died
    if (v.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}

// Elf attacking Troll
bool Elf::attack(Troll & t) {
    // SPECIAL EFFECT: gets two attacks 
    for (int i = 0; i < 2; i++) {
        // Determine attack success/fail
        if (std::rand() % 2 == 0) {
            // Attack failed
            continue;
        } // Else, attack proceeds
        
        // Calculate damage dealt
        double damage = std::ceil(100/(100 + t.getDef()) * this->getAtk());

        // Set new defender HP
        t.setHP(t.getHP() - damage);
    }

    // Check if defender died
    if (t.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}

// Elf attacking Goblin
bool Elf::attack(Goblin & g) {
    // SPECIAL EFFECT: gets two attacks 
    for (int i = 0; i < 2; i++) {
        // Determine attack success/fail
        if (std::rand() % 2 == 0) {
            // Attack failed
            continue;
        } // Else, attack proceeds
        
        // Calculate damage dealt
        double damage = std::ceil(100/(100 + g.getDef()) * this->getAtk());

        // Set new defender HP
        g.setHP(g.getHP() - damage);
    }

    // Check if defender died
    if (g.getHP() <= 0) {
        return true;
    }

    // Defender alive otherwise
    return false;
}
