#ifndef __POTION_H__
#define __POTION_H__
#include <string>

class Player;

class Potion {
    std::string type;

  public:
    // constructor
    Potion(std::string type);

    // accessor
    std::string getType() const;

    // applyEffects mutates the player's stats depending on the effect of the potion
    virtual void applyEffects(Player& player, double multiplier) = 0;
};

#endif
