#ifndef __DRAGON_H__
#define __DRAGON_H__

#include "enemy.h"

// SPECIAL EFFECT: Guards Dragon Hoards

class Dragon : public Enemy {
    private:

    public:
        // Constructor
        Dragon();

        virtual bool getAttacked(Player & p) override;
        virtual bool attack(Shade & s) override;
        virtual bool attack(Drow & d) override;
        virtual bool attack(Vampire & v) override;
        virtual bool attack(Troll & t) override;
        virtual bool attack(Goblin & g) override;


}

#endif