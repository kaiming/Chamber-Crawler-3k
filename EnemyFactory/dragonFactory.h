#ifndef __DRAGFACTORY_H__
#define __DRAGFACTORY_H__
#include "./efactory.h"

class Enemy;

class DragonFactory : public EFactory {
  public:
    // spawnEnemy returns a pointer to a new enemy
    virtual std::shared_ptr<Enemy> spawn() override;
}; 

#endif
