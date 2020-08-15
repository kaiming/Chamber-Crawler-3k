#ifndef __HUMANFACTORY_H__
#define __HUMANFACTORY_H__
#include "efactory.h"

class Enemy;

class HumanFactory : public EFactory {
  public:
    // spawnEnemy creates a specific type of tile for the floor
    std::shared_ptr<Enemy> spawnEnemy() override;
}; 

#endif
