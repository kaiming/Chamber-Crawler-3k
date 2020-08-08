#include "bd.h"
#include "../Player/player.h"


// constructor
BD::BD() : Potion {"BD"} {}


// BD::applyEffects(player, multiplier) increases DEF by 5
void BD::applyEffects(Player& player, double multiplier) {
    player.setDef(player.getDef() + (5 * multiplier));
}
