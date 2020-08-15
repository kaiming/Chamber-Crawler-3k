#ifndef __HUMANFACTORY_H__
#define __HUMANFACTORY_H__
#include "efactory.h"

class Enemy;

class HumanFactory : public EFactory {
  public:
    // spawnEnemy returns a pointer to a new enemy
    std::shared_ptr<Enemy> spawnEnemy() override;
}; 

#endif
