#ifndef __PFACTORY_H__
#define __PFACTORY_H__
#include <memory>
#include "../PieceFactory/pieceFactory.h"

class Potion;

class PFactory : public PieceFactory {
  public:
    // spawn returns a pointer to a new Potion
    virtual std::shared_ptr<Potion> spawn() = 0;
}; 

#endif
