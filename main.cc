#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "tile.h"
// add includes


// readFloorPlan helper (PUT IN A SEPARATE FILE LATER) 
void readFloorPlan(std::istream& infile, std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors, std::vector<bool> filled) {
    
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        // get file name
        const std::string fileName {argv[0]};

        std::ifstream infile {fileName};
        std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors;
        std::vector<bool> filled;

        // reads in file and creates the tiles (and maybe the items/characters, excluding player) of each floor
        readFloorPlan(infile, floors, filled);
    }


}