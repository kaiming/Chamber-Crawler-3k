#ifndef __DROW_H__
#define __DROW_H__
#include <memory>
#include "player.h"

class Drow : public Player {
    double maxHP;

  public:
    // constructor
    Drow();

    // override visitor methods
    void getAttacked(Enemy& e) override;
    bool attack(Human& h) override;
    bool attack(Dwarf& d) override;
    bool attack(Elf& e) override;
    bool attack(Orc& o) override;
    bool attack(Merchant& m) override;
    bool attack(Dragon& drag) override;
    bool attack(Halfling& half) override;

    // override usePotion method to apply 1.5 multiplier
    void usePotion(std::shared_ptr<Potion> p) override;
};

#endif