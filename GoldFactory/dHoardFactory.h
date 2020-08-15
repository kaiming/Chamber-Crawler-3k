#ifndef __DHOARDFACTORY_H__
#define __DHOARDFACTORY_H__
#include <memory>
#include "goldFactory.h"

class Gold;

class DHoardFactory : public GFactory {
  public:
    DHoardFactory();
    // spawnGold returns a pointer to a new Gold Hoard
    virtual std::shared_ptr<Gold> spawn() override;
}; 

#endif
