#include "rh.h"
#include "player.h"


// constructor
RH::RH() : Potion {"RH"} {}


// RH::applyEffects(player, multiplier) restores up to 10 HP
void RH::applyEffects(Player& player, double multiplier) {
    // if player is a vampire or player health is at least 10 HP away from max
    if ((player.getMaxHP() < 0) || (player.getHP() + (10 * multiplier) <= player.getMaxHP())) {
        player.setHP(player.getHP() + (10 * multiplier));
    } else {
        player.setHP(player.getMaxHP());
    } // else add health to full
}
