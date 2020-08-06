#ifndef __RH_H__
#define __RH_H__
#include "potion.h"

class RH : public Potion {
  public:
    // constructor
    RH();

    // applyEffects restores up to 10 HP
    void applyEffects(Player& player, double multiplier);
};

#endif
