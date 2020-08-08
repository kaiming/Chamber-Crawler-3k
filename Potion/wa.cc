#include "wa.h"
#include "../Player/player.h"


// constructor
WA::WA() : Potion {"WA"} {}


// WA::applyEffects(player, multiplier) decreases ATK by 5
void WA::applyEffects(Player& player, double multiplier) {
    if (player.getAtk() - (5 * multiplier) >= 0) {
        player.setAtk(player.getAtk() - (5 * multiplier));
    } else {
        player.setAtk(0);
    }
}
