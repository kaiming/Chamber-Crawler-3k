#ifndef __ORC_H__
#define __ORC_H__

#include "enemy.h"

// SPECIAL EFFECT: Does 50% more damage to Goblins

class Orc : public Enemy {
    private:

    public:
        // Constructor
        Orc();

        virtual bool getAttacked(Player & p) override;
        virtual bool attack(Shade & s) override;
        virtual bool attack(Drow & d) override;
        virtual bool attack(Vampire & v) override;
        virtual bool attack(Troll & t) override;
        virtual bool attack(Goblin & g) override;


}

#endif