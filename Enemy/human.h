#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "enemy.h"

class Human : public Enemy {
    private:

    public:
        virtual bool getAttacked(Player & p) override;
        virtual void attack(Shade & s) override;
        virtual void attack(Drow & d) override;
        virtual void attack(Vampire & v) override;
        virtual void attack(Troll & t) override;
        virtual void attack(Goblin & g) override;


}

#endif
