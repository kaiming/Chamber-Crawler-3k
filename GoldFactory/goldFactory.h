#ifndef __GFACTORY_H__
#define __GFACTORY_H__
#include <memory>

class Gold;

class GFactory {
  private:
    std::string type;
    int value;
  public:
    // spawnGold returns a pointer to a new Gold Hoard
    virtual GFactory(std::string type, int value);
    virtual std::shared_ptr<Gold> spawn();
}; 

#endif
