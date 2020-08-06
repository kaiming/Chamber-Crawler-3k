#ifndef _CHARACTER_H_
#define _CHARACTER_H_

class Character {
  protected:
    double HP, atk, def;

  public:
    // constructor
    Character(double HP, double atk, double def);
    // destructor
    virtual ~Character() = 0;

    // accessors and mutators
    double getHP() const;
    double getAtk() const;
    double getDef() const;
    void setHP(double HP); 
    void setAtk(double atk);
    void setDef(double def);
};

#endif
