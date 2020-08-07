#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "tile.h"
#include "factory.h"
// add includes


// readFloorPlan helper (PUT IN A SEPARATE FILE LATER) 
void readFloorPlan(std::istream& in, std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors, std::vector<bool> filled) {
    std::shared_ptr<Factory>;
    char type;
    while (in >> type) {
        
    }
}

int main(int argc, char* argv[]) {
    std::ifstream infile;
    infile.exceptions(std::ifstream::failbit);
    std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors;
    std::vector<bool> filled;

    // if no file is passed in command line
    if (argc == 0) {
        infile.open("default.txt");

        // reads in default file with an empty floor plan
        readFloorPlan(infile, floors, filled);
    } else { // if there are at least one command line argument (only take the first one and try to open it as a file)
        try {
            // get file name
            const std::string fileName {argv[0]};

            std::ifstream infile {fileName};

            // reads in file and creates the tiles (and maybe the items/characters, excluding player) of each floor
            readFloorPlan(infile, floors, filled);
        } catch (std::ios_base::failure& fail) {
            std::cerr << "Unable to open file" << std::endl;
            infile.close();
            return;
        }
    } 

    // close file
    infile.close();



}
