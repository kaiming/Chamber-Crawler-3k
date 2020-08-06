#ifndef __WD_H__
#define __WD_H__
#include "potion.h"

class WD : public Potion {
  public:
    // constructor
    WD();

    // applyEffects decreases DEF by 5
    void applyEffects(Player& player, double multiplier);
};

#endif
