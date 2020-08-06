#include "ba.h"
#include "player.h"


// constructor
BA::BA() : Potion {"BA"} {}


// BA::applyEffects(player, multiplier) increases ATK by 5
void BA::applyEffects(Player& player, double multiplier) {
    player.setAtk(player.getAtk() + (5 * multiplier));
}
