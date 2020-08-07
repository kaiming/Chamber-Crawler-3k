#include <iostream>
#include "readPlan.h"
#include "tile.h"
#include "walkabletile.h"
#include "board.h"
#include "textdisplay.h"
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

    Board b;
    TextDisplay td;

    // Ask player to enter one of the specified races or quit
    std::string race;

    std::cout << "Welcome to ChamberCrawler3000, prepare to enter the unknown!" << std::endl;
    std::cout << "Choose your character: Shade 's' (default), Drow 'd', Vampire 'v', Goblin 'g', Troll 't'" << std::endl;
    std::cout << "Enter here: ";

    std::cin >> race;
    
    while (race != "" || race != "s" || race != "d" || race != "v" || race != "g" || race != "t") {
        std::cerr << "Invalid race" << std::endl;
        std::cout << "Enter here: ";

        if (std::cin.fail()) {
            if (std::cin.eof()) return;

            std::cin.clear();
            std::cin.ignore();
        }

        std::cin >> race;
    }

    if (race == "q") {
        return; // NOTE: MAYBE HAVEIT SO A NEW GAME STARTS??
    } else if (race == "") { // default race
        b = Board {floors, filled, playerSpawns, enemies, dragonHoards, "s"};
    } else {
        b = Board {floors, filled, playerSpawns, enemies, dragonHoards, race};
    }

    td.drawFloor(std::cout, b, "The adventure begins");

    std::string cmd;

    while (true) {
        std::cout << "Enter command: ";
        std::cin >> cmd;

        // break clause
        if (std::cin.fail()) {
            if (std::cin.eof()) return;

            // NOTE: ELSE DO SMTH
        }


    }

}
