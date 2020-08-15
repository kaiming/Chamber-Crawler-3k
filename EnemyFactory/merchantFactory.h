#ifndef __MERCHFACTORY_H__
#define __MERCHFACTORY_H__
#include "efactory.h"

class Enemy;

class MerchantFactory : public EFactory {
  public:
    // spawnEnemy returns a pointer to a new enemy
    std::shared_ptr<Enemy> spawnEnemy() override;
}; 

#endif
