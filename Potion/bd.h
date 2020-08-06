#ifndef __BD_H__
#define __BD_H__
#include "potion.h"

class BD : public Potion {
  public:
    // constructor
    BD();

    // applyEffects increases DEF by 5
    void applyEffects(Player& player, double multiplier);
};

#endif
