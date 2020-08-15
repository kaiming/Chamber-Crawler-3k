#ifndef __PHFACTORY_H__
#define __PHFACTORY_H__
#include "pfactory.h"

class Potion;

class PHFactory : public PFactory {
  public:
    // spawnPotion returns a pointer to a new Potion
    std::shared_ptr<Potion> spawnPotion() override;
}; 

#endif
