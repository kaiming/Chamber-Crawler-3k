#ifndef __EFACTORY_H__
#define __EFACTORY_H__
#include <memory>
#include "../PieceFactory/pieceFactory.h"

class Enemy;

class EFactory : public PieceFactory {
  public:
    // spawnEnemy returns a pointer to a new enemy
    virtual std::shared_ptr<Enemy> spawn() = 0;
}; 

#endif
