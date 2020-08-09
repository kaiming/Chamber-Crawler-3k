#include "readPlan.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <cmath>
#include <utility>

#include "../Tile/tile.h"
#include "../Tile/walkabletile.h"
#include "../Factory/factory.h"
#include "../Factory/walkablefactory.h"
#include "../Factory/nonwalkablefactory.h"
#include "../Potion/potion.h"
#include "../Potion/rh.h"
#include "../Potion/ba.h"
#include "../Potion/bd.h"
#include "../Potion/ph.h"
#include "../Potion/wa.h"
#include "../Potion/wd.h"
#include "../Gold/gold.h"
#include "../Gold/dragonhoard.h"
#include "../Enemy/human.h"
#include "../Enemy/dwarf.h"
#include "../Enemy/elf.h"
#include "../Enemy/orc.h"
#include "../Enemy/merchant.h"
#include "../Enemy/dragon.h"
#include "../Enemy/halfling.h"

// helper for readFloorPlan
bool isWalkable(char type) {
    return ((type >= '0' && type <= '9') || type == 'P' || type == 'G' || type == '@' || type == 'H' || type == 'W' ||
    type == 'E' || type == 'O' || type == 'M' || type == 'D' || type == 'L' || type == '\\' || type == '.' || type == '+' || type == '#');
}


