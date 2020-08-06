#ifndef __GOBLIN_H__
#define __GOBLIN_H__
#include "player.h"

class Goblin : public Player {
  public:
    // constructor
    Goblin();

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
