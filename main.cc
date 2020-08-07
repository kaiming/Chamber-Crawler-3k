#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

#include "tile.h"
#include "factory.h"
#include "walkablefactory.h"
#include "nonwalkablefactory.h"
// add includes


// readFloorPlan helper (PUT IN A SEPARATE FILE LATER) 
void readFloorPlan(std::istream& in, std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>>& floors, std::vector<bool>& filled) {
    std::shared_ptr<Factory> tileType;
    std::string line;
    int floorNum {0}, rowNum {0};
    // count of the number of borders, '|' chars, and '-' chars respectively
    int borderCount {0}, vert {0}, horiz {0};

    while (true) {
        std::getline(in, line);

        // break clause
        if (in.fail()) {
            // if entire file has been read
            if (in.eof()) return;
            
            // else if theres some other failed read
            std::cerr << "error reading in file" << std::endl;
        }

        // case of the start of a new floor
        if (borderCount == 2) {
            ++floorNum;
            borderCount = 0;
            
            // keep discarding spaces between floor layouts
            while (line == "") {
                std::getline(in, line);
            }
        }

        std::istringstream ssl {line};
        int colNum {0};

        // grab each character and create the appropriate Tile
        while (true) {
            char type;
            ssl >> type;

            // break clause
            if (ssl.fail()) {
                // if end of line
                if (ssl.eof()) {
                    if (vert == 2 && horiz == static_cast<int>(line.size() - 2)) {
                        ++borderCount;
                        vert = 0;
                        horiz = 0;
                        break;
                    }
                }

                // else read in fail
                std::cerr << "error reading in file" << std::endl;
            }

            // x is colNum and y is rowNum
            if (type == '|' || type == '-' || type == ' ') {
                switch (type) {
                    case ('|'):
                    {
                        auto temp {std::make_shared<NonWalkableFactory>('|', colNum, rowNum)};
                        tileType = temp;

                        ++vert;
                    }

                    case ('-'):
                    {
                        auto temp {std::make_shared<NonWalkableFactory>('-', colNum, rowNum)};
                        tileType = temp;

                        ++horiz;
                    }

                    case (' '):
                    {
                        auto temp {std::make_shared<NonWalkableFactory>(' ', colNum, rowNum)};
                        tileType = temp;
                    }

                    default:
                        ++colNum;
                }   

            }
        }
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
