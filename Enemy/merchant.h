#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include "enemy.h"
#include <string>

// SPECIAL EFFECT: None

class Merchant : public Enemy {
    private:

    public:
        // Constructor
        Merchant();
        virtual std::string getRace() const override;

        virtual bool getAttacked(Player & p) override;
        virtual bool attack(Shade & s) override;
        virtual bool attack(Drow & d) override;
        virtual bool attack(Vampire & v) override;
        virtual bool attack(Troll & t) override;
        virtual bool attack(Goblin & g) override;


};

#endif
