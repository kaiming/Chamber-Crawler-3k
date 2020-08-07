#ifndef __READPLAN_H__
#define __READPLAN_H__
#include <fstream>
#include <vector>
#include <memory>

class Tile;

void readFloorPlan(std::istream& in, std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>>& floors, std::vector<bool>& filled);

#endif