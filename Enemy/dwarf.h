#ifndef __DWARF_H__
#define __DWARF_H__

class Player;
class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;

#include "enemy.h"

// SPECIAL EFFECT: Vampires lose 5 hp instead of gaining when attacking Dwarves

class Dwarf : public Enemy {
    private:

    public:
        // Constructor
        Dwarf();

        virtual bool getAttacked(Player & p) override;
        virtual bool attack(Shade & s) override;
        virtual bool attack(Drow & d) override;
        virtual bool attack(Vampire & v) override;
        virtual bool attack(Troll & t) override;
        virtual bool attack(Goblin & g) override;


}

#endif