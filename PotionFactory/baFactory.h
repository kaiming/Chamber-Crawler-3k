#ifndef __BAFACTORY_H__
#define __BAFACTORY_H__
#include "pfactory.h"

class Potion;

class BAFactory : public PFactory {
  public:
    // spawnPotion returns a pointer to a new Potion
    std::shared_ptr<Potion> spawn() override;
}; 

#endif
