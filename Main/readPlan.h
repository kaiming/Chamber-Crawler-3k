#ifndef __READPLAN_H__
#define __READPLAN_H__
#include <fstream>
#include <vector>
#include <memory>

class Tile;
class WalkableTile;

void readFloorPlan(std::istream& in, std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>>& floors, std::vector<std::shared_ptr<WalkableTile>>& playerSpawns, std::vector<std::shared_ptr<WalkableTile>>& enemies, std::vector<std::shared_ptr<WalkableTile>>& dragonHoards, std::vector<bool>& filled);

#endif