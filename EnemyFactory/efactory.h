#ifndef __EFACTORY_H__
#define __EFACTORY_H__
#include <memory>

class Enemy;

class EFactory {
  public:
    // spawnEnemy returns a pointer to a new enemy
    virtual std::shared_ptr<Enemy> spawn() = 0;
    virtual ~EFactory() = 0;
}; 

#endif
