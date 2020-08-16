#ifndef __RHFACTORY_H__
#define __RHFACTORY_H__
#include "pfactory.h"

class Potion;

class RHFactory : public PFactory {
  public:
    // spawnPotion returns a pointer to a new Potion
    std::shared_ptr<Potion> spawn() override;
}; 

#endif
