#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <string>

class Character {
  protected:
    double HP, atk, def;

  public:
    // constructor
    Character(double HP, double atk, double def);

    // accessors and mutators
    double getHP() const;
    double getAtk() const;
    double getDef() const;
    void setHP(double HP); 
    void setAtk(double atk);
    void setDef(double def);

    // returns the race of the character as a string
    virtual std::string getRace() const = 0;
};

#endif
