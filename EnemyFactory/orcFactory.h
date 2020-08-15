#ifndef __ORCFACTORY_H__
#define __ORCFACTORY_H__
#include "efactory.h"

class Enemy;

class OrcFactory : public EFactory {
  public:
    // spawnEnemy creates a specific type of tile for the floor
    std::shared_ptr<Enemy> spawnEnemy() override;
}; 

#endif
