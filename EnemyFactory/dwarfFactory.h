#ifndef __DWARFFACTORY_H__
#define __DWARFACTORY_H__
#include "efactory.h"

class Enemy;

class DwarfFactory : public EFactory {
  public:
    // spawnEnemy creates a specific type of tile for the floor
    std::shared_ptr<Enemy> spawnEnemy() override;
}; 

#endif
