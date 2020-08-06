#ifndef __HUMAN_H__
#define __HUMAN_H__

class Player;
class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;

#include "enemy.h"

// SPECIAL EFFECT: Drop 2 Normal Piles of Gold on Death

class Human : public Enemy {
    private:

    public:
        // Constructor
        Human();

        virtual bool getAttacked(Player & p) override;
        virtual bool attack(Shade & s) override;
        virtual bool attack(Drow & d) override;
        virtual bool attack(Vampire & v) override;
        virtual bool attack(Troll & t) override;
        virtual bool attack(Goblin & g) override;


}

#endif
