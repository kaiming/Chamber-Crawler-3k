#include "player.h"
// add includes once Enemy and Potion classes are set up


// constructor
Player::Player(double HP, double atk, double def, int gold) :
    Character {HP, atk, def},
    gold {gold}
{}


// accessors and mutators
int Player::getGold() const {
    return gold;
}


void Player::setGold(int gold) {
    if (gold >= 0) this->gold = gold;
}


// Player::usePotion(p) applies the effects of a potion to the player
void Player::usePotion(std::shared_ptr<Potion> p) {
    p->applyEffects(*this, 1);
}