#include "player.h"
// add in relative paths later
#include "potion.h"


// constructor
Player::Player(double HP, double maxHP, double atk, double def) :
    Character {HP, atk, def},
    gold {0},
    maxHP {maxHP}
{}


// accessors and mutators
int Player::getGold() const {
    return gold;
}


void Player::setGold(int gold) {
    if (gold >= 0) this->gold = gold;
}


double Player::getMaxHP() const {
    return maxHP;
}


// Player::usePotion(p) applies the effects of a potion to the player
void Player::usePotion(std::shared_ptr<Potion> p) {
    p->applyEffects(*this, 1);
}
