#ifndef __EFACTORY_H__
#define __EFACTORY_H__
#include <memory>

class Enemy;

class EFactory {
  public:
    // spawnEnemy creates a specific type of tile for the floor
    virtual std::shared_ptr<Enemy> spawnEnemy() = 0;
}; 

#endif
