#ifndef __HALFFACTORY_H__
#define __HALFFACTORY_H__
#include "efactory.h"

class Enemy;

class HalflingFactory : public EFactory {
  public:
    // spawnEnemy creates a specific type of tile for the floor
    std::shared_ptr<Enemy> spawnEnemy() override;
}; 

#endif
