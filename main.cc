#include <iostream>
#include "readPlan.h"
#include "tile.h"
#include "walkabletile.h"
// add includes

int main(int argc, char* argv[]) {
    std::ifstream infile;
    infile.exceptions(std::ifstream::failbit);
    std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> floors;
    std::vector<std::shared_ptr<WalkableTile>> playerSpawns;
    std::vector<std::shared_ptr<WalkableTile>> enemies;
    std::vector<std::shared_ptr<WalkableTile>> dragonHoards;
    std::vector<bool> filled;

    // if no file is passed in command line
    if (argc == 0) {
        infile.open("default.txt");

        // reads in default file with an empty floor plan
        readFloorPlan(infile, floors, playerSpawns, enemies, dragonHoards, filled);
    } else { // if there are at least one command line argument (only take the first one and try to open it as a file)
        try {
            // get file name
            const std::string fileName {argv[0]};

            std::ifstream infile {fileName};

            // reads in file and creates the tiles (and maybe the items/characters, excluding player) of each floor
            readFloorPlan(infile, floors, playerSpawns, enemies, dragonHoards, filled);
        } catch (std::ios_base::failure& fail) {
            std::cerr << "Unable to open file" << std::endl;
            infile.close();
            return;
        }
    } 

    // close file
    infile.close();

    // Ask player to enter one of the specified races or quit
    std::string race {"s"};

    std::cout << "Welcome to ChamberCrawler3000, prepare to enter the unknown!" << std::endl;
    std::cout << "Choose your character: Shade 's' (default), 
    std::cout << "Choose your player: "

    std::cin >> cmd;

}
