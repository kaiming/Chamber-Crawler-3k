#ifndef __WAFACTORY_H__
#define __WAFACTORY_H__
#include "pfactory.h"

class Potion;

class WAFactory : public PFactory {
  public:
    // spawnPotion returns a pointer to a new Potion
    std::shared_ptr<Potion> spawn() override;
}; 

#endif
