#include "bd.h"
#include "player.h"


// constructor
BD::BD() : Potions {"BD"} {}


// BD::applyEffects(player, multiplier) increases DEF by 5
void BD::applyEffects(Player& player, double multiplier) {
    player.setDef(player.getDef() + (5 * multiplier));
}
