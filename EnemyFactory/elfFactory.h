#ifndef __ELFFACTORY_H__
#define __ELFFACTORY_H__
#include "efactory.h"

class Enemy;

class ElfFactory : public EFactory {
  public:
    // spawnEnemy creates a specific type of tile for the floor
    std::shared_ptr<Enemy> spawnEnemy() override;
}; 

#endif
