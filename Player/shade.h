#ifndef __SHADE_H__
#define __SHADE_H__
#include "player.h"


class Shade : public Player {
  public:
    // constructor
    Shade();

    // override visitor methods
    bool getAttacked(Enemy& e) override;
    bool attack(Human& h) override;
    bool attack(Dwarf& d) override;
    bool attack(Elf& e) override;
    bool attack(Orc& o) override;
    bool attack(Merchant& m) override;
    bool attack(Dragon& drag) override;
    bool attack(Halfling& half) override;   

    // returns the race of the character as a string
    std::string getRace() const override;
};


#endif
