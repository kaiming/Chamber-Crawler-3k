#include "ph.h"
#include "../Player/player.h"


// constructor
PH::PH() : Potion {"PH"} {}


// PH::applyEffects(player, multiplier) reduces player's HP by up to 10 HP
void PH::applyEffects(Player& player, double multiplier) {
    // if players HP is at least 10 HP
    if (player.getHP() >= (10 * multiplier)) {
        player.setHP(player.getHP() - (10 * multiplier));
    } else {
        player.setHP(0);
    } // else set HP to 0
}
