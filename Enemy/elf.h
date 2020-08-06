#ifndef __ELF_H__
#define __ElF_H__

#include "enemy.h"

// SPECIAL EFFECT: Gets two attacks against every race except drow

class Elf : public Enemy {
    private:

    public:
        // Constructor
        Elf();

        virtual bool getAttacked(Player & p) override;
        virtual bool attack(Shade & s) override;
        virtual bool attack(Drow & d) override;
        virtual bool attack(Vampire & v) override;
        virtual bool attack(Troll & t) override;
        virtual bool attack(Goblin & g) override;


}

#endif