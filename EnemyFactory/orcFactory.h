#ifndef __ORCFACTORY_H__
#define __ORCFACTORY_H__
#include "./efactory.h"

class Enemy;

class OrcFactory : public EFactory {
  public:
    // spawnEnemy returns a pointer to a new enemy
    virtual std::shared_ptr<Enemy> spawn() override;
}; 

#endif
