#ifndef __BA_H__
#define __BA_H__
#include "potion.h"

class BA : public Potion {
  public:
    // constructor
    BA();

    // applyEffects increases ATK by 5
    void applyEffects(Player& player, double multiplier);
};

#endif
