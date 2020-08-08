#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <memory>
#include "../Character/character.h"

class Enemy;
class Human;
class Dwarf;
class Elf;
class Orc;
class Merchant;
class Dragon;
class Halfling;
class Potion;


class Player : public Character {
  protected:
    int gold;
    const double maxHP;

  public:
    // constructor
    Player(double HP = 0, double maxHP = 0, double atk = 0, double def = 0);

    // accessors and mutators
    int getGold() const;
    void setGold(int gold);
    double getMaxHP() const;

    // visitor (attack and getting attacked mechanisms)
    virtual bool getAttacked(Enemy& e) = 0;
    virtual bool attack(Human& h) = 0;
    virtual bool attack(Dwarf& d) =  0;
    virtual bool attack(Elf& e) = 0;
    virtual bool attack(Orc& o) = 0;
    virtual bool attack(Merchant& m) = 0;
    virtual bool attack(Dragon& drag) = 0;
    virtual bool attack(Halfling& half) = 0;

    // applies potion effects to player
    virtual void usePotion(std::shared_ptr<Potion> p);
};


#endif
