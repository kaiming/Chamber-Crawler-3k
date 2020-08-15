#ifndef __PFACTORY_H__
#define __PFACTORY_H__
#include <memory>

class Potion;

class PFactory {
  public:
    // spawnPotion returns a pointer to a new Potion
    virtual std::shared_ptr<Potion> spawnPotion() = 0;
}; 

#endif
