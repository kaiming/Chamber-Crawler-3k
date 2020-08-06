#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include "player.h"

class Vampire : public Player {
    double maxHP;

  public:
    // constructor
    Vampire();

    // override visitor methods
    bool getAttacked(Enemy& e) override;
    bool attack(Human& h) override;
    bool attack(Dwarf& d) override;
    bool attack(Elf& e) override;
    bool attack(Orc& o) override;
    bool attack(Merchant& m) override;
    bool attack(Dragon& drag) override;
    bool attack(Halfling& half) override;
};

#endif