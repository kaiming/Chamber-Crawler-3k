#ifndef __ELFFACTORY_H__
#define __ELFFACTORY_H__
#include "efactory.h"

class Enemy;

class ElfFactory : public EFactory {
  public:
    // spawnEnemy returns a pointer to a new enemy
    std::shared_ptr<Enemy> spawnEnemy() override;
}; 

#endif
