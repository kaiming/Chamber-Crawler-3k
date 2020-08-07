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
    int floorNum {-1}, rowNum {0};
    // count of the number of borders, '|' chars, and '-' chars respectively
    int borderCount {0}, vert {0}, horiz {0};
    bool isStart {false};

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
        if (!isStart) {
            bool valid {true};
            borderCount = 0;
            
            // check if next line is a valid start of a floor
            for (int counter {0}; counter < static_cast<int>(line.size()); ++counter) {
                // MIN REQUIREMENT OF A FLOOR DIMENSION IS WIDTH THREE?
                if (static_cast<int>(line.size()) < 3) {
                    valid = false;
                    break;
                }

                // if the first and last chars are not '|'
                if ((counter == 0 || counter == static_cast<int>(line.size()) - 1) && line[counter] != '|') {
                    valid = false;
                    break;
                } 

                // if the chars inbetween first and last are not '-'
                if ((counter > 0 || counter < static_cast<int>(line.size()) - 1) && line[counter] != '-') {
                    valid = false;
                    break;
                }
            }

            // if line is a valid start to a floor then continueously read each line till the end of next floor
            if (valid) {
                isStart = true;

                // push in a new floor grid
                std::vector<std::vector<std::shared_ptr<Tile>>> grid;
                floors.push_back(grid);
                ++floorNum;
            } else {
                // if not a valid line then ignore and continue reading the next line
                continue;
            }
        }

        std::istringstream ssl {line};
        char type;
        int colNum {0};

        // push in a new row
        std::vector<std::shared_ptr<Tile>> row;
        floors[floorNum].push_back(row);

        // grab each character and create the appropriate Tile
        while (true) {
            ssl >> type;

            // break clause
            if (ssl.fail()) {
                // if end of line
                if (ssl.eof()) {
                    if (vert == 2 && horiz == static_cast<int>(line.size() - 2)) {
                        ++borderCount;
                        vert = 0;
                        horiz = 0;
                        if (borderCount == 2) isStart = false;
                        break;
                    }
                }

                // else read in fail
                std::cerr << "error reading in file" << std::endl;
            }

            // x is colNum and y is rowNum
            // if char is of type nonwalkable tile
            if (type == '|' || type == '-' || type == ' ') {
                switch (type) {
                    case ('|'):
                    {
                        auto temp {std::make_shared<NonWalkableFactory>('|', colNum, rowNum)};
                        tileType = temp;

                        ++vert;
                        break;
                    }

                    case ('-'):
                    {
                        auto temp {std::make_shared<NonWalkableFactory>()};
                        tileType = temp;

                        ++horiz;
                        break;
                    }

                    case (' '):
                    {
                        auto temp {std::make_shared<NonWalkableFactory>()};
                        tileType = temp;
                        break;
                    }

                    default:
                        break;
                }   

                // make tile
                auto tempTile {tileType->makeTile(type, colNum, rowNum)};
                // add to floor
                floors[floorNum][rowNum].push_back(tempTile);
            } else { // else char is a walkable tile and need to check for pregeneration
                switch (type) {

                }

        
            }

            ++colNum;
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
