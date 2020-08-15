#ifndef __PFACTORY_H__
#define __PFACTORY_H__
#include <memory>

class Potion;

class PFactory {
  public:
    // spawn returns a pointer to a new Potion
    virtual std::shared_ptr<Potion> spawn() = 0;
    virtual ~PFactory() = 0;
}; 

#endif
