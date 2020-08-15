#ifndef __BDFACTORY_H__
#define __BDFACTORY_H__
#include "pfactory.h"

class Potion;

class BDFactory : public PFactory {
  public:
    // spawnPotion returns a pointer to a new Potion
    std::shared_ptr<Potion> spawn() override;
    virtual ~BAFactory();
}; 

#endif
