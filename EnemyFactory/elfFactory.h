#ifndef __ELFFACTORY_H__
#define __ELFFACTORY_H__
#include "efactory.h"

class Enemy;

class ElfFactory : public EFactory {
  public:
    // spawnEnemy returns a pointer to a new enemy
    virtual std::shared_ptr<Enemy> spawn() override;
}; 

#endif