// readFloorPlan helper (PUT IN A SEPARATE FILE LATER) 
void readFloorPlan(std::istream& in, std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>>& floors, std::vector<std::shared_ptr<WalkableTile>>& playerSpawns, std::vector<std::shared_ptr<WalkableTile>>& enemies, std::vector<std::shared_ptr<WalkableTile>>& dragonHoards, std::vector<bool>& filled) {
    std::shared_ptr<Factory> tileType;
    std::shared_ptr<WalkableFactory> walkable;
    std::shared_ptr<NonWalkableFactory> nonWalkable;
    // keep track of the generated dragonhoard to add dragon after
    std::vector<std::pair<std::pair<int, int>, std::shared_ptr<DragonHoard>>> hoards;
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
            return;
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
                rowNum = 0;

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
                        if (borderCount == 2) isStart = false;
                    }

                    vert = 0;
                    horiz = 0;
                    break;
                }

                // else read in fail
                std::cerr << "error reading in file" << std::endl;
                break;
            }

            // x is colNum and y is rowNum
            // if char is of type nonwalkable tile
            if (type == '|' || type == '-' || type == ' ') {
                tileType = nonWalkable;

                switch (type) {
                    case ('|'):
                        ++vert;
                        break;

                    case ('-'):
                        ++horiz;
                        break;

                    default:
                        break;
                }   

                // make tile
                auto tempTile {tileType->makeTile(type, colNum, rowNum)};
                // add to floor
                floors[floorNum][rowNum].push_back(tempTile);
            } else if (isWalkable(type)) { // else if char is a walkable tile and need to check for pregeneration
                tileType = walkable;

                switch (type) {
                    case ('0'):
                    {
                        // RH potion
                        auto tempPotion {std::make_shared<RH>()};
                        type = 'P';
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, nullptr, tempPotion, {}, false)};
                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }
                    
                    case ('1'):
                    {
                        // BA potion
                        auto tempPotion {std::make_shared<BA>()};
                        type = 'P';
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, nullptr, tempPotion, {}, false)};
                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('2'):
                    {
                        // BD potion
                        auto tempPotion {std::make_shared<BD>()};
                        type = 'P';
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, nullptr, tempPotion, {}, false)};
                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('3'):
                    {
                        // PH potion
                        auto tempPotion {std::make_shared<PH>()};
                        type = 'P';
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, nullptr, tempPotion, {}, false)};
                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('4'):
                    {
                        // WA potion
                        auto tempPotion {std::make_shared<WA>()};
                        type = 'P';
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, nullptr, tempPotion, {}, false)};
                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('5'):
                    {
                        // WD potion
                        auto tempPotion {std::make_shared<WD>()};
                        type = 'P';
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, nullptr, tempPotion, {}, false)};
                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('6'):
                    {
                        // normal gold pile
                        auto tempGold {std::make_shared<Gold>("normal pile", 2)};
                        type = 'G';
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, nullptr, nullptr, {tempGold}, false)};
                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('7'):
                    {
                        // small gold pile
                        auto tempGold {std::make_shared<Gold>("small pile", 1)};
                        type = 'G';
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, nullptr, nullptr, {tempGold}, false)};
                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('8'):
                    {
                        // merchant hoard
                        auto tempGold {std::make_shared<Gold>("merchant hoard", 4)};
                        type = 'G';
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, nullptr, nullptr, {tempGold}, false)};
                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('9'):
                    {
                        // dragon hoard
                        auto tempGold {std::make_shared<DragonHoard>()};
                        hoards.push_back(std::pair<std::pair<int, int>, std::shared_ptr<DragonHoard>>{std::pair<int, int> {colNum, rowNum}, tempGold});
                        type = 'G';
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, nullptr, nullptr, {tempGold}, false)};

                        dragonHoards.push_back(std::static_pointer_cast<WalkableTile>(tempTile));

                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('D'):
                    {
                        // dragon (must check which of the list of dragon hoards this dragon is guarding, if there are non then produce error saying improper generation)
                        bool set {false};
                        auto tempDrag {std::make_shared<Dragon>()};
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, tempDrag)};
                        auto dCoord {std::pair<int, int> {colNum, rowNum}};

                        for (auto& n : hoards) {
                            auto gCoord {n.first};

                            // calc distance from drag 
                            double distance = std::floor(std::sqrt(std::pow((dCoord.first - gCoord.first), 2) + std::pow((dCoord.second - gCoord.second), 2)));
                            // if the hoard is within a distance of 1 and there isn't already a dragon guarding it
                            if (distance == 1 && n.second->getDragonTile() == nullptr) {
                                n.second->setDragonTile(std::static_pointer_cast<WalkableTile>(tempTile));
                                set = true;
                            }
                        }

                        if (!set) { // NOTE: CAN CHANGE THE BEHAVIOUR IF THE CASE WHERE A PREGENERATED DRAG DOESNT GUARD A HOARD 
                            std::cerr << "Error: Dragon does not guard a dragon hoard, despawning ..." << std::endl;
                            break;
                        }

                        enemies.push_back(std::static_pointer_cast<WalkableTile>(tempTile));

                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('H'):
                    {
                        // Human
                        auto tempHuman {std::make_shared<Human>()};
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, tempHuman)};

                        enemies.push_back(std::static_pointer_cast<WalkableTile>(tempTile));                        

                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('W'):
                    {
                        // Dwarf
                        auto tempHuman {std::make_shared<Dwarf>()};
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, tempHuman)};

                        enemies.push_back(std::static_pointer_cast<WalkableTile>(tempTile));

                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('E'):
                    {
                        // Elf
                        auto tempHuman {std::make_shared<Elf>()};
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, tempHuman)};

                        enemies.push_back(std::static_pointer_cast<WalkableTile>(tempTile));

                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('O'):
                    {
                        // Orc
                        auto tempHuman {std::make_shared<Orc>()};
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, tempHuman)};

                        enemies.push_back(std::static_pointer_cast<WalkableTile>(tempTile));

                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }
                    
                    case ('M'):
                    {
                        // Merchant
                        auto tempHuman {std::make_shared<Merchant>()};
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, tempHuman)};

                        enemies.push_back(std::static_pointer_cast<WalkableTile>(tempTile));

                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('L'):
                    {
                        // Halfling
                        auto tempHuman {std::make_shared<Halfling>()};
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, tempHuman)};

                        enemies.push_back(std::static_pointer_cast<WalkableTile>(tempTile));

                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    case ('@'):
                    {
                        // player spawn
                        auto tempPlayer {std::make_shared<Player>()}; // NOTE: GAVE PLAYER A DEFAULT CONSTRUCTOR INITIALIZES FIELDS TO 0 SINCE THE BOARD CONSTRUCTOR WILL REASSIGN THE OCCUPANT FIELD FOR PLAYER
                        std::shared_ptr<Character> tempCharacter;
                        tempCharacter = tempPlayer;
                        auto tempGold = std::vector<std::shared_ptr<Gold>> {};
                        auto tempPotion = std::make_shared<Potion>(nullptr);
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, tempPlayer, tempPotion, tempGold, false)};
                        
                        // if the current floor has more than 1 @ symbol or none at all ------------------------------
                        if (floorNum != static_cast<int>(playerSpawns.size())) {
                            std::cerr << "Invalid number of players being spawned! Despawning ..." << std::endl;
                            return; //NOTE: RETURN OR BREAK?
                        }

                        playerSpawns.push_back(std::static_pointer_cast<WalkableTile>(tempTile));

                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                    }

                    case ('\\'):
                    {
                        // stairs
                        auto tempTile {tileType->makeTile(type, colNum, rowNum, nullptr, nullptr, {}, true)};
                        floors[floorNum][rowNum].push_back(tempTile);
                        if (!filled[floorNum]) filled[floorNum] = true;
                        break;
                    }

                    default:
                    {
                        // either ., +, or #
                        auto tempTile {tileType->makeTile(type, colNum, rowNum)};
                        floors[floorNum][rowNum].push_back(tempTile);
                    }
                }

        
            } else { // unrecognized  symbol
                std::cerr << "Error: Unrecogonized symbol" << std::endl;
            }

            ++colNum;
        }

        ++rowNum;
    }
}
