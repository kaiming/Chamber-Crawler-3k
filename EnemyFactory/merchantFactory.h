#ifndef __MERCHFACTORY_H__
#define __MERCHFACTORY_H__
#include "efactory.h"

class Enemy;

class MerchantFactory : public EFactory {
  public:
    // spawnEnemy creates a specific type of tile for the floor
    std::shared_ptr<Enemy> spawnEnemy() override;
}; 

#endif
