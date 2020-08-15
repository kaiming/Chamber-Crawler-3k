#ifndef __PFACTORY_H__
#define __PFACTORY_H__
#include <memory>

class Potion;

class PFactory {
  public:
    // spawnPotion creates a specific type of tile for the floor
    virtual std::shared_ptr<Potion> spawnPotion() = 0;
}; 

#endif
