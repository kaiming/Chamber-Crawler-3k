#ifndef __HALFLING_H__
#define __HALFLING_H__

#include "enemy.h"

// SPECIAL EFFECT: Causes Player to have 50% attack miss

class Halfling : public Enemy {
    private:

    public:
        // Constructor
        Halfling();

        virtual bool getAttacked(Player & p) override;
        virtual bool attack(Shade & s) override;
        virtual bool attack(Drow & d) override;
        virtual bool attack(Vampire & v) override;
        virtual bool attack(Troll & t) override;
        virtual bool attack(Goblin & g) override;


}

#endif