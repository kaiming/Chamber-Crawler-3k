#include "wd.h"
#include "player.h"


// constructor
WD::WD() : Potion {"WD"} {}


// WD::applyEffects(player, multiplier) decreases DEF by 5
void WD::applyEffects(Player& player, double multiplier) {
    // player def can never drop below 0
    if (player.getDef() - (5 * multiplier) >= 0) {
        player.setDef(player.getDef() - (5 * multiplier));
    } else {
        player.setDef(0);
    }
}