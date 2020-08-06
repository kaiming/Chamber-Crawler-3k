#ifndef __WA_H__
#define __WA_H__
#include "potion.h"

class WA : public Potion {
  public:
    // constructor
    WA();

    // applyEffects decreases ATK by 5
    void applyEffects(Player& player, double multiplier);
};

#endif
