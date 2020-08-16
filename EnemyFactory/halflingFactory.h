#ifndef __HALFFACTORY_H__
#define __HALFFACTORY_H__
#include "./efactory.h"

class Enemy;

class HalflingFactory : public EFactory {
  public:
    // spawnEnemy returns a pointer to a new enemy
    virtual std::shared_ptr<Enemy> spawn() override;
}; 

#endif
