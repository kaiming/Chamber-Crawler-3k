#ifndef __TILE_H__
#define __TILE_H__
#include <utility>
#include <memory>

class Tile {
    char type;
    std::pair<int, int> coord;

  public:
    // constructor
    Tile(char type, int x, int y);
    virtual ~Tile();

    // accessors
    char getType() const;
    std::pair<int, int> getCoord() const;
};

#endif
