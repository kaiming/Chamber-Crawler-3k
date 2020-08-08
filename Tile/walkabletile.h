#ifndef __WALKABLETILE_H__
#define __WALKABLETILE_H__
#include <memory>
#include <vector>
#include "tile.h"

class Character;
class Potion;
class Gold;

class WalkableTile : public Tile {
    std::shared_ptr<Character> occupant;
    std::shared_ptr<Potion> potion;
    std::vector<std::shared_ptr<Gold>> goldStash;
    bool exit;
    int roomNum;

  public:
    // constructor
    WalkableTile(char type, int x, int y, std::shared_ptr<Character> occupant, std::shared_ptr<Potion> potion, std::vector<std::shared_ptr<Gold>> goldStash, bool exit);

    // accessors and mutators
    std::shared_ptr<Character> getOccupant() const;
    void setOccupant(const std::shared_ptr<Character> character);
    std::shared_ptr<Potion> getPotion() const;
    void setPotion(const std::shared_ptr<Potion> potion);
    std::vector<std::shared_ptr<Gold>> getGold() const;
    void setGold(const std::shared_ptr<Gold> g);
    bool isExit() const;
    void setExit(const bool exit);
    int getRoom() const;
    void setRoom(const int r);

    // swaps the location of character at the current WalkableTile to the destination WalkableTile
    std::shared_ptr<WalkableTile> move(std::shared_ptr<WalkableTile> destination);
};

#endif
