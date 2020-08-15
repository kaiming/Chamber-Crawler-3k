#ifndef __WDFACTORY_H__
#define __WDFACTORY_H__
#include "pfactory.h"

class Potion;

class WDFactory : public PFactory {
  public:
    // spawnPotion returns a pointer to a new Potion
    std::shared_ptr<Potion> spawn() override;
}; 

#endif
