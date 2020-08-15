#ifndef __DWARFFACTORY_H__
#define __DWARFACTORY_H__
#include "efactory.h"

class Enemy;

class DwarfFactory : public EFactory {
  public:
    // spawnEnemy returns a pointer to a new enemy
    std::shared_ptr<Enemy> spawnEnemy() override;
}; 

#endif
