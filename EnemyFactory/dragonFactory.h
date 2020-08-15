#ifndef __DRAGFACTORY_H__
#define __DRAGFACTORY_H__
#include "efactory.h"

class Enemy;

class DragonFactory : public EFactory {
  public:
    // spawnEnemy creates a specific type of tile for the floor
    std::shared_ptr<Enemy> spawnEnemy() override;
}; 

#endif
