#ifndef __PH_H__
#define __PH_H__
#include "potion.h"

class PH : public Potion {
  public:
    // constructor
    PH();

    // applyEffects reduces player's HP by up to 10 HP
    void applyEffects(Player& player, double multiplier);
};

#endif
