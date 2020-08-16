#ifndef __HUMANFACTORY_H__
#define __HUMANFACTORY_H__
#include "./efactory.h"

class Enemy;

class HumanFactory : public EFactory {
  public:
    // spawnEnemy returns a pointer to a new enemy
    virtual std::shared_ptr<Enemy> spawn() override;
}; 

#endif
