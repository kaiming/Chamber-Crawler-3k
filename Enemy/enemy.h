#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "character.h"

class Enemy : public Character {
    private:

    public:
        virtual bool getAttacked(Player & p) = 0;
        virtual bool attack(Shade & s) = 0;
        virtual bool attack(Drow & d) = 0;
        virtual bool attack(Vampire & v) = 0;
        virtual bool attack(Troll & t) = 0;
        virtual bool attack(Goblin & g = 0;


}

#endif
